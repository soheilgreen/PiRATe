import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import "Global.js" as Global
import "qrc:/CustomControls"
import com.cpp.test 1.0

Item
{
   id: root

   signal requestStackChange(var stack, var properties)



   Tests
   {
       id: test

       onTestStart:
       {
           te_result.text = Global.testStartMessage;
           waitProgress.visible = true;
           waitProgress.running = true;
       }

       onFinished:
       {
           te_result.lblText = "Result: ";
           te_result.text = test.getResult();
           Global.BorelTestResult = te_result.text;

           waitProgress.visible = false;
           waitProgress.running = false;
       }

   }

   Component.onCompleted:
   {
//       te_result.text = Global.BorelTestResult
   }


   CustomCheckBox
   {
     id: chk_verbose

     anchors
     {
        top: parent.top
        left: parent.left
        leftMargin: 10
     }
     text: qsTr("Verbose");
     checked: false

     font.family: Global.font_eng.name
     font.pixelSize: parent.width * 0.022

   }


   CustomResult
   {
        id: te_result

        height: parent.height * 0.7
        anchors
        {
            top: chk_verbose.bottom
            topMargin: 4

            left: chk_verbose.left

            right: parent.right
            rightMargin: 8
        }

   }

//    Text
//    {
//        id: lbl_result

//        anchors
//        {
//            top: parent.top
//            topMargin: 20

//            left: parent.left
//            leftMargin: 10
//        }

//        font.family: Global.font_eng.name
//        font.pixelSize: parent.width * 0.022

//        color: Global.textColor

//        text: qsTr("Result: ");
//    }


//    TextEdit
//    {
//        id: te_result

//        readOnly: true
//        anchors
//        {
//            top: lbl_result.top

//            left: lbl_result.right
//            leftMargin: 5

//            right: parent.right
//            rightMargin: 10
//        }


//        clip: true
//        wrapMode: TextEdit.WrapAnywhere

//        color: Global.textColor
//        padding: 3
//        verticalAlignment: TextEdit.AlignVCenter

//        font: lbl_result.font



//    }


    CustomButton
    {

        id: btn_start

        width: Math.max(80, parent.width * 0.53)
        height: Math.max(30, parent.height * 0.15)

        anchors
        {
            bottom: parent.bottom
            bottomMargin: 10

            horizontalCenter: parent.horizontalCenter
        }

        font.family: Global.font_eng.name
        font.pixelSize: parent.width * 0.032
        text: qsTr("Start Test")

        onClicked:
        {
            te_result.text = Global.testStartMessage;
            var result = test.borelTest(Global.pathText, (chk_verbose.checked ? 1 : 0));
            if(result !== "")
                te_result.text = result;
        }

    }

    CustomBusyIndicator
    {
        id: waitProgress

        running: false
        visible: false
        anchors{ top: btn_start.top; bottom: btn_start.bottom;
            left: btn_start.right; leftMargin: Math.max(40, parent.width * 0.12)}

        width: height
    }
}
