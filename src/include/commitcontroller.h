#ifndef COMMITCONTROLLER_H
#define COMMITCONTROLLER_H
#include <QObject>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QThread>
#include <QFutureWatcher>
#include <qtconcurrentrun.h>

#include "commitmodel.h"

class CommitController : public QObject
{
    Q_OBJECT
public:
    explicit CommitController(QObject *parent = 0);
    explicit CommitController(QQmlApplicationEngine *engine, GitAdapter * adapter, QObject *parent=0);
    ~CommitController();

    CommitModel *getCommitModel() const;

signals:
    void modelChanged();

public slots:
    void resetModel();
    void loadModel(const QString &branch);
    void updateCommitView();
    QString getCommit(int row,QString role);
    QString searchCommits(QString query,int role);


private:
    QFutureWatcher<void> *_watcher;
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    CommitModel *_commitModel = NULL;

};
#endif // COMMITCONTROLLER_H
