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
}

/**
 * @brief CommitController::getCommitModel - returns the model object
 * @return CommitModel
 */
CommitModel *CommitController::getCommitModel() const
{
    return _commitModel;
}

/**
 * @brief CommitController::resetModel - clears model
 * @signal modelChanged()
 */
void CommitController::resetModel()
{
    _commitModel->clear();
    emit this->modelChanged();
}

/**
 * @brief CommitController::loadCommits - load commits from branch
 * @param branch - name of the branch to load
 * @signal commitsLoaded()
 */
void CommitController::loadCommits(const QString &branch)
{
    _commitModel->clear();
    QFuture<void> gitter;
    connect(_watcher,SIGNAL(finished()),this,SIGNAL(commitsLoaded()),Qt::UniqueConnection);
    gitter = QtConcurrent::run(this->_adapter,&GitAdapter::getCommits,_modelSurrogate,branch,true,true);
    _watcher->setFuture(gitter);
}

/**
 * @brief CommitController::populateModel - populates model with commits from branch
 * @signal modelChanged()
 */
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

/**
 * @brief CommitController::updateView - updates the commit view with model
 */
void CommitController::updateView()
{
    _engine->rootContext()->setContextProperty("commitModel",_commitModel);
}

/**
 * @brief CommitController::getCommit - updates commit view (detail) with individual model properties
 * @param row - identifies an item in the model collection
 * @param role - identifies the property in the model item
 * @return QString
 */
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
