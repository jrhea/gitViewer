#include <libGitWrap/Result.hpp>
#include <libGitWrap/Tree.hpp>
#include <libGitWrap/TreeEntry.hpp>
#include <libGitWrap/TreeBuilder.hpp>
#include <libGitWrap/BranchRef.hpp>
#include <libGitWrap/Reference.hpp>
#include <libGitWrap/Index.hpp>
#include <libGitWrap/IndexEntry.hpp>
#include <libGitWrap/Repository.hpp>

#include "gitadapter.h"

GitAdapter::GitAdapter(QObject *parent) : QObject(parent)
{

}

void GitAdapter::openRepository(const QString &path)
{
    Git::Result r;
    _repository = Git::Repository::open(r,path);
    if ( !r )
    {
        qCritical( "Unable to open repository at %s."
                       "\nGit error: %s",
                       qPrintable( path ), qPrintable( r.errorText() ) );
    }
    else
    {
       emit repositoryChanged();
    }

    return;
}

QString GitAdapter::getBranchName(const QString &objectId) const
{
    QString result = "";
    return result;
}

QString GitAdapter::getHeadBranchName()
{
    QString result;
    Git::Result r;
    result = _repository.headBranchName(r);
    return result;
}

QStringList GitAdapter::getBranchNames(bool local, bool remote)
{
    QStringList result;
    Git::Result r;
    result = _repository.branchNames(r,local,remote);
    return result;
}

//void GitAdapter::getBranches(QStandardItemModel * branchModel, const QString &branch, int role, bool local, bool remote) const
//{
//    Git::Result r;
//    QStandardItem *it = NULL;
//    _branch = _repository.currentBranch(r);

//    if(r)
//    {

//        it = new QStandardItem();
//        it->setData(branch,role);
//        branchModel->setItem(0,0,it);
//    }
//}

void GitAdapter::getCommits(QStandardItemModel * commitModel, QList<int> roles,const QString &branch, bool topoSort, bool timeSort)
{
    Git::Result r;
    Git::Commit commit = NULL;
    Git::BranchRef branchRef = getBranch(branch);
    Git::ObjectId oid = branchRef.objectId();

    Git::RevisionWalker walker;
    walker = Git::RevisionWalker::create(r,_repository);
    //_commitModel->clear();

    if(r)
    {
        walker.setSorting(r,topoSort,timeSort);
        //walker.hideRef(r,"refs/heads/new");
        walker.push(r, oid);


        QStandardItem* it = NULL;
        while(walker.next(r,oid))
        {
            commit = _repository.lookupCommit(r,oid);
            it = new QStandardItem();
            it->setData(commit.shortMessage(), roles[0]);
            it->setData(commit.author().name(), roles[1]);
            it->setData(commit.author().email(), roles[2]);
            it->setData(commit.author().when().toString("MM-dd-yyyy hh:mm ap"), roles[3]);
            it->setData(commit.id().toString(), roles[4]);
            commitModel->appendRow(it);

            if(!r)
            {
                qCritical( "Failed to lookup the next object."
                               "\nGit error: %s", qPrintable( r.errorText() ) );
            }
        }
        //_engine->rootContext()->setContextProperty("commitModel",_commitModel);
    }
}

Git::BranchRef GitAdapter::getBranch(const QString &name)
{
    Git::BranchRef result = NULL;
    Git::Result r;
    result = _repository.branchRef(r,name);
    return result;
}

Git::Commit GitAdapter::getCommit(const Git::ObjectId &objectId)
{
    Git::Commit result;
    Git::Result r;
    result = _repository.lookupCommit(r,objectId);
    return result;
}


