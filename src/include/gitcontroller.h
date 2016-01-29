#ifndef GITMODEL_H
#define GITMODEL_H

#include <QFileSystemModel>
#include <QObject>
#include <QUrl>
#include <QQmlApplicationEngine>

#include <libGitWrap/Commit.hpp>
#include <libGitWrap/Repository.hpp>
#include <sortfilterproxymodel.h>

#include <branchmodel.h>
#include <commitmodel.h>

class GitController : public QObject
{
    Q_OBJECT
public:
    explicit GitController(QObject *parent = 0);
    explicit GitController(QQmlApplicationEngine *engine, QObject *parent=0);
    ~GitController();
    //Q_PROPERTY(QString selectedPath READ selectedPath WRITE selectPath NOTIFY selectedPathChanged)
    Q_PROPERTY(QString branch READ branch WRITE setBranch NOTIFY branchChanged)

    QFileSystemModel *getFileSystemModel() const;
    BranchModel *getBranchModel() const;
    CommitModel *getCommitModel() const;
    QString branch() const;

    void setBranch(const QString &branch); //called from QML

signals:
    void repositoryChanged();
    void branchChanged();

public slots:
    void loadRepository(const QModelIndex &index); //Called from QML
    void loadBranchModel();
    void loadCommitModel();
    QVariant loadCommitVisualization();
    void interceptSort(QModelIndex one, int two, int three, QModelIndex four, int five);

protected:
    bool isAncestor(Git::Commit &commit,Git::Commit &currentCommit);

private:
    QQmlApplicationEngine *_engine;
    Git::Repository _repository = NULL;
    QFileSystemModel *_fileSystemModel;
    BranchModel *_branchModel;
    CommitModel *_commitModel;
    QString _selectedPath;
    QString _branch;
    QString _commitVis;

};

#endif // GITMODEL_H
