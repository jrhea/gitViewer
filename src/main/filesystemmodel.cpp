#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent): QFileSystemModel(parent)
{

}

QString FileSystemModel::getPath(const QModelIndex &index)
{
    return this->filePath(index);
}
