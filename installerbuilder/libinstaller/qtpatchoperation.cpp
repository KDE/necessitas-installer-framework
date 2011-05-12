/**************************************************************************
**
** This file is part of Qt SDK**
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).*
**
** Contact:  Nokia Corporation qt-info@nokia.com**
**
** No Commercial Usage
**
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception version
** 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you are unsure which license is appropriate for your use, please contact
** (qt-info@nokia.com).
**
**************************************************************************/
#include "qtpatchoperation.h"
#include "qtpatch.h"
#ifdef Q_OS_MAC
#include "macrelocateqt.h"
#endif

#include "common/utils.h"
#include <qinstaller.h>

#include <QMap>
#include <QSet>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDirIterator>
#include <QDebug>



using namespace QInstaller;

//"anonymous" namespace to make clear that this is only for inside use
namespace {
    QMap<QByteArray, QByteArray> generatePatchValueMap( const QByteArray & newQtPath,
                                                        const QHash<QString, QByteArray> & qmakeValueHash )
    {
        QMap<QByteArray, QByteArray> replaceMap; //first == searchstring: second == replace string
        char nativeSeperator = QDir::separator().toAscii();
        QByteArray oldValue;

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_PREFIX") );
        replaceMap.insert( QByteArray("qt_prfxpath=%1").replace( "%1", oldValue ),
                           QByteArray("qt_prfxpath=%1/").replace( "%1/", newQtPath ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_DOCS") );
        replaceMap.insert( QByteArray("qt_docspath=%1").replace( "%1", oldValue ),
                           QByteArray("qt_docspath=%1/doc").replace( "%1/", newQtPath + nativeSeperator ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_HEADERS") );
        replaceMap.insert( QByteArray("qt_hdrspath=%1").replace( "%1", oldValue ),
                           QByteArray("qt_hdrspath=%1/include").replace( "%1/", newQtPath + nativeSeperator ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_LIBS") );
        replaceMap.insert( QByteArray("qt_libspath=%1").replace( "%1", oldValue ),
                           QByteArray("qt_libspath=%1/lib").replace( "%1/", newQtPath + nativeSeperator ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_BINS") );
        replaceMap.insert( QByteArray("qt_binspath=%1").replace( "%1", oldValue ),
                           QByteArray("qt_binspath=%1/bin").replace( "%1/", newQtPath + nativeSeperator ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_PLUGINS") );
        replaceMap.insert( QByteArray("qt_plugpath=%1").replace( "%1", oldValue ),
                           QByteArray("qt_plugpath=%1/plugins").replace( "%1/", newQtPath + nativeSeperator ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_IMPORTS") );
        replaceMap.insert( QByteArray("qt_impspath=%1").replace( "%1", oldValue ),
                           QByteArray("qt_impspath=%1/imports").replace( "%1/", newQtPath + nativeSeperator ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_DATA") );
        replaceMap.insert(  QByteArray("qt_datapath=%1").replace( "%1", oldValue ),
                            QByteArray("qt_datapath=%1/").replace( "%1/", newQtPath + nativeSeperator ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_TRANSLATIONS") );
        replaceMap.insert(  QByteArray("qt_trnspath=%1").replace( "%1", oldValue ),
                            QByteArray("qt_trnspath=%1/translations").replace( "%1/", newQtPath + nativeSeperator ) );

// This must not be patched. Commenting out to fix QTSDK-429
//        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_CONFIGURATION"));
//        replaceMap.insert(  QByteArray("qt_stngpath=%1").replace( "%1", oldValue),
//                            QByteArray("qt_stngpath=%1").replace( "%1", newQtPath));

        //examples and demoes can patched outside separately,
        //but for cosmetic reasons - if the qt version gets no examples later.
        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_EXAMPLES") );
        replaceMap.insert(  QByteArray("qt_xmplpath=%1").replace( "%1", oldValue ),
                            QByteArray("qt_xmplpath=%1/examples").replace( "%1/", newQtPath + nativeSeperator ) );

        oldValue = qmakeValueHash.value( QLatin1String("QT_INSTALL_DEMOS") );
        replaceMap.insert(  QByteArray("qt_demopath=%1").replace( "%1", oldValue ),
                            QByteArray("qt_demopath=%1/demos").replace( "%1/", newQtPath + nativeSeperator ) );

        return replaceMap;
    }

}//"anonymous" namespace

QtPatchOperation::QtPatchOperation()
{
    setName(QLatin1String("QtPatch"));
}

QtPatchOperation::~QtPatchOperation()
{
}

void QtPatchOperation::backup()
{
}

bool QtPatchOperation::performOperation()
{
    // Arguments:
    // 1. new/target qtpath
    // 2. old qtpath (optional)

    if( arguments().count() < 1 ) {
        setError( InvalidArguments );
        setErrorString( tr("Invalid arguments in %0: %1 arguments given, at least 1 expected.")
                        .arg(name()).arg( arguments().count() ) );
        return false;
    }

    const QString newQtPathStr = QDir::toNativeSeparators( arguments().at(0) );
    const QByteArray newQtPath = newQtPathStr.toUtf8();

    QByteArray oldQtPath;
    QString prefix = QFile::decodeName(newQtPath);

    if (! prefix.endsWith(QLatin1Char('/')) )
        prefix += QLatin1Char('/');

    if( arguments().count()==1)
    {
        QString qmakePath = QString::fromUtf8(newQtPath) + QLatin1String("/bin/qmake");
    #ifdef Q_OS_WIN
        qmakePath = qmakePath + QLatin1String(".exe");
    #endif

        if (!QFile::exists(qmakePath))
        {
            setError( UserDefinedError );
            setErrorString( tr("QMake from the current Qt version \n(%1)"  \
                               "is not existing. Please make a bugreport with this dialog at http://bugreports.qt.nokia.com.\n" \
                               ).arg(QDir::toNativeSeparators(qmakePath)));
            return false;
        }

        QByteArray qmakeOutput;
        QHash<QString, QByteArray> qmakeValueHash = QtPatch::qmakeValues(qmakePath, &qmakeOutput);

        if (qmakeValueHash.isEmpty())
        {
            setError( UserDefinedError );
            setErrorString( tr("The output of \n%1 -query\n"  \
                               "is not parseable. Please make a bugreport with this dialog http://bugreports.qt.nokia.com.\n" \
                               "output: \"%2\"").arg(QDir::toNativeSeparators(qmakePath), QString::fromUtf8(qmakeOutput)));
            return false;
        }

        oldQtPath = qmakeValueHash.value( QLatin1String("QT_INSTALL_PREFIX") );
        if (oldQtPath.isEmpty())
        {
            setError( UserDefinedError );
            setErrorString( tr("The installer was not able to get the unpatched path from \n%1.(maybe it is broken or removed)\n"  \
                               "It tried to patch the Qt binaries, but all other files in Qt are unpatched.\n" \
                               "This could result in a broken Qt version.\n" \
                               "Sometimes it helps to restart the installer with a switched off antivirus software."
                               ).arg(QDir::toNativeSeparators(qmakePath)));
            return false;
        }

        //maybe we don't need this, but I 255 should be a rational limit
        if (255 < newQtPath.size()) {
            setError( UserDefinedError );
            setErrorString( tr("Qt patch error: new Qt dir(%1)\n" \
                               "needs to be less than 255 characters.").arg(newQtPathStr) );
            return false;
        }

        QStringList filesToPatch;
        filesToPatch<<QLatin1String("bin/qmake")<<QLatin1String("bin/lrelease")
    #ifdef Q_OS_WIN
           <<QLatin1String(".exe");
    #endif
        ;

    //BEGIN - patch binary files
        QMap<QByteArray, QByteArray> patchValueMap = generatePatchValueMap(newQtPath, qmakeValueHash);

        foreach (QString fileName, filesToPatch) {
            fileName.prepend(prefix);
            QFile file(fileName);

            //without a file we can't do anything
            if (!file.exists()) {
                continue;
            }

            if (!QtPatch::openFileForPatching(&file)) {
                setError( UserDefinedError );
                setErrorString( tr("Qt patch error: Can not open %1(%2).").arg(file.fileName()).arg(file.errorString()) );
                return false;
            }

            QMapIterator<QByteArray, QByteArray> it(patchValueMap);
            while(it.hasNext()) {
                it.next();
                bool isPatched = QtPatch::patchBinaryFile(&file, it.key(), it.value());
                if (!isPatched) {
                    QInstaller::verbose() << "qpatch: warning: file '" << qPrintable(fileName) << "' could not patched" << std::endl;
                }
            }
        } //foreach (QString fileName, filesToPatch)
    //END - patch binary files
    }
    else
        oldQtPath = arguments().at(1).toUtf8();

//BEGIN - patch text files
    QByteArray newQtPathWithNormalSlashes = QDir::fromNativeSeparators(newQtPathStr).toUtf8();

    QHash<QByteArray, QByteArray> searchReplacePairs;
    searchReplacePairs.insert(oldQtPath, newQtPathWithNormalSlashes);
    searchReplacePairs.insert(QByteArray(oldQtPath).replace("/", "\\"), newQtPathWithNormalSlashes);
    searchReplacePairs.insert(QByteArray(oldQtPath).replace("\\", "/"), newQtPathWithNormalSlashes);

#ifdef Q_OS_WIN
    QByteArray newQtPathWithDoubleBackSlashes = QByteArray(newQtPathWithNormalSlashes).replace("/", "\\\\");
    searchReplacePairs.insert(QByteArray(oldQtPath).replace("/", "\\\\"), newQtPathWithDoubleBackSlashes);
    searchReplacePairs.insert(QByteArray(oldQtPath).replace("\\", "\\\\"), newQtPathWithDoubleBackSlashes);

    //this is checking for a possible drive letter, which could be upper or lower
    if (oldQtPath.mid(1,1) == ":")
    {
        QHash<QByteArray, QByteArray> tempSearchReplacePairs;
        QHashIterator<QByteArray, QByteArray> it(searchReplacePairs);
        QByteArray driveLetter = oldQtPath.left(1);
        while(it.hasNext()) {
            it.next();
            QByteArray currentPossibleSearchByteArrayWithoutDriveLetter = QByteArray(it.key()).remove(0, 1);
            tempSearchReplacePairs.insert(driveLetter.toLower() + currentPossibleSearchByteArrayWithoutDriveLetter, it.value());
            tempSearchReplacePairs.insert(driveLetter.toUpper() + currentPossibleSearchByteArrayWithoutDriveLetter, it.value());
        }
        searchReplacePairs = tempSearchReplacePairs;
    }
#endif
    QDirIterator textFilesIterator( prefix, QStringList()<<QLatin1String("*.pc")<<QLatin1String("*.la")<<QLatin1String("*.prl")<<QLatin1String("*.prf"), QDir::Files, QDirIterator::Subdirectories );
    QString fileName;
    while(textFilesIterator.hasNext()) {
        fileName=textFilesIterator.next();

        if (QFile::exists(fileName)) {
            //TODO: use the return value for an error message at the end of the operation
            QtPatch::patchTextFile(fileName, searchReplacePairs);
        }
    }
//END - patch text files

#ifdef Q_OS_MAC
    Relocator relocator;
    bool successMacRelocating = false;
    QInstaller::Installer *installer = value(QLatin1String("installer")).value<QInstaller::Installer*>();
    Q_CHECK_PTR(installer);
    successMacRelocating = relocator.apply(newQtPathStr, installer->value(QLatin1String("TargetDir")));
    if (!successMacRelocating)
    {
        setError( UserDefinedError );
        setErrorString(tr("Error while relocating Qt: %1").arg(relocator.errorMessage()));
        return false;
    }
#endif
    return true;
}

bool QtPatchOperation::undoOperation()
{
    return true;
}

bool QtPatchOperation::testOperation()
{
    return true;
}

KDUpdater::UpdateOperation* QtPatchOperation::clone() const
{
    return new QtPatchOperation();
}

