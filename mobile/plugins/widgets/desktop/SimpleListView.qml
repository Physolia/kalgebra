import QtDesktop 0.1

TableView
{
    id: view
    property alias role: col.role
    headerVisible: false

    TableColumn {
        id: col
        
        caption: "Value"
    }
}