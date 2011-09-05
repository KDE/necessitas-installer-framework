#if defined(WIN32) && defined(__GNUC__)
#define _WIN32_WINNT 0x0500
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#if defined (__NetBSD__) || defined(__OpenBSD__) || defined (__FreeBSD__) || defined (__FreeBSD_kernel__) || defined (__APPLE__)
#include <sys/param.h>
#include <sys/sysctl.h>
#elif defined(__linux__) || defined(__CYGWIN__) || defined(sun) || defined(__NETWARE__)
#include <unistd.h>
#elif defined(hpux) || defined(__hpux)
#include <sys/param.h>
#include <sys/pstat.h>
#endif

#if defined(__NETWARE__)
#include <sys/sysinfo.h>
#endif

#if defined(ENV_BEOS)
#include <be/kernel/OS.h>
#endif

#include "Common/Types.h"

namespace NWindows
{
	namespace NSystem
	{
		/************************ GetNumberOfProcessors ************************/

		#if defined (__NetBSD__) || defined(__OpenBSD__)
		UInt32 GetNumberOfProcessors() {
			int mib[2], value;
		  	int nbcpu = 1;

		  	mib[0] = CTL_HW;
		  	mib[1] = HW_NCPU;
		  	size_t len = sizeof(size_t);
		  	if (sysctl(mib, 2, &value, &len, NULL, 0) >= 0)
		  		if (value > nbcpu)
					nbcpu = value;
			return nbcpu;
		}
		#elif defined (__FreeBSD__) || defined (__FreeBSD_kernel__)
		UInt32 GetNumberOfProcessors() {
		  	int nbcpu = 1;
			size_t value;
			size_t len = sizeof(value);
			if (sysctlbyname("hw.ncpu", &value, &len, NULL, 0) == 0)
				nbcpu = value;
			return nbcpu;
		}
		#elif defined (__APPLE__)
		UInt32 GetNumberOfProcessors() {
		  	int nbcpu = 1,value;
			size_t valSize = sizeof(value);
			if (sysctlbyname ("hw.ncpu", &value, &valSize, NULL, 0) == 0)
				nbcpu = value;
			return nbcpu;
		}

		#elif defined(__linux__) || defined(__CYGWIN__) || defined(sun)
		UInt32 GetNumberOfProcessors() {
		  	int nbcpu = sysconf (_SC_NPROCESSORS_CONF);
			if (nbcpu < 1) nbcpu = 1;
			return nbcpu;
		}
		#elif defined(hpux) || defined(__hpux)
		UInt32 GetNumberOfProcessors() {
			struct pst_dynamic psd;
			if (pstat_getdynamic(&psd, sizeof(psd), (size_t)1, 0) != -1)
				return (UInt32)psd.psd_proc_cnt;
			return 1;
		}
		#elif defined(__NETWARE__)
		UInt32 GetNumberOfProcessors() {
			// int nbcpu = get_nprocs_conf();
			int nbcpu = get_nprocs();
			if (nbcpu < 1) nbcpu = 1;
			return nbcpu;
		}
		#elif defined(ENV_BEOS)
		UInt32 GetNumberOfProcessors() {
			system_info info;
			get_system_info(&info);
			int nbcpu = info.cpu_count;
			if (nbcpu < 1) nbcpu = 1;
			return nbcpu;
		}
        #elif defined(WIN32)
        UInt32 GetNumberOfProcessors()
        {
            SYSTEM_INFO systemInfo;
            GetSystemInfo( &systemInfo );
            return (UInt32)systemInfo.dwNumberOfProcessors;
        }
		#else
		#warning Generic GetNumberOfProcessors
		UInt32 GetNumberOfProcessors() {
			return 1;
		}
		#endif

		/************************ GetRamSize ************************/
	UInt64 GetRamSize() {
			UInt64 ullTotalPhys = 128 * 1024 * 1024; // default : 128MB

#ifdef linux
	 		FILE * f = fopen( "/proc/meminfo", "r" );
	 		if (f)
	 		{
				char buffer[256];
				unsigned long total;

				ullTotalPhys = 0;

		  		while (fgets( buffer, sizeof(buffer), f ))
		  		{
		 		/* old style /proc/meminfo ... */
					if (sscanf( buffer, "Mem: %lu", &total))
					{
					 	ullTotalPhys += total;
					}

					/* new style /proc/meminfo ... */
					if (sscanf(buffer, "MemTotal: %lu", &total))
					 	ullTotalPhys = ((UInt64)total)*1024;
		  		}
		  		fclose( f );
			}
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__APPLE__)
#ifdef HW_MEMSIZE
			uint64_t val = 0; // support 2Gb+ RAM
			int mib[2] = { CTL_HW, HW_MEMSIZE };
#else // HW_MEMSIZE
			unsigned int val = 0; // For old system
			int mib[2] = { CTL_HW, HW_PHYSMEM };
#endif // HW_MEMSIZE
			size_t size_sys = sizeof(val);

			sysctl(mib, 2, &val, &size_sys, NULL, 0);
			if (val) ullTotalPhys = val;
#elif defined(__CYGWIN__)
			unsigned long pagesize=4096; // FIXME - sysconf(_SC_PAGESIZE) returns 65536 !?
					// see http://readlist.com/lists/cygwin.com/cygwin/0/3313.html
			unsigned long maxpages=sysconf(_SC_PHYS_PAGES);
			ullTotalPhys = ((UInt64)pagesize)*maxpages;
#elif defined ( sun ) || defined(__NETWARE__)
			unsigned long pagesize=sysconf(_SC_PAGESIZE);
			unsigned long maxpages=sysconf(_SC_PHYS_PAGES);
			ullTotalPhys = ((UInt64)pagesize)*maxpages;
#elif defined(hpux) || defined(__hpux)
			struct pst_static pst;
			union pstun pu;
						
			pu.pst_static = &pst;
			if ( pstat( PSTAT_STATIC, pu, (size_t)sizeof(pst), (size_t)0, 0 ) != -1 ) {
				ullTotalPhys = ((UInt64)pst.physical_memory)*pst.page_size;
			}
#elif defined(ENV_BEOS)
			system_info info;
			get_system_info(&info);
			ullTotalPhys = info.max_pages;
			ullTotalPhys *= 4096;
#elif defined(WIN32)
             MEMORYSTATUSEX stat;
             stat.dwLength = sizeof(stat);
             GlobalMemoryStatusEx(&stat);
             return stat.ullTotalPhys;
#else
#warning Generic GetRamSize
#endif
			return ullTotalPhys;
		}

	}
}

