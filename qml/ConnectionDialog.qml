import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Dialog {
    modal: true
    width: 300
    height: 400
    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2
    closePolicy: Popup.NoAutoClose
    title: "Serial Ports"
    contentItem: ListView {
        id: portList
        anchors.margins: 16
        model: application.serialPorts
        currentIndex: -1
        highlight: Rectangle { color: "lightgrey" }
        clip: true
        property string selectedPortName: ""
        delegate: Item {
            height: 50
            anchors { left: parent.left; right: parent.right }
            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: "Port " + model.index + "\t" + modelData
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.debug("port " + model.index + " selected")
                    portList.currentIndex = model.index
                    portList.selectedPortName = modelData
                }
                onDoubleClicked: {
                    sensorHandler.openSerialPort(modelData)
                }
            }

        }
    }
    footer: Button {
        text: "Connect"
        enabled: portList.currentIndex >= 0
        onClicked: sensorHandler.openSerialPort(portList.selectedPortName)
    }
}
