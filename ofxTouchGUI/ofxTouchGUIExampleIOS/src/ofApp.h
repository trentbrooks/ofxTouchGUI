#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#include "ofxTouchGUI.h"

class ofApp : public ofxiOSApp{
	
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

    // settings
    ofxTouchGUI settings;
    void onGUIChanged(ofxTouchGUIEventArgs& args);
    
    // test values
    float sliderValX;
    int sliderValY;
    bool toggleValA, toggleValB;
    int selectListIndex;
    int mouseX, mouseY;
    
};


