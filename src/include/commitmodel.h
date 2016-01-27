#ifndef COMMITMODEL_H
#define COMMITMODEL_H

#include <QObject>
#include <QStandardItemModel>


class CommitModel : public QStandardItemModel
{
public:
    enum Role {
        Message=Qt::UserRole,
        Author,
        Date,
    };
    explicit CommitModel(QObject * parent = 0);
    explicit CommitModel( int rows, int columns, QObject * parent = 0 );
    QHash<int, QByteArray> roleNames() const;

};

#endif // COMMITMODEL_H
