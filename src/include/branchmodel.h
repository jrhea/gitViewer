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
    explicit BranchModel(GitAdapter * adapter, QObject * parent = 0);
    explicit BranchModel(const BranchModel&);
    virtual QStandardItemModel *clone() const;
    ~BranchModel();
    //Q_PROPERTY(QString branch READ branch WRITE setBranch NOTIFY branchChanged)
    QHash<int, QByteArray> roleNames() const;

    QString branch() const;
    void setBranch(const QString &branch);

    void loadModel();

signals:
    //void branchChanged(const QString &branch);
    //void modelChanged();

public slots:
    //void loadModel();

private:
    GitAdapter *_adapter;
    QString _branch;
};
Q_DECLARE_METATYPE(BranchModel)
#endif // GITBRANCHMODEL_H
