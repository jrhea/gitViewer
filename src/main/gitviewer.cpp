//QT
#include <QDebug>
#include <QQmlContext>
#include <QApplication>

//custom
#include "gitviewer.h"

using namespace QtConcurrent;

GitViewer::GitViewer(QQmlApplicationEngine *engine, QObject *parent): QObject(parent)
{
    _engine = engine;
    _adapter = new GitAdapter();
    _path = QDir::homePath();  //TODO: set this to C:\ for windows

    _fileSystemModel = new FileSystemModel(parent);
    _fileSystemModel->setRootPath(_path);
    _fileSystemModel->setResolveSymlinks(true);

    _branchController = new BranchController(_engine, _adapter);
    _commitController = new CommitController(_engine, _adapter);

    connect(_fileSystemModel,SIGNAL(pathChanged(const QString &)),
            this,SLOT(setPath(const QString &)));

    connect(_fileSystemModel,SIGNAL(pathChanged(const QString &)),
            _adapter,SLOT(openRepository(const QString &)));

    connect(_adapter,SIGNAL(repositoryChanged()),
            _branchController,SLOT(loadModel()));

    connect(_branchController,SIGNAL(branchChanged(const QString &)),
            _commitController,SLOT(loadModel(const QString &)));

    connect(_branchController,SIGNAL(modelChanged()),
            _branchController,SLOT(updateBranchView()));

    connect(_commitController,SIGNAL(modelChanged()),
            _commitController,SLOT(updateCommitView()));
}

GitViewer::~GitViewer()
{
    delete _adapter;
    delete _fileSystemModel;
    delete _branchController;
    delete _commitController;
}

FileSystemModel* GitViewer::getFileSystemModel() const
{
    return _fileSystemModel;
}

BranchController* GitViewer::getBranchController() const
{
    return _branchController;
}

CommitController *GitViewer::getCommitController() const
{
    return _commitController;
}

void GitViewer::setPath(const QString &path)
{
    if(path != _path)
    {
        _path = path;
    }
}
