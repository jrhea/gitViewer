#include "branchmodel.h"

BranchModel::BranchModel(QObject * parent) : QStandardItemModel(parent)
{

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



