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
       }
       onFinished:
       {
           te_result.text = test.getResult();
       }
   }
   Component.onCompleted:
   {
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

        savePath: true

        placeholder: qsTr("Choose Save Path")

        onPathChanged:
        {
            Global.outputPath = path;
        }
   }

   CustomResult
   {
        id: te_result

        height: parent.height * 0.2
        anchors
        {
            top: path.bottom
            topMargin: 5

            left: path.left

            right: parent.right
            rightMargin: 8
        }

   }


   Rectangle
   {
     id: checkBoxContainer

     anchors
     {
        top: te_result.bottom
        topMargin: 10

        left: te_result.left
     }


     color: "transparent"
     width: parent.width * 0.4
     height: rowContainer.implicitHeight


     Row
     {
         id: rowContainer
        Column
        {
            id: col1

            CustomCheckBox
            {
              id: chk_dieharder

              text: qsTr(Global.dieharderText);
              checked: false

              font: chk_borel.font
            }

            CustomCheckBox
            {
              id: chk_ent

              text: qsTr(Global.EntText);
              checked: false

              font: chk_borel.font
            }

            CustomCheckBox
            {
              id: chk_Css3

              text: qsTr(Global.SSTest3Text);
              checked: false

              font: chk_borel.font
            }

        }

        Column
        {
            id: col2

            CustomCheckBox
            {
              id: chk_nist22

              text: qsTr(Global.NIST_SP800_22Text);
              checked: false

              font: chk_borel.font
            }

            CustomCheckBox
            {
              id: chk_borel

              text: qsTr(Global.BorelText);
              checked: false

              font.family: Global.font_eng.name
              font.pixelSize: root.width * 0.015
            }


            CustomCheckBox
            {
              id: chk_Css4

              text: qsTr(Global.SSTest4Text);
              checked: false

              font: chk_borel.font
            }

        }

        Column
        {
            id: col3


            CustomCheckBox
            {
              id: chk_nist90b

              text: qsTr(Global.NIST_SP800_90BText);
              checked: false

              font: chk_borel.font

            }

            CustomCheckBox
            {
              id: chk_Css12

              text: qsTr(Global.SSTest12Text);
              checked: false

              font: chk_borel.font
            }

        }
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
        text: qsTr("Save Tests")

        onClicked:
        {
            var tests = [];
            if(Global.BorelTestResult !== "" && chk_borel.checked)
                tests.push("Borel Test Result:\n\n" + Global.BorelTestResult);

            if(Global.EntTestResult !== "" && chk_ent.checked)
                tests.push("Ent Test Result:\n\n" + Global.EntTestResult);

            if(Global.NIST_SP800_22Result !== "" && chk_nist22.checked)
                tests.push("NIST_SP800_22 Test Result:\n\n" + Global.NIST_SP800_22Result);

            if(Global.dieharderTestResult !== "" && chk_dieharder.checked)
                tests.push("Dieharder Test Result:\n\n" + Global.dieharderTestResult);

            if(Global.SSTest12Result !== "" && chk_Css12.checked)
                tests.push("CSSTest12 Test Result:\n\n" + Global.SSTest12Result);

            if(Global.SSTest3Result !== "" && chk_Css3.checked)
               tests.push("CSSTest3 Test Result:\n\n" +Global.SSTest3Result);

            if(Global.SSTest4Result !== "" && chk_Css4.checked)
                tests.push("CSSTest4 Test Result:\n\n" +Global.SSTest4Result);

            if(Global.NIST_SP800_90BResult !== "" && chk_nist90b.checked)
                tests.push("NIST_SP800_90B Test Result:\n\n" + Global.NIST_SP800_90BResult);


            var result = test.saveResult(path.path, tests);
        }

    }
}
