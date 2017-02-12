import bb.cascades 1.4

Page {
    id: page
    titleBar: titlebar
    
    Container {
        ItemList {
            id: theItemList
        }
    }
    
    actions: [
        ActionItem {
           title: qsTr("Add")
           imageSource: "asset:///images/ic_add.png"
           ActionBar.placement: ActionBarPlacement.Signature
           
           shortcuts: SystemShortcut {
               type: SystemShortcuts.CreateNew
           }
           
           onTriggered: {
               var itemSheet = itemSheetDefinition.createObject();
               itemSheet.open();
           }
        },
        ActionItem {
            title: qsTr("Search")
            imageSource: "asset:///images/ic_search.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            
            shortcuts: SystemShortcut {
                type: SystemShortcuts.Search
            }
            
            onTriggered: {
                page.titleBar = searchbar;
                searchbar.textField.requestFocus();
            }
        },
        MultiSelectActionItem {
            multiSelectHandler: theItemList.multiSelectHandler
        },
        
        DeleteActionItem {
        }
    ]
    
    attachedObjects: [
        ComponentDefinition {
           id: itemSheetDefinition
           source: "AddSheet.qml"
        },
        
        TitleBar {
            id: titlebar
            scrollBehavior: TitleBarScrollBehavior.Sticky
            kind: TitleBarKind.Segmented

            options: [
                Option {
                    text: qsTr("Day")
                    value: "day"
                },
                Option {
                    text: qsTr("Month")
                    value: "month"
                },
                Option {
                    text: qsTr("Year")
                    value: "year"
                }
            ]
            onSelectedValueChanged: {
                theItemList.set_filter(selectedValue);
            }
        },

        TitleBar {
            id: searchbar
            property alias textField: kindprop.textField

            kind: TitleBarKind.TextField
            kindProperties: TextFieldTitleBarKindProperties {
                id: kindprop
                textField.hintText: qsTr("not implement yet") // qsTr("Search items")
            }
            scrollBehavior: TitleBarScrollBehavior.Sticky

            dismissAction: ActionItem {
                title: qsTr("Cancel")
                onTriggered: {
                    page.titleBar = titlebar
                    kindprop.textField.text = ""
                }
            }
        }
    ]
}
