#include "branchmodel.h"

BranchModel::BranchModel(QObject * parent) : QStandardItemModel(parent)
{

}

BranchModel::BranchModel(GitAdapter * adapter, QObject * parent) : QStandardItemModel(parent)
{
    _adapter = adapter;
}

BranchModel::BranchModel(const BranchModel &)
{

}

QStandardItemModel *BranchModel::clone() const
{
    return new BranchModel(_adapter);
}

BranchModel::~BranchModel()
{

}

QHash<int, QByteArray> BranchModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";

    return roles;
}

QString BranchModel::branch() const
{
    return _branch;
}

void BranchModel::setBranch(const QString &branch)
{
    if(branch != _branch)
    {
        _branch = branch;
        //emit this->branchChanged(branch);
    }
}

void BranchModel::loadModel()
{
    this->clear();
    QStandardItem *it = NULL;
    QString branchName = _adapter->getHeadBranchName();
    QStringList branchNames = _adapter->getBranchNames(true, true);
    //add current branch first
    it = new QStandardItem();
    it->setData(branchName,BranchModel::Name);
    this->setItem(0,0,it);

    //add the rest of the branches
    for(int i=0;i<branchNames.count();i++)
    {
        if(branchNames.at(i) != branchName)
        {
            it = new QStandardItem();
            it->setData(branchNames.at(i), BranchModel::Name);
            this->setItem(i,0,it);
        }
    }
    this->setBranch(branchName);
    //emit this->modelChanged();
}


