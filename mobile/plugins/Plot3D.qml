/*************************************************************************************
 *  Copyright (C) 2015 by Aleix Pol <aleixpol@kde.org>                               *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0
import org.kde.analitza 1.1
import widgets 1.0

KAlgebraPage
{
    id: page

    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0

    FileDialog {
        id: fileDialog
        folder: shortcuts.home
        onAccepted: proceed()

        property var proceed
    }

    contextualActions: [
        Action {
            text: i18n("Save...")
            onTriggered: {
                fileDialog.title = text
                fileDialog.proceed = function() {
                    var ret = view.save(fileDialog.fileUrl)
                    console.log("saved 3D", fileDialog.fileUrl, ret)
                }
                fileDialog.nameFilters = view.filters
                fileDialog.selectExisting = false
                fileDialog.open()
            }
        },
        Action {
            text: i18n("Reset Viewport")
            onTriggered: view.resetViewport()
        }
    ]

    Graph3D
    {
        id: view
        anchors.fill: parent
        model: app.functionsModel()

        Dialog {
            id: dialog
            height: Math.min((4*view.height)/5, list.contentHeight)+page.dp*10

            SimpleListView {
                id: list
                anchors {
                    fill: parent
                    margins: page.dp*4
                }
                role: "description"
                model: view.model

                header: RowLayout {
                    width: parent.width
                    ExpressionInput {
                        id: input
                        Layout.fillWidth: true
                        text: "sin x*sin y"
                        focus: true
                        Component.onCompleted: selectAll()
                        onAccepted: {
                            input.selectAll()
                            var err = app.functionsModel().addFunction(input.text, 4, app.variables)
                            if (err.length>0)
                                console.warn("errors:", err)
                        }
                    }
                    Button {
                        iconName: "list-add"
                        onClicked: {
                            input.selectAll()
                            var err = view.addFunction(input.text, app.variables)
                            if (err.length>0)
                                console.warn("errors:", err)
                        }
                    }
                }

                footer: Button {
                    text: i18n("Clear All")
                    onClicked: {
                        view.model.clear()
                        view.resetView()
                    }
                }
            }
        }

        AddButton {
            onClicked: {
                dialog.open();
            }
        }
    }
}
