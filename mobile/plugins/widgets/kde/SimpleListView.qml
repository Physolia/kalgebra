import org.kde.plasma.components 2.0
import QtQuick 2.0

ListView
{
    id: scrollList
    property string role: ""
    property string title: ""
    delegate: Label { text: model[role] }
    header: Label { visible: ListView.view.title!=""; text: ListView.view.title }
    clip: true
    
    ScrollBar {
        id: scrollBar
        orientation: Qt.Vertical
        flickableItem: scrollList
        stepSize: 40
        scrollButtonInterval: 50
        anchors {
            top: scrollList.top
            right: scrollList.right
            bottom: scrollList.bottom
        }
    }
}

