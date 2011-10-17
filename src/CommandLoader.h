//
//  CommandLoader.h
//  emptyExample
//
//  Created by Tarei on 17/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

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
    vector<Option> getPins();
    vector<Option> getSpecial();
};


#endif
