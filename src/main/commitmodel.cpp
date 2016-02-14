#include "commitmodel.h"

CommitModel::CommitModel(QObject * parent): QStandardItemModel(parent)
{

}

CommitModel::~CommitModel()
{

}

/**
 * @brief CommitModel::roleNames - creates a key value store containing roleindex (key), rolename (value)
 * @return QHash<int, QByteArray>
 */
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

/**
 * @brief BranchModel::roleList - creates a list of role index keys
 * @return QList<int>
 */
QList<int> CommitModel::roleList() const
{
    QList<int> result;
    for(int i=Message;i<=FullMessage;i++)
    {
        result.append(i);
    }
    return result;
}

