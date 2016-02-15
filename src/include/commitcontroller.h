#ifndef COMMITCONTROLLER_H
#define COMMITCONTROLLER_H
#include <QObject>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QThread>
#include <QFutureWatcher>
#include <qtconcurrentrun.h>

#include "commitmodel.h"
#include <gitadapter.h>

/**
 * @brief The CommitController class is the CommitModel's controller class
 *
 * Responsibilities:
 * - binds the model to the view
 * - handles signals from the view
 * - updates the model
 */
class CommitController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ctor
     * @param parent
     */
    explicit CommitController(QObject *parent = nullptr);

    /**
     * @brief ctor
     * @param engine
     * @param adapter
     * @param parent
     */
    explicit CommitController(QQmlApplicationEngine *engine, GitAdapter * adapter, QObject *parent=0);

    ~CommitController();

    /**
     * @brief returns the model object
     * @return CommitModel
     */
    CommitModel *getCommitModel() const;

signals:
    /**
     * @brief triggered when the model changes
     * @note emitted by resetModel() and populateModel()
     * @sa resetModel(), populateModel()
     */
    void modelChanged();

    /**
     * @brief triggered when data adapter has new data to be loaded into the model
     * @note emitted by loadCommits()
     * @sa loadCommits()
     */
    void commitsLoaded();

public slots:
    /**
     * @brief restores the model to the initial state
     * @sa modelChanged()
     */
    void resetModel();

    /**
     * @brief load commits from branch
     * @param branch name of the branch to load
     * @note emits signal commitsLoaded()
     * @sa commitsLoaded()
     */
    void loadCommits(const QString &branch);

    /**
     * @brief populates model with commits from branch
     * @note emits signal modelChanged()
     * @sa modelChanged()
     */
    void populateModel();

    /**
     * @brief updates the commit view with model
     */
    void updateView();

    /**
     * @brief updates commit view (detail) with individual model properties
     * @param row identifies an item in the model collection
     * @param role identifies the property in the model item
     * @note called from QML
     * @return QString
     */
    QString getCommit(int row,QString role);

private:
    QFutureWatcher<void> *_watcher;
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    CommitModel *_commitModel;
    QList<QStringList*> *_modelSurrogate;

};
#endif // COMMITCONTROLLER_H
