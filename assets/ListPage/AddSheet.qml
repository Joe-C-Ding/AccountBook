import bb.cascades 1.4

Sheet {
    id: sheet
    property bool isView: false
    property variant index: []
    
    Page {
        titleBar: TitleBar {
            id: titlebar
            title: isView ? qsTr("View Item") : qsTr("Edit Item")
            
            acceptAction: ActionItem {
                id: save
                title: isView ? qsTr("Edit") : qsTr("Save")
                enabled: isView
                
                onTriggered: {
                    if (isView) {
                        isView = false;
                    } else {
                        
                    }
                }
            }
            
            dismissAction: ActionItem {
                title: qsTr("Back")
                onTriggered: {
                    sheet.close();
                }
            }
        }
        
        Container {
            topPadding: ui.du(3.0)
            leftPadding: ui.du(3.0)
            rightPadding: ui.du(3.0)
            
            DateTimePicker {
                id: datepicker
                
                title: qsTr("Date")
                mode: DateTimePickerMode.DateTime
                enabled: !isView
            }
            
            Divider {
            }
            
            TextField {
                id: expense
                hintText: qsTr("expense")
                inputMode: TextFieldInputMode.NumbersAndPunctuation
                enabled: !isView
                
                onTextChanging: {
                    save.enabled = (text != "" && item.text != "");
                }
            }
            
            TextField {
                id: item
                hintText: qsTr("item")
                enabled: !isView
                
                onTextChanging: {
                    save.enabled = (text != "" && expense.text != "");
                }
            }
            
            TextField {
                id: note
                hintText: qsTr("note")
                enabled: !isView
            }
        }
    }
    
//    onIndexPathChanged: {
//        if (indexPath.length < 4) {
//            isView = false;
//            
//            datepicker.value = new Date();
//            expense.text = "";
//            item.text = "";
//            note.text = "";
//        } else {
//            var choenItem = datamodel.data(indexPath);
//            isView = true;
//            
//            datepicker.value = new Date(choenItem["date"]);
//            expense.text = choenItem["expense"];
//            item.text = choenItem["detail"];
//            note.text = choenItem["comment"];
//        }
//    }
}
