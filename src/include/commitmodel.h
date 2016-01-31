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
    explicit CommitModel(GitAdapter * adapter, QObject * parent = 0);
    explicit CommitModel(const CommitModel&);
    ~CommitModel();
    virtual QStandardItemModel *clone() const;
    QHash<int, QByteArray> roleNames() const;

    void loadModel(const QString &branch);
signals:
     //void modelChanged();

public slots:
    //void loadModel(const QString &branch);

private:
     GitAdapter *_adapter;

};
Q_DECLARE_METATYPE(CommitModel)

#endif // COMMITMODEL_H
