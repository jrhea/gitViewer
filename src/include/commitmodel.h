#ifndef COMMITMODEL_H
#define COMMITMODEL_H

#include <QObject>
#include <QStandardItemModel>

#include <gitadapter.h>
/**
 * @brief The CommitModel class contains the commits for the currently selected branch
 */
class CommitModel : public QStandardItemModel
{
public:
    enum Role {
        Message=Qt::UserRole,
        Author,
        Email,
        Date,
        CommitId,
        FullMessage
    };

    /**
     * @brief ctor
     * @param parent
     */
    explicit CommitModel(QObject * parent = nullptr);

    ~CommitModel();

    /**
     * @brief creates a key value store containing roleindex (key), rolename (value)
     * @return QHash<int, QByteArray>
     */
    QHash<int, QByteArray> roleNames() const;

    /**
     * @brief creates a list of role index keys
     * @return QList<int>
     */
    QList<int> roleList() const;
};

#endif // COMMITMODEL_H
