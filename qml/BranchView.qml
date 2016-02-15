import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtWebKit 3.0
import QtQuick.Extras 1.4

ToolBar {
    id: root
    property alias model: branchComboBox.model
    signal refresh()
    onRefresh: {
        branchComboBox.model = branchModel
        branchComboBox.currentIndex=0
        branchComboBox.update()
       // branchController.branch = branchComboBox.currentText;
    }


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
        onCurrentIndexChanged:
        {
            branchController.branch = branchComboBox.currentText;
        }
    }
}
