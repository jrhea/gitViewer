/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//This file was taken from one of the QT examples and modified heavily (keeping the above comments to comply with license)
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtWebKit 3.0
import QtQuick.Extras 1.4

ScrollView {
    id: root
    property Item authorField: authorTextField
    property Item emailField: emailTextField
    property Item dateField: dateTextField
    property Item commitIdField: commitIdTextField
    property Item commitMessageField: commitMessageTextArea


    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    Item {
        id: content
        width: Math.max(root.viewport.width, column.implicitWidth + 2 * column.spacing)
        height: Math.max(root.viewport.height, column.implicitHeight + 2 * column.spacing)

        ColumnLayout {
            id: column
            anchors.fill: parent
            anchors.margins: column.spacing
            GroupBox {
                checked: true
                flat: false
                Layout.fillHeight: true
                title: ""
                Layout.fillWidth: true
                ColumnLayout {
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                    anchors.fill: parent
                    GridLayout {
                        id: gridLayout1
                        width: 100
                        height: 100
                        Layout.maximumWidth: 65533
                        rows: 2
                        columns: 3

                        Label {
                            id: label2
                            text: qsTr("Author")
                        }

                        Label {
                            id: label4
                            text: qsTr("Email")
                        }

                        Label {
                            id: label3
                            text: qsTr("Date")
                        }

                        TextField {
                            id: authorTextField
                            text: ""
                            Layout.fillWidth: true
                            readOnly: true
                            placeholderText: qsTr("")
                        }

                        TextField {
                            id: emailTextField
                            text: ""
                            readOnly: true
                            Layout.fillWidth: true
                            placeholderText: qsTr("")
                        }

                        TextField {
                            id: dateTextField
                            text: ""
                            Layout.fillWidth: false
                            readOnly: true
                            inputMask: "00-00-0000"
                            placeholderText: qsTr("")
                        }

                    }

                    Label {
                        id: label5
                        text: qsTr("Commit ID")
                    }

                    TextField {
                        id: commitIdTextField
                        text: ""
                        readOnly: true
                        Layout.fillWidth: true
                        placeholderText: qsTr("")
                    }


                    Label {
                        id: label1
                        text: qsTr("Commit Message")
                        font.bold: false
                        verticalAlignment: Text.AlignTop
                    }


                    TextArea {
                        id: commitMessageTextArea
                        text: ""
                        tabChangesFocus: true
                        highlightOnFocus: true
                        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                        x: 129
                        y: 16
                        Layout.minimumHeight: 150
                        Layout.maximumHeight: 250
                        antialiasing: true
                        readOnly: true
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                    }
                }
            }
        }
    }
}

