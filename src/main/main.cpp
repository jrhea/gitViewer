#include <QtQml>
#include <QQmlContext>
#include <QUrl>
#include <QDateTime>
#include <QDesktopServices>
#include <QString>
#include <QQuickView>
#include <QQml.h>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include<QDebug>

#ifdef QT_WIDGETS_LIB
#include <QtWidgets/QApplication>
#else
#include <QtGui/QGuiApplication>
#endif

#ifdef QT_WIDGETS_LIB
#define QtQuickControlsApplication QApplication
#else
#define QtQuickControlsApplication QGuiApplication
#endif

#include <gitviewer.h>

int main(int argc, char *argv[])
{
    QtQuickControlsApplication app(argc, argv);
    app.setOrganizationName("jonny rhea");
    app.setOrganizationDomain("jrhea.github.io");
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());

    if (QCoreApplication::arguments().contains(QLatin1String("--coreprofile")))
    {
        QSurfaceFormat fmt;
        fmt.setVersion(3,3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
        QSurfaceFormat::setDefaultFormat(fmt);
    }
    //For debugging QML/OpenGL issue with VirtualBox/Windows 7
#if 0
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qpa.gl=true"));
#endif

    QQmlApplicationEngine engine;
    engine.addImportPath("src/include");

    QScopedPointer<GitViewer> gitViewer(new GitViewer());
    gitViewer->init(&engine);

    qmlRegisterType<SortFilterProxyModel>("sortfilterproxymodel",1,0,"SortFilterProxyModel");

    engine.load(QUrl(QStringLiteral("qrc:/mainView.qml")));

    return app.exec();
}
