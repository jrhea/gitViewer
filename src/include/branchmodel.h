#ifndef GITBRANCHMODEL_H
#define GITBRANCHMODEL_H

#include <QObject>
#include <QStandardItemModel>

#include <gitadapter.h>
/**
 * @brief The BranchModel class contains the branches for the current repository.
 */
class BranchModel : public QStandardItemModel
{
public:
    enum Role {
        Name=Qt::UserRole,
    };
    /**
     * @brief ctor
     * @param parent
     */
    explicit BranchModel(QObject * parent = nullptr);

    ~BranchModel();

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

#endif // GITBRANCHMODEL_H
