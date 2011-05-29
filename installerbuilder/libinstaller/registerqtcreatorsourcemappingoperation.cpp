/*
I BogDan Vatra < bog_dan_ro@yahoo.com >, the copyright holder of this work,
hereby release it into the public domain. This applies worldwide.

In case this is not legally possible, I grant any entity the right to use
this work for any purpose, without any conditions, unless such conditions
are required by law.
*/

#include "registerqtcreatorsourcemappingoperation.h"

#include <QSettings>

using namespace QInstaller;

static const QLatin1String sourcePathMappingArrayName("SourcePathMappings");
static const QLatin1String sourcePathMappingSourceKey("Source");
static const QLatin1String sourcePathMappingTargetKey("Target");

RegisterQtCreatorSourceMappingOperation::RegisterQtCreatorSourceMappingOperation()
{
    setName(QLatin1String("RegisterQtCreatorSourceMapping"));
}

void RegisterQtCreatorSourceMappingOperation::backup()
{
}

bool RegisterQtCreatorSourceMappingOperation::performOperation()
{
    const QStringList args = arguments();

    if( args.count() != 3) {
        setError( InvalidArguments );
        setErrorString( tr("Invalid arguments in %0: %1 arguments given, exact 3 expected(rootInstallPath, oldPath, newPath).")
                        .arg(name()).arg( arguments().count() ) );
        return false;
    }

    const QString &rootInstallPath = args.at(0); //for example "C:\\Nokia_SDK\\"
    const QString &oldPath = args.at(1);
    const QString &newPath = args.at(2);

#if defined(Q_OS_MAC)
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QLatin1String("eu.licentia.necessitas"),
        QLatin1String("NecessitasQtCreator"));
#else
    QString iniFileLocation = QLatin1String("%1/QtCreator/share/qtcreator/Nokia/QtCreator.ini");
    QSettings settings( iniFileLocation.arg(rootInstallPath),
                        QSettings::IniFormat );
#endif

    QMap<QString, QString> sourcePathMap;
    if (const int count = settings.beginReadArray(sourcePathMappingArrayName))
    {
        for (int i = 0; i < count; ++i)
        {
            settings.setArrayIndex(i);
            const QString source = settings.value(sourcePathMappingSourceKey).toString();
            const QString target = settings.value(sourcePathMappingTargetKey).toString();
            if (source==oldPath || target==newPath)
                return true;
            sourcePathMap.insert(source, target);
        }
    }
    settings.endArray();

    sourcePathMap.insert(oldPath, newPath);
    settings.beginWriteArray(sourcePathMappingArrayName);
    if (!sourcePathMap.isEmpty())
    {
        int i = 0;
        const QMap<QString, QString>::const_iterator cend = sourcePathMap.constEnd();
        for (QMap<QString, QString>::const_iterator it = sourcePathMap.constBegin(); it != cend; ++it, ++i)
        {
            settings.setArrayIndex(i);
            settings.setValue(sourcePathMappingSourceKey, it.key());
            settings.setValue(sourcePathMappingTargetKey, it.value());
        }
    }
    settings.endArray();
    return true;
}

bool RegisterQtCreatorSourceMappingOperation::undoOperation()
{
    return true;
}

bool RegisterQtCreatorSourceMappingOperation::testOperation()
{
    return true;
}

KDUpdater::UpdateOperation* RegisterQtCreatorSourceMappingOperation::clone() const
{
    return new RegisterQtCreatorSourceMappingOperation();
}
