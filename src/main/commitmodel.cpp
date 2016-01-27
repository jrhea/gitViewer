#include "commitmodel.h"

CommitModel::CommitModel(QObject * parent): QStandardItemModel(parent)
{
}

CommitModel::CommitModel( int rows, int columns, QObject * parent): QStandardItemModel(rows, columns, parent)
{
}

QHash<int, QByteArray> CommitModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Message] = "message";
    roles[Author] = "author";
    roles[Date] = "date";

    return roles;
}

