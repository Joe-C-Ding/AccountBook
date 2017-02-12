import bb.cascades 1.4
import bb.data 1.0

import com.accountbook.datamodel 1.0

ListView {
    id: theItemList
    accessibility.name: "Listing"
    property bool hasSelection: false
    
    property string filter: "month"
    rootIndexPath: [0]
    function set_filter(str) {
        filter = str;
        switch (str) {
            case "year":
                rootIndexPath = [];
                break;
            case "month":
                rootIndexPath = [0];
                break;
            case "day":
                rootIndexPath = [0, 0];
                break;
            default:
                console.log("set_filter: Wrong type: %1".arg(str));
                break;
        }
    }
    
    dataModel: ABDataModel {
        id: datamodel
        source: "data.db"
    }
    
    function itemType(data, indexPath) {
        var type = datamodel.itemType(indexPath);
        if (type != "item" && type != filter) {
            type += "header";
        }
        return type;
    }
    
    listItemComponents: [
        ListItemComponent {
            type: "rootheader"
            Header {
                title: qsTr("total: [¥%1]").arg(Number(ListItemData.mean).toFixed(2))
                subtitle: qsTr("¥") + Number(ListItemData.expense).toFixed(2)
            }
        },
        ListItemComponent {
            type: "year"
            YearItem {
            }
        },
        ListItemComponent {
            type: "yearheader"
            Header {
                title: ListItemData.year
                subtitle: qsTr("¥") + Number(ListItemData.expense).toFixed(2)
            }
        },
        ListItemComponent {
            type: "month"
            MonthItem {
            }
        },
        ListItemComponent {
            type: "monthheader"
            
            Header {
                title: monthtitle(ListItemData)
                subtitle: qsTr("¥") + Number(ListItemData.expense).toFixed(2)
                
                function monthtitle(data) {
                    var mname = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];
                    var month = mname[Number(data.month)];
                    return month.slice(0, 3) + ", " + data.year;
                }
            }
        },
        ListItemComponent {
            type: "item"
            ExpenseItem {
            }
        }
    ]
    
    // this list action will be added to every item context menu
    // so we can active multiselect from either item's context menu
    // or list's action menu. 
    multiSelectAction: MultiSelectActionItem {
    }
    
    multiSelectHandler {
        status: "None selected"
        
        actions: [
            DeleteActionItem {
                enabled: theItemList.hasSelection
            }
        ]
    }
    
    // Change the status text in the multiSelectHandler to show how many items
    // are selected
    onSelectionChanged: {
        if(selectionList().length > 1) {
            hasSelection = true
            multiSelectHandler.status = selectionList().length + " items selected";
        }
        else if(selectionList().length == 1) {
            hasSelection = true
            multiSelectHandler.status = "1 item selected";
        }
        else {
            hasSelection = false
            multiSelectHandler.status = "None selected";
        }
    }
    
    onTriggered: {
        switch (indexPath.length) {
            case 0:    // nothing to do with universal
            case 1:
                break;
            case 2:    // scroll to that year
                break;
            case 3:    // scroll to that month
                break;
            case 4:    // open a item viewer
                var itemSheet = itemSheetDefinition.createObject();
                itemSheet.index = indexPath;
                itemSheet.open();
                break;
            default:
                break;
        }
    }
    
    attachedObjects: [
        ComponentDefinition {
            id: itemSheetDefinition
            source: "AddSheet.qml"
        }
    ]
}