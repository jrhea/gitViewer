#ifndef BRANCHCONTROLLER_H
#define BRANCHCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QThread>
#include <QFutureWatcher>
#include <qtconcurrentrun.h>

#include "branchmodel.h"
#include "gitadapter.h"

/**
 * @brief The BranchController class is the BranchModel's controller class
 *
 * Responsibilities:
 * - binds the model to the view
 * - handles signals from the view
 * - updates the model
 */
class BranchController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ctor
     * @param parent
     */
    explicit BranchController(QObject *parent = nullptr);
    /**
     * @brief ctor
     * @param engine
     * @param adapter
     * @param parent
     */
    explicit BranchController(QQmlApplicationEngine *engine, GitAdapter * adapter, QObject *parent=nullptr);

    ~BranchController();

    Q_PROPERTY(QString branch READ branch WRITE setBranch NOTIFY branchChanged)

    /**
     * @brief returns the branch model object
     * @return BranchModel
     */
    BranchModel *getBranchModel() const;

    /**
     * @brief name of the branch that the commit model represents
     * @return QString
     */
    QString branch() const;

    /**
     * @brief updates what branch the commit model represents
     * @param branch name of the branch to load
     * @note emits signal branchChanged()
     *
     * Called from QML and C++
     * @sa branchChanged()
     */
    void setBranch(const QString &branch);

signals:
    /**
     * @brief triggered when the branch has been changed
     * @param branch the name of the branch currently viewed
     * @note emitted by setBranch()
     * @sa setBranch()
     */
    void branchChanged(const QString &branch);

    /**
     * @brief triggered when data adapter has new data to be loaded into the model
     * @note emitted by loadBranches()
     * @sa loadBranches()
     */
    void branchesLoaded();

    /**
     * @brief triggered when the model changes
     * @note emitted by resetModel() and populateModal()
     * @sa resetModel(),populateModal()
     */
    void modelChanged();

public slots:
    /**
     * @brief restores the model to the initial state
     */
    void resetModel();

    /**
     * @brief load branches
     * @note emits signal branchesLoaded()
     * @sa branchesLoaded()
     */
    void loadBranches();

    /**
     * @brief populates the branch model
     * @note emits modelChanged() signal
     * @sa modelChanged()
     */
    void populateModel();

    /**
     * @brief updates the branch view with model
     */
    void updateView();

private:
    QFutureWatcher<QStringList> *_watcher;
    QQmlApplicationEngine *_engine;
    GitAdapter *_adapter;
    BranchModel *_branchModel;
    QString _branch;

};

#endif // BRANCHCONTROLLER_H
