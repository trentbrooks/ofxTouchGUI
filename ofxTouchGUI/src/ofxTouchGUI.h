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


#define SLIDER_TYPE "slider"
#define BUTTON_TYPE "button"
#define TOGGLE_TYPE "toggle"
#define TEXT_TYPE "text"
#define DROPDOWN_TYPE "dropdown"
#define TEXTINPUT_TYPE "input"
#define CONST_TYPE "constant"
#define VAR_TYPE "variable"

enum { _INT, _FLOAT, _BOOL, _STRING };

struct NameValuePair {
    string name;
    void* value;
    int type;
    
    template <typename T>
    void setValue(T *valuePtr) {

        if(typeid(T) == typeid(int&))
            type = _INT;
        else if(typeid(T) == typeid(string&))
            type = _STRING;
        else if(typeid(T) == typeid(float&))
            type = _FLOAT;
        else if(typeid(T) == typeid(bool&))
            type = _BOOL;
        else
            cout << "* NameValuePair error: template type is unknown *" << endl;
        
        value = valuePtr;
    };
 
};

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

    // default positioning/sizing
    int defaultPosX;
    int defaultPosY;
    int defaultColumn;
    int defaultItemWidth;
    int defaultItemHeight;
    int defaultSpacer;
    void checkPosSize(int& posX, int& posY, int& width, int& height);
    int lastItemPosX;
    int lastItemPosY;
    int lastItemWidth;
    int lastItemHeight;
    
    // when auto positioning you can call this to change columns before adding another item
    void nextColumn();
    
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
    ofxTouchGUISlider* addSlider(string sliderLabel, float *val, float min, float max, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUISlider* addSlider(string sliderLabel, int *val, int min, int max, int posX=-1, int posY=-1, int width=-1, int height=-1);

    ofxTouchGUIText* addVarText(string textLabel, string *val, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIText* addVarText(string textLabel, int *val, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIText* addVarText(string textLabel, bool *val, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIText* addVarText(string textLabel, float *val, int posX=-1, int posY=-1, int width=-1, int height=-1);
    
    ofxTouchGUIText* addTitleText(string textLabel, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIText* addText(string textLabel, int posX=-1, int posY=-1, int width=-1, int height=-1);
    
    
    ofxTouchGUIButton* addButton(string btnLabel, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIToggleButton* addToggleButton(string toggleLabel, bool *toggleVal, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIDropDown* addDropDown(string listLabel, int numValues, string* listValues, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIDropDown* addDropDown(string listLabel, int numValues, int* selectedId, string* listValues, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIDropDown* addDropDown(string listLabel, int numValues, vector<string> listValues, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUIDropDown* addDropDown(string listLabel, int numValues, int* selectedId, vector<string> listValues, int posX=-1, int posY=-1, int width=-1, int height=-1);
    ofxTouchGUITextInput* addTextInput(string *placeHolderText, int posX=-1, int posY=-1, int width=-1, int height=-1);
    
    // add a constant for read only (set once from app, can only be changed in xml) - good for config options
    template <typename T>
    void setConstant(string constName,T *fixedConst); //pointer
    template <typename T>
    void setConstant(string constName,T fixedConst); // non-pointer
    int constantCount;
    
    // add a regular var for saving - by default values are over-written when added
    //void setVariable(string varName, string *regVar, bool overwriteXMLValue = false);
    //void setVariable(string varName, bool *regVar, bool overwriteXMLValue = false);
    //void setVariable(string varName, int *regVar, bool overwriteXMLValue = false);
   // void setVariable(string varName, float *regVar, bool overwriteXMLValue = false);
    template <typename T>
    void setVariable(string varName, T *regVar);
    vector <NameValuePair*>varItems;
    int variableCount;
    
    // save settings xml
    string saveToFile;
    string defaultSaveToFile;
    void saveSettings();
    ofxXmlSettings XML;
    bool settingsLoaded;
    
    // using a template to pass in parameter of any type
    template <typename T>
    bool saveControl(string currentType, string currentLabel, T* currentValue, bool overwriteXMLValue = false);    
    
    // all controls
    NameValuePair* getVarByLabel(string textLabel);
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




