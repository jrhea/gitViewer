#include <QtQml>
#include <QQmlContext>
#include <QUrl>
#include <QDateTime>
#include <QDesktopServices>
#include <QString>
#include <QQuickView>
#include <QQml.h>
#include <QQuickItem>
#include <QtQml/qqmlapplicationengine.h>
#include <QtGui/qsurfaceformat.h>
#include <QtWidgets/QApplication>
#include <QtQml/qqml.h>
#define QtQuickControlsApplication QApplication


#include <gitviewer.h>

#include<QDebug>

int main(int argc, char *argv[])
{
    QtQuickControlsApplication app(argc, argv);
    QQmlApplicationEngine engine;
    if (QCoreApplication::arguments().contains(QLatin1String("--coreprofile"))) {
        QSurfaceFormat fmt;
        fmt.setVersion(4, 4);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
        QSurfaceFormat::setDefaultFormat(fmt);
    }

    GitViewer *gitController = new GitViewer(&engine);
    engine.rootContext()->setContextProperty("branchController", gitController->getBranchController());
    engine.rootContext()->setContextProperty("fileSystemModel", gitController->getFileSystemModel());
    engine.rootContext()->setContextProperty("commitController",gitController->getCommitController());
    engine.addImportPath("src/include");
    qmlRegisterType<SortFilterProxyModel>("sortfilterproxymodel",1,0,"SortFilterProxyModel");

    engine.load(QUrl(QStringLiteral("qrc:/mainView.qml")));
    return app.exec();
}
