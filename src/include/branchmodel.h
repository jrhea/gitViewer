#ifndef GITBRANCHMODEL_H
#define GITBRANCHMODEL_H

#include <QObject>
#include <QStringList>
#include <QStringListModel>

class BranchModel : public QStringListModel
{
    Q_OBJECT
public:
    explicit BranchModel(QObject *parent = 0);
    ~BranchModel();
    void loadModel(QStringList,QStringList);
    QStringList getNames();
    QStringList getIds();
    QString idToName(QString);
    QString nameToId(QString);
signals:

public slots:
    QString getBranch(int index) const;

private:
    QHash<QString,QString> *_nameToId;
    QHash<QString,QString> *_idToName;
    QStringList *_ids;
};

#endif // GITBRANCHMODEL_H
