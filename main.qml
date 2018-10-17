import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.2

//import Controller 1.0
import PaintedItem 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("SimplePainter")


    Rectangle{
        id:root
        color:"lightBlue"
        anchors.fill:parent

//        Controller{
//            id:controller
//            onModelDataChanged: {
//                painter.update()
//            }
//        }

        Row{
            id:colorTools
            anchors{
                horizontalCenter: parent.horizontalCenter
                top:parent.top
                topMargin: 8
            }
            property color painterColor: "red"
            spacing:4
            Repeater{
                model: ["red","green","blue","yellow","white"]
                ColorSquare{
                    width: 100
                    height: 30
                    color: modelData
                    active: parent.painterColor === color
                    onClicked:{
                        colorTools.painterColor = color
                        console.log(colorTools.painterColor)
                        painter.penColor = color
                        controller.onColorChange(color);
                    }
                }
            }

            Column{

                spacing:5

                Button{
                    id:clear
                    width: 96
                    height: 26
                    text: "clear"
                    onClicked: {
                        painter.clear()
                    }
                }

                Button{
                    id:undo
                    width: 96
                    height: 20
                    text: "undo"
                    onClicked: {
                        painter.undo()
                    }
                }

            }
        }
        /*
//        Canvas{
//            id:canvas
//            anchors {
//                left: parent.left
//                right:parent.right
//                top:colorTools.bottom
//                bottom: parent.bottom
//                margins: 8
//            }
//            property real lastX
//            property real lastY
//            property real currentX
//            property real currentY
//            property color color:colorTools.painterColor
//            property bool isSender:true

//            onPaint: {
//                var ctx = getContext("2d")

//                //本地数据绘制
//                if(isSender){
//                    ctx.strokeStyle =color
//                    ctx.lineWidth = 4
//                    ctx.beginPath()

//                    //console.log("local pos data")

//                    ctx.moveTo(lastX,lastY)
//                    currentX = area.mouseX
//                    currentY = area.mouseY
//                    ctx.lineTo(currentX,currentY)
//                    lastX = currentX
//                    lastY = currentY
//                    ctx.stroke()
//                }
//                //远端接受数据绘制
//                else
//                {
//                    //console.log("net pos data")
//                    ctx.strokeStyle =dataModel.pointData.color
//                    ctx.lineWidth = 4
//                    ctx.beginPath()

//                    if(dataModel.pointData.opera===0){
//                        console.log("dataModel.pointData.opera===0")
//                        lastX = dataModel.pointData.posX
//                        lastY = dataModel.pointData.posY
//                        console.log("lastX,lastY"+lastX+" "+lastY)
//                    }
//                    else if(dataModel.pointData.opera===2){
//                        console.log("dataModel.pointData.opera===2")
//                        ctx.moveTo(lastX,lastY)
//                        currentX = dataModel.pointData.posX
//                        currentY = dataModel.pointData.posY
//                        lastX = currentX
//                        lastY = currentY
//                    }
//                    if(dataModel.pointData.opera!==1){
//                        console.log("dataModel.pointData.opera!==1")
//                        ctx.lineTo(currentX,currentY)
//                        console.log("currentX,currentY"+currentX+" "+currentY)
//                        console.log("lastX,lastY"+lastX+" "+lastY)
//                    }
//                    ctx.stroke()
//                }
//            }

//            MouseArea{
//                id:area
//                anchors.fill: canvas
//                onPressed:{
//                    canvas.isSender = true
//                    canvas.lastX = mouseX
//                    canvas.lastY = mouseY
//                    controller.onMousePressed(mouseX,mouseY);
//                }
//                onReleased: {
//                    canvas.isSender = false
//                    controller.onMouseRelesed(mouseX,mouseY);
//                }
//                onPositionChanged: {
//                    controller.onMousePositionChanged(mouseX,mouseY);
//                    canvas.requestPaint()
//                }
//            }
//        }
*/
        PaintedItem{
            id:painter
            anchors {
                left: parent.left
                right:parent.right
                top:colorTools.bottom
                bottom: parent.bottom
                margins: 8
            }
            penColor: "red"
            penWidth: 4

            MouseArea{
                id:area
                anchors.fill: painter
                onPressed:{
                    Controller.onMousePressed(mouseX,mouseY);
                    painter.update()
                }
                onReleased: {
                    Controller.onMouseRelesed(mouseX,mouseY);
                    painter.update()
                }
                onPositionChanged: {
                    Controller.onMousePositionChanged(mouseX,mouseY);
                    painter.update()
                }
            }

        }
    }
}
