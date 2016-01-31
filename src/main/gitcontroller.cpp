//QT
#include <QDebug>
#include <QQmlContext>
#include <QApplication>

//3rd Party
//#include <libGitWrap/Result.hpp>
//#include <libGitWrap/Tree.hpp>
//#include <libGitWrap/TreeEntry.hpp>
//#include <libGitWrap/TreeBuilder.hpp>
//#include <libGitWrap/BranchRef.hpp>
//#include <libGitWrap/Reference.hpp>
//#include <libGitWrap/Index.hpp>
//#include <libGitWrap/IndexEntry.hpp>

//custom
#include "gitcontroller.h"


GitController::GitController(QObject *parent) : QObject(parent)
{

}

GitController::GitController(QQmlApplicationEngine *engine, QObject *parent) :GitController(parent)
{
    _engine = engine;
    //TODO: Set this to windows c:
    //_path = QDir::homePath();

    _adapter = new GitAdapter();

    _fileSystemModel = new FileSystemModel(parent);
    _fileSystemModel->setRootPath(QDir::homePath());
    _fileSystemModel->setResolveSymlinks(true);

    _branchModel = new BranchModel(_adapter);
    _commitModel = new CommitModel(_adapter);

    connect(_fileSystemModel,SIGNAL(pathChanged(const QString &)),
            _adapter,SLOT(openRepository(const QString &)));

    connect(_adapter,SIGNAL(repositoryChanged()),
            this,SLOT(loadBranchModel()));

    connect(this,SIGNAL(branchChanged(const QString &)),
            this,SLOT(loadCommitModel(const QString &)));

    connect(this,SIGNAL(branchModelChanged()),
            this,SLOT(updateBranchView()));

    connect(this,SIGNAL(commitModelChanged()),
            this,SLOT(updateCommitView()));


//    connect(this,SIGNAL(pathChanged()),
//            this,SLOT(loadRepository()));
//    connect(this,SIGNAL(repositoryChanged()),
//            this,SLOT(loadBranchModel()));
//    connect(this,SIGNAL(branchChanged()),
//            this,SLOT(loadCommitModel()));

    //_adapter->openRepository(_path);
}

GitController::~GitController()
{
    delete _adapter;
    delete _fileSystemModel;
    delete _branchModel;
    delete _commitModel;
}

FileSystemModel* GitController::getFileSystemModel() const
{
    return _fileSystemModel;
}

BranchModel* GitController::getBranchModel() const
{
    return _branchModel;
}

CommitModel *GitController::getCommitModel() const
{
    return _commitModel;
}

//QString GitController::path() const
//{
//    return _path;
//}

QString GitController::branch() const
{
    return _branchModel->branch();
}

//void GitController::setPath(const QString &path)
//{
//    if(path != _path)
//    {
//        _path = path;
//        emit pathChanged();
//    }
//}

void GitController::setBranch(const QString &branch)
{
    _branchModel->setBranch(branch);
    emit branchChanged(branch);
}

void GitController::loadRepository()
{
    _adapter->openRepository(_fileSystemModel->path());
    return;
}

void GitController::loadBranchModel()
{
    _branchModel->loadModel();
    emit this->branchModelChanged();
    emit this->branchChanged(_branchModel->branch());
}

void GitController::loadCommitModel(const QString &branch)
{
    _commitModel->loadModel(branch);
    emit this->commitModelChanged();
}

void GitController::updateBranchView()
{
    _engine->rootContext()->setContextProperty("branchModel",_branchModel);
}

void GitController::updateCommitView()
{
    _engine->rootContext()->setContextProperty("commitModel",_commitModel);
}

//void GitController::loadBranchModel()
//{
//    _branchModel->clear();
//    _branch = _adapter->getHeadBranchName();



//    Git::Result r;
//    QStringList branchNames;
//    QStandardItem *it = NULL;
//    _branchModel->clear();
//    _branch = _repository.headBranchName(r);

//    if(r)
//    {

//        it = new QStandardItem();
//        it->setData(_branch,BranchModel::Name);
//        _branchModel->setItem(0,0,it);
//    }

//    //TODO: local & remote should be be set from UI
//    branchNames = _repository.branchNames(r,true,true);
//    if(r)
//    {
//        for(int i=1;i<branchNames.count();i++)
//        {
//            it = new QStandardItem();
//            it->setData(branchNames.at(i), BranchModel::Name);
//            _branchModel->setItem(i,0,it);
//        }

//        emit branchChanged();
//    }
//}

//void GitController::loadCommitModel()
//{
//    commitModel->clear();
//    _adapter->getCommits(_commitModel,_branch,true,true);

//}

QString GitController::getCommitInfo(int index, QString role)
{
    QString result;
    if(_commitModel != NULL)
    {

        QHash<int, QByteArray> roles = _commitModel->roleNames();
        QHashIterator<int, QByteArray> it(roles);
        while (it.hasNext()) {
            it.next();
            if(it.value() == role)
            {
                QModelIndex modelIndex = _commitModel->index(index,0);
                result = _commitModel->data(modelIndex, it.key()).toString();
                break;
            }
        }
    }
    return result;
}
