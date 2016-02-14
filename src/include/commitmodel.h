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
        CommitId,
        FullMessage
    };
    explicit CommitModel(QObject * parent = nullptr);
    ~CommitModel();
    QHash<int, QByteArray> roleNames() const;
    QList<int> roleList() const;
};

#endif // COMMITMODEL_H
