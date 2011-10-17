// CommandLoader.h
//
// Tarei King 2011
// Loads the XML file and makes a pointer array of objects for use
// with the x.bee configuration file

#ifndef emptyExample_CommandLoader_h
#define emptyExample_CommandLoader_h

#include "ofMain.h"
#include <iostream>
#include "Option.h"
#include "ofxXmlSettings.h"

class CommandLoader {
    ofxXmlSettings xml;
    vector<Option *> pins;
    vector<Option *> special;

    
public:
    CommandLoader();
    vector<Option *> getPins();
    vector<Option *> getSpecial();
};


#endif
