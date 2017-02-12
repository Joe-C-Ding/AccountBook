import bb.cascades 1.4

StandardListItem {
    title: monthTitle(ListItemData.month)
    status: qsTr("¥") + Number(ListItemData.expense).toFixed(2)
    description: describe(ListItemData)
    
    function monthTitle(m) {
        var mname = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];
        return mname[Number(m)];
    }
    
    function describe(data) {
        var relative = 100 * (data.expense - data.m_mean) / data.m_mean
        relative = (relative > 0 ? " +" : " ") + Number(relative).toFixed(2) + "%";
        return qsTr("¥") + Number(ListItemData.m_mean).toFixed() + relative;
    }
}

