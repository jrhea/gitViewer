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
    _modelSurrogate = new QList<QStringList*>();
    updateView();
}

CommitController::~CommitController()
{
    delete _commitModel;
    delete _modelSurrogate;
    delete _watcher;
}

CommitModel *CommitController::getCommitModel() const
{
    return _commitModel;
}

void CommitController::resetModel()
{
    _commitModel->clear();
    emit this->modelChanged();
}

void CommitController::loadCommits(const QString &branch)
{
    _commitModel->clear();
    QFuture<void> gitter;
    connect(_watcher,SIGNAL(finished()),this,SIGNAL(commitsLoaded()),Qt::UniqueConnection);
    gitter = QtConcurrent::run(this->_adapter,&GitAdapter::getCommits,_modelSurrogate,branch,true,true);
    _watcher->setFuture(gitter);
}

void CommitController::populateModel()
{
    QStandardItem *item=nullptr;
    QList<int> roles = _commitModel->roleList();

    for(int i=0;i<_modelSurrogate->count();i++)
    {
        item = new QStandardItem();
        for(int j=0;j<_modelSurrogate->at(i)->count();j++)
        {
            item->setData(_modelSurrogate->at(i)->at(j),roles[j]);
        }
        _commitModel->appendRow(item);
        _modelSurrogate->at(i)->clear();
        delete(_modelSurrogate->at(i));
    }
    _modelSurrogate->clear();
    emit this->modelChanged();
}

void CommitController::updateView()
{
    _engine->rootContext()->setContextProperty("commitModel",_commitModel);
}

QString CommitController::getCommit(int row, QString role)
{
    QString result;
    if(_commitModel != nullptr)
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
