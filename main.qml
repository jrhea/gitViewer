import QtQuick 2.5
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
    id: applicationWindow1
    visible: true
    width: 1024
    height: 768
    title: qsTr("Git Viewer")
    //color: "#161616"
    ItemSelectionModel {
        id: itemSelection
        model: fileSystemModel
    }

    SplitView {
        id: splitView2
        anchors.fill: parent
        orientation: Qt.Horizontal

        Rectangle
        {
            id: dummyFileView
            width: parent.width/4
            height: parent.height
            color: "#cc0e0e"
            // @disable-check M300
            TreeView
            {
                id: fileView
                anchors.fill: parent
                model: fileSystemModel
                selection: itemSelection
                verticalScrollBarPolicy: 2

                TableViewColumn
                {
                    title: "File System"
                    role: "fileName"
                    resizable: true
                }
                onClicked:
                {
                    gitController.loadRepository(index);
                    branchComboBox.model = branchModel
                    //forces commitView to resynch
                    proxyModel.source = commitModel
                    //proxyModel.sortRole = commitModel.count > 0 ? commitView.getColumn(commitView.sortIndicatorColumn).role : ""

//                    var html = gitController.loadCommitVisualization();
//                    commitGraphWebView.loadHtml(html,"","");
                }
                onDoubleClicked: isExpanded(index) ? collapse(index) : expand(index)
                onActivated : Qt.openUrlExternally(fileSystemModel.data(index, 263))
            }

        }

        Item {
            id: commitItem
            height: 419
            anchors.top: parent.top
            anchors.topMargin: 341
            anchors.left: dummyFileView.right
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            // @disable-check M300
            TabView {
                id: tabView1
                antialiasing: true
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: commitView.top
                anchors.bottomMargin: 0
                transformOrigin: Item.Center
                anchors.top: commitView.bottom
                anchors.topMargin: -applicationWindow1.height + commitViewToolBar.height + messageSearchField.height
                Tab {
                    title: "Detail"
                    Detail {
                        enabled: true
                    }
                }
                Tab {
                    title: "Options"
                    Options {
                        enabled: true
                    }
                }
            }

            TableView {
                id: commitView
                anchors.bottomMargin: 51
                frameVisible: true
                sortIndicatorColumn: 3
                sortIndicatorVisible: true
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.fill:parent
                horizontalScrollBarPolicy: -1
                backgroundVisible: true
                antialiasing: true
                highlightOnFocus: true
                headerVisible: true
                //model: commitModel
                alternatingRowColors: true
                TableViewColumn {
                    id: messageColumn
                    title: "Message"
                    role: "message"
                    width: commitView.width/10 * 6
                    resizable: false
                }
                TableViewColumn {
                    id: authorColumn
                    title: "Author"
                    role: "author"
                    width: commitView.width/10 * 2
                    resizable: false
                }

                TableViewColumn {
                    id: dateColumn
                    title: "Date"
                    role: "date"
                    width: commitView.width/10 * 2
                    resizable: false
                }

                onSortIndicatorOrderChanged:
                {
                    proxyModel.sortRole = commitView.sortIndicatorColumn === 1 ? "message" : commitView.sortIndicatorColumn === 2 ? "author" : "date"
                    proxyModel.sortOrder = commitView.sortIndicatorOrder
                    proxyModel.sortCaseSensitivity = Qt.CaseInsensitive
                }

                // @disable-check M300
                model: SortFilterProxyModel
                {
                    id: proxyModel
                    source: commitModel.count > 0 ? commitModel : null
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
                        proxyModel.filterRole="message";
                        proxyModel.filterString= "*" + messageSearchField.text + "*"
                        proxyModel.filterSyntax= SortFilterProxyModel.Wildcard
                        proxyModel.filterCaseSensitivity= Qt.CaseInsensitive
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
                        proxyModel.filterRole="author";
                        proxyModel.filterString= "*" + authorSearchField.text + "*"
                        proxyModel.filterSyntax= SortFilterProxyModel.Wildcard
                        proxyModel.filterCaseSensitivity= Qt.CaseInsensitive
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
                        proxyModel.filterRole="date";
                        proxyModel.filterString= "*" + dateSearchField.text + "*"
                        proxyModel.filterSyntax= SortFilterProxyModel.Wildcard
                        proxyModel.filterCaseSensitivity= Qt.CaseInsensitive
                    }
                }
            }

            ToolBar {
                id: commitViewToolBar
                x: 0
                height: 31
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: parent.bottom
                anchors.topMargin: -30
                Label {
                    id: label1
                    text: qsTr("Current Branch:")
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                }
                ComboBox {
                    id: branchComboBox
                    y: 149
                    height: 26
                    anchors.right: parent.right
                    anchors.rightMargin: 450
                    activeFocusOnPress: false
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: label1.right
                    anchors.leftMargin: 10
                    model: emptyModel
                    onCurrentIndexChanged:
                    {
                        gitController.branch = branchComboBox.currentText;
                    }
                }
            }

//           Item
//           {
//               id:commitGraphItem
//               //prevents the webview from being scrolled
//               enabled: false
//               width: commitItem.width/10
//               height: 382
//               visible: false
//               //make height smaller than child to force clipping
//               anchors.top: commitView.top
//               anchors.topMargin: 19
//               //anchors.top: commitView.top
//               //anchors.bottomMargin: 0
//               //make the height smaller than the child to force clipping
//               clip: false  //cut off the top of the child
//               //move the item down so that it doesn't hide the tableview's col header
//               x: 0
//                WebView
//                {
//                    id: commitGraphWebView
//                    width: 77
//                    //anchors.fill: parent
//                    height: commitView.viewport.height
//                    clip: false
//                    visible: false
//                    anchors.bottom: parent.bottom
//                    anchors.bottomMargin: 12
//                    contentWidth: commitItem.width/10
//                    contentHeight: commitItem.height
//                    //this forces the webview to be rendered from top up
//                }
//           }

             }
        }


        ListModel{
            id: emptyModel
            ListElement{  }
        }

    Component {
        id: webDelegate
        WebView {
            id: webview
            width: commitView.width/10
            height:commitView.height - 20
            y: 20
            url: "src/main/index.html"
            anchors.fill: parent
            onNavigationRequested: {
                // detect URL scheme prefix, most likely an external link
                var schemaRE = /^\w+:/;
                if (schemaRE.test(request.url)) {
                    request.action = WebView.AcceptRequest;
                } else {
                    request.action = WebView.IgnoreRequest;
                    // delegate request.url here
                }
            }
        }
    }
    Component {
        id: emptyDelegate
        Item {
            width:0
            height:0
        }
    }
    Component {
        id: commitGraphDelegate
        Item {
            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                width: 1000
                height: 1000

                cache : true;
                asynchronous: true;
                source: "http://images.freeimages.com/images/premium/previews/4852/48521810-globe-icon-flat-icon-with-long-shadow.jpg"
            }
        }
    }

}
