#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QFileSystemModel>
/**
 * @brief The FileSystemModel class represents the filesystem
 */
class FileSystemModel: public QFileSystemModel
{
    Q_OBJECT
public:
    /**
     * @brief ctor
     * @param parent
     */
    explicit FileSystemModel(QObject *parent = Q_NULLPTR);

    Q_PROPERTY(QModelIndex pathIndex READ pathIndex WRITE setPathIndex)

    /**
     * @brief returns the currently selected path index
     * @note called by QML
     * @return QModelIndex
     */
    QModelIndex pathIndex() const;

    /**
     * @brief changes the the currently selected path
     * @param pathIndex represents the path that was selected
     * @note emits pathChanged() signal
     * @sa pathChanged()
     */
    void setPathIndex(const QModelIndex &pathIndex);

signals:
    /**
     * @brief triggered after the path index has been changed
     * @param path represents the new directory location selected
     * @note emmitted by setPathIndex()
     */
    void pathChanged(const QString &path);

private:
    QModelIndex _index;
};

#endif // FILESYSTEMMODEL_H


