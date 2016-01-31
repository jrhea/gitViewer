import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtWebKit 3.0
import QtQuick.Extras 1.4

Item
{
    id: root
    property alias model:fileTreeView.model
    signal directorySelected(var index)
    Component.onCompleted:
    {
        fileTreeView.clicked.connect(directorySelected)
    }
    //color: "#cc0e0e"
    // @disable-check M300
    TreeView
    {
        id: fileTreeView
        anchors.fill: parent
        selection: itemSelection
        verticalScrollBarPolicy: 2

        TableViewColumn
        {
            title: "File System"
            role: "fileName"
            resizable: true
        }

        ItemSelectionModel {
            id: itemSelection
            model: fileSystemModel
        }

        onDoubleClicked: isExpanded(index) ? collapse(index) : expand(index)
    }

}
