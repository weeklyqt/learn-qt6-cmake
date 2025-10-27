import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Item {
        anchors.fill: parent

        Image {
            source: ":/qt/qml/assets/github.png"
            anchors.centerIn: parent
        }
    }
}
