#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject *parent): QFileSystemModel(parent)
{

}

/**
 * @brief FileSystemModel::pathIndex - returns the currently selected path index
 * @return QModelIndex
 */
QModelIndex FileSystemModel::pathIndex() const
{
    return _index;
}


/**
 * @brief FileSystemModel::setPathIndex - changes the the currently selected path
 * @param index - represents the path that was selected
 * @signal pathChanged(QString)
 */
void FileSystemModel::setPathIndex(const QModelIndex &index)
{
    if(index != _index)
    {
        _index = index;
        emit pathChanged(this->filePath(_index));
    }
}
