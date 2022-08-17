import QtQuick 2.13
import QtQuick.Controls 2.13
import "qrc:/Global.js" as Global

CheckBox {
    id: root
    text: qsTr("CheckBox")
    checked: true

    readonly property string activeTextColor:"#000016"
    readonly property string normalColor: "#004683"

    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26
        x: root.leftPadding
        y: parent.height / 2 - height / 2
        radius: 3
        border.color: root.down ? root.activeTextColor : root.normalColor

        Rectangle {
            width: 14
            height: 14
            x: 6
            y: 6
            radius: 2
            color: root.down ? root.activeTextColor : root.normalColor
            visible: root.checked
        }
    }

    contentItem: Text {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.down ? root.activeTextColor : root.normalColor
        verticalAlignment: Text.AlignVCenter
        leftPadding: root.indicator.width + root.spacing
    }
}
