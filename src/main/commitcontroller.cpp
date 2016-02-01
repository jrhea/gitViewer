#include <QQmlContext>
#include <QApplication>

#include "commitcontroller.h"

using namespace QtConcurrent;

CommitController::CommitController(QObject *parent) : QObject(parent)
{

}

CommitController::CommitController(QQmlApplicationEngine *engine, GitAdapter *adapter, QObject *parent) : QObject(parent)
{
    _watcher  = new QFutureWatcher<void>();
    _engine = engine;
    _adapter = adapter;
    _commitModel = new CommitModel();
}

CommitController::~CommitController()
{
    delete _commitModel;
}

CommitModel *CommitController::getCommitModel() const
{
    return _commitModel;
}

void CommitController::loadModel(const QString &branch)
{
    _commitModel->clear();
    QList<int> roles;
    roles.append(CommitModel::Message);
    roles.append(CommitModel::Author);
    roles.append(CommitModel::Email);
    roles.append(CommitModel::Date);
    roles.append(CommitModel::CommitId);

//    QFuture<void> gitter;
//    connect(_watcher,SIGNAL(finished()),this,SIGNAL(modelChanged()));
//    gitter = QtConcurrent::run(_adapter,&GitAdapter::getCommits,_commitModel,roles,branch,true,true);
//    _watcher->setFuture(gitter);
    _adapter->getCommits(_commitModel,roles,branch,true,true);
    emit this->modelChanged();
}

void CommitController::updateCommitView()
{
    _engine->rootContext()->setContextProperty("commitModel",_commitModel);
}

QString CommitController::getCommit(int row, QString role)
{
    QString result;
    if(_commitModel != NULL)
    {

        QHash<int, QByteArray> roles = _commitModel->roleNames();
        QHashIterator<int, QByteArray> it(roles);
        while (it.hasNext()) {
            it.next();
            if(it.value() == role)
            {
                QModelIndex modelIndex = _commitModel->index(row,0);
                result = _commitModel->data(modelIndex, it.key()).toString();
                break;
            }
        }
    }
    return result;
}

QString CommitController::searchCommits(QString query, int role)
{
    QString result;
    QHash<int, QByteArray> roles = _commitModel->roleNames();
    int numCommits = _commitModel->rowCount();
    for(int i=0;i<numCommits;i++)
    {
        QModelIndex modelIndex = _commitModel->index(i,0);
        //result = _commitModel->data(modelIndex, roles[role]).toString();
        if(result == query)
        {

        }
    }
    return result;


}
