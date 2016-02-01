#ifndef COMMITMODEL_H
#define COMMITMODEL_H

#include <QObject>
#include <QStandardItemModel>

#include <gitadapter.h>

class CommitModel : public QStandardItemModel
{
public:
    enum Role {
        Message=Qt::UserRole,
        Author,
        Email,
        Date,
        CommitId
    };
    explicit CommitModel(QObject * parent = 0);
    ~CommitModel();
    QHash<int, QByteArray> roleNames() const;
};

#endif // COMMITMODEL_H
