#ifndef GITMODEL_H
#define GITMODEL_H

#include <QFileSystemModel>
#include <QObject>
#include <QUrl>
#include <QQmlApplicationEngine>

#include <sortfilterproxymodel.h>

#include <gitadapter.h>
#include <filesystemmodel.h>
#include <branchmodel.h>
#include <commitmodel.h>

class GitController : public QObject
{
    Q_OBJECT
public:
    explicit GitController(QObject *parent = 0);
    explicit GitController(QQmlApplicationEngine *engine, QObject *parent=0);

    ~GitController();

    Q_PROPERTY(QString branch READ branch WRITE setBranch NOTIFY branchChanged)

    FileSystemModel *getFileSystemModel() const;
    BranchModel *getBranchModel() const;
    CommitModel *getCommitModel() const;

//    QString path() const;
    QString branch() const;

//    void setPath(const QString &path);
    void setBranch(const QString &branch);

signals:
    void branchChanged(const QString &branch);
    void branchModelChanged();
    void commitModelChanged();
//    void pathChanged();
//    void repositoryChanged();
//    void branchChanged();

public slots:
    void loadRepository();
    void loadBranchModel();
    void loadCommitModel(const QString &branch);
    void updateBranchView();
    void updateCommitView();
    QString getCommitInfo(int index,QString role);


private:
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    FileSystemModel *_fileSystemModel = NULL;
    BranchModel *_branchModel = NULL;
    CommitModel *_commitModel = NULL;
//    QString _path;
//    QString _branch;

};

#endif // GITMODEL_H
