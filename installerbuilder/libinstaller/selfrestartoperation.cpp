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
#include "selfrestartoperation.h"
#include "packagemanagercore.h"

#include <kdselfrestarter.h>

using namespace QInstaller;

SelfRestartOperation::SelfRestartOperation()
{
    setName(QLatin1String("SelfRestart"));
}

void SelfRestartOperation::backup()
{
    setValue(QLatin1String("PreviousSelfRestart"), KDSelfRestarter::restartOnQuit());
}

bool SelfRestartOperation::performOperation()
{
    PackageManagerCore *const core = qVariantValue<PackageManagerCore *>(value(QLatin1String("installer")));
    if (!core) {
        setError(UserDefinedError);
        setErrorString(tr("Needed installer object in \"%1\" operation is empty.").arg(name()));
        return false;
    }

    if (!core->isUpdater() && !core->isPackageManager()) {
        setError(UserDefinedError);
        setErrorString(tr("Self Restart: Only valid within updater or packagemanager mode."));
        return false;
    }

    if (!arguments().isEmpty()) {
        setError(InvalidArguments);
        setErrorString(tr("Self Restart: Invalid arguments"));
        return false;
    }
    KDSelfRestarter::setRestartOnQuit(true);
    return KDSelfRestarter::restartOnQuit();
}

bool SelfRestartOperation::undoOperation()
{
    KDSelfRestarter::setRestartOnQuit(value(QLatin1String("PreviousSelfRestart")).toBool());
    return true;
}

bool SelfRestartOperation::testOperation()
{
    return true;
}

Operation *SelfRestartOperation::clone() const
{
    return new SelfRestartOperation();
}
