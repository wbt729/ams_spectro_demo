import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    visible: true
    width: 1024
    height: 800
    title: qsTr("AMS 7265 Demo")
    Material.primary: Material.Indigo

    //ApplicationWindow does not have a states property,
    //therefore the states are defined in this item
    Item {
        id: statesItem
        state: sensorHandler.state
        states: [
            State {
                name: "notConnected"
                PropertyChanges { target: connectionDialog; visible: true }
                PropertyChanges { target: toolBar; enabled: false }
            },
            State {
                name: "idle"
                PropertyChanges { target: connectionDialog; visible: false }
                PropertyChanges { target: toolBar; enabled: true }
                PropertyChanges { target: buttonMeasure; icon.source: "qrc:/icons/play_arrow-24px.svg" }
            },
            State {
                name: "measuring"
                PropertyChanges { target: connectionDialog; visible: false }
                PropertyChanges { target: toolBar; enabled: true }
                PropertyChanges { target: buttonMeasure; icon.source: "qrc:/icons/stop-24px.svg" }
            }
        ]
    }

    header: ToolBar {
        id: toolBar
        contentItem:  Row {
            spacing: 8
//            anchors { verticalCenter: parent.verticalCenter; leftMargin: 160 }

            ToolButton {
                id: buttonMeasure
                text: "Measure"
                onClicked: sensorHandler.toggleMeasurement()
            }

            ToolSeparator {}
            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: "Gain"
            }
            SpinBox {
                anchors.verticalCenter: parent.verticalCenter
                id: gainSpinBox
                value: 0
                from: 0
                to: 3
                onValueChanged: sensorHandler.setGain(gainSpinBox.value)
                textFromValue: function(value, locale) {
                    if(value == 0)
                        return "1 x"
                    else if(value == 1)
                        return "3.7 x"
                    else if(value == 2)
                        return "16 x"
                    else if(value == 3)
                        return "64 x"
                    else
                        return "undefined"
                }
            }
            ToolSeparator {}
            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: "Integration Time"
            }
            SpinBox {
                id: integrationTimeSpinBox
                value: 50
                from: 0
                to: 255
                onValueChanged: sensorHandler.setIntegrationTime(integrationTimeSpinBox.value)
                textFromValue: function(value, locale) { return Number(2.8 * value).toLocaleString(locale, 'f', 0) + " ms"; }
            }
            ToolSeparator {}
            CheckBox {
                id: autoscaleCheckBox
                anchors.verticalCenter: parent.verticalCenter
                text: "Auto Scale"
                checked: true
            }
        }
    }

    SpectraChart {
        anchors { fill: parent; margins: 16 }
        autoScale: autoscaleCheckBox.checked
    }

    ConnectionDialog {
        id: connectionDialog
    }
}
