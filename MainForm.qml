import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "Global.js" as Global
import "qrc:/CustomControls"

Item
{

    id: root

    property var loaders: []

    function invisLoaders()
    {
        for(var i = 0; i < loaders.length; i++)
            loaders[i].visible = false;
    }

    function loadLoader(item)
    {
        if(view_container.currentVisible !== null && view_container.currentVisible !== item)
            view_container.currentVisible.visible = false;
        item.visible = true;
        view_container.currentVisible = item;
    }

    Component.onCompleted:
    {
//        Global.view = view;
        loaders.push(loader_SSTest12);
        loaders.push(loader_SSTest3);
        loaders.push(loader_SSTest4);
        loaders.push(loader_borel);
        loaders.push(loader_ent);
        loaders.push(loader_NIST_SP800_90B);
        loaders.push(loader_dieharder);
        loaders.push(loader_NIST_SP800_22);
        loaders.push(loader_output);
    }

//    Rectangle
//    {
//        id: background

//        anchors.fill: parent
//        color: Global.backgorundColor
//    }

    CustomDialog
    {
        id: dlg
        modal: Dialog

        width: parent.width * 0.8
        height: parent.height * 0.7

        anchors.centerIn: parent
    }

    Image
    {
        id: background
        anchors.fill: parent
        source: "qrc:/Pictures/Assets/BackgroundImage.jpg"

        fillMode: Image.Stretch
        asynchronous: true
    }

    //Set Drop Activity
    DropArea
    {
        id: dropArea
       anchors.fill: parent
       enabled: true

       Rectangle
       {
        anchors.fill: parent

        color: "#b9ffb8"
        visible: parent.containsDrag
       }

       onDropped:
       {
         te_path.path = drop.text.slice(7 , drop.text.length);
       }
    }




    CustomFileDialog
    {
        id: fileDialog
    }

    CustomMenuBar
    {
        id: menubar

        height: parent.height * 0.05

        anchors
        {
            top: parent.top
            left:parent.left
            right: parent.right
        }

        onClickedButtonChanged:
        {
            if(menubar.clickedButton === "")
                return;

            if( menubar.clickedButton === "Help")
            {
                dlg.text = Global.helpText;
                dlg.open();
                menubar.clickedButton = "";
            }

            if( menubar.clickedButton === "About")
            {
                dlg.text = Global.aboutText;
                dlg.open();
                menubar.clickedButton = "";
            }

        }
    }

    //ICQt Image
    Image
    {
        id: img_icqt

        width: parent.width * 0.18
        height: parent.height * 0.12

        anchors{ top: lbl_title.top; left: parent.left; leftMargin: parent.width * 0.01 }

        fillMode: Image.PreserveAspectFit

        source: "qrc:/Pictures/Assets/ICQTs.png"
    }

    //Icon Image
    Image
    {
        id: img_icon

        width: parent.width * 0.18
        height: parent.height * 0.12

        anchors{ top: lbl_title.top; right: lbl_title.left; rightMargin: -40}

        fillMode: Image.PreserveAspectFit

        source: "qrc:/Pictures/Assets/icon.png"
    }

    Text
    {
        id: lbl_title
        font.family: Global.font_eng.name
        font.pixelSize: parent.width * 0.044
        font.bold: true

        text: qsTr("PiRATe")

        anchors
        {
            top: menubar.bottom
            horizontalCenter: view_container.horizontalCenter
//            left:parent.left
//            right: parent.right
        }
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        color: Global.textColor;
    }


    CustomPath
    {
        id: te_path

        anchors
        {
            top: img_icqt.bottom
            topMargin: 10
            horizontalCenter: view_container.horizontalCenter
        }

        width: parent.width * 0.6
        height: parent.height * 0.08

        placeholder: qsTr("Drop File On Window or choose path");

        onPathChanged:
        {
            path = path.replace("\r", "");
            path = path.replace("\n", "");
            Global.pathText = path;
        }

    }
    //End Of te_path

    Component
    {
        id: borelCmp
        BorelForm
        {

        }
    }

    CustomButtonLayout
    {
        id: side_tests

        width: parent.width * 0.18
        height: parent.height * 0.51

        y: parent.height * 0.5 - height / 2

        anchors
        {
            left: parent.left
        }


        onClicked:
        {
            if(activeButton === Global.EntText)
            {
                loadLoader(loader_ent);
            }
//                if(Global.view.depth < 1)
//                    Global.view.push( "qrc:/EntForm.qml",{ objectName: "Ent Form"})
//                else
//                    Global.view.replace( "qrc:/EntForm.qml",{objectName: "Ent Form"})


            if(activeButton === Global.BorelText)
            {
                  loadLoader(loader_borel);
//                Global.view.push([borelCmp , {objectName: "Borel Form"}]);
            }

            if(activeButton === Global.SSTest3Text)
            {
                loadLoader(loader_SSTest3);

            }
//                if(Global.view.depth < 1)
//                    Global.view.push( "qrc:/SSTest3.qml",{ objectName: "Css Test3 Form"})
//                else
//                    Global.view.replace( "qrc:/SSTest3.qml",{objectName: "Css Test3 Form"})

            if(activeButton === Global.SSTest4Text)
            {
                loadLoader(loader_SSTest4);

            }

//                if(Global.view.depth < 1)
//                    Global.view.push( "qrc:/ssTest4.qml",{ objectName: "Css Test4 Form"})
//                else
//                    Global.view.replace( "qrc:/ssTest4.qml",{objectName: "Css Test4 Form"})

            if(activeButton === Global.SSTest12Text)
            {
                loadLoader(loader_SSTest12);

            }

            if(activeButton === Global.NIST_SP800_90BText)
            {
                loadLoader(loader_NIST_SP800_90B);

            }

            if(activeButton === Global.dieharderText)
            {
                loadLoader(loader_dieharder);
            }

            if(activeButton === Global.NIST_SP800_22Text)
            {
                loadLoader(loader_NIST_SP800_22);
            }

            if(activeButton === Global.outputText)
            {
                loadLoader(loader_output);
            }

//                if(Global.view.depth < 1)
//                    Global.view.push( "qrc:/SSTest12.qml",{objectName: "Css Test12 Form"})
//                else
//                    Global.view.replace( "qrc:/SSTest12.qml",{objectName: "Css Test12 Form"})
            }


    }

    Rectangle
    {
        id: view_container
        property var currentVisible: null

        anchors
        {
            left: side_tests.right
            leftMargin: 10

            right: parent.right
            rightMargin: 5
            top: te_path.bottom
            topMargin: 10
            bottom: parent.bottom
        }

        color: "transparent"

        border.width: 1
        border.color: Global.textColor
        radius: width * 0.03

        Loader{id: loader_borel; anchors.fill: parent; z: 1; visible: false; source: "qrc:/BorelForm.qml"}
        Loader{id: loader_ent; anchors.fill: parent; z: 1; visible: false; source: "qrc:/EntForm.qml"}
        Loader{id: loader_SSTest12; anchors.fill: parent; z: 1; visible: false; source: "qrc:/SSTest12.qml"}
        Loader{id: loader_SSTest3; anchors.fill: parent; z: 1; visible: false; source: "qrc:/SSTest3.qml"}
        Loader{id: loader_SSTest4; anchors.fill: parent; z: 1; visible: false; source: "qrc:/ssTest4.qml"}
        Loader{id: loader_NIST_SP800_90B; anchors.fill: parent; z: 1; visible: false; source: "qrc:/NIST_SP800_90B_Form.qml"}
        Loader{id: loader_dieharder; anchors.fill: parent; z: 1; visible: false; source: "qrc:/DieharderForm.qml"}
        Loader{id: loader_NIST_SP800_22; anchors.fill: parent; z: 1; visible: false; source: "qrc:/NistSp80022Form.qml"}
        Loader{id: loader_output; anchors.fill: parent; z: 1; visible: false; source: "qrc:/OutputForm.qml"}



//        StackView
//        {
//            id: view
//            anchors.fill: parent
//            readonly property int animationDuration : 500


//            onCurrentItemChanged:
//            {
//                view.currentItem.requestStackChange.connect(view.replace);
//            }

//            pushEnter: Transition
//            {
//                PropertyAnimation
//                {
//                    property: "opacity"
//                    from: 0
//                    to: 1
//                    duration: view.animationDuration
//                }

//            }
//            pushExit: Transition
//            {
//                PropertyAnimation
//                {
//                    property: "opacity"
//                    from: 1
//                    to:0
//                    duration: view.animationDuration
//                }
//            }
//            popEnter: Transition
//            {
//                PropertyAnimation
//                {
//                    property: "opacity"
//                    from: 1
//                    to:0
//                    duration: view.animationDuration
//                }
//            }
//            popExit: Transition
//            {
//                PropertyAnimation
//                {
//                    property: "opacity"
//                    from: 0
//                    to: 1
//                    duration: view.animationDuration
//                }
//            }

//            replaceEnter: Transition
//            {
//                PropertyAnimation
//                {
//                    property: "opacity"
//                    from: 0
//                    to: 1
//                    duration: view.animationDuration
//                }

//            }

//            replaceExit: Transition
//            {
//                PropertyAnimation
//                {
//                    property: "opacity"
//                    to:0
//                    duration: view.animationDuration
//                }
//            }


//            }
        }

}
