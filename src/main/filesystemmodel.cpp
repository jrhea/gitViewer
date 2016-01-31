#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent): QFileSystemModel(parent)
{

}

QString FileSystemModel::path() const
{
    return this->filePath(_index);
}

QModelIndex FileSystemModel::index() const
{
    return _index;
}

void FileSystemModel::setIndex(const QModelIndex &index)
{
    if(index != _index)
    {
        _index = index;
        //emit indexChanged();
        emit pathChanged(this->filePath(_index));
        //emit modelChanged();
    }
}

//QString FileSystemModel::getPath(const QModelIndex &index)
//{
//    return this->filePath(index);
//}
