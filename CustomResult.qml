import QtQuick 2.13
import QtQuick.Controls 2.13
import "qrc:/Global.js" as Global
Item
{

    id: root
    property string text: ""
    property string lblText: ""

    Text
    {
        id: lbl_result

//        implicitWidth: 100
//        implicitHeight: 50

        anchors
        {
            top: parent.top
            topMargin: 20
            left: parent.left
            leftMargin: 10
        }


        font.family: Global.font_eng.name
        font.pixelSize: parent.width * 0.022

        color: Global.textColor

        text: qsTr(lblText);
    }


    ScrollView
    {
        anchors
        {
            top: lbl_result.top

            left: lbl_result.right
            leftMargin: 5

            right: parent.right
            rightMargin: 4

            bottom: parent.bottom
            bottomMargin: 10
        }

        TextEdit
        {
            id: te_result

            readOnly: true

            anchors.fill: parent

            text: root.text
            clip: true
            wrapMode: TextEdit.WrapAnywhere

            color: Global.textColor
            verticalAlignment: TextEdit.AlignTop

            font: lbl_result.font



        }
    }

}
