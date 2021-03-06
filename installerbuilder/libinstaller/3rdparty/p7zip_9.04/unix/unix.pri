DEFINES += FILE_OFFSET_BITS=64 _LARGEFILE_SOURCE NDEBUG _REENTRANT COMPRESS_MT COMPRESS_BZIP2_MT COMPRESS_MF_MT BREAK_HANDLER BENCH_MT

unix:DEFINES += ENV_UNIX 
#macx:DEFINES += _LZMA_UINT32_IS_ULONG
win32:DEFINES += _UNICODE _CRT_SECURE_NO_WARNINGS

INCLUDEPATH += $$P7ZIP_BASE/ $$P7ZIP_BASE/unix/CPP $$P7ZIP_BASE/unix/CPP/myWindows 
unix:INCLUDEPATH += $$P7ZIP_BASE/unix/CPP/include_windows

SOURCES +=  $$P7ZIP_BASE/lib7z_facade.cpp
HEADERS +=  $$P7ZIP_BASE/lib7z_facade.h

unix:SOURCES += $$P7ZIP_BASE/unix/CPP/myWindows/myGetTickCount.cpp \
                $$P7ZIP_BASE/unix/CPP/myWindows/wine_date_and_time.cpp \
                $$P7ZIP_BASE/unix/CPP/myWindows/myAddExeFlag.cpp \ 
                $$P7ZIP_BASE/unix/CPP/myWindows/mySplitCommandLine.cpp \

win32:SOURCES += $$P7ZIP_BASE/unix/C/Alloc.c

win32:LIBS += -loleaut32 -luser32

SOURCES += \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Console/ConsoleClose.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Console/ExtractCallbackConsole.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Console/List.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Console/OpenCallbackConsole.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Console/PercentPrinter.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Console/UpdateCallbackConsole.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Console/UserInputUtils.cpp \
$$P7ZIP_BASE/unix/CPP/Common/CommandLineParser.cpp \
$$P7ZIP_BASE/unix/CPP/Common/CRC.cpp \
$$P7ZIP_BASE/unix/CPP/Common/IntToString.cpp \
$$P7ZIP_BASE/unix/CPP/Common/ListFileUtils.cpp \
$$P7ZIP_BASE/unix/CPP/Common/StdInStream.cpp \
$$P7ZIP_BASE/unix/CPP/Common/StdOutStream.cpp \
$$P7ZIP_BASE/unix/CPP/Common/MyString.cpp \
$$P7ZIP_BASE/unix/CPP/Common/StringToInt.cpp \
$$P7ZIP_BASE/unix/CPP/Common/UTFConvert.cpp \
$$P7ZIP_BASE/unix/CPP/Common/StringConvert.cpp \
$$P7ZIP_BASE/unix/CPP/Common/MyWindows.cpp \
$$P7ZIP_BASE/unix/CPP/Common/MyVector.cpp \
$$P7ZIP_BASE/unix/CPP/Common/Wildcard.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/Error.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/FileDir.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/FileFind.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/FileIO.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/FileName.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/PropVariant.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/PropVariantConversions.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/Synchronization.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/System.cpp \
$$P7ZIP_BASE/unix/CPP/Windows/Time.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/CreateCoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/CWrappers.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/FilePathAutoRename.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/FileStreams.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/FilterCoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/InBuffer.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/InOutTempBuffer.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/LimitedStreams.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/LockedStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/MemBlocks.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/MethodId.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/MethodProps.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/OffsetStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/OutBuffer.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/OutMemStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/ProgressMt.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/ProgressUtils.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/StreamBinder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/StreamObjects.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/StreamUtils.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Common/VirtThread.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/ArchiveCommandLine.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/ArchiveExtractCallback.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/ArchiveOpenCallback.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/DefaultName.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/EnumDirItems.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/Extract.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/ExtractingFilePath.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/LoadCodecs.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/OpenArchive.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/PropIDUtils.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/SetProperties.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/SortUtils.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/TempFiles.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/Update.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/UpdateAction.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/UpdateCallback.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/UpdatePair.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/UI/Common/UpdateProduce.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Bz2Handler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/GzHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/LzmaHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/SplitHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/XzHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/ZHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/CoderMixer2.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/CoderMixer2MT.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/CrossThreadProgress.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/DummyOutStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/FindSignature.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/HandlerOut.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/InStreamWithCRC.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/ItemNameUtils.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/MultiStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/OutStreamWithCRC.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Common/ParseProperties.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zCompressionMode.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zDecode.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zEncode.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zExtract.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zFolderInStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zFolderOutStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zHandlerOut.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zHeader.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zIn.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zOut.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zProperties.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zSpecStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zUpdate.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Cab/CabBlockInStream.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Cab/CabHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Cab/CabHeader.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Cab/CabIn.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Tar/TarHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Tar/TarHandlerOut.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Tar/TarHeader.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Tar/TarIn.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Tar/TarOut.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Tar/TarUpdate.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipAddCommon.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipHandler.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipHandlerOut.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipHeader.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipIn.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipItem.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipOut.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipUpdate.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BcjCoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/Bcj2Coder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BitlDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BranchCoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BranchMisc.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/ByteSwap.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BZip2Crc.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BZip2Decoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BZip2Encoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/CopyCoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/DeflateDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/DeflateEncoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/DeltaFilter.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/ImplodeDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/ImplodeHuffmanDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/Lzma2Decoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/Lzma2Encoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/LzmaDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/LzmaEncoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/LzOutWindow.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/Lzx86Converter.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/LzxDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/PpmdDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/PpmdEncoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/QuantumDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/ShrinkDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/ZDecoder.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/LZMA_Alone/LzmaBench.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/LZMA_Alone/LzmaBenchCon.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/7zAes.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/HmacSha1.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/MyAes.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/Pbkdf2HmacSha1.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/RandGen.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/Sha1.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/WzAes.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/ZipCrypto.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/ZipStrong.cpp \
$$P7ZIP_BASE/unix/C/7zStream.c \
$$P7ZIP_BASE/unix/C/Aes.c \
$$P7ZIP_BASE/unix/C/Bra.c \
$$P7ZIP_BASE/unix/C/Bra86.c \
$$P7ZIP_BASE/unix/C/BraIA64.c \
$$P7ZIP_BASE/unix/C/BwtSort.c \
$$P7ZIP_BASE/unix/C/Delta.c \
$$P7ZIP_BASE/unix/C/HuffEnc.c \
$$P7ZIP_BASE/unix/C/LzFind.c \
$$P7ZIP_BASE/unix/C/LzFindMt.c \
$$P7ZIP_BASE/unix/C/Lzma2Dec.c \
$$P7ZIP_BASE/unix/C/Lzma2Enc.c \
$$P7ZIP_BASE/unix/C/LzmaDec.c \
$$P7ZIP_BASE/unix/C/LzmaEnc.c \
$$P7ZIP_BASE/unix/C/MtCoder.c \
$$P7ZIP_BASE/unix/C/Sha256.c \
$$P7ZIP_BASE/unix/C/Sort.c \
$$P7ZIP_BASE/unix/C/Threads.c \
$$P7ZIP_BASE/unix/C/Xz.c \
$$P7ZIP_BASE/unix/C/XzCrc64.c \
$$P7ZIP_BASE/unix/C/XzDec.c \
$$P7ZIP_BASE/unix/C/XzEnc.c \
$$P7ZIP_BASE/unix/C/XzIn.c \
$$P7ZIP_BASE/unix/C/7zCrc.c \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/7z/7zRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Cab/CabRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Tar/TarRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Archive/Zip/ZipRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/Bcj2Register.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BcjRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BranchRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/BZip2Register.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/CopyRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/Deflate64Register.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/DeflateRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/Lzma2Register.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/LzmaRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Compress/PpmdRegister.cpp \
$$P7ZIP_BASE/unix/CPP/7zip/Crypto/7zAesRegister.cpp
