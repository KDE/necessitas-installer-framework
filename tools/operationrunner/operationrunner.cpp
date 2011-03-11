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
#include <common/errors.h>
#include <common/utils.h>
#include <common/repositorygen.h>
#include <common/installersettings.h>

#include <init.h>
#include <KDUpdater/UpdateOperation>
#include <KDUpdater/UpdateOperationFactory>

#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <QStringList>

#include <iostream>

static void printUsage()
{
    std::cout << "Usage: " << std::endl;
    std::cout << std::endl;
    std::cout << "operationrunner \"Execute\" \"{0,1}\" \"C:\\Windows\\System32\\cmd.exe\" \"/A\" \"/Q\" \"/C\" \"magicmaemoscript.bat\" \"showStandardError\"" << std::endl;
}

int main(int argc, char **argv)
{
    try {
        QCoreApplication app(argc, argv);

        QStringList argumentList = app.arguments();

        if( argumentList.count() < 2 || argumentList.contains("--help") )
        {
            printUsage();
            return 1;
        }
        argumentList.removeFirst(); // we don't need the application name

        QInstaller::init();

        QInstaller::setVerbose( true );

        QString operationName = argumentList.takeFirst();
        KDUpdater::UpdateOperation* const operation = KDUpdater::UpdateOperationFactory::instance().create( operationName );
        if (!operation) {
            std::cerr << "Can not find the operation: " << qPrintable(operationName) << std::endl;
            return 1;
        }
        operation->setArguments(argumentList);
        bool readyPerformed = operation->performOperation();
        if (readyPerformed) {
            std::cout << "Operation was succesfully performed." << std::endl;
        } else {
            std::cerr << "There was a problem while performing the operation: " << qPrintable(operation->errorString()) << std::endl;
        }
        return 0;
    } catch ( const QInstaller::Error& e ) {
        std::cerr << qPrintable(e.message()) << std::endl;
    }
    return 1;
}