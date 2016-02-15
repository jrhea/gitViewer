#include <QQmlContext>
#include <QApplication>

#include "branchcontroller.h"

using namespace QtConcurrent;

BranchController::BranchController(QObject *parent) : QObject(parent)
{

}

BranchController::BranchController(QQmlApplicationEngine *engine, GitAdapter *adapter, QObject *parent) : QObject(parent)
{
    _watcher  = new QFutureWatcher<QStringList>();
    _engine = engine;
    _adapter = adapter;
    _branchModel = new BranchModel();
    updateView();
}

BranchController::~BranchController()
{
    delete _watcher;
    delete _branchModel;
}

BranchModel *BranchController::getBranchModel() const
{
    return _branchModel;
}

QString BranchController::branch() const
{
    return _branch;
}

void BranchController::setBranch(const QString &branch)
{
    if(branch != _branch)
    {
        _branch = branch;
        emit this->branchChanged(branch);
    }
}

void BranchController::resetModel()
{
    _branchModel->clear();
    _branch = QString();
}

void BranchController::loadBranches()
{
    QFuture<QStringList> gitter;
    connect(_watcher,SIGNAL(finished()),this,SIGNAL(branchesLoaded()),Qt::UniqueConnection);
    gitter = QtConcurrent::run(this->_adapter,&GitAdapter::getBranchNames,true,false);
    _watcher->setFuture(gitter);
}


void BranchController::populateModel()
{
    resetModel();
    QString currentBranchName = _adapter->getCurrentBranchName();
    QStringList branchNames = _watcher->future().result();
    QStandardItem *item = new QStandardItem();

    item->setData(currentBranchName,BranchModel::Name);
    _branchModel->setItem(0,0,item);

    for(int i=0;i<branchNames.count();i++)
    {
        if(branchNames.at(i) != currentBranchName)
        {
            item = new QStandardItem();
            item->setData(branchNames.at(i), BranchModel::Name);
            _branchModel->appendRow(item);
        }
    }

    this->setBranch(currentBranchName);
    emit this->modelChanged();
}

void BranchController::updateView()
{
    _engine->rootContext()->setContextProperty("branchModel",_branchModel);
}
