#pragma once

#include "ofMain.h"
//#include "ofxiPhone.h"
#include "ofxTouchGUIBase.h"
#include "ofxTouchGUISlider.h"
#include "ofxTouchGUIText.h"
#include "ofxTouchGUIButton.h"
#include "ofxTouchGUIToggleButton.h"
#include "ofxTouchGUIDropDown.h"
#include "ofxTouchGUITextInput.h"
#include "ofxXmlSettings.h"
#include "ofxOsc.h"


static string SLIDER_TYPE= "slider";
static string BUTTON_TYPE ="button";
static string TOGGLE_TYPE="toggle";
static string TEXT_TYPE = "text";
static string DROPDOWN_TYPE = "dropdown";
static string TEXTINPUT_TYPE = "input";
static string FIXEDVAR_TYPE = "fixedVar";


class ofxTouchGUI {

public:
    
    ofxTouchGUI();
	~ofxTouchGUI();
    void resetDefaultValues();
    void loadSettings(string saveToFile = "settings.xml", bool loadDefaultFont = false, bool useMouse = false);
    bool useMouse; // by default this is false for touch controls
    
    // style
    bool hasBackground;
	void loadBackground(string imgPath);
    ofImage background;
    // color background
    bool hasBackgroundColor;
    void setBackgroundColor(ofColor bg,int bgX, int bgY, int bgWidth, int bgHeight);
    ofColor bg;
    int bgX,bgY,bgWidth,bgHeight;
    bool hasFont;
    void loadFont(string fontPath, int fontSize, int fontSizeLarge, bool antialiased = true);
    void loadFonts(string fontPathSmall, string fontPathLarge, int fontSizeSmall, int fontSizeLarge, bool antialisedSmall = true, bool antialisedLarge = true);
    ofTrueTypeFont guiFont;
    ofTrueTypeFont guiFontLarge;
    int fontSize;
    int fontSizeLarge;
    
    // drawing
    void draw();
    bool isHidden;
    void show();
    void hide();
    void toggleDisplay();
    bool isAutoDrawing;
    void autoDraw(bool allowAutoDraw = true);
    void aDraw(ofEventArgs &e);
        
    // gui create
    ofxTouchGUISlider* addSlider(string sliderLabel, float *val, float min, float max, int posX, int posY, int width, int height);
    ofxTouchGUISlider* addSlider(string sliderLabel, int *val, int min, int max, int posX, int posY, int width, int height);
    ofxTouchGUIText* addTitleText(string textLabel, int posX, int posY, int width);
    ofxTouchGUIText* addText(string textLabel, int posX, int posY, int width);
    ofxTouchGUIButton* addButton(string btnLabel, int posX, int posY, int width, int height);
    ofxTouchGUIToggleButton* addToggleButton(string toggleLabel, bool *toggleVal, int posX, int posY, int width, int height);
    ofxTouchGUIDropDown* addDropDown(string listLabel, int numValues, string* listValues, int posX, int posY, int width, int height);
    ofxTouchGUIDropDown* addDropDown(string listLabel, int numValues, int* selectedId, string* listValues, int posX, int posY, int width, int height);
    ofxTouchGUIDropDown* addDropDown(string listLabel, int numValues, vector<string> listValues, int posX, int posY, int width, int height);
    ofxTouchGUIDropDown* addDropDown(string listLabel, int numValues, int* selectedId, vector<string> listValues, int posX, int posY, int width, int height);
    ofxTouchGUITextInput* addTextInput(string *placeHolderText, int posX, int posY, int width, int height);
    
    // add a fixed var for saving - good for xml config options
    void addFixedVar(string *fixedVar,string varName);
    void addFixedVar(bool *fixedVar,string varName);
    void addFixedVar(int *fixedVar,string varName);
    void addFixedVar(float *fixedVar,string varName);
    int fixedVarCount;
    
    // save settings xml
    string saveToFile;
    string defaultSaveToFile;
    void saveSettings();
    ofxXmlSettings XML;
    bool settingsLoaded;
    
    // using a template to pass in parameter of any type
    template <typename T>
    bool saveControl(string currentType, string currentLabel, T* currentValue);    
    
    // all controls
    ofxTouchGUIBase* getItemByLabelAndType(string textLabel, string itemType);
    ofxTouchGUIBase* getItemById(string itemId);
    vector <ofxTouchGUIBase*> guiItems;
    int numGuiItems;
    
    // osc settings
    void setupSendOSC(string host, int port);
    void disableSendOSC();
    ofxOscSender* oscSender;
    //ofxOscMessage msg;
    bool oscEnabled;

};




