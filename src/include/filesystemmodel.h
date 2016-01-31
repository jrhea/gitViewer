#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QFileSystemModel>

class FileSystemModel: public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FileSystemModel(QObject *parent = Q_NULLPTR);

    Q_PROPERTY(QModelIndex index READ index WRITE setIndex NOTIFY indexChanged)
    QString path() const;
    QModelIndex index() const;
    void setIndex(const QModelIndex &index);

signals:
    void indexChanged();
    void pathChanged(const QString &path);

public slots:
    //QString getPath(const QModelIndex &index);

private:
    QModelIndex _index;
};

#endif // FILESYSTEMMODEL_H


