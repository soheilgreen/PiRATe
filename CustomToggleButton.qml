import QtQuick 2.13
import QtQuick.Controls 2.13
import "qrc:/Global.js" as Global

Button
{

    id: root
    property bool isActive: false
//    readonly property string activeTextColor: "#abe7ff"
//    readonly property string activeTextColor:"#bbffcb"
//    readonly property string normalColor: "#fdeac8"
    readonly property string activeTextColor:"#000016"
    readonly property string normalColor: "#004683"
    property string color

    contentItem: Text
    {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.isActive ? activeTextColor : normalColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle
    {
        implicitWidth: 100
        implicitHeight: 40
        color: root.color
        opacity: enabled ? 1 : 0.3
        border.color: root.isActive ? activeTextColor : normalColor
        border.width: root.isActive ? 2 : 1
        radius: root.width * 0.05
    }

}
