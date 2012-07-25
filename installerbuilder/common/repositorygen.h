/**************************************************************************
**
** This file is part of Installer Framework
**
** Copyright (c) 2010-2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
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
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef QINSTALLER_REPOSITORYGEN_H
#define QINSTALLER_REPOSITORYGEN_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVector>

namespace QInstallerTools {

void printRepositoryGenOptions();

struct PackageInfo
{
    QString name;
    QString version;
    QString directory;
    QStringList dependencies;
    QStringList copiedArchives;
};
typedef QVector<PackageInfo> PackageInfoVector;

enum FilterType {
    Include,
    Exclude
};

QMap<QString, QString> buildPathToVersionMap(const PackageInfoVector &info);

void compressMetaDirectories(const QString &repoDir);
void compressDirectory(const QStringList &paths, const QString &archivePath);
void compressMetaDirectories(const QString &repoDir, const QString &baseDir,
    const QMap<QString, QString> &versionMapping);

void copyComponentData(const QString &packageDir, const QString &repoDir, PackageInfoVector &infos);

void generateMetaDataDirectory(const QString &outDir, const QString &dataDir,
    const PackageInfoVector &packages, const QString &appName,
    const QString& appVersion, const QString &redirectUpdateUrl = QString());

PackageInfoVector createListOfPackages(const QString &packagesDirectory, const QStringList &filteredPackages,
    FilterType ftype);

} // namespace QInstallerTools

#endif // QINSTALLER_REPOSITORYGEN_H
