#ifndef GITBRANCHMODEL_H
#define GITBRANCHMODEL_H

#include <QObject>
#include <QStandardItemModel>

class BranchModel : public QStandardItemModel
{
public:
    enum Role {
        Name=Qt::UserRole,
    };
    explicit BranchModel(QObject *parent = 0);
    explicit BranchModel( int rows, int columns, QObject * parent = 0 );
    QHash<int, QByteArray> roleNames() const;
};

#endif // GITBRANCHMODEL_H
