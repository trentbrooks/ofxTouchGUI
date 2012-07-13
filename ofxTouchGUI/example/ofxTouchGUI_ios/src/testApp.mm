#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);
	
	ofBackground(127,127,127);
    
    
    // set some default values
    sliderValX = 0.69f;
    sliderValY = 30;
    toggleValA = true;
    toggleValB = false;
    selectListIndex = 1;
    string ddOptions[] = {"Oranges", "Bananas", "Apples", "Kiwis", "Mangoes"};
    string description = "ofxTouchGUI includes slider, dropdown list, toggle button, push button, text/title fields, input text (ios only atm), and general fixed variables. Values can be sent via OSC.";
    host = "127.0.0.1";
    portStr = "4444";
    port = ofToInt(portStr);
    
    // gui settings
    settings.loadSettings("tg_settings.xml"); // savefile, default font, use mouse
    //settings.useMouse = true; // set useMouse to true for mouse events instead of touch
    settings.loadFont("VAGRoundedStd-Light.otf", 10, 20, true); // path to font, small font size and large font size - antialiased (optional)
    settings.loadBackground("guiBg.png"); // path to image (retina image: guiBg@2x.png)  
    //settings.autoDraw();

    // add any random properties to be saved - good for configs
    //settings.addFixedVar(&host, "host");
    //settings.addFixedVar(&port, "port");
    
    
    // add controls
    settings.addTitleText("ofxTouchGUI", 20, 50, ofGetWidth()-40); // label, x, y, width, height
    settings.addText("OSC settings (host/port):", 21, 67, ofGetWidth()-50); // label, x, y, width, height (auto wraps text to width)
    hostInput = settings.addTextInput(&host, 20, 75, 120, 35);
    portInput = settings.addTextInput(&portStr, 145, 75, 75, 35);
    ofxTouchGUIButton* oscBtn = settings.addButton("SETUP", 225, 75, 74, 35); // label, x, y, width, height
    //oscBtn->loadImageStates("play-up.png", "play-down.png");
    ofAddListener(oscBtn->onChangedEvent, this, &testApp::onButtonPressed);
    settings.addSlider("SLIDER X", &sliderValX, 0.0f, 1.0f, 20, 115, ofGetWidth()-40, 35); // label, value, x, y, width, height
    settings.addSlider("SLIDER Y", &sliderValY, 0.0f, 100.0f, 20, 155, ofGetWidth()-40, 35); // label, value, x, y, width, height
    settings.addDropDown("DROPDOWN LIST A", 5, ddOptions, 20, 195, ofGetWidth()-40, 35); // label, num items, items[], x, y, width, height
    settings.addDropDown("DROPDOWN LIST B", 4, &selectListIndex, ddOptions, 20, 235, ofGetWidth()-40, 35); // label, num items, preselected index, items[], x, y, width, height
    settings.addToggleButton("TOGGLE A", &toggleValA, 20, 275, 137, 35); // label, value, x, y, width, height
    settings.addToggleButton("TOGGLE B", &toggleValB, 162, 275, 137, 35); // label, value, x, y, width, height
    
    settings.addText(description, 25, 335, ofGetWidth()-50); // label, x, y, width, height (auto wraps text to width)
    
    ofxTouchGUIButton* saveBtn = settings.addButton("SAVE", 20, 425, 89, 35); // label, x, y, width, height
    ofAddListener(saveBtn->onChangedEvent, this, &testApp::onButtonPressed); // note: buttons have no context unless binded to a function
    ofxTouchGUIButton* resetBtn = settings.addButton("RESET", 114, 425, 89, 35); // label, x, y, width, height
    ofAddListener(resetBtn->onChangedEvent, this, &testApp::onButtonPressed); // bind a function to the element
    ofxTouchGUIButton* closeBtn = settings.addButton("CLOSE", 208, 425, 89, 35); // label, x, y, width, height
    ofAddListener(closeBtn->onChangedEvent, this, &testApp::onButtonPressed); // bind a function to the element
    
    
    // enable osc
    settings.setupSendOSC(host, port);
    
    
    // items don't need to be added to the settings controller (ofxTouchGUI) - you can add individual elements
    customButton = new ofxTouchGUIButton();
    customButton->setDisplay("", int(ofGetWidth()/2) - 22, int(ofGetHeight()/2) - 22, 44, 44); // label, x, y, width, height
    customButton->loadImageStates("play-up.png", "play-down.png");
    customButton->enableTouch(); // or enableMouse
    customButton->hide();
    ofAddListener(customButton->onChangedEvent, this, &testApp::onCustomButtonPressed); // bind a function to the element    
}

void testApp::onButtonPressed(const void* sender, string &buttonLabel) {
    
    // could use the pointer to button that was pressed? eg. 
    ofxTouchGUIButton * button = (ofxTouchGUIButton*)sender;
    cout << buttonLabel << " - " << button->getValue() << endl;
    
    // or just use the label as the identifier
    if(buttonLabel == "SAVE") {
        settings.saveSettings();
        cout << "Saving settings" << endl;
    }
    else if(buttonLabel == "RESET") { 
        settings.resetDefaultValues();
        cout << "Resetting defaults" << endl;
    }
    else if(buttonLabel == "CLOSE") { 
        settings.hide();
        customButton->show();
        cout << "Hiding settings" << endl;
    }
    else if(buttonLabel == "SETUP") { 
        host = hostInput->getInput();
        portStr = portInput->getInput();
        port = ofToInt(portStr);
        settings.setupSendOSC(host, port); 
    }
    
}


void testApp::onCustomButtonPressed(const void* sender, string &buttonLabel) {
    
    cout << "Custom button pressed" << endl;
    settings.show();
    customButton->hide();
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255);
    
    // manual ui drawing
    settings.draw(); 
    
    // draw the custom button
    customButton->draw();
    
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

