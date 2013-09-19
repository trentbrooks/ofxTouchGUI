#include "ofxTouchGUIDropDown.h"



ofxTouchGUIDropDown::ofxTouchGUIDropDown(){
    
    toggleShowList = false;
    
    defaultSelectId = initialSelectId = -1;
    selectId = &initialSelectId;
    numListItems = 0;
    listValues = NULL;
    listHeight = 0;
    
    // DEFAULT BUTTON BACKGROUND CLRS: GRADIENT DARKER GRAY 75%
    // creates a darker fade from top to bottom instead of left to right
    bgClrTL = ofColor(120,120,120,255); //rgba
    bgClrTR = ofColor(120,120,120,255); //rgba
    bgClrBL = ofColor(180,180,180,255); //rgba
    bgClrBR = ofColor(180,180,180,255); //rgba  
    
    arrowClr = ofColor(255,255,255,180); //rgba
    arrowOffset = 5; // doubles for retina. making this a percentage of the height instead
    
    isInteractive = true;
}

ofxTouchGUIDropDown::~ofxTouchGUIDropDown(){
	
}

void ofxTouchGUIDropDown::resetDefaultValue(){
    
    // reset the toggle value to the original value passed in by setValues
    //cout << "reseting defaut " + ofToString(defaultSelectId) << endl;
    *selectId = defaultSelectId;
}

//--------------------------------------------------------------
void ofxTouchGUIDropDown::setArrowClr(ofColor clr) {
    arrowClr = clr;
}

//--------------------------------------------------------------
void ofxTouchGUIDropDown::setValues(int numValues, string* listValues) {
        
    //this->listValues = listValues;
    numListItems = numValues;
    this->listValues = new string[numListItems];
    
    for(int i = 0; i < numListItems; i++) {
        this->listValues[i] = listValues[i];
    }   
    
    listHeight = int(height * numListItems);
    arrowOffset = height * .15;
}

void ofxTouchGUIDropDown::setValues(int numValues, string* listValues, int* selectedId) {    

    defaultSelectId = ofClamp(*selectedId, -1, numValues-1); // -1
    //cout << "XXXXX setting default: " + ofToString(defaultSelectId) << endl;
    
    this->selectId = selectedId;
    
    //  update the list
    setValues(numValues, listValues);
}

void ofxTouchGUIDropDown::setValues(int numValues, vector<string> listValues) {
    
    //this->listValues = listValues;
    numListItems = numValues;
    this->listValues = new string[numListItems];
    
    for(int i = 0; i < numListItems; i++) {
        this->listValues[i] = listValues[i];
    }   
    
    listHeight = int(height * numListItems);
    arrowOffset = height * .15;
}

void ofxTouchGUIDropDown::setValues(int numValues, vector<string> listValues, int* selectedId) {    
    
    defaultSelectId = ofClamp(*selectedId, -1, numValues-1); // -1
    //cout << "XXXXX setting default: " + ofToString(defaultSelectId) << endl;
    
    this->selectId = selectedId;
    
    //  update the list
    setValues(numValues, listValues);
}

    
//--------------------------------------------------------------
void ofxTouchGUIDropDown::draw(){
    
    if(!hidden) {
        ofPushMatrix();
        ofTranslate(int(posX), int(posY));
        
        float destValX = width - height;
        
        // draw the background rectangle- move the right side of the percentage bar. modify vertex values directly
        vertexArr[1] = 0; // TL y
        vertexArr[3] = 0; // TR y
        vertexArr[5] = height; // BL y
        vertexArr[7] = height; // BR y
        drawGLRect(vertexArr, colorsArr);
        
            
        // draw triangle upside down or not 
        float arrowCenterX = (width - destValX) * .5 + destValX; 
        float arrowCenterY = height * .5;  
        float destArrowLowerY = arrowOffset * .5 + arrowCenterY;
        float destArrowUpperY = -arrowOffset * .5 + arrowCenterY; 
        ofSetColor(arrowClr);
        ofFill();

        if(toggleShowList) {        
             /*ofTriangle(arrowCenterX - arrowOffset, destArrowUpperY, arrowCenterX, destArrowUpperY + arrowOffset, arrowCenterX + arrowOffset, destArrowUpperY);
            
            // display drop down list bg
            vertexArr[1] = height; // TL y
            vertexArr[3] = height; // TR y
            vertexArr[5] = height + listHeight;//height * numListItems; // BL y
            vertexArr[7] = height + listHeight;//height * numListItems; // BR y
            drawGLRect(vertexArr, colorsArr);//colorsArrActive);
            
            // draw items
            ofPushStyle();
            for(int i = 0; i < numListItems; i++) {
                int listY = (i + 1) * height;// + posY;//int destY = int(textOffsetY + height * 0.5);
                
                // draw active background
                if(*selectId == i) {                
                    vertexArrActive[1] = listY; // TL y
                    vertexArrActive[3] = listY; // TR y
                    vertexArrActive[5] = listY + height; // BL y
                    vertexArrActive[7] = listY + height; // BR y
                    drawGLRect(vertexArrActive, colorsArrActive);
                }            
                
                // draw text
                ofSetColor(textColour);
                drawText(listValues[i], textOffsetX, listY + int(textOffsetY + height * 0.5));
                
                // draw line dividers
                if(i > 0) {
                    ofSetColor(arrowClr);
                    //ofLine(0, listY, width, listY); // weird bug with ofLine when 4x sampling enabled in main.mm
                    ofRect(0, listY, width, 1); // 1px rect instead of ofLine for now
                }
            }      
            ofPopStyle();*/
            
         } else {
              ofTriangle(arrowCenterX - arrowOffset, destArrowLowerY, arrowCenterX, destArrowLowerY - arrowOffset, arrowCenterX + arrowOffset, destArrowLowerY);
         }
        
        // draw text
        ofPushStyle();
        ofSetColor(textColourLight);
        //drawText((toggleShowList) ? label : listValues[selectId], 0);
        drawText((*selectId < 0) ? label : listValues[*selectId], 0);
        ofPopStyle();
          
        ofPopMatrix();   
    }
}

void ofxTouchGUIDropDown::drawOverlay() {
    
    //for drawing the overlay dropdown  on top of everything else
    if(!hidden && toggleShowList) {
        ofPushMatrix();
        ofTranslate(int(posX), int(posY));
            
        float destValX = width - height;
        
        // draw triangle upside down or not
        float arrowCenterX = (width - destValX) * .5 + destValX;
        float arrowCenterY = height * .5;
        float destArrowLowerY = arrowOffset * .5 + arrowCenterY;
        float destArrowUpperY = -arrowOffset * .5 + arrowCenterY;
        ofSetColor(arrowClr);
        ofFill();
        
        ofTriangle(arrowCenterX - arrowOffset, destArrowUpperY, arrowCenterX, destArrowUpperY + arrowOffset, arrowCenterX + arrowOffset, destArrowUpperY);
        
        // display drop down list bg
        vertexArr[1] = height; // TL y
        vertexArr[3] = height; // TR y
        vertexArr[5] = height + listHeight;//height * numListItems; // BL y
        vertexArr[7] = height + listHeight;//height * numListItems; // BR y
        drawGLRect(vertexArr, colorsArr);//colorsArrActive);
        
        // draw items
        ofPushStyle();
        for(int i = 0; i < numListItems; i++) {
            int listY = (i + 1) * height;// + posY;//int destY = int(textOffsetY + height * 0.5);
            
            // draw active background
            if(*selectId == i) {
                vertexArrActive[1] = listY; // TL y
                vertexArrActive[3] = listY; // TR y
                vertexArrActive[5] = listY + height; // BL y
                vertexArrActive[7] = listY + height; // BR y
                drawGLRect(vertexArrActive, colorsArrActive);
            }
            
            // draw text
            ofSetColor(textColour);
            drawText(listValues[i], textOffsetX, listY + int(textOffsetY + height * 0.5));
            
            // draw line dividers
            if(i > 0) {
                ofSetColor(arrowClr);
                //ofLine(0, listY, width, listY); // weird bug with ofLine when 4x sampling enabled in main.mm
                ofRect(0, listY, width, 1); // 1px rect instead of ofLine for now
            }
        }
        ofPopStyle();        
        ofPopMatrix();
    }
}


// need to override the down + up functions for dropdowns
bool ofxTouchGUIDropDown::onDown(float x, float y){
    
    if(!isInteractive || hidden) return false;
        
    // when the dropdown area is touched, or the menu is already opened
    if(hitTest(x,y) || toggleShowList) {
        isPressed = true;
        return true;
    } 

    return false;
}

bool ofxTouchGUIDropDown::onUp(float x, float y){
    
    if(!isInteractive || hidden) return false;
    

    if(isPressed) {
        
        // reset press same as normal button
        isPressed = false;
        
        // activate/deactivate dropdown menu
        if(hitTest(x,y)) {            
            // switch the toggle value
            toggleShowList = !toggleShowList;
            //ignoreExternalEvents = itemActive = toggleShowList; // static property (ignoreEvents)
            return true;
        }
        // check if selected a dropdown item
        else if(toggleShowList) {
            
            // reset everything
            //toggleShowList = itemActive = ignoreExternalEvents = false;
            toggleShowList = false;
            
            // when clicked in list
            if(hitTest(x, y, width, height + listHeight)) {
                
                int selected = ( (y - posY) / listHeight) * numListItems - 1;
                doSelectAction(selected);
                //*selectId = ( (y - posY) / listHeight) * numListItems - 1;
                //ofNotifyEvent(onChangedEvent,label,this);
                //sendOSC(*selectId);
                return true;
            }             
        }
    }
    
    return false;
}

void ofxTouchGUIDropDown::doSelectAction(int select, bool doOSC) {
    
    *selectId = select;
    ofNotifyEvent(onChangedEvent,label,this);
    if(doOSC) sendOSC(*selectId);
}

int ofxTouchGUIDropDown::getValue() {
    
    return *selectId;
}





