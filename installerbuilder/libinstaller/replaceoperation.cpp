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
#include "replaceoperation.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

using namespace QInstaller;

ReplaceOperation::ReplaceOperation()
{
    setName(QLatin1String("Replace"));
}

void ReplaceOperation::backup()
{
}

bool ReplaceOperation::performOperation()
{
    const QStringList args = arguments();

    // Arguments:
    // 1. filename
    // 2. Source-String
    // 3. Replace-String
    if (args.count() != 3) {
        setError(InvalidArguments);
        setErrorString(tr("Invalid arguments in %0: %1 arguments given, 3 expected.").arg(name()).arg(args
            .count()));
        return false;
    }
    const QString fileName = args.at(0);
    const QString before = args.at(1);
    const QString after = args.at(2);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        setError(UserDefinedError);
        setErrorString(QObject::tr("Failed to open %1 for reading").arg(fileName));
        return false;
    }

    QTextStream stream(&file);
    QString replacedFileContent = stream.readAll();
    file.close();

    if (!file.open(QIODevice::WriteOnly)) {
        setError(UserDefinedError);
        setErrorString(QObject::tr("Failed to open %1 for writing").arg(fileName));
        return false;
    }

    stream.setDevice(&file);
    stream << replacedFileContent.replace(before, after);
    file.close();

    return true;
}

bool ReplaceOperation::undoOperation()
{
    // Need to remove settings again
    return true;
}

bool ReplaceOperation::testOperation()
{
    return true;
}

Operation *ReplaceOperation::clone() const
{
    return new ReplaceOperation();
}
