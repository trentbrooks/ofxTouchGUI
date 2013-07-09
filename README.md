![https://github.com/trentbrooks/ofxTouchGUI/raw/master/screenshot1.jpg](https://github.com/trentbrooks/ofxTouchGUI/raw/master/screenshot1.jpg)
## ofxTouchGUI ##
Openframeworks addon (tested with 0073 and 0074 ios and osx). It's basically just another GUI, but geared more towards remote controlling stuff from iPhone or iPad through OSC (works with desktop). Also allows to save fixed variables, listen to events, save to XML, and reset GUI values.

It's kind of like Memo's ofxSimpleGuiToo and the Processing library controlP5, but with OSC control and underwhelming gradient fills. It's also handy for creating inidividual UI elements on their own, eg. image buttons for different screens.

Includes slider, dropdown list, button/image button, toggle button, text/title fields, input text (ios only atm), and general variables. All items can be custom positioned/sized on creation. Colours, fonts, etc can be changed. Settings can be saved to XML. Values can be sent via OSC.

Ubuntu and windows user's will need to rename the file's from .mm to .cpp.

## Sample usage ##
	// setup
	ofxTouchGUI settings;
	settings.loadSettings("tg_settings.xml");

	// add a slider
	ofxTouchGUISlider* sliderX = settings.addSlider("SLIDER X", &someValue, 0.0f, 1.0f, 20, 115, 200, 35); // label, value, min, max, x, y, width, height
	// or auto position/size without extra parameters
	ofxTouchGUISlider* sliderX = settings.addSlider("SLIDER X", &someValue, 0.0f, 1.0f); // label, value, min, max

	// add an image button
	ofxTouchGUIButton* imageBtn = settings.addButton("MY IMAGE BUTTON", 225, 75, 74, 35); // label, value, x, y, width, height
	imageBtn->loadImageStates("play-up.png", "play-down.png"); // touch down and up images
	ofAddListener(imageBtn->onChangedEvent, this, &testApp::onImageButtonPressed); // bind a function in testApp to the element

	// enable osc
	settings.setupSendOSC("127.0.0.1", 4444);

	// add variables or constants (not for display, good for configs, etc.)
	settings.setConstant("myConstant", &someConstant);
    settings.setVariable("myVar", &someVar);

    // or add variables for display
    settings.addVarText("Mouse X", &mouseX); 
    settings.addVarText("Mouse Y", &mouseY);

See example files for more detailed code samples.

## Openframeworks addons required ##
* 	ofxXmlSettings & ofxOsc (in addons folder)

-Trent Brooks