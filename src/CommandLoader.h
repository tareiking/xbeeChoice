/// Loads data from xml and parses them into option, params etc
//
//
/// CommandLoader class loads xml settings and command details from xml found in the data/ folder
/// The x.bee and xml files can be edited directly to add new functionality.
/// Go ahead! Your welcome
/// Tarei King, 2011

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
    /// Does all the heavy lifting and creates vectors of type Option for use in mainclass
    CommandLoader();
    /// Returns vector of options for all pin commands in xml file
    vector<Option *> getPins();
    /// returns vector of options for all special (non-pin) commands in xml file
    vector<Option *> getSpecial();
};


#endif
