#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	
    bool isRetina = (ofGetWidth() >= 640) ? true : false;
    int retinaScale = (isRetina) ? 2 : 1;
    
    
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    iPhoneSetOrientation(OFXIPHONE_ORIENTATION_PORTRAIT);	
	ofBackground(127,127,127);
    ofEnableAlphaBlending();
    
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
    settings.loadFont("VAGRoundedStd-Light.otf", 10 * retinaScale, 20 * retinaScale, true); // path to font, small font size and large font size - antialiased (optional)
    settings.loadBackground((isRetina) ? "guiBg@2x.png" : "guiBg.png"); // path to image (retina image: guiBg@2x.png)  
    //settings.autoDraw();
    
    
    // add constants or variables to be saved - good for configs
    //settings.setConstant("host", &host);
    //settings.setConstant("port", &port);
    //settings.setVariable("host", &host);
    //settings.setVariable("port", &port);
    
    int guiItemWidth = ofGetWidth()-(40 * retinaScale);
    int guiItemHeight = 35* retinaScale;
    
    // add controls - all controls in this example are manually positioned + sized (remove those parameters for auto placement)
    settings.addTitleText("ofxTouchGUI", 20 * retinaScale, 40 * retinaScale, guiItemWidth); // label, x, y, width, height
    settings.addText("OSC settings (host/port):", 21 * retinaScale, 47 * retinaScale, guiItemWidth); // label, x, y, width, height (auto wraps text to width)
    hostInput = settings.addTextInput(&host, 20, 75, 120, 35); // text inputs are native, so no need to multiple by retina scale
    portInput = settings.addTextInput(&portStr, 145, 75, 75, 35); // text inputs are native, so no need to multiple by retina scale
    ofxTouchGUIButton* oscBtn = settings.addButton("SETUP", 225* retinaScale, 75* retinaScale, 74* retinaScale, guiItemHeight); // label, x, y, width, height
    //oscBtn->loadImageStates("play-up.png", "play-down.png");
    ofAddListener(oscBtn->onChangedEvent, this, &testApp::onButtonPressed);
    settings.addSlider("SLIDER X", &sliderValX, 0.0f, 1.0f, 20* retinaScale, 115* retinaScale, guiItemWidth, guiItemHeight); // label, value, x, y, width, height
    settings.addSlider("SLIDER Y", &sliderValY, 0.0f, 100.0f, 20* retinaScale, 155* retinaScale, guiItemWidth, guiItemHeight); // label, value, x, y, width, height
    settings.addDropDown("DROPDOWN LIST A", 5, ddOptions, 20* retinaScale, 195* retinaScale, guiItemWidth, guiItemHeight); // label, num items, items[], x, y, width, height
    settings.addDropDown("DROPDOWN LIST B", 4, &selectListIndex, ddOptions, 20* retinaScale, 235* retinaScale, guiItemWidth, guiItemHeight); // label, num items, preselected index, items[], x, y, width, height
    settings.addToggleButton("TOGGLE A", &toggleValA, 20* retinaScale, 275* retinaScale, 137* retinaScale, guiItemHeight); // label, value, x, y, width, height
    settings.addToggleButton("TOGGLE B", &toggleValB, 162* retinaScale, 275* retinaScale, 137* retinaScale, guiItemHeight); // label, value, x, y, width, height    
    settings.addText(description, 25* retinaScale, 315* retinaScale, ofGetWidth()-(50* retinaScale)); // label, x, y, width, height (auto wraps text to width)
    
    
    // controls can be binded to methods
    ofxTouchGUIButton* saveBtn = settings.addButton("SAVE", 20* retinaScale, 425* retinaScale, 89* retinaScale, guiItemHeight); // label, x, y, width, height
    ofAddListener(saveBtn->onChangedEvent, this, &testApp::onButtonPressed); // note: buttons have no context unless binded to a function
    ofxTouchGUIButton* resetBtn = settings.addButton("RESET", 114* retinaScale, 425* retinaScale, 89* retinaScale, guiItemHeight); // label, x, y, width, height
    ofAddListener(resetBtn->onChangedEvent, this, &testApp::onButtonPressed); // bind a function to the element
    ofxTouchGUIButton* closeBtn = settings.addButton("CLOSE", 208* retinaScale, 425* retinaScale, 89* retinaScale, guiItemHeight); // label, x, y, width, height
    ofAddListener(closeBtn->onChangedEvent, this, &testApp::onButtonPressed); // bind a function to the element
    
    
    // enable osc
    settings.setupSendOSC(host, port);
    
    
    // items don't need to be added to the settings controller (ofxTouchGUI) - you can add individual elements
    customButton = new ofxTouchGUIButton();
    int imageSize = (isRetina) ? 132 : 66;
    string upImagePath = (isRetina) ? "play-up@2x.png": "play-up.png";
    string downImagePath = (isRetina) ? "play-down@2x.png" : "play-down.png";
    customButton->setDisplay("", int(ofGetWidth()/2) - (imageSize/2), int(ofGetHeight()/2) - (imageSize/2), imageSize, imageSize); // label, x, y, width, height
    customButton->loadImageStates(upImagePath, downImagePath);
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
	
    ofSetColor(255);
    
    // manual ui drawing
    settings.draw(); 
    
    // draw the custom button
    customButton->draw();
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

