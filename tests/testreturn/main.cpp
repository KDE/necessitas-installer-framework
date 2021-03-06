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
#include <QFile>
#include <QString>
#include <iostream>

static void crash() {
    QString* nemesis = 0;
    nemesis->clear();
}

int main( int argc, char** argv ) {
    std::cout << "Hello." << std::endl;
    if ( argc < 2 )
        return 0;
    const QString arg = QString::fromLocal8Bit( argv[1] ); 
    bool ok = false;
    const int num = arg.toInt( &ok );
    if ( ok )
        return num;
    if ( arg == QLatin1String("crash") ) {
        std::cout << "Yeth, mather. I Crash." << std::endl;
        crash();
    }
    if ( arg == QLatin1String("--script") ) {
        const QString fn = QString::fromLocal8Bit( argv[2] ); 
        QFile f( fn );
        if ( !f.open( QIODevice::ReadOnly ) ) {
            std::cerr << "Could not open file for reading: " << qPrintable(f.errorString()) << std::endl;
            crash();
        }
        bool ok;
        const int rv = QString::fromLatin1( f.readAll() ).toInt( &ok );
        if ( ok )
            return rv;
        else
            crash();
    }

}
