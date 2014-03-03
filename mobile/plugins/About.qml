import QtQuick 2.0
import org.kde.analitza 1.0
import widgets 1.0

KAlgebraPage
{
	Column {
		anchors.margins: 20
		anchors.fill: parent
		spacing: 20
		
		Image {
			source: "qrc:/kalgebra.svgz"
			anchors.horizontalCenter: parent.horizontalCenter
			MouseArea {
				anchors.fill: parent
				onClicked: Qt.openUrlExternally("http://edu.kde.org/applications/mathematics/kalgebra")
			}
		}
		
		Label {
			anchors.left: parent.left
			anchors.right: parent.right
			
			wrapMode: Text.WordWrap
			horizontalAlignment: Text.AlignHCenter
			text: ("KAlgebra is brought to you by the lovely community of <a href='http://kde.org'>KDE</a> "+
					"and <a href='http://edu.kde.org/'>KDE Edu</a> from a Free Software envionment.")
			onLinkActivated: Qt.openUrlExternally(link)
		}
		
		Label {
			anchors.left: parent.left
			anchors.right: parent.right
			
			wrapMode: Text.WordWrap
			horizontalAlignment: Text.AlignHCenter
			text: ("In case you want to learn more about KAlgebra, you can find more information "+
					"<a href='http://edu.kde.org/applications/mathematics/kalgebra/'>in the official site</a> and in "+
					"the <a href='http://userbase.kde.org/KAlgebra'>users wiki</a>.<br/>"+
					"If you have any problem with your software, please report it to <a href='http://bugs.kde.org'>our bug tracker</a>.")
			onLinkActivated: Qt.openUrlExternally(link)
		}
		
		Label {
			anchors.left: parent.left
			anchors.right: parent.right
			
			wrapMode: Text.WordWrap
			horizontalAlignment: Text.AlignHCenter
			text: "Aleix Pol Gonzalez &lt;<a href='mailto:aleixpol@kde.org'>aleixpol@kde.org</a>&gt;"
			onLinkActivated: Qt.openUrlExternally(link)
		}
		
		Image {
			source: "qrc:/kde-edu-logo.png"
			anchors.horizontalCenter: parent.horizontalCenter
			
			MouseArea {
				anchors.fill: parent
				onClicked: Qt.openUrlExternally("http://edu.kde.org")
			}
		}
	}
}
