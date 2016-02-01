#ifndef GITMODEL_H
#define GITMODEL_H

#include <QFileSystemModel>
#include <QObject>
#include <QUrl>
#include <QQmlApplicationEngine>
#include <QThread>
#include <qtconcurrentrun.h>

#include <sortfilterproxymodel.h>

#include <gitadapter.h>
#include <filesystemmodel.h>
#include <branchcontroller.h>
#include <commitcontroller.h>

class GitViewer : public QObject
{
    Q_OBJECT
public:

    explicit GitViewer(QQmlApplicationEngine *engine, QObject *parent=0);

    ~GitViewer();

    FileSystemModel *getFileSystemModel() const;
    BranchController *getBranchController() const;
    CommitController *getCommitController() const;

    void loadModelAsync(const QString &foo = 0);

signals:

public slots:
    void setPath(const QString &path);

private:
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    QString _path;
    FileSystemModel *_fileSystemModel = NULL;
    BranchController *_branchController = NULL;
    CommitController *_commitController = NULL;


};

#endif // GITMODEL_H
