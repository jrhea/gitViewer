#ifndef GITADAPTER_H
#define GITADAPTER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>

#include <git2.h>

#define CSTR2QSTR(s, ...) QString::fromUtf8(s, ##__VA_ARGS__)
#define QSTR2CSTR(s) qPrintable(s)


class GitAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GitAdapter(QObject *parent = nullptr);
    ~GitAdapter();

    QString getCurrentBranchName();
    QStringList getBranchNames(bool local=true, bool remote=false);

    void getCommits(QList<QStringList*> *modelSurrogate, const QString &branch, bool topoSort = true, bool timeSort = true);

signals:
    void repositoryChanged();
    void invalidRepository();

public slots:
    void openRepository(const QString &path);


private:
    git_repository *_repo = nullptr;
};

#endif // GITADAPTER_H
