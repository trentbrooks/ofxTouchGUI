#include "ofApp.h"

string keyboardText = "";
//--------------------------------------------------------------
void ofApp::setup(){	
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(20);
    
    // defaults
    mouseX = mouseY = 0;
    sliderValX = 0.69f;
    sliderValY = 30;
    toggleValA = true;
    toggleValB = false;
    selectListIndex = 1;
    string ddOptions[] = {"Oranges", "Bananas", "Apples", "Kiwis", "Mangoes"};
    string description = "ofxTouchGUI includes slider, dropdown list, button/image button, toggle button, text/title fields, input text (ios only atm), and general fixed variables. All items are custom positioned/sized on creation. Colours, fonts, etc can be changed. Settings can be saved to XML. Values can be sent via OSC.";
    
    
    // settings
    settings.loadSettings("settings.xml", false, false); // savefile, default font, use mouse (true for mouse, false for multitouch)
    settings.loadFonts("VAGRoundedStd-Light.otf", "VAGRoundedStd-Light.otf", 20, 40); // optional
    settings.setupSendOSC("10.0.1.131", 5556); // optional (send to desktop machine running ofxTouchGUIExample)
    settings.setupReceiveOSC(5555); // optional (receives from desktop machine running ofxTouchGUIExample)
    settings.setItemSize(ofGetWidth()-40, 70);
    settings.setItemSpacer(10);
    settings.setScrollable(true); // optional - new columns will not be auto created, all items add to a single column instead.
    
    // add controls
    settings.addTitleText("ofxTouchGUI " + ofToString(OFXTOUCHGUI_VERSION));
    settings.addSlider("SLIDER X", &sliderValX, 0.0f, 1.0f);
    settings.addSlider("SLIDER Y", &sliderValY, 0, 100);
    settings.addDropDown("DROPDOWN LIST A", 5, ddOptions);
    settings.addDropDown("DROPDOWN LIST B", 4, &selectListIndex, ddOptions);
    settings.addToggleButton("TOGGLE A", &toggleValA);
    settings.addToggleButton("TOGGLE B", &toggleValB);
    settings.addText(description);
    settings.addButton("SAVE");
    settings.addButton("RESET");

    // adds a listener to all gui items, pointing to onGUIChanged();
    settings.addEventListenerAllItems(this);
}

void ofApp::onGUIChanged(ofxTouchGUIEventArgs& args) {
    
    ofxTouchGUIBase* target = args.target;
    string buttonLabel = target->getLabel();
    
    // or just use the label as the identifier
    if(buttonLabel == "SAVE") {
        settings.saveSettings();
    }
    else if(buttonLabel == "RESET") {
        settings.resetDefaultValues();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	settings.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}
