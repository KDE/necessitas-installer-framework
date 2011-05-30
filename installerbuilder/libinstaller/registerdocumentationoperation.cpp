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
#include "registerdocumentationoperation.h"
#include "fsengineclient.h"

#include <QHelpEngine>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QDebug>

using namespace QInstaller;

RegisterDocumentationOperation::RegisterDocumentationOperation()
{
    setName(QLatin1String("RegisterDocumentation"));
}

RegisterDocumentationOperation::~RegisterDocumentationOperation()
{
}

void RegisterDocumentationOperation::backup()
{
}

namespace {
    // get the right filename of the qsettingsfile (root/user)
    QString settingsFileName()
    {
        #if defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
            // If the system settings are writable, don't touch the user settings.
            // The reason is that a doc registered while running with sudo could otherwise create
            // a root-owned configuration file a user directory.
            QScopedPointer<QSettings> settings(new QSettings(QSettings::IniFormat, QSettings::UserScope, QLatin1String(NQTC_SETTINGS_ORG), QLatin1String(NQTC_SETTINGS_APPNAME)));

            // QSettings::isWritable isn't reliable enough in 4.7, determine writability experimentally
            settings->setValue(QLatin1String("iswritable"), QLatin1String("accomplished"));
            settings->sync();
            if (settings->status() == QSettings::NoError) {
                // we can use the system settings
                if (settings->contains(QLatin1String("iswritable")))
                    settings->remove(QLatin1String("iswritable"));
            } else {
                // we have to use user settings
                settings.reset(new QSettings(QSettings::IniFormat, QSettings::UserScope, QLatin1String(NQTC_SETTINGS_ORG), QLatin1String(NQTC_SETTINGS_APPNAME)));
            }

        #else
            QScopedPointer<QSettings> settings(new QSettings(QSettings::IniFormat, QSettings::UserScope,
                               QLatin1String(NQTC_SETTINGS_ORG), QLatin1String(NQTC_SETTINGS_APPNAME)));
        #endif
            return settings->fileName();
    }
}

bool RegisterDocumentationOperation::performOperation()
{
    const QStringList args = arguments();

    if( args.count() != 1 ) {
        setError( InvalidArguments );
        setErrorString( tr("Invalid arguments in %0: %1 arguments given, 1 expected.")
                        .arg(name()).arg( args.count() ) );
        return false;
    }
    const QString helpFile = args.at(0);


    QFileInfo fileInfo(settingsFileName());
    QDir settingsDir(fileInfo.absolutePath() + QLatin1String("/qtcreator"));

    if (!settingsDir.exists())
        settingsDir.mkpath(settingsDir.absolutePath());
    const QString collectionFile = settingsDir.absolutePath() + QLatin1String("/helpcollection.qhc");
    qDebug() << "collectionFile: " << collectionFile;

    if ( !QFileInfo( helpFile ).exists() ) {
        setError ( UserDefinedError );
        setErrorString( tr("Could not register help file %1: File not found.").arg( helpFile ) );
        return false;
    }

    QHelpEngineCore help(collectionFile);
    QString oldData = help.customValue(QLatin1String("AddedDocs")).toString();
    if (!oldData.isEmpty())
        oldData.append(QLatin1String(";"));
    const QString newData = oldData + QFileInfo(helpFile).absoluteFilePath();
    return help.setCustomValue(QLatin1String("AddedDocs"), newData);
}

bool RegisterDocumentationOperation::undoOperation()
{
    const QString helpFile = arguments().first();

    QFileInfo fileInfo(settingsFileName());
    QDir settingsDir(fileInfo.absolutePath() + QLatin1String("/qtcreator"));

    if (!settingsDir.exists())
        settingsDir.mkpath(settingsDir.absolutePath());
    const QString collectionFile = settingsDir.absolutePath() + QLatin1String("/helpcollection.qhc");

    if ( !QFileInfo( helpFile ).exists() ) {
        setError ( UserDefinedError );
        setErrorString( tr("Could not unregister help file %1: File not found.").arg( helpFile ) );
        return false;
    }

    QHelpEngineCore help(collectionFile);
    const QString nsName = help.namespaceName(helpFile);
    return help.unregisterDocumentation(nsName);
}

bool RegisterDocumentationOperation::testOperation()
{
    return true;
}

KDUpdater::UpdateOperation* RegisterDocumentationOperation::clone() const
{
    return new RegisterDocumentationOperation();
}

