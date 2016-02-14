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
    explicit CommitController(QObject *parent = nullptr);
    explicit CommitController(QQmlApplicationEngine *engine, GitAdapter * adapter, QObject *parent=0);
    ~CommitController();

    CommitModel *getCommitModel() const;

signals:
    void modelChanged();
    void commitsLoaded();

public slots:
    void resetModel();
    void loadCommits(const QString &branch);
    void populateModel();
    void updateView();
    QString getCommit(int row,QString role);

private:
    QFutureWatcher<void> *_watcher;
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    CommitModel *_commitModel = NULL;
    QList<QStringList*> *_modelSurrogate = NULL;

};
#endif // COMMITCONTROLLER_H
