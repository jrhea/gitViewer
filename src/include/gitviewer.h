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

class GitViewer : QObject
{
    Q_OBJECT
public:

    explicit GitViewer(QObject *parent=nullptr): QObject(parent)
    {
        _adapter = new GitAdapter();
        _fileSystemModel = new FileSystemModel();
    }

    void init(QQmlApplicationEngine *engine)
    {
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
    ~GitViewer()
    {
        delete _adapter;
        delete _fileSystemModel;
        delete _branchController;
        delete _commitController;
    }

private:
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    FileSystemModel *_fileSystemModel;
    BranchController *_branchController;
    CommitController *_commitController;


};

#endif // GITVIEWER_H
