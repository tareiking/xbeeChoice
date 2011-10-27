//! XBEE CONFIGURATOR: sends and receives AT commands for xbee config

/// Loads xml of options->parameters and then displays them as GUI items
/// Press 'space' to enter command mode
/// Then click options on screen, if they have multiple parameters these will be shown onscreen
/// Press 'enter' to send the message string
/// If something is missing, then you can 'roll your own' by manually typing onscreen

#pragma once
#include "ofMain.h"
#include "Option.h"
#include "Param.h"
#include "ofxXmlSettings.h"
#include "CommandLoader.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        vector<char> stringToCharVector(string _incoming, bool _addCarriageReturn); ///< Converts a string object to a vector of type char
        
        void updateIncoming();///< Converts messages from xbee to @incomingMessage variable
        void updateOutgoing();///< Sends @outgoingMessage to xbee    
    
    bool mouseInRect(int x, int y, int width, int height);///< Checks mouse location against rect(ish) and returns true if inside
    
    vector<ofPoint> guiPoints;  ///< vector of ofPoints for checking against mouseInrect and drawing gui rectangles
    vector<char> outgoingStr;   ///< vector of chars for sending to xbee
    vector<char> incomingStr;   ///< vector of chars for returning from xbee
    
    CommandLoader loader;       ///< loader. takes care of xml via commandLoader
    ofSerial serial;            
    ofImage bg;
    
    ofxXmlSettings xml;
    vector<Option*> options;            ///< contains all options returned from loader
    vector<Option*> testOpts;
    vector<Option*> specialCommands;    ///< contains all special (nonpin) commands from loader
    vector<Option*> pinCommands;        ///< contains all pin commands from loader
    
};
