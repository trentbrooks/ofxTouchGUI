#include "testApp.h"

//--------------------------------------------------------------

void testApp::setup(){
    
    // set some default values
    mouseX = mouseY = 0;
    sliderValX = 0.69f;
    sliderValY = 30;
    toggleValA = true;
    toggleValB = false;
    selectListIndex = 1;
    string ddOptions[] = {"Oranges", "Bananas", "Apples", "Kiwis", "Mangoes"};
    string description = "ofxTouchGUI includes slider, dropdown list, button/image button, toggle button, text/title fields, input text (ios only atm), and general fixed variables. All items are custom positioned/sized on creation. Colours, fonts, etc can be changed. Settings can be saved to XML. Values can be sent via OSC.";
    host = "127.0.0.1"; // change via xml
    port = 4444; // change via xml
    
    
    // gui settings
    settings.loadSettings("settings.xml", false, true); // savefile, default font, use mouse
    settings.loadFonts("stan0755.ttf", "VAGRoundedStd-Light.otf", 6, 14, true);
    settings.loadBackground("guiBg.png");    
    //settings.autoDraw();
    
    
    // add any random properties to be saved - good for configs, once set can only be changed via xml
    settings.setConstant("host", &host);
    settings.setConstant("port", &port);
    //settings.setVariable("host", &host); //can be changed
    //settings.setVariable("port", &port); // can be changed

    
    // enable osc
    settings.setupSendOSC(host, port); 

    // add controls
    settings.addText("ofxTouchGUI - " + host + ":" + ofToString(port));//->setBackgroundVisible(true);
    settings.addSlider("SLIDER X", &sliderValX, 0.0f, 1.0f);
    settings.addSlider("SLIDER Y", &sliderValY, 0, 100);    
    settings.addDropDown("DROPDOWN LIST A", 5, ddOptions);
    settings.addText("ofxTouchGUI - " + host + ":" + ofToString(port));
    settings.addDropDown("DROPDOWN LIST B", 4, &selectListIndex, ddOptions);
    settings.addToggleButton("TOGGLE A", &toggleValA);
    settings.addToggleButton("TOGGLE B", &toggleValB);    
    settings.addText(description);//, destX + 5, 230, itemsWidth);

    ofxTouchGUIButton* saveBtn = settings.addButton("SAVE"); 
    ofAddListener(saveBtn->onChangedEvent, this, &testApp::onButtonPressed);
    ofxTouchGUIButton* resetBtn = settings.addButton("RESET");
    ofAddListener(resetBtn->onChangedEvent, this, &testApp::onButtonPressed);
    
    //settings.nextColumn(); // jump to a new column?
    //settings.moveTo(350, 20); // move anywhere?
    
    // addVarText is just for displaying variables. Not hooked up with the OSC controller.
    settings.addVarText("Mouse X", &mouseX);
    settings.addVarText("Mouse Y", &mouseY);
    
}


void testApp::onButtonPressed(const void* sender, string &buttonLabel) {
    
    // could use the pointer to button that was pressed? eg. 
    ofxTouchGUIButton * button = (ofxTouchGUIButton*)sender;
    cout << buttonLabel << " - " << button->getValue() << endl;
    
    // or just use the label as the identifier
    if(buttonLabel == "SAVE") {
        settings.saveSettings();
    }
    else if(buttonLabel == "RESET") { 
        settings.resetDefaultValues();
    }
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    ofEnableAlphaBlending();
    
    // manual ui drawing
    settings.draw(); 

    ofDisableAlphaBlending();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

    if(key == ' ') settings.toggleDisplay();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}