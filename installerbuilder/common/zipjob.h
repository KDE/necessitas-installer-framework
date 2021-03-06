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
#ifndef ZIPJOB_H
#define ZIPJOB_H

#include <QProcess>
#include <QRunnable>

QT_BEGIN_NAMESPACE
class QDir;
class QIODevice;
class QStringList;
QT_END_NAMESPACE

class ZipJob : public QObject, public QRunnable
{
    Q_OBJECT

public:
    ZipJob();
    ~ZipJob();

    void setOutputDevice(QIODevice *device);
    void setWorkingDirectory(const QDir &dir);
    void setFilesToArchive(const QStringList &files);

    void run();

Q_SIGNALS:
    void finished();
    void error();

private Q_SLOTS:
    void processError(QProcess::ProcessError);
    void processFinished(int, QProcess::ExitStatus);
    void processReadyReadStandardOutput();

private:
    class Private;
    Private *const d;
};

class UnzipJob : public QObject, public QRunnable
{
    Q_OBJECT

public:
    UnzipJob();
    ~UnzipJob();

    void setInputDevice(QIODevice *device);
    void setOutputPath(const QString &path);
    void setFilesToExtract(const QStringList &files);

    void run();

Q_SIGNALS:
    void finished();
    void error();

private Q_SLOTS:
    void processError(QProcess::ProcessError);
    void processFinished(int, QProcess::ExitStatus);

private:
    class Private;
    Private *const d;
};

#endif // ZIPJOB_H
