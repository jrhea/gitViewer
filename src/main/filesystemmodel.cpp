#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent): QFileSystemModel(parent)
{

}

QModelIndex FileSystemModel::pathIndex() const
{
    return _index;
}

void FileSystemModel::setPathIndex(const QModelIndex &index)
{
    if(index != _index)
    {
        _index = index;
        emit pathChanged(this->filePath(_index));
    }
}
