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
            name: "思源楼"
            desc: "思源"
            image_url: "qrc:res/res/SiYuan.png"
        }
        ListElement{
            name: "思源西楼"
            desc: "法学院"
            image_url: "qrc:res/res/SiYuanXi.png"
        }
        ListElement{
            name: "思源东楼"
            desc: "经管学院"
            image_url: "qrc:res/res/SiYuanDong.png"
        }
        ListElement{
            name: "明湖"
            desc: "就，湖"
            image_url: "qrc:res/res/MingHu.png"
        }
        ListElement{
            name: "芳华园"
            desc: "花花草草木木"
            image_url: "qrc:res/res/FangHuaYuan.png"
        }
        ListElement{
            name: "图书馆"
            desc: "书书书书书书书"
            image_url: "qrc:res/res/TuShuGuan.png"
        }
        ListElement{
            name: "学活"
            desc: "《一站式》服务中心"
            image_url: "qrc:res/res/XueHuo.png"
        }
        ListElement{
            name: "世纪钟"
            desc: "逝者如斯"
            image_url: "qrc:res/res/ShiJiZhong.png"
        }
        ListElement{
            name: "积秀园"
            desc: "秀"
            image_url: "qrc:res/res/JiXiuYuan.png"
        }
        ListElement{
            name: "南门"
            desc: "全亚洲最高的校门"
            image_url: "qrc:res/res/NanMen.png"
        }
        ListElement{
            name: "天佑会堂"
            desc: "天佑，会堂"
            image_url: "qrc:res/res/TianYou.png"
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
                        anchors.margins: 8
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
        radius: 20
        clip:true

        ListView {
            id: listView
            width: 300
            height: parent - 16
            anchors.margins: 8
            anchors.fill: parent
            interactive: false
            delegate: listDelegate
            model: listModel
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            clip: true
            ScrollBar.vertical: ScrollBar {
                id: scrollBar
                onActiveChanged: {
                    active = true;
                }
                background: Rectangle {
                    color: "white"
                }
            }
        }

    }
}
