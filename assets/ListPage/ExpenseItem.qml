import bb.cascades 1.4

StandardListItem {
    title: ListItemData.detail
    description: Qt.formatDateTime(new Date(ListItemData.date), "yyyy-MM-dd hh:mm:ss")
    status: '¥' + Number(ListItemData.expense).toFixed(2)
    
    // this ActionSet is for item context menu
    // see ListView.multiSelectAction bellow
    contextActions: ActionSet {
        DeleteActionItem {
        }
    }
}
