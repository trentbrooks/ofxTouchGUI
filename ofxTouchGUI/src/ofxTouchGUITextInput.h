#pragma once


#include "ofMain.h"
#include "ofxTouchGUIBase.h"

#ifdef TARGET_OF_IPHONE
    #include "ofxiOSKeyboard.h"
#endif

/*
 ofxTouchGUITextInput.
 - originally just for ios
 - osx + win will use a dialog popup
 */

class ofxTouchGUITextInput : public ofxTouchGUIBase {
	
public:
    
    ofxTouchGUITextInput();
	~ofxTouchGUITextInput();
    
    virtual void resetDefaultValue();
    
    // display
    virtual void draw();
    
    virtual void hide();
    virtual void show(bool activateSingleItem);
    
    //int fontSize;
    
    void setInput(string *placeHolderText);
    string getInput();
    string *input;
    string defaultInput;
    void setPlaceHolderText(string text);
    
    // touch events
    virtual bool onUp(float x, float y, int pId=-1);
    
protected:
    
#ifdef TARGET_OF_IPHONE
    ofxiOSKeyboard* keyboard;
#endif
    
    //string placeHolderInput;
    
    bool keyboardSet;
    bool wasKeyboardOpen;
    void updateKeyboard();
    void onKeyboardInput();
};

