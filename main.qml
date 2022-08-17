import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "Global.js" as Global
import "qrc:/CustomControls"


Window {
    width: Screen.width * 0.7
    height: Screen.height * 0.6
    visible: true



    Component.onCompleted:
    {
        Global.font_eng = fnt_eng;
        Global.font_normal = fnt_normal;
        Global.font_title = fnt_title;

        loader.source = "qrc:/MainForm.qml";

    }


    property FontLoader fnt_eng: FontLoader{ source: "qrc:/Fonts/Assets/times new roman.ttf"}
    property FontLoader fnt_normal: FontLoader{ source: "qrc:/Fonts/Assets/nasim.ttf"}
    property FontLoader fnt_title: FontLoader{ source: "qrc:/Fonts/Assets/BTitrBold.ttf"}



//    Rectangle
//    {
//        id: background

//        anchors.fill: parent
//        color: Global.backgorundColor
//    }

    Image
    {
        id: background
        anchors.fill: parent

        source: "qrc:/Pictures/Assets/BackgroundImage.jpg"

        fillMode: Image.Stretch
        asynchronous: true
    }

    Loader
    {
        id: loader
        anchors.fill: parent
    }

}
