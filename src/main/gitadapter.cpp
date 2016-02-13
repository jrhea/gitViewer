#include <stdio.h>
#include <QDateTime>

#include "gitadapter.h"


GitAdapter::GitAdapter(QObject *parent) : QObject(parent)
{
    git_libgit2_init();
}

GitAdapter::~GitAdapter()
{
    git_repository_free(_repo);
    git_libgit2_shutdown();
}

void GitAdapter::openRepository(const QString &path)
{
    int git_result = git_repository_open(&_repo,QSTR2CSTR(path));
    if(git_result != 0)
    {
        const git_error *e = giterr_last();
        printf("Error %d/%d: %s\n", git_result, e->klass, e->message);
        emit invalidRepository();
    }
    else
    {
        emit repositoryChanged();
    }
    return;
}

QString GitAdapter::getCurrentBranchName()
{
    QString result;
    git_reference* ref = NULL;
    git_repository_head( &ref, _repo );
    result = CSTR2QSTR(git_reference_shorthand(ref));
    git_reference_free(ref);
    return result;
}

QStringList GitAdapter::getBranchNames(bool local, bool remote)
{
    QStringList result;
    git_branch_t type;
    git_reference* ref;
    int git_result;
    QString name;
    int flags = 0;
    git_branch_iterator* iter = nullptr;

    if (local) flags |= GIT_BRANCH_LOCAL;
    if (remote)flags |= GIT_BRANCH_REMOTE;

    if (git_branch_iterator_new(&iter, _repo, static_cast<git_branch_t>(flags)) == GITERR_NONE)
    {
        while ( (git_result = git_branch_next(&ref, &type, iter)) == GITERR_NONE)
        {
            Q_ASSERT(ref);

            name = CSTR2QSTR(git_reference_shorthand(ref));
            result << name;

            git_reference_free(ref);
            ref = nullptr;
        }

        if (git_result != GIT_ITEROVER)
        {
            result = QStringList();
        }
    }
    return result;
}

void GitAdapter::getCommits(QStandardItemModel * commitModel, QList<int> roles, const QString &branch, bool topoSort, bool timeSort)
{
    int git_result;
    int msg_len;
    const char *message;

    const git_signature *committer;
    git_revwalk *walker;
    git_reference *ref;
    git_commit *commit;
    git_oid oid;

    QStandardItem* it;
    QString refname;

    git_result = git_revwalk_new(&walker, _repo);
    if(git_result == 0)
    {
        //git_revwalk_sorting(walker,  GIT_SORT_TOPOLOGICAL | GIT_SORT_TIME);
        git_result = git_reference_dwim(&ref, _repo, QSTR2CSTR(branch));
        refname = CSTR2QSTR(git_reference_name(ref));
        git_reference_lookup(&ref, _repo, QSTR2CSTR(refname));

        oid = *git_reference_target(ref);
        git_revwalk_push(walker, &oid);

        while(git_revwalk_next(&oid, walker) == 0)
        {
            if(git_commit_lookup(&commit, _repo, &oid))
            {
                qCritical("Failed to lookup the next object\n",stderr);
                break;
            }

            it = new QStandardItem();

            message = git_commit_message(commit);
            for (msg_len=0;message[msg_len] && message[msg_len] != '\n';msg_len++){}
            it->setData(CSTR2QSTR(message,msg_len), roles[0]);

            committer = git_commit_committer(commit);
            it->setData(committer->name, roles[1]);
            it->setData(committer->email, roles[2]);

            QDateTime commitTime = QDateTime::fromTime_t(committer->when.time);
            commitTime.setUtcOffset(committer->when.offset * 60);
            it->setData(commitTime.toString("MM-dd-yyyy hh:mm ap"), roles[3]);

            QByteArray id(GIT_OID_HEXSZ+1, 0);
            git_oid_tostr(id.data(), GIT_OID_HEXSZ+1, &oid);
            it->setData(CSTR2QSTR(id.data()), roles[4]);

            it->setData(CSTR2QSTR(message), roles[5]);

            commitModel->appendRow(it);

            git_commit_free(commit);
        }

        git_revwalk_free(walker);
    }
    return;
}


