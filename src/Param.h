//
//  Param.h
//  emptyExample
//
//  Created by Tarei on 17/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_Param_h
#define emptyExample_Param_h

#include "ofMain.h"

#include <iostream>

class Param {
    ofPoint loc;
    int type;
    string name;
    string description;
    string command;
    int parentPin;
            
public:
    Param();
    Param(int _type, string _name, string _description, string _command);
    string getName();
    int getType();
    string getDescription();
    string getCommand();
    int getPin();
};


#endif
