#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // set some default values
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
    settings.loadSettings("settings.xml", true, true); // savefile, default font, use mouse
    settings.loadBackground("guiBg.png");
    
    // add any random properties to be saved - good for configs, once set can only be changed via xml
    settings.addFixedVar(&host, "host");
    settings.addFixedVar(&port, "port");

    // enable osc
    settings.setupSendOSC(host, port); 
    
    // add controls
    int itemsWidth = 200;
    int itemsHeight = 25;
    int destX = 20;
    settings.addText("ofxTouchGUI - " + host + ":" + ofToString(port), destX, 25, itemsWidth); 
    settings.addSlider("SLIDER X", &sliderValX, 0.0f, 1.0f, destX, 35, itemsWidth, itemsHeight); 
    settings.addSlider("SLIDER Y", &sliderValY, 0.0f, 100.0f, destX, 65, itemsWidth, itemsHeight); 
    settings.addDropDown("DROPDOWN LIST A", 5, ddOptions, destX, 95, itemsWidth, itemsHeight); 
    settings.addDropDown("DROPDOWN LIST B", 4, &selectListIndex, ddOptions, destX, 125, itemsWidth, itemsHeight);
    settings.addToggleButton("TOGGLE A", &toggleValA, destX, 155, 137, itemsHeight);
    settings.addToggleButton("TOGGLE B", &toggleValB, destX, 185, 137, itemsHeight);     
    settings.addText(description, destX + 5, 230, itemsWidth); 
    
    ofxTouchGUIButton* saveBtn = settings.addButton("SAVE", destX, 325, 89, itemsHeight); 
    ofAddListener(saveBtn->onChangedEvent, this, &testApp::onButtonPressed);
    ofxTouchGUIButton* resetBtn = settings.addButton("RESET", 114, 325, 89, itemsHeight); 
    ofAddListener(resetBtn->onChangedEvent, this, &testApp::onButtonPressed);
    
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