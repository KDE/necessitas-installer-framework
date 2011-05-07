#include "registerqtcreatorsourcemappingoperation.h"

#include <QSettings>

using namespace QInstaller;

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
    QString iniFileLocation = QLatin1String("%1/Qt Creator.app/Contents/Resources/Nokia/QtCreator.ini");
#else
    QString iniFileLocation = QLatin1String("%1/QtCreator/share/qtcreator/Nokia/QtCreator.ini");
#endif

    QSettings settings( iniFileLocation.arg(rootInstallPath),
                        QSettings::IniFormat );

    settings.beginGroup(QLatin1String("SourcePathMappings"));
    int size=settings.value(QLatin1String("size")).toInt();
    for (int i=0;i<size;i++)
    {
        if (settings.value(QString(QLatin1String("%1\\Source")).arg(i)).toString()==oldPath ||
                settings.value(QString(QLatin1String("%1\\Target")).arg(i)).toString()==newPath)
            return true;
    }
    settings.setValue(QString(QLatin1String("%1\\Source")).arg(size+1), oldPath);
    settings.setValue(QString(QLatin1String("%1\\Target")).arg(size+1), newPath);
    settings.setValue(QLatin1String("size"), size+1);
    settings.endGroup();
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
