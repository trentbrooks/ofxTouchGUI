#pragma once


#include "ofMain.h"
#include "ofxTouchGUIBase.h"


class ofxTouchGUIDataGraph : public ofxTouchGUIBase {
	
public:
    
    ofxTouchGUIDataGraph();
	~ofxTouchGUIDataGraph();
    
    void reset();
    
    // for charting the values over time    
    virtual void setCustomRange(float min, float max);
    virtual void setMaximumValues(int count); // size of chart entries
    deque<float> savedValues;
    virtual void insertValue(float val);
    float currentValue;
    float getMinValue() { return min; }
    float getMaxValue() { return max; }
    
    // gl    
    void setFilled(bool fill);
    void setGraphFillClr(ofColor clr);
    
    // display
    virtual void draw();
    
protected:
    
    float min;
    float max;
    bool isCustomRangeSet; // off by default, graph is scaled dynamically
    int maxValuesToSave;
    
    //gl
    vector<float> shapeVertices;
    ofColor graphFillClr;
    bool isFilled; // line based or triangle based
};

