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
           waitProgress.visible = true;
           waitProgress.running = true;
           te_result.text = "";
       }

       onVerboseData: (text) =>
       {
            te_result.lblText = "Result: ";
            te_result.text += text;
       }

       onFinished:
       {
           te_result.lblText = "Result: ";
           te_result.text += test.getResult();
           Global.SSTest3Result = te_result.text;

           waitProgress.visible = false;
           waitProgress.running = false;
       }
   }
   Component.onCompleted:
   {
//       te_result.text = Global.SSTest3Result;
//       path.path = Global.SSTest3FilePath;
   }

   CustomPath
   {
        id: path

        anchors
        {
            top: parent.top
            topMargin: 10

            left: parent.left
            leftMargin: 10
        }

        width: parent.width * 0.7
        height: parent.height * 0.12

        placeholder: qsTr("Enter the Carmichael numbers file")

        onPathChanged:
        {
            Global.SSTest3FilePath = path;
        }
   }

   CustomCheckBox
   {
     id: chk_bitflip

     anchors
     {
        top: path.top
        bottom: path.bottom

        left: path.right

     }
     text: qsTr("Bit Flip");
     checked: false

     font.family: Global.font_eng.name
     font.pixelSize: parent.width * 0.022
   }

   CustomCheckBox
   {
     id: chk_verbose

     anchors
     {
        top: path.top
        bottom: path.bottom

        left: chk_bitflip.right
        leftMargin: 2

        right: parent.right
        rightMargin: 5
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
            top: path.bottom
            topMargin: 5

            left: path.left

            right: parent.right
            rightMargin: 8
        }

   }



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
            var result = test.ssTest3(Global.pathText, path.path, chk_bitflip.checked, chk_verbose.checked ? 1 : 0);
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
