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
#ifndef ADMINAUTHORIZATION_H
#define ADMINAUTHORIZATION_H

#include <QtCore/QObject>

class AdminAuthorizationBase
{
protected:
    AdminAuthorizationBase();

public:
    virtual ~AdminAuthorizationBase() {}

    virtual bool authorize() = 0;
    bool isAuthorized() const;

protected:  
    void setAuthorized();

private:
    bool m_authorized;
};

class AdminAuthorization : public QObject, public AdminAuthorizationBase
{
    Q_OBJECT
    Q_PROPERTY(bool authorized READ isAuthorized)

public:
    AdminAuthorization();
#ifdef Q_OS_MAC
    ~AdminAuthorization();
#endif

    bool execute(QWidget *dialogParent, const QString &programs, const QStringList &arguments);
    static bool hasAdminRights();

public Q_SLOTS:
    bool authorize();

Q_SIGNALS:
    void authorized();

#ifdef Q_OS_MAC
private:
    class Private;
    Private *d;
#endif
};

#endif // ADMINAUTHORIZATION_H
