#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxTouchGUI.h"

class testApp : public ofxiPhoneApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
        // ofxTouchGUI
        ofxTouchGUI settings;
        
        // test values
        float sliderValX;
        int sliderValY;
        bool toggleValA;
        bool toggleValB;
        int selectListIndex;
        string host;
        int port;
        string portStr;
        
        // bind methods to buttons
        void onButtonPressed(const void* sender, string &buttonLabel);
        
        // input fields
        ofxTouchGUITextInput * hostInput;
        ofxTouchGUITextInput * portInput;
        
        // create gui items individually (eg. without a settings menu)
        ofxTouchGUIButton* customButton;
        void onCustomButtonPressed(const void * sender, string &buttonLabel);

};


