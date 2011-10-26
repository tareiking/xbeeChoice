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

        vector<char> stringToCharVector(string _incoming, bool _addCarriageReturn);
        
        void updateIncoming();
        void updateOutgoing();
    
    void reportIncoming();
    
    bool mouseInRect(int x, int y, int width, int height);
    
    vector<ofPoint> guiPoints;
    vector<char> outgoingStr;
    vector<char> incomingStr;
    
    CommandLoader loader;
    ofSerial serial;
    ofImage bg;
    
    ofxXmlSettings xml;
    vector<Option*> options;
    vector<Option*> testOpts;
    vector<Option*> specialCommands;
    vector<Option*> pinCommands;
    
};
