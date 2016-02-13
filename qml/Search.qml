import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtWebKit 3.0
import QtQuick.Extras 1.4

ScrollView {
    id: page

    property int searchType
    property string searchRole
    property string searchText

    width: 700
    height: 400
    implicitHeight: 300
    implicitWidth: 640
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    Item {
        id: content
        width: 640
        height: 300
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout3
            width: 0
            anchors.left: parent.left
            anchors.leftMargin: 25
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            GroupBox {
                id: groupBox1
                Layout.minimumHeight: page.height-50
                Layout.minimumWidth: page.width-50
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.fillHeight: true
                title: "Select a field to search:"
                Layout.fillWidth: true

                ColumnLayout {
                    id: columnLayout2
                    width: 640
                    height: 250
                    anchors.fill: parent
                    Layout.fillWidth: false
                    Layout.rowSpan: 1


                    RowLayout {
                        id: rowLayout1
                        width: 640
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        anchors.fill: parent
                        spacing: 20

                        ColumnLayout {
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            Layout.fillWidth: true
                            spacing: 20
                            anchors.fill: parent
                            ExclusiveGroup
                            {
                                id: radioGroup
                                property string role: "author"
                            }
                            RadioButton
                            {
                                text: "Author";
                                checked: true;
                                exclusiveGroup: radioGroup
                                onClicked: {
                                    radioGroup.role = "author"
                                }

                            }
                            RadioButton
                            {
                                text: "Date Range";
                                exclusiveGroup: radioGroup
                                onClicked: {
                                    radioGroup.role = "date"
                                }
                            }
                            RadioButton
                            {
                                text: "Commit ID";
                                exclusiveGroup: radioGroup;
                                checked: false
                                onClicked: {
                                    radioGroup.role = "commitId"
                                }
                            }
                        }

                        ColumnLayout {
                            id: columnLayout1
                            Layout.fillHeight: true
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            spacing: 20
                            Layout.fillWidth: true

                            TextField {
                                id: authorTextField
                                height: 22
                                Layout.fillWidth: true
                                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                                Layout.columnSpan: 1
                                placeholderText: qsTr("Search Author")
                            }

                            RowLayout {
                                id: rowLayout2
                                height: 20
                                Layout.fillHeight: true
                                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                                Layout.fillWidth: true

                                TextField {
                                    id: startDateTextField
                                    height: 22
                                    inputMask: "00-00-0000"
                                    Layout.fillWidth: false
                                    placeholderText: qsTr("")
                                }

                                Label {
                                    id: label1
                                    width: 0
                                    height: 16
                                    text: qsTr("to")
                                    verticalAlignment: Text.AlignVCenter
                                    horizontalAlignment: Text.AlignHCenter
                                }

                                TextField {
                                    id: endDateTextField
                                    height: 22
                                    inputMask: "00-00-0000"
                                    Layout.fillWidth: false
                                    placeholderText: qsTr("")
                                }

                                Rectangle {
                                    id: rectangle1
                                    width: 400
                                    height: 20
                                    color: "#00000000"
                                    Layout.fillWidth: true
                                    Layout.maximumHeight: 20
                                    border.width: 0
                                    border.color: "#00000000"
                                }

                            }

                            TextField {
                                id: commitIDTextField
                                height: 22
                                Layout.fillWidth: true
                                placeholderText: qsTr("Search Commit ID")
                            }


                        }
                    }

                    RowLayout {
                        id: rowLayout3
                        width: 100
                        height: 100
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                        Button
                        {
                            id: searchBtn;
                            text: "Search";
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter;
                            transformOrigin: Item.Center;
                            isDefault: true
                            onClicked:
                            {
                                searchRole = radioGroup.role
                                searchType = searchRole === "date" ? 1 : 0
                                if(searchRole === "author")
                                {
                                    searchText = authorTextField.text
                                }
                                else if(searchRole === "commitId")
                                {
                                    searchText = commitIDTextField.text
                                }
                                else
                                {
                                    searchText = startDateTextField.text + ":" + endDateTextField.text
                                }
                                search(searchRole,searchType,searchText)
                            }
                        }

                        Button {
                            id: clearBtn
                            text: qsTr("Clear")
                            Layout.fillWidth: false
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            onClicked:
                            {
                                startDateTextField.text = ""
                                endDateTextField.text = ""
                                authorTextField.text = ""
                                commitIDTextField.text = ""
                                searchRole = radioGroup.role
                                search(searchRole,-1,"")

                            }
                        }
                    }
                }

            }
        }
    }
}
