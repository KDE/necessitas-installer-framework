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
#ifndef UPDATESETTINGSDIALOG_H
#define UPDATESETTINGSDIALOG_H

#include <QtGui/QDialog>

#include <KDToolsCore/pimpl_ptr.h>

#include "installer_global.h"

namespace QInstaller
{

class INSTALLER_EXPORT UpdateSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UpdateSettingsDialog( QWidget* parent = 0 );
    ~UpdateSettingsDialog();

Q_SIGNALS:
    void checkForUpdates();

public Q_SLOTS:
    void accept();

private:
    class Private;
    kdtools::pimpl_ptr< Private > d;
};

}

#endif