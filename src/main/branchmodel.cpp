#include "branchmodel.h"

BranchModel::BranchModel(QObject *parent) : QStandardItemModel(parent)
{
}

BranchModel::BranchModel( int rows, int columns, QObject * parent): QStandardItemModel(rows, columns, parent)
{
}

QHash<int, QByteArray> BranchModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "name";

    return roles;
}


