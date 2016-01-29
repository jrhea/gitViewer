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
    _selectedPath = QDir::homePath();//"/Users/jrhea1980/Documents/projects/questionnaire";

    _fileSystemModel = new QFileSystemModel(parent);
    _fileSystemModel->setRootPath(_selectedPath);
    _fileSystemModel->setResolveSymlinks(true);

    _branchModel = new BranchModel();
    _commitModel = new CommitModel();

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

QFileSystemModel* GitController::getFileSystemModel() const
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

QString GitController::branch() const
{
    return _branch;
}

void GitController::loadRepository(const QModelIndex &index)
{
    if(_selectedPath != _fileSystemModel->filePath(index))
    {
         _selectedPath = _fileSystemModel->filePath(index);
         Git::Result r;
         _repository = Git::Repository::open(r,_selectedPath);
         if ( !r )
         {
             qCritical( "Unable to open repository at %s."
                            "\nGit error: %s",
                            qPrintable( _selectedPath ), qPrintable( r.errorText() ) );
         }
         else
         {
            emit repositoryChanged();
            //qDebug() << "repository changed: " << _filePath;
         }
    }

    return;
}

void GitController::loadBranchModel()
{
    Git::Result r;
    QStringList branchNames;
    QStandardItem *it = NULL;
    _branch = _repository.headBranchName(r);

    if(r)
    {
        it = new QStandardItem();
        it->setData(_branch,BranchModel::Name);
        _branchModel->setItem(0,0,it);
    }

    branchNames = _repository.branchNames(r,true,true);  //TODO: local & remote need to be set from QML
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

void GitController::setBranch(const QString &branch)
{
    if(branch != _branch)
    {
        _branch = branch;
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
     _commitVis.clear();

     if(r)
     {
         walker.setSorting(r,true,false);
         //walker.hideRef(r,"refs/heads/new");
         walker.push(r, oid);

         Git::Commit commit = NULL;
         Git::Commit branchCommit = NULL;
         QStandardItem* it = NULL;
         int numParents = 0;
         int commitNum = 0;


         QList<Git::ObjectId> branchIDs;
         //QList<Git::Commit> commitList;
         while(walker.next(r,oid))
         {
             commit = _repository.lookupCommit(r,oid);

             qDebug()<<"row count: "<<_commitModel->rowCount()<<"\n";
             it = new QStandardItem();
             it->setData(commit.shortMessage(), CommitModel::Message);
             it->setData(commit.author().name(), CommitModel::Author);
             it->setData(commit.author().when().toString("MM-dd-yyyy hh:mm ap"), CommitModel::Date);
             it->setIcon(QIcon());
             numParents = commit.numParentCommits();

//             if(numParents == 0)
//             {
//                //top parent
//             }
//             else if(numParents == 1)
//             {
//                 if(_branchModel->idToName(commit.id().toString()) != "")
//                 {
//                    //create branch
//                    qDebug()<<"create branch: "<<_branchModel->idToName(commit.id().toString());
//                    qDebug()<<"    id: " << commit.id().toString();
//                    qDebug()<<"    message: "<<commit.shortMessage()<<"\n";
//                    branchIDs.append(oid);
//                 }
//                 else
//                 {
//                     for(int i=0;i<branchIDs.count();i++)
//                     {
//                         //is current commit a parent of a branch we have found?
//                         branchCommit = _repository.lookupCommit(r,branchIDs.at(i));
//                         if(isAncestor(branchCommit,commit))
//                         //if(commit.isParentOf(r,branchCommit))
//                         {
//                             qDebug()<<"commit: "<<"\n";
//                             qDebug()<<"    message: "<<commit.shortMessage()<<"\n";
//                             qDebug()<<"    id: " << commit.id().toString();
//                             qDebug()<<"    branch:  "<<_branchModel->idToName(branchIDs.at(i).toString())<<"\n";
//                         }
//                     }


//                    //straight line
//                 }

//             }
//             else if(numParents == 2)
//             {
//                 //merge branch
//                 qDebug()<<"merge:";
//                 qDebug()<<"    message: "<<commit.shortMessage()<<"\n";
//                 qDebug()<<"    parent 1:"<<commit.parentCommit(r,0).shortMessage()<<"\n";
//                 qDebug()<<"    parent 2:"<<commit.parentCommit(r,1).shortMessage()<<"\n";
//             }
             commitNum++;
             _commitModel->appendRow(it);
              qDebug()<<"    message: "<<commit.shortMessage()<<"\n";
              qDebug()<<"    id: " << commit.id().toString();
             //qDebug()<<"parent count: "<<commit.parentCommits(r).count();

             if(!r)
             {
                 qCritical( "Failed to lookup the next object."
                                "\nGit error: %s", qPrintable( r.errorText() ) );
             }
             _commitVis += "blah blah blah ";
             //qDebug()<<_branchModel->idToName(oid.toString())<<commit.message()<<commit.author().fullName();
         }
         //_engine->rootContext()->setContextProperty("sortFilterProxyModel",_sortFilterProxyModel);
         _engine->rootContext()->setContextProperty("commitModel",_commitModel);
     }
}

QVariant GitController::loadCommitVisualization()
{
    QString s;
    if(_commitVis != "")
    {
        QString path = QApplication::applicationDirPath();
        QFile file(path+"/../../../../src/main/index.html");  //TODO:Should get this from the res dir
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&file);
            s= in.readAll();
        }
    }
    return QVariant(s);
    //return QVariant("<html><body><h1>FOOOOOOO</h1></body></html>");
}

bool GitController::isAncestor(Git::Commit &commit,Git::Commit &currentCommit)
{
    Git::Result r;
    bool result = false;
    Git::Commit parentCommit;
    for(int i=0;i<commit.numParentCommits();i++)
    {
        parentCommit = commit.parentCommits(r).at(i);

        if(parentCommit.id() == currentCommit.id() || isAncestor(parentCommit,currentCommit))
        {
            //qDebug()<<"Parent: "<<parentCommit.id()<<"current: "<<currentCommit.id()<<"\n";
            result = true;
        }
        else
        {
            result = false;
        }
    }
    return result;
}


void GitController::interceptSort(QModelIndex one, int two, int three, QModelIndex four, int five)
{
    int goo = 1;
    goo=3;
}




