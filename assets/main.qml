import bb.cascades 1.4

import "ListPage"

TabbedPane {
    showTabsOnActionBar: false
    
    Tab {
        title: qsTr("Account")
        description: qsTr("List every day expense")
        
        ItemListPage {
            
        }
    }
    Tab {
        title: qsTr("Analysis")
        description: qsTr("Statistics report")
        
        Page {

        }
    }
    Tab {
        title: "Config"
        description: qsTr("Configure Classification")
        
        Page {

        }
    }
}
