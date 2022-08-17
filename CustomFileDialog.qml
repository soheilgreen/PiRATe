import QtQuick 2.13
import QtQuick.Controls 2.13
import "qrc:/Global.js" as Global
import com.cpp.test 1.0

Item
{
    id: root

    property string text: ""
    property bool save: false

    Tests{ id: test}

    signal fileChosen

    function open()
    {
        var text = test.openFileDialog(save);
        text.replace(' ', '\ ');
        if(text !== "")
            root.text = text;
        fileChosen();
    }


}
