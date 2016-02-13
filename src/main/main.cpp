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

#include<QDebug>

int main(int argc, char *argv[])
{
    QtQuickControlsApplication::setAttribute(Qt::AA_UseDesktopOpenGL,true);
    QtQuickControlsApplication app(argc, argv);
    app.setOrganizationName("Me");
    app.setOrganizationDomain("jrhea.github.io");
    app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());

    if (QCoreApplication::arguments().contains(QLatin1String("--coreprofile")))
    {
        QSurfaceFormat fmt;
        fmt.setVersion(3,3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
        QSurfaceFormat::setDefaultFormat(fmt);
    }


    //    QQuickView view;
    //if (qgetenv("QT_QUICK_CORE_PROFILE").toInt())
    //{
//        QSurfaceFormat f = view.format();
//        f.setProfile(QSurfaceFormat::CoreProfile);
//        f.setVersion(4, 4);
//        view.setFormat(f);
   // }

    QQmlApplicationEngine engine;
    GitViewer *gitController = new GitViewer(&engine);
    engine.rootContext()->setContextProperty("branchController", gitController->getBranchController());
    engine.rootContext()->setContextProperty("fileSystemModel", gitController->getFileSystemModel());
    engine.rootContext()->setContextProperty("commitController",gitController->getCommitController());
    engine.addImportPath("src/include");
    qmlRegisterType<SortFilterProxyModel>("sortfilterproxymodel",1,0,"SortFilterProxyModel");

    engine.load(QUrl(QStringLiteral("qrc:/mainView.qml")));
    return app.exec();
}
