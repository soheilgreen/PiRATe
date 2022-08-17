import QtQuick 2.13
import QtQuick.Controls 2.13
import "qrc:/Global.js" as Global


Item
{
    id: root

    property bool readonly: false
    property string placeholder: ""
    property string path: ""
    property bool savePath: false

    TextField
    {
        id: te_path

        anchors
        {

            top: parent.top
            topMargin: 2
            bottom: parent.bottom

            left: parent.left
        }

        width: parent.width * 0.75


        background: Rectangle
        {
            color: "transparent"
            border
            {
                width: 1
                color: Global.textColor
            }
            radius: width * 0.01
        }

        text: root.path

        font.family: Global.font_eng.name
        font.pixelSize: width * 0.04
        color: Global.textColor

        placeholderText: qsTr(root.placeholder)
        placeholderTextColor: "#555"

        readOnly: root.readonly

        verticalAlignment: TextField.AlignVCenter
        horizontalAlignment: TextField.AlignHCenter

        onTextChanged:
        {
            root.path = text;
        }
    }

    CustomButton
    {
        id: btn_browse

        text: "Choose File"

        anchors
        {
            top: te_path.anchors.top
            topMargin: te_path.anchors.topMargin

            bottom: te_path.anchors.bottom

            left: te_path.right
            leftMargin: 2

            right: parent.right

        }

        font: te_path.font

        onClicked:
        {
            dlg.open();
        }
    }

    CustomFileDialog
    {
        id: dlg

        save: savePath

        onFileChosen:
        {
            te_path.text = dlg.text;
            console.log(dlg.text);
        }
    }
}
