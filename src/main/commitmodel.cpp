#include "commitmodel.h"

CommitModel::CommitModel(QObject * parent): QStandardItemModel(parent)
{

}

CommitModel::CommitModel(GitAdapter *adapter, QObject * parent): QStandardItemModel(parent)
{
    _adapter = adapter;
}

CommitModel::CommitModel(const CommitModel &)
{

}

CommitModel::~CommitModel()
{

}

QStandardItemModel *CommitModel::clone() const
{
     return new CommitModel(_adapter);
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

void CommitModel::loadModel(const QString &branch)
{
    this->clear();
    QList<int> roles;
    roles.append(Message);
    roles.append(Author);
    roles.append(Email);
    roles.append(Date);
    roles.append(CommitId);
    _adapter->getCommits(this,roles,branch,true,true);
    //emit this->modelChanged();
}

