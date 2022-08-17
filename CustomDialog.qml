import QtQuick 2.13
import QtQuick.Controls 2.13
import "qrc:/Global.js" as Global


Dialog
{
    id: root
    property string text: ""
    readonly property string normalColor: "#004683"

    modal: Qt.WindowModal

    Image
    {
        id: background
        anchors.fill: parent
        source: "qrc:/Pictures/Assets/BackgroundImage.jpg"

        fillMode: Image.Stretch
        asynchronous: true
    }

    ScrollView
    {
//        height: lbl.contentHeight

        width: parent.width
        height: parent.height

//        contentHeight: lbl.contentHeight
//        anchors
//        {
//            left: parent.left
//            right: parent.right
//            leftMargin: 20
//            rightMargin: 20
//        }

        clip: true

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn


                 Text{
                    id: lbl
                    width: root.width
    //                height: root.height
                    text: root.text
                    font.family: Global.font_eng.name
                    font.pixelSize: root.width * 0.012
        //            font.bold: true
    //                clip: true
                    wrapMode: Text.WordWrap
                    color:  root.normalColor
                    verticalAlignment: Text.AlignVCenter
        //            leftPadding: root.indicator.width + root.spacing
            }


    }

}
