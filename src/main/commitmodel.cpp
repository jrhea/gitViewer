#include "commitmodel.h"

CommitModel::CommitModel(QObject * parent): QStandardItemModel(parent)
{

}

CommitModel::~CommitModel()
{

}

QHash<int, QByteArray> CommitModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Message] = "message";
    roles[Author] = "author";
    roles[Email] = "email";
    roles[Date] = "date";
    roles[CommitId] = "commitId";

    return roles;
}

