import QtQuick
import QtQuick.Controls.Basic

Button {
    id: control
    text: qsTr("Button")

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? (control.down ? 0.8 : 1.0) : 0.3
        color: CTheme.buttonTextColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? (control.down ? 0.8 : 1.0) : 0.3
        border.color: Qt.darker(color, 2)
        border.width: 1
        radius: 4
        color: CTheme.buttonBackgroundColor
    }
}
