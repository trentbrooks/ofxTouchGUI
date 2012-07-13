#include "ofxTouchGUIText.h"



ofxTouchGUIText::ofxTouchGUIText(){
    
    isTextTitle = false;
}

ofxTouchGUIText::~ofxTouchGUIText(){
	
}


    
//--------------------------------------------------------------
void ofxTouchGUIText::draw(){
    
    if(!isHidden) {
        ofPushMatrix();
        ofTranslate(int(posX), int(posY));
        
        // draw text
        ofPushStyle();
        //ofSetColor(textColourDark); 
        ofSetColor(textColourLight); 
        
        if(isTextTitle) {
            drawLargeText(label, 0, 0); 
        } else {
            drawText(label, 0, 0);
        }
        
        ofPopStyle();      
        
        ofPopMatrix();
    }
    
    
}

/*
 int fontWidth = guiFont.stringWidth(label);
 guiFont.drawString(label, int(width - fontWidth - textOffsetX), int(textOffsetY + height * 0.5) );    
 guiFont.drawString(ofToString(formattedValue), textOffsetX, int(textOffsetY + height * 0.5) );
 }
 else
 {
 int fontWidth2 = (int)label.length() * 8; // trying to figure out how wide the default text is, magic number= 8px?
 */

void ofxTouchGUIText::formatText(bool isTextTitle) {
    
    this->isTextTitle = isTextTitle;
    if(isTextTitle) {
        // automatically offset the text based on the font size
        textOffsetX = fontSizeLarge;
        textOffsetY = int(textOffsetX / 2);
    }
    
    label = wrapString(label, width);
}

string ofxTouchGUIText::wrapString(string text, int maxWidth) {
	
	string typeWrapped = "";
	string tempString = "";
	vector <string> words = ofSplitString(text, " ");
	int stringwidth = 0;
    
	for(int i=0; i<words.size(); i++) {
		
		string wrd = words[i];
		
		// if we aren't on the first word, add a space
		if (i > 0) {
			tempString += " ";
		}
		tempString += wrd;
		
        if(hasFont) {
            
            if(isTextTitle) {
                stringwidth = guiFontLarge->stringWidth(tempString);
            } else {
                stringwidth = guiFont->stringWidth(tempString); 
            }
             
        } else {
            // magic number here used as well as slider!
            stringwidth = (int)tempString.length() * 8; // trying to figure out how wide the default text is, magic number= 8px?
        }
        
		if(stringwidth >= maxWidth) {
			typeWrapped += "\n";
			tempString = wrd;		// make sure we're including the extra word on the next line
		} else if (i > 0) {
			// if we aren't on the first word, add a space
			typeWrapped += " ";
		}
		
		typeWrapped += wrd;
	}
    
    return typeWrapped;
}







