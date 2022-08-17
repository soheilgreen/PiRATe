import QtQuick 2.13
import QtQuick.Controls 2.13
import "qrc:/Global.js" as Global

Item
{
    id: root
    property string activeButton
    signal clicked()

    QtObject
    {
        id: privateVar

        property var buttons: []

        function checkActivates(btn_active)
        {
            for(var i = 0; i < buttons.length; i++)
            {
                if(buttons[i] !== btn_active)
                    buttons[i].isActive = false;
            }
        }
    }

    Component.onCompleted:
    {
        privateVar.buttons.push(btn_borel);
        privateVar.buttons.push(btn_ss3);
        privateVar.buttons.push(btn_dieharder);
        privateVar.buttons.push(btn_ent);
        privateVar.buttons.push(btn_SP800_22);
        privateVar.buttons.push(btn_SP800_90B);
        privateVar.buttons.push(btn_ss3);
        privateVar.buttons.push(btn_ss4);
        privateVar.buttons.push(btn_ss12);
        privateVar.buttons.push(btn_output);
    }

    Rectangle
    {
        id: background
        anchors.fill: parent
        color: "transparent"
    }


    //Layout
    Column
    {
        id: layout
        anchors.fill: parent


        function activeButton(btn)
        {
            btn.isActive = true
            root.activeButton = btn.text
            privateVar.checkActivates(btn);
            root.clicked();
        }


        Text
        {
            id: lbl_title

            width: parent.width

            text: qsTr("Tests")
            font.family: Global.font_title.name
            font.pixelSize: 15

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: btn_borel.activeTextColor
        }


        CustomToggleButton
        {
            id: btn_dieharder


            width: btn_borel.width
            height: btn_borel.height

            text: Global.dieharderText
            font: btn_borel.font

            color: btn_borel.color
            onClicked:
            {
                layout.activeButton(this)
            }
        }


        CustomToggleButton
        {
            id: btn_SP800_22

            width: btn_borel.width
            height: btn_borel.height

            text: Global.NIST_SP800_22Text
            font: btn_borel.font

            color: btn_borel.color
            onClicked:
            {
                layout.activeButton(this)
            }
        }


        CustomToggleButton
        {
            id: btn_SP800_90B

            width: btn_borel.width
            height: btn_borel.height

            text: Global.NIST_SP800_90BText
            font: btn_borel.font

            color: btn_borel.color
            onClicked:
            {
                layout.activeButton(this)
            }
        }

        CustomToggleButton
        {
            id: btn_ent

            width: btn_borel.width
            height: btn_borel.height

            text: Global.EntText
            font: btn_borel.font

            color: btn_borel.color
            onClicked:
            {
                layout.activeButton(this)
            }
        }

        CustomToggleButton
        {
            id: btn_borel

            width: parent.width
            height: Math.max(30, parent.height * 0.135)

            text: Global.BorelText
            font.family: Global.font_eng.name
            font.pixelSize: parent.width * 0.08

            color: "transparent"
            onClicked:
            {
                layout.activeButton(this)
            }
        }
        CustomToggleButton
        {
            id: btn_ss12

            width: parent.width
            height: btn_borel.height

            text: Global.SSTest12Text
            font: btn_borel.font

            color: "transparent"
            onClicked:
            {
                layout.activeButton(this)
            }
        }


        CustomToggleButton
        {
            id: btn_ss3

            width: parent.width
            height: btn_borel.height

            text: Global.SSTest3Text
            font: btn_borel.font

            color: "transparent"
            onClicked:
            {
                layout.activeButton(this)
            }
        }


        CustomToggleButton
        {
            id: btn_ss4

            width: parent.width
            height: btn_borel.height

            text: Global.SSTest4Text
            font: btn_borel.font


            color: "transparent"
            onClicked:
            {
                layout.activeButton(this)
            }
        }


        CustomToggleButton
        {
            id: btn_output

            width: btn_borel.width
            height: btn_borel.height

            text: Global.outputText
            font: btn_borel.font

            color: btn_borel.color
            onClicked:
            {
                layout.activeButton(this)
            }
        }

    }
    //End Of Layout

}
