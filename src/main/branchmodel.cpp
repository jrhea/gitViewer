#include "branchmodel.h"

BranchModel::BranchModel(QObject * parent) : QStandardItemModel(parent)
{

}

BranchModel::~BranchModel()
{

}

/**
 * @brief CommitModel::roleNames - creates a key value store containing roleindex (key), rolename (value)
 * @return QHash<int, QByteArray>
 */
QHash<int, QByteArray> BranchModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";

    return roles;
}

/**
 * @brief BranchModel::roleList - creates a list of role index keys
 * @return QList<int>
 */
QList<int> BranchModel::roleList() const
{
    QList<int> result;
    for(int i=Name;i<=Name;i++)
    {
        result.append(i);
    }
    return result;
}



