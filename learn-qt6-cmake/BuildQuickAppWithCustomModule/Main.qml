import QtQuick
import CControls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: CTheme.windowColor

    Item {
        anchors.fill: parent

        CButton {
            id: button
            anchors.centerIn: parent
            text: "CButton Change theme"

            onClicked: {
                CTheme.darkTheme = !CTheme.darkTheme;
                console.log("CButton Change theme, dark:", CTheme.darkTheme);
            }
        }
    }
}
