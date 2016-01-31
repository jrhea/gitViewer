﻿import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtWebKit 3.0
import sortfilterproxymodel 1.0
import "qml"
import QtQuick.Extras 1.4

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1024
    height: 768
    title: qsTr("Git Viewer")
    //color: "#161616"

    SplitView {
        id: splitView
        anchors.fill: parent
        orientation: Qt.Horizontal

        FileSystemView {
            id:fileSystem
            width: parent.width/4
            height: parent.height
            model: fileSystemModel
            onDirectorySelected: {
                fileSystemModel.index = index;
            }
        }

        CommitView {
            id:commitView
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: fileSystem.right
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: branchViewToolBar.top
            anchors.bottomMargin: 0
            // @disable-check M300
            model: SortFilterProxyModel
            {
                id: proxyModel
                source: model.count > 0 ? model : null
            }
            onRefresh:
            {
                proxyModel.source = commitModel
                detail.refresh(-1)
            }
            onSort:
            {
                proxyModel.sortRole = sortRole
                proxyModel.sortOrder = sortOrder
                proxyModel.sortCaseSensitivity = Qt.CaseInsensitive
            }
            onFilter:
            {
                proxyModel.filterRole= filterRole;
                proxyModel.filterString= "*" + filterText + "*"
                proxyModel.filterSyntax= SortFilterProxyModel.Wildcard
                proxyModel.filterCaseSensitivity= Qt.CaseInsensitive
            }
        }

        BranchView {
            id: branchViewToolBar
            model: ListModel{}
            anchors.top: parent.bottom
            anchors.topMargin: -30
            anchors.left: fileSystem.right
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
        }

        Component.onCompleted:
        {
            fileSystem.directorySelected.connect(branchViewToolBar.refresh)
            fileSystem.directorySelected.connect(commitView.refresh)
        }
    }
}
