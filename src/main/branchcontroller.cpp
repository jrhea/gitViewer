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

/**
 * @brief BranchController::getBranchModel - returns the branch model object
 * @return BranchModel
 */
BranchModel *BranchController::getBranchModel() const
{
    return _branchModel;
}

/**
 * @brief BranchController::branch - name of the branch that the commit model represents
 * @return QString
 */
QString BranchController::branch() const
{
    return _branch;
}

/**
 * @brief BranchController::setBranch - updates what branch the commit model represents
 * @param branch - name of the branch to load
 * @signal branchChanged(QString)
 */
void BranchController::setBranch(const QString &branch)
{
    if(branch != _branch)
    {
        _branch = branch;
        emit this->branchChanged(branch);
    }
}

/**
 * @brief BranchController::resetModel - clears the branch model
 * @signal modelChanged()
 */
void BranchController::resetModel()
{
    _branchModel->clear();
    _branch = QString();
    emit this->modelChanged();
}

/**
 * @brief BranchController::loadModel - populates the branch model
 * @signal modelChanged
 */
void BranchController::loadModel()
{
    this->resetModel();
    QString currentBranchName = _adapter->getCurrentBranchName();
    QStringList branchNames = _adapter->getBranchNames();
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

/**
 * @brief BranchController::updateView - updates the branch view with model
 */
void BranchController::updateView()
{
    _engine->rootContext()->setContextProperty("branchModel",_branchModel);
}
