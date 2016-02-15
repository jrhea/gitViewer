#ifndef GITADAPTER_H
#define GITADAPTER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>

#include <git2.h>

#define CSTR2QSTR(s, ...) QString::fromUtf8(s, ##__VA_ARGS__)
#define QSTR2CSTR(s) qPrintable(s)

/**
 * @brief The GitAdapter class is the data adapter that handles communication with git repositories
 */
class GitAdapter : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ctor
     * @param parent
     */
    explicit GitAdapter(QObject *parent = nullptr);

    ~GitAdapter();

    /**
     * @brief returns the name of the current branch
     * @return QString
     */
    QString getCurrentBranchName();

    /**
     * @brief return a list of branch names
     * @param local corresponds to libGit2's GIT_BRANCH_LOCAL
     * @param remote corresponds to libGit2's GIT_BRANCH_REMOTE (not implemented)
     * @return QStringList
     */
    QStringList getBranchNames(bool local=true, bool remote=false);

    /**
     * @brief populate a model with commits from a branch
     * @param modelSurrogate contains model data to be loaded into commitModel
     * @param branch name of the branch to load
     * @param topoSort corresponds to libGit2's GIT_SORT_TOPOLOGICAL
     * @param timeSort corresponds to libGit2's GIT_SORT_TIME
     */
    void getCommits(QList<QStringList*> *modelSurrogate, const QString &branch, bool topoSort = true, bool timeSort = true);

signals:
    /**
     * @brief triggered when the directory is changed to a valid git repo
     * @note triggered by openRepository()
     * @sa openRepository()
     */
    void repositoryChanged();
    /**
     * @brief triggered when the directory is changed to a directory that isn't a git repo
     * @note triggered by openRepository()
     * @sa openRepository()
     */
    void invalidRepository();

public slots:
    /**
     * @brief opens repo at path
     * @param path location of the repo to open
     * @note emits signals repositoryChanged() and invalidRepository()
     * @sa repositoryChanged(),invalidRepository()
     */
    void openRepository(const QString &path);


private:
    git_repository *_repo = nullptr;
};

#endif // GITADAPTER_H
