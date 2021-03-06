/**************************************************************************
**
** This file is part of Qt SDK**
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).*
**
** Contact:  Nokia Corporation qt-info@nokia.com**
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
#ifndef QINSTALLER_GLOBAL_H
#define QINSTALLER_GLOBAL_H

#include <installer_global.h>

#include <kdupdaterupdate.h>
#include <kdupdaterupdateoperation.h>
#include <kdupdaterpackagesinfo.h>

QT_BEGIN_NAMESPACE
class QScriptContext;
class QScriptEngine;
class QScriptValue;
QT_END_NAMESPACE


namespace QInstaller {

enum INSTALLER_EXPORT RunMode
{
    AllMode,
    UpdaterMode
};

enum INSTALLER_EXPORT JobError
{
    InvalidUrl = 0x24B04,
    Timeout,
    DownloadError,
    InvalidUpdatesXml,
    InvalidMetaInfo,
    ExtractionError,
    UserIgnoreError,
    RepositoryUpdatesReceived
};

typedef KDUpdater::UpdateOperation Operation;
typedef QList<QInstaller::Operation*> OperationList;

typedef KDUpdater::Update Package;
typedef QList<QInstaller::Package*> PackagesList;

typedef KDUpdater::PackageInfo LocalPackage;
typedef QHash<QString, LocalPackage> LocalPackagesHash;

QString uncaughtExceptionString(QScriptEngine *scriptEngine, const QString &context = QString());
QScriptValue qInstallerComponentByName(QScriptContext *context, QScriptEngine *engine);

QScriptValue qDesktopServicesOpenUrl(QScriptContext *context, QScriptEngine *engine);
QScriptValue qDesktopServicesDisplayName(QScriptContext *context, QScriptEngine *engine);
QScriptValue qDesktopServicesStorageLocation(QScriptContext *context, QScriptEngine *engine);

} // namespace QInstaller

#endif // QINSTALLER_GLOBAL_H
