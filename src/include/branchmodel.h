#ifndef GITBRANCHMODEL_H
#define GITBRANCHMODEL_H

#include <QObject>
#include <QStandardItemModel>

#include <gitadapter.h>

class BranchModel : public QStandardItemModel
{
public:
    enum Role {
        Name=Qt::UserRole,
    };
    explicit BranchModel(QObject * parent = 0);
    ~BranchModel();
    QHash<int, QByteArray> roleNames() const;


};

#endif // GITBRANCHMODEL_H
