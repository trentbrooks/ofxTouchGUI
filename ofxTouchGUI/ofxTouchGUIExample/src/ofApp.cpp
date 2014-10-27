#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(20);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    
    // defaults
    mouseX = mouseY = 0;
    sliderValX = 0.69f;
    sliderValY = 30;
    toggleValA = true;
    toggleValB = false;
    selectListIndex = 1;
    inputText = "Input text...";
    string ddOptions[] = {"Oranges", "Bananas", "Apples", "Kiwis", "Mangoes"};
    string description = "ofxTouchGUI includes slider, dropdown list, button/image button, toggle button, text/title fields, input text (ios only atm), and general fixed variables. All items are custom positioned/sized on creation. Colours, fonts, etc can be changed. Settings can be saved to XML. Values can be sent via OSC.";
    
    
    // settings
    settings.loadSettings("settings.xml", true, true); // savefile, default font, use mouse
    //settings.loadFonts("stan0755.ttf", "VAGRoundedStd-Light.otf", 6, 14, true); // optional
    settings.setupSendOSC("10.0.1.134", 5555); // optional (send to iOS device running ofxTouchGUIExampleIOS. Remember to change ip to match your ios device)
    settings.setupReceiveOSC(5556); // optional (example receives from iOS device running ofxTouchGUIExampleIOS)
    //settings.setWindowPosition(ofGetWidth()-250, 0); // optional
    
    // add controls
    settings.addTitleText("OFXTOUCHGUI " + ofToString(OFXTOUCHGUI_VERSION))->setBackgroundVisible(true);
    settings.addSlider("SLIDER X", &sliderValX, 0.0f, 1.0f);
    settings.addSlider("SLIDER Y", &sliderValY, 0, 100);
    settings.addDropDown("DROPDOWN LIST A", 5, ddOptions);
    settings.addDropDown("DROPDOWN LIST B", 4, &selectListIndex, ddOptions);
    settings.addToggleButton("TOGGLE A", &toggleValA);
    settings.addToggleButton("TOGGLE B", &toggleValB);
    settings.addText(description);
    settings.addTextInput(&inputText);
    settings.setItemSize(200, 100);
    graph= settings.addDataGraph("GRAPH MOUSE X", 500);
    graph->setCustomRange(0, ofGetWidth());
    settings.setItemSize(200, 25);
    settings.addButton("SAVE");
    settings.addButton("RESET");

    
    // adds a listener to all gui items, pointing to onGuiChanged();
    settings.addEventListenerAllItems(this);

}


void ofApp::onGUIChanged(ofxTouchGUIEventArgs& args) {//const void* sender, string &buttonLabel) {
    
    ofxTouchGUIBase* target = args.target;
    string buttonLabel = target->getLabel();
        
    // or just use the label as the identifier
    if(buttonLabel == "SAVE") {
        settings.saveSettings();
    }
    else if(buttonLabel == "RESET") {
        settings.resetDefaultValues(); // reset to the code entered values
        //settings.resetFromSettings("settings.xml"); // reset to the last saved xml values
    }    
}

//--------------------------------------------------------------
void ofApp::update(){

    //if(ofGetMousePressed())
        //ofLog() << "mouse pressed " << ofGetMousePressed();
}

//--------------------------------------------------------------
void ofApp::draw(){

    settings.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case ' ':
            settings.toggleDisplay();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    graph->insertValue(x);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
