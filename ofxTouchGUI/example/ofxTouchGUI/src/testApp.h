#pragma once

#include "ofMain.h"
#include "ofxTouchGUI.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        // ofxTouchGUI
        ofxTouchGUI settings;
        void setupGUI();
        
        // test values
        float sliderValX;
        int sliderValY;
        bool toggleValA;
        bool toggleValB;
        int selectListIndex;
        string host;
        int port;
        
        // bind methods to buttons
        void onButtonPressed(const void* sender, string &buttonLabel);

    
};
