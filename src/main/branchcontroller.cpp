#include <QQmlContext>
#include <QApplication>

#include "branchcontroller.h"

BranchController::BranchController(QObject *parent) : QObject(parent)
{

}

BranchController::BranchController(QQmlApplicationEngine *engine, GitAdapter *adapter, QObject *parent) : QObject(parent)
{
    _engine = engine;
    _adapter = adapter;
    _branchModel = new BranchModel();
}

BranchController::~BranchController()
{
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

void BranchController::loadModel()
{
    _branchModel->clear();
    QStandardItem *it = NULL;
    QString branchName = _adapter->getHeadBranchName();
    QStringList branchNames = _adapter->getBranchNames(true, false);
    //add current branch first
    it = new QStandardItem();
    it->setData(branchName,BranchModel::Name);
    _branchModel->setItem(0,0,it); //load the head as the first item

    //add the rest of the branches
    for(int i=0;i<branchNames.count();i++)
    {
        if(branchNames.at(i) != branchName)
        {
            it = new QStandardItem();
            it->setData(branchNames.at(i), BranchModel::Name);
            _branchModel->setItem(i+1,0,it);  //+1 to avoid overiding head in the first position
        }
    }
    this->setBranch(branchName);
    emit this->modelChanged();
}

void BranchController::updateBranchView()
{
    _engine->rootContext()->setContextProperty("branchModel",_branchModel);
}
