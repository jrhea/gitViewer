#ifndef GITVIEWER_H
#define GITVIEWER_H

#include <QFileSystemModel>
#include <QObject>
#include <QUrl>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include <QApplication>

#include <sortfilterproxymodel.h>

#include <gitadapter.h>
#include <filesystemmodel.h>
#include <branchcontroller.h>
#include <commitcontroller.h>

/**
 * @brief The GitViewer class initializes controllers, models, adapters, and QML engine.
 *
 * Signal/Slot Management:
 * - FileSystemModel::pathChanged()    -> GitAdapter::openRepository()
 * - GitAdapter::repositoryChanged()   -> BranchController::loadModel()
 * - BranchController::branchChanged() -> CommitController::loadCommits()
 * - CommitController::commitsLoaded() -> CommitController::populateModel()
 * - BranchController::modelChanged()  -> BranchController::updateView()
 * - CommitController::modelChanged()  -> CommitController::updateView()
 */
class GitViewer : QObject
{
    Q_OBJECT
public:
    /**
     * @brief ctor
     * @param parent
     */
    explicit GitViewer(QObject *parent=nullptr): QObject(parent){ }

    ~GitViewer()
    {
        delete _adapter;
        delete _fileSystemModel;
        delete _branchController;
        delete _commitController;
    }

    /**
     * @brief contains logic needed to initialize the application.
     *
     * Instantiates:
     * - C++ controllers
     * - C++ models that don't have controllers (i.e. FileSystemModel)
     * - C++ data adapters (i.e. GitAdapter)
     *
     * Signal/Slot Connections:
     * - C++ definitions of signal/slot connections
     *
     * QML Engine Config
     * - Exposes relevant C++ controllers and models to QML engine
     * @param engine
     */
    void init(QQmlApplicationEngine *engine)
    {
        _adapter = new GitAdapter();
        _fileSystemModel = new FileSystemModel();
        _branchController = new BranchController(engine, _adapter);
        _commitController = new CommitController(engine, _adapter);

        _fileSystemModel->setRootPath(QDir::rootPath());
        _fileSystemModel->setResolveSymlinks(true);

        connect(_fileSystemModel,SIGNAL(pathChanged(const QString &)),
                _adapter,SLOT(openRepository(const QString &)));

        connect(_adapter,SIGNAL(repositoryChanged()),
                _branchController,SLOT(loadModel()));

        connect(_branchController,SIGNAL(branchChanged(const QString &)),
                _commitController,SLOT(loadCommits(const QString &)));

        connect(_commitController,SIGNAL(commitsLoaded()),
                _commitController,SLOT(populateModel()));

        connect(_branchController,SIGNAL(modelChanged()),
                _branchController,SLOT(updateView()));

        connect(_commitController,SIGNAL(modelChanged()),
                _commitController,SLOT(updateView()));

        engine->rootContext()->setContextProperty("branchController", _branchController);
        engine->rootContext()->setContextProperty("fileSystemModel", _fileSystemModel);
        engine->rootContext()->setContextProperty("commitController", _commitController);
    }

private:
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    FileSystemModel *_fileSystemModel;
    BranchController *_branchController;
    CommitController *_commitController;


};

#endif // GITVIEWER_H
