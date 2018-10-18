import QtQuick 2.0

Rectangle {
    id:root
    property bool active: false
    signal clicked

    border.width: 4
    border.color: active?"grey":"#d3d3d3"

    MouseArea{
        id:mouseHandle
        anchors.fill:parent
        onClicked: {
            root.clicked()
            console.log("ColorSquare Clicked")
        }

    }


}
