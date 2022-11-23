import QtQuick
import QtQuick.Controls

Item {
    id: heiheiheiha
    visible: true
    width: 300
    height: 400

    signal mySelect(int index)
    signal myCheck(int index, bool checked)

    ListModel{
        id: listModel
        ListElement{
            name: "逸夫教学楼"
            desc: "软件🤤嘿嘿...软件🤤嘿嘿..."
            image_url: "qrc:res/res/YiFu.png"
        }
        ListElement{
            name: "逸夫教学楼"
            desc: "软件🤤嘿嘿...软件🤤嘿嘿..."
            image_url: "qrc:res/res/YiFu.png"
        }
    }

    Component {
        id: listDelegate
        Item {
            id: delegateItem
            width: listView.width
            height: 64
            Rectangle {
                id: listItem
                width: listView.width
                height: 64
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
//                border.color: "lightgray"
                color: delegateItem.ListView.isCurrentItem ? "#fff2ed" : "white"

                Item {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    Image {
                        id: img
                        height: 56
                        width: 56
                        anchors.margins: 4
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        fillMode: Image.PreserveAspectCrop
                        source: image_url

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                delegateItem.ListView.view.currentIndex = index
                                mySelect(index)
                            }
                        }
                    }
                    Column {
                        id: col
                        width: 160
                        anchors.margins: 4
                        anchors.left: img.right
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 8
                        Text {
                            text: name
                            font.pixelSize: 18
                            color: delegateItem.ListView.isCurrentItem ? "red" : "black"
                        }
                        Text {
                            text: desc
                            font.pixelSize: 12
                            font.weight: Font.Thin
                            color: "#777"
                        }
                    }
                    MySwitch {
                        id: myswitch
                        checked: true
                        anchors.left: col.right
                        anchors.verticalCenter: parent.verticalCenter
                        checkedColor: "#87bdff"
                        onClicked: {
                            myCheck(index, checked)
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: rootItem
        anchors.fill: parent
        color: "#fff"
        radius: 8
        clip:true

        ListView {
            anchors.margins: 4
            id: listView
//            property int dragItemIndex: -1

            anchors.fill: parent
            interactive: false
            delegate: listDelegate
            model: listModel
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            clip: true

            DropArea {
                id: dropArea
                anchors.fill: parent
                onPositionChanged: {
                    var targetIndex = listView.indexAt(drag.x, drag.y + listView.contentY)
                    if(targetIndex>-1)
                    {
                        listModel.move(listView.dragItemIndex, targetIndex, 1)
                        listView.dragItemIndex=targetIndex
                    }
                }
            }
        }
    }
}
