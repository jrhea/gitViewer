#ifndef GITADAPTER_H
#define GITADAPTER_H

#include <QObject>
#include <QStandardItemModel>

#include <libGitWrap/Commit.hpp>
#include <libGitWrap/Repository.hpp>

class GitAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GitAdapter(QObject *parent = 0);


    QString getBranchName(const QString &objectId) const;
    QString getHeadBranchName();
    //Returns all local and remote branch names
    QStringList getBranchNames(bool local, bool remote);

   // void getBranches(QStandardItemModel * branchModel, const QString &branch, int role, bool local, bool remote) const;
    void getCommits(QStandardItemModel * commitModel, QList<int> roles, const QString &branch, bool topoSort, bool timeSort);

signals:
    void repositoryChanged();
public slots:
    void openRepository(const QString &path);

protected:
    Git::BranchRef getBranch(const QString &name);
    Git::Commit getCommit(const Git::ObjectId &objectId);

private:
    Git::Repository _repository = NULL;
};

#endif // GITADAPTER_H
