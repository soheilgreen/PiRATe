import QtQuick 2.13
import QtQuick.Controls 2.13
import "qrc:/Global.js" as Global
import com.cpp.test 1.0

MenuBar {
    id: menuBar    

    property string clickedButton: ""

    ToolButton
    {
//        anchors.right: parent.right
        id: btn_help
        anchors
        {
            top: parent.top
            bottom: parent.bottom
        }
        parent: menuBar // Set main menu toolbar as parent for tool button
        text: "Help"

        onClicked:
        {
            clickedButton = text
        }
    }

    ToolButton
    {
        anchors
        {
            top: btn_help.top
            bottom: btn_help.bottom
            left: btn_help.right
        }
        parent: menuBar // Set main menu toolbar as parent for tool button
        text: "About"

        onClicked:
        {
            clickedButton = text
        }
    }
    delegate: MenuBarItem {
        id: menuBarItem

        contentItem: Text {
            text: menuBarItem.text
            font: menuBarItem.font
            opacity: enabled ? 1.0 : 0.3
            color: menuBarItem.highlighted ? "#ffffff" : "#21be2b"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }

        background: Rectangle {
            implicitWidth: 40
            implicitHeight: 40
            opacity: enabled ? 1 : 0.3
            color: menuBarItem.highlighted ? "#21be2b" : "transparent"
        }
    }

    background: Rectangle {
        implicitWidth: 40
        implicitHeight: 40
        color: "#addade"

        Rectangle {
            color: "#21be2b"
            width: parent.width
            height: 1
            anchors.bottom: parent.bottom
        }
    }
}
