#ifndef BRANCHCONTROLLER_H
#define BRANCHCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QUrl>

#include "branchmodel.h"

class BranchController : public QObject
{
    Q_OBJECT
public:
    explicit BranchController(QObject *parent = 0);
    explicit BranchController(QQmlApplicationEngine *engine, GitAdapter * adapter, QObject *parent=0);

    ~BranchController();

    Q_PROPERTY(QString branch READ branch WRITE setBranch NOTIFY branchChanged)

    BranchModel *getBranchModel() const;


    QString branch() const;
    void setBranch(const QString &branch);

signals:
    void branchChanged(const QString &branch);
    void modelChanged();

public slots:
    void loadModel();
    void updateBranchView();


private:
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    BranchModel *_branchModel = NULL;
    QString _branch;

};

#endif // BRANCHCONTROLLER_H
