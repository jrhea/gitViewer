#ifndef GITADAPTER_H
#define GITADAPTER_H

#include <QObject>
#include <QString>
#include <QStandardItemModel>

#include <git2.h>

#define CSTR2QSTR(s, ...) QString::fromUtf8(s, ##__VA_ARGS__)
#define QSTR2CSTR(s) qPrintable(s)


class GitAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GitAdapter(QObject *parent = 0);
    ~GitAdapter();

    QString getCurrentBranchName();
    //Returns all local and remote branch names
    QStringList getBranchNames(bool local, bool remote);

    void getCommits(QStandardItemModel * commitModel, QList<int> roles, const QString &branch, bool topoSort, bool timeSort);

signals:
    void repositoryChanged();
    void invalidRepository();
public slots:
    void openRepository(const QString &path);

protected:
 //   Git::BranchRef getBranch(const QString &name);
 //   Git::Commit getCommit(const Git::ObjectId &objectId);

private:
   // Git::Repository _repository = NULL;
    git_repository *_repo = NULL;
};

#endif // GITADAPTER_H
