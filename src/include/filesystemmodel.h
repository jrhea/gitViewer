#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QFileSystemModel>

class FileSystemModel: public QFileSystemModel
{
    Q_OBJECT
public:
    explicit FileSystemModel(QObject *parent = Q_NULLPTR);

public slots:
    QString getPath(const QModelIndex &index);
};

#endif // FILESYSTEMMODEL_H


