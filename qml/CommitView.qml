import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtWebKit 3.0
import QtQuick.Extras 1.4
import sortfilterproxymodel 1.0


Item {
    id: root
    property alias model: commitTable.model
    property Item detailtab: detailTab
    property Item searchtab: searchTab
    signal refresh()
    signal search(string searchRole, int searchType, string searchText)
    signal sort(string sortRole, int sortOrder)
    signal filter(string filterRole, string filterText)

    Component.onCompleted:
    {
        commitTable.clicked.connect(detailTab.refresh)
    }

    // @disable-check M300
    TabView {
        id: detailTabView
        antialiasing: true
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: commitTable.top
        anchors.bottomMargin: 0
        transformOrigin: Item.Center
        Tab {
            id: detailTab
            property Item authorField: item.authorField
            property Item emailField: item.emailField
            property Item dateField: item.dateField
            property Item commitIdField: item.commitIdField
            property Item commitMessageField: item.commitMessageField
            signal refresh(int row)
            onRefresh:
            {
                if(row === -1)
                {
                    item.authorField.text = "";
                    item.emailField.text = "";
                    item.dateField.text = "";
                    item.commitIdField.text = "";
                    item.commitMessageField.text = "";
                }
                else
                {
                    item.authorField.text = commitController.getCommit(row,"author");
                    item.emailField.text = commitController.getCommit(row,"email");
                    item.dateField.text = commitController.getCommit(row,"date");
                    item.commitIdField.text = commitController.getCommit(row,"commitId");
                    item.commitMessageField.text = commitController.getCommit(row,"fullmessage");
                }

            }
            title: "Detail"
            Detail {
                id: detailComponent
                enabled: true
            }
        }
        Tab {
            id:searchTab
            property Item searchButton: item.searchButton
            property int searchType : item.searchType
            property string searchRole : item.searchRole
            property string searchText : item.searchText

            title: "Search"
            Search {
                enabled: true
            }
        }
    }

    TableView {
        id: commitTable
        frameVisible: true
        sortIndicatorColumn: -1
        sortIndicatorVisible: false
        height: parent.height/2
        sortIndicatorOrder: -1
        selectionMode: 1
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom:  parent.bottom
        anchors.bottomMargin: 20
        horizontalScrollBarPolicy: -1
        backgroundVisible: true
        antialiasing: true
        highlightOnFocus: true
        headerVisible: true
        alternatingRowColors: true

        TableViewColumn {
            id: messageColumn
            title: "Message"
            role: "message"
            width: commitTable.width/10 * 6
            resizable: false
        }

        TableViewColumn {
            id: authorColumn
            title: "Author"
            role: "author"
            width: commitTable.width/10 * 2
            resizable: false
        }

        TableViewColumn {
            id: dateColumn
            title: "Date"
            role: "date"
            width: commitTable.width/10 * 2
            resizable: false
        }

        onSortIndicatorOrderChanged:
        {
            var role = sortIndicatorColumn === 1 ? "message" : sortIndicatorColumn === 2 ? "author" : "date"
            sort(role,sortIndicatorOrder)
        }

        TextField
        {
            id: messageSearchField
            width: messageColumn.width
            height: 20
            font.italic: true
            style: TextFieldStyle {
                placeholderTextColor: "lightcoral"
            }
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -20
            anchors.left: parent.left
            anchors.leftMargin: 0
            placeholderText: qsTr("Filter Messages...")
            inputMethodHints: Qt.ImhNoPredictiveText
            onTextChanged:
            {
                root.filter("message",text);
            }
        }

        TextField
        {
            id: authorSearchField
            width: authorColumn.width
            height: 20
            font.italic: true
            style: TextFieldStyle {
                placeholderTextColor: "lightcoral"
            }
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -20
            anchors.left: messageSearchField.right
            anchors.leftMargin: 0
            placeholderText: qsTr("Filter Authors...")
            inputMethodHints: Qt.ImhNoPredictiveText
            onTextChanged:
            {
                root.filter("author",text);
            }
        }

        TextField
        {
            id: dateSearchField
            width: dateColumn.width
            height: 20
            font.italic: true
            style: TextFieldStyle {
                placeholderTextColor: "lightcoral"
            }
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -20
            anchors.left: authorSearchField.right
            anchors.leftMargin: 0
            placeholderText: qsTr("Filter Date...")
            inputMethodHints: Qt.ImhDate
            onTextChanged:
            {
                root.filter("date",text);
            }
        }

    }
}

