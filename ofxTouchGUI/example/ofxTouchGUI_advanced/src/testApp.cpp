#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //ofSetFrameRate(60);

    // set some default values
    sliderValX = 0.69f;
    sliderValY = 30;//30.0f;
    toggleValA = true;
    toggleValB = false;
    selectListIndex = 1;
    string ddOptions[] = {"Oranges", "Bananas", "Apples", "Kiwis", "Mangoes"};
    string description = "ofxTouchGUI includes slider, dropdown list, button/image button, toggle button, text/title fields, input text (ios only atm), and general fixed variables. All items are custom positioned/sized on creation. Colours, fonts, etc can be changed. Settings can be saved to XML. Values can be sent via OSC.";
    host = "127.0.0.1"; // change via xml
    port = 4444; // change via xml
    
    // gui settings
    settings.loadSettings(); //if iphone need to pass in the directory to save to public docs
    //settings.loadSettings(ofxiPhoneGetDocumentsDirectory(), true, false); //if iphone need to pass in the directory to save to public docs
    settings.useMouse = true; // set useMouse to true for mouse events instead of touch
    settings.loadFonts("stan0755.ttf", "VAGRoundedStd-Light.otf", 6, 20, true); // path to font, small font size and large font size - antialiased (optional)
    //settings.loadFont("stan0755.ttf", 6, 12, false);
    //settings.loadFont("VAGRoundedStd-Light.otf", 8, 20, true);
    settings.loadBackground("guiBg.png"); // path to image (retina image: guiBg@2x.png)  
    //settings.autoDraw();
    
    
    // add any random properties to be saved - good for configs, once set can only be changed via xml
    settings.setConstant("host", &host);
    settings.setConstant("port", &port);
    //settings.setVariable("host", &host); //can be changed
    //settings.setVariable("port", &port); // can be changed

    // enable osc?
    settings.setupSendOSC(host, port); 
    
    // add controls - all are manullay sized + positioned
    int itemsWidth = 200;
    int itemsHeight = 25;
    int destX = 20;
    int destY = 60;
    settings.addTitleText("ofxTouchGUI advanced", destX, destY-10, 300); // label, x, y, width, height
    settings.addText("OSC settings: " + host + ":" + ofToString(port) + " (can be changed in settings.xml)", destX, destY+5, 300); // label, x, y, width, height (auto wraps text to width)
    ofxTouchGUISlider* sliderA = settings.addSlider("SLIDER X", &sliderValX, 0.0f, 1.0f, destX, destY+30, itemsWidth, itemsHeight); // label, value, x, y, width, height
    ofAddListener(sliderA->onChangedEvent, this, &testApp::onSliderChanged);
    ofxTouchGUISlider* sliderB = settings.addSlider("SLIDER Y", &sliderValY, 0.0f, 100.0f, destX, destY+60, itemsWidth, itemsHeight); // label, value, x, y, width, height
    ofAddListener(sliderB->onChangedEvent, this, &testApp::onSliderChanged);
    ofxTouchGUIDropDown* dropdownA =  settings.addDropDown("DROPDOWN LIST A", 5, ddOptions, destX, destY+90, itemsWidth, itemsHeight); // label, num items, items[], x, y, width, height
    ofAddListener(dropdownA->onChangedEvent, this, &testApp::onDropdownChanged);
    ofxTouchGUIDropDown* dropdownB = settings.addDropDown("DROPDOWN LIST B", 4, &selectListIndex, ddOptions, destX, destY+120, itemsWidth, itemsHeight); // label, num items, preselected index, items[], x, y, width, height
    ofAddListener(dropdownB->onChangedEvent, this, &testApp::onDropdownChanged);
    ofxTouchGUIToggleButton * toggleA = settings.addToggleButton("TOGGLE A", &toggleValA, destX, destY+150, 137, itemsHeight); // label, value, x, y, width, height
    ofAddListener(toggleA->onChangedEvent, this, &testApp::onToggleChanged);
    ofxTouchGUIToggleButton * toggleB = settings.addToggleButton("TOGGLE B", &toggleValB, destX, destY+180, 137, itemsHeight); // label, value, x, y, width, height
    ofAddListener(toggleB->onChangedEvent, this, &testApp::onToggleChanged);
    settings.addText(description, destX + 5, destY+225, 300); // label, x, y, width, height (auto wraps text to width)
    
    // just displays variables
    settings.addVarText("Display X", &sliderValX); 
    settings.addVarText("Display Y", &sliderValY);
    
    ofxTouchGUIButton* saveBtn = settings.addButton("SAVE", destX, 430, 89, itemsHeight); // label, x, y, width, height
    ofAddListener(saveBtn->onChangedEvent, this, &testApp::onButtonPressed); // note: buttons have no context unless binded to a function
    ofxTouchGUIButton* resetBtn = settings.addButton("RESET", 114, 430, 89, itemsHeight); // label, x, y, width, height
    ofAddListener(resetBtn->onChangedEvent, this, &testApp::onButtonPressed); // bind a function to the element
    
    
    
    settings.hide();
    
    
    // items don't need to be added to the settings controller (ofxTouchGUI) - you can add individual elements
    customButton = new ofxTouchGUIButton();
    customButton->setDisplay("", int(ofGetWidth()/2) - 22, int(ofGetHeight()/2) - 22, 44, 44); // label, x, y, width, height
    customButton->loadImageStates("play-up.png", "play-down.png");
    customButton->enableMouse(); // or enableTouch
    //customButton->hide();
    ofAddListener(customButton->onChangedEvent, this, &testApp::onCustomButtonPressed); // bind a function to the element 
}


void testApp::onSliderChanged(const void* sender, string &buttonLabel) {
    
    ofxTouchGUISlider * slider = (ofxTouchGUISlider*)sender;
    cout << buttonLabel << " - " << slider->getValue() << endl;
}

void testApp::onDropdownChanged(const void* sender, string &buttonLabel) {
    
    ofxTouchGUIDropDown * dropdown = (ofxTouchGUIDropDown*)sender;
    cout << buttonLabel << " - " << dropdown->getValue() << endl;
}

void testApp::onToggleChanged(const void* sender, string &buttonLabel) {
    
    ofxTouchGUIToggleButton * toggle = (ofxTouchGUIToggleButton*)sender;
    cout << buttonLabel << " - " << toggle->getValue() << endl;
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

void testApp::onCustomButtonPressed(const void* sender, string &buttonLabel) {
    
    ofxTouchGUIButton * button = (ofxTouchGUIButton*)sender;
    cout << "Custom button pressed: " << button->getValue() << endl;
    settings.toggleDisplay();
    //customButton->show(); // must hit show when hiding the settings for custom buttons
    //(customButton->isHidden) ? customButton->show(): customButton->hide();
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    ofEnableAlphaBlending();
    ofSetColor(255);
    
    // manual ui drawing
    settings.draw(); 
    
    // draw the custom button
    ofSetColor(255);
    customButton->draw();
    
    //ofSetColor(0, 0, 0,200);
    //ofRect(0, 0, ofGetWidth(), ofGetHeight());
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