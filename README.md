![https://github.com/trentbrooks/ofxTouchGUI/raw/master/screenshot1.jpg](https://github.com/trentbrooks/ofxTouchGUI/raw/master/screenshot1.jpg)
![https://github.com/trentbrooks/ofxTouchGUI/raw/master/screenshot2.jpg](https://github.com/trentbrooks/ofxTouchGUI/raw/master/screenshot2.jpg)
## ofxTouchGUI ##
Openframeworks addon (tested with 007 and 0071 ios and osx). GUI addon I built to remote control stuff from iPhone or iPad through OSC, but works with desktop as well. I also wanted the ability to save fixed variables, listen to events, save to XML, and reset GUI values.

It's kind of like Memo's ofxSimpleGuiToo and the Processing library controlP5, but with OSC control and underwhelming gradient fills. It's also handy for creating inidividual UI elements on their own, eg. image buttons for different screens.

Includes slider, dropdown list, button/image button, toggle button, text/title fields, input text (ios only atm), and general fixed variables. All items are custom positioned/sized on creation. Colours, fonts, etc can be changed. Settings can be saved to XML. Values can be sent via OSC.

## Sample usage ##
	// setup
	ofxTouchGUI settings;
	settings.loadSettings("tg_settings.xml");

	// add a slider
	ofxTouchGUISlider* sliderX = settings.addSlider("SLIDER X", &someValue, 0.0f, 1.0f, 20, 115, 200, 35); // label, value, x, y, width, height

	// add an image button
	ofxTouchGUIButton* imageBtn = settings.addButton("MY IMAGE BUTTON", 225, 75, 74, 35); // label, value, x, y, width, height
	imageBtn->loadImageStates("play-up.png", "play-down.png"); // touch down and up images
	ofAddListener(imageBtn->onChangedEvent, this, &testApp::onImageButtonPressed); // bind a function in testApp to the element

	// enable osc
	settings.setupSendOSC("127.0.0.1", 4444);

See example files for more detailed code samples.

## Openframeworks addons required ##
* 	ofxXmlSettings & ofxOsc (in addons folder)

-Trent Brooks