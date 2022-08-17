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
           Global.SSTest4Result = te_result.text;

           waitProgress.visible = false;
           waitProgress.running = false;
       }
    }

   CustomCheckBox
   {
     id: chk_bitflip

     anchors
     {
        top: parent.top
        topMargin: 5

        left: parent.left
        leftMargin: 10
        right: parent.horizontalCenter
        rightMargin: 5
     }
     text: qsTr("Bit Flip");
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
            top: chk_bitflip.bottom
            topMargin: 5

            left: chk_bitflip.left

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
            var result = test.ssTest4(Global.pathText, chk_bitflip.checked);
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
