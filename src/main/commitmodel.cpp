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
    roles[FullMessage] = "fullmessage";
    return roles;
}

QList<int> CommitModel::roleList() const
{
    QList<int> result;
    for(int i=Message;i<=FullMessage;i++)
    {
        result.append(i);
    }
    return result;
}

