import bb.cascades 1.4


StandardListItem {
  title: ListItemData.year
  status: qsTr("¥") + Number(ListItemData.expense).toFixed(2)
  description: "%1 / %2 / %3"
      .arg(Number(ListItemData.max).toFixed(2))
      .arg(Number(ListItemData.mean).toFixed(2))
      .arg(Number(ListItemData.min).toFixed(2))
}
