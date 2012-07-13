#pragma once


#include "ofMain.h"
#include "ofxTouchGUIBase.h"


class ofxTouchGUIText : public ofxTouchGUIBase {
	
public:
    
    ofxTouchGUIText();
	~ofxTouchGUIText();
    
    // display
    virtual void draw();
    bool isTextTitle;
    
    void formatText(bool isTextTitle);
    string wrapString(string text, int maxWidth);
     
};

