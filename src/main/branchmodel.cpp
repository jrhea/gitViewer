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

QList<int> BranchModel::roleList() const
{
    QList<int> result;
    for(int i=Name;i<=Name;i++)
    {
        result.append(i);
    }
    return result;
}



