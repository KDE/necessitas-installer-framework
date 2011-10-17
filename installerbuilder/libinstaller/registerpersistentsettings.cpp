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

#include "registerpersistentsettings.h"

#include "constants.h"
#include "packagemanagercore.h"
#include "qtcreator_constants.h"

#include "persistentsettings.h"
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QDebug>

namespace QInstaller {


RegisterPersistentSettings::RegisterPersistentSettings()
{
    setName(QLatin1String("RegisterPersistentSettings"));
}

RegisterPersistentSettings::~RegisterPersistentSettings()
{
}

void RegisterPersistentSettings::backup()
{
}

// Parameter List:
// settings file name - File name where we store the settings
// settings key - key
// settings value - value
bool RegisterPersistentSettings::performOperation()
{
    const QStringList args = arguments();

    if (args.count() != 3) {
        setError(InvalidArguments);
        setErrorString(tr("Invalid arguments in %0: %1 arguments given, minimum 3 expected.")
                        .arg(name()).arg(args.count()));
        return false;
    }

    PackageManagerCore *const core = qVariantValue<PackageManagerCore*>(value(QLatin1String("installer")));
    if (!core) {
        setError(UserDefinedError);
        setErrorString(tr("Needed installer object in \"%1\" operation is empty.").arg(name()));
        return false;
    }
    const QString &rootInstallPath = core->value(scTargetDir);
    if (rootInstallPath.isEmpty() || !QDir(rootInstallPath).exists()) {
        setError(UserDefinedError);
        setErrorString(tr("The given TargetDir %1 is not a valid/existing dir.").arg(rootInstallPath));
        return false;
    }
    const QString settingsFileName= rootInstallPath
            + QString::fromLatin1(GenericQtSettingsSuffixPath)+args.at(0);

    const QString &settingsKey = args.at(1);
    const QString &settingsValue = args.at(2);

    ProjectExplorer::PersistentSettingsReader reader;
    QVariantMap map;
    if (reader.load(settingsFileName))
        map = reader.restoreValues();
    map[settingsKey]=settingsValue;
    ProjectExplorer::PersistentSettingsWriter writer;
    foreach (QString key, map.keys())
        writer.saveValue(key,map[key]);
    QDir().mkpath(QFileInfo(settingsFileName).absolutePath());
    writer.save(settingsFileName, QString::fromLatin1("QtCreatorSettings"));
    return true;
}

bool RegisterPersistentSettings::undoOperation()
{
    return true;
}

bool RegisterPersistentSettings::testOperation()
{
    return true;
}

Operation* RegisterPersistentSettings::clone() const
{
    return new RegisterPersistentSettings();
}

}
