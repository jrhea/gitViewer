#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QFileSystemModel>

class FileSystemModel: public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FileSystemModel(QObject *parent = Q_NULLPTR);

    Q_PROPERTY(QModelIndex pathIndex READ pathIndex WRITE setPathIndex)
    QModelIndex pathIndex() const;
    void setPathIndex(const QModelIndex &pathIndex);

signals:
    void pathChanged(const QString &path);

private:
    QModelIndex _index;
};

#endif // FILESYSTEMMODEL_H


