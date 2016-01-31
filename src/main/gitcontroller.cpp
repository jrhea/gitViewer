//QT
#include <QDebug>
#include <QQmlContext>
#include <QApplication>

//3rd Party
#include <libGitWrap/Result.hpp>
#include <libGitWrap/Tree.hpp>
#include <libGitWrap/TreeEntry.hpp>
#include <libGitWrap/TreeBuilder.hpp>
#include <libGitWrap/BranchRef.hpp>
#include <libGitWrap/Reference.hpp>
#include <libGitWrap/Index.hpp>
#include <libGitWrap/IndexEntry.hpp>

//custom
#include "gitcontroller.h"


GitController::GitController(QObject *parent) : QObject(parent)
{

}

GitController::GitController(QQmlApplicationEngine *engine, QObject *parent) :GitController(parent)
{
    _engine = engine;
    //TODO: Set this to windows c:
    _path = QDir::homePath();

    _fileSystemModel = new FileSystemModel(parent);
    _fileSystemModel->setRootPath(_path);
    _fileSystemModel->setResolveSymlinks(true);

    _branchModel = new BranchModel();
    _commitModel = new CommitModel();

    connect(this,SIGNAL(pathChanged()),
            this,SLOT(loadRepository()));
    connect(this,SIGNAL(repositoryChanged()),
            this,SLOT(loadBranchModel()));
    connect(this,SIGNAL(branchChanged()),
            this,SLOT(loadCommitModel()));
    emit repositoryChanged();
}

GitController::~GitController()
{
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

QString GitController::path() const
{
    return _path;
}

QString GitController::branch() const
{
    return _branch;
}

void GitController::setPath(const QString &path)
{
    if(path != _path)
    {
        _path = path;
        emit pathChanged();
    }
}

void GitController::setBranch(const QString &branch)
{
    if(branch != _branch)
    {
        _branch = branch;
        emit branchChanged();
    }
}

void GitController::loadRepository()
{
     Git::Result r;
     _repository = Git::Repository::open(r,_path);
     if ( !r )
     {
         qCritical( "Unable to open repository at %s."
                        "\nGit error: %s",
                        qPrintable( _path ), qPrintable( r.errorText() ) );
     }
     else
     {
        emit repositoryChanged();
     }

    return;
}

void GitController::loadBranchModel()
{
    Git::Result r;
    QStringList branchNames;
    QStandardItem *it = NULL;
    _branchModel->clear();
    _branch = _repository.headBranchName(r);

    if(r)
    {

        it = new QStandardItem();
        it->setData(_branch,BranchModel::Name);
        _branchModel->setItem(0,0,it);
    }

    //TODO: local & remote should be be set from UI
    branchNames = _repository.branchNames(r,true,true);
    if(r)
    {
        for(int i=1;i<branchNames.count();i++)
        {
            it = new QStandardItem();
            it->setData(branchNames.at(i), BranchModel::Name);
            _branchModel->setItem(i,0,it);
        }
        _engine->rootContext()->setContextProperty("branchModel",_branchModel);
        emit branchChanged();
    }
}

void GitController::loadCommitModel()
{
     Git::Result r;
     Git::ObjectId oid = _repository.branchRef(r,_branch).objectId();
     Git::RevisionWalker walker;
     walker = Git::RevisionWalker::create(r,_repository);
     _commitModel->clear();

     if(r)
     {
         //TODO: sort option should be set from UI
         walker.setSorting(r,true,false);
         //walker.hideRef(r,"refs/heads/new");
         walker.push(r, oid);

         Git::Commit commit = NULL;
         QStandardItem* it = NULL;
         int commitNum = 0;
         while(walker.next(r,oid))
         {
             commit = _repository.lookupCommit(r,oid);

             it = new QStandardItem();
             it->setData(commit.shortMessage(), CommitModel::Message);
             it->setData(commit.author().name(), CommitModel::Author);
             it->setData(commit.author().email(), CommitModel::Email);
             it->setData(commit.id().toString(), CommitModel::CommitId);
             it->setData(commit.author().when().toString("MM-dd-yyyy hh:mm ap"), CommitModel::Date);

             commitNum++;
             _commitModel->appendRow(it);
             if(!r)
             {
                 qCritical( "Failed to lookup the next object."
                                "\nGit error: %s", qPrintable( r.errorText() ) );
             }
         }
         _engine->rootContext()->setContextProperty("commitModel",_commitModel);
     }
}

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
