//
//  Option.h
//  emptyExample
//
//  Created by Tarei on 17/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef emptyExample_Option_h
#define emptyExample_Option_h

#include <iostream>
#include "ofMain.h"
#include "Param.h"

class Option {
    ofPoint loc;
    int pin;
    string name;
    string description;
    string command;
    vector<Param> params;

    
public:
    Option();    
    Option(ofPoint _loc, int _pin, string _name,  string _description, string _command);
    Option(ofPoint _loc, string _name,  string _description, string _command);    
    void setLoc(ofPoint &_loc);
    void setPin(int _pin);
    void setName(string _name);
    void setDescription(string _description);
    void addParam(int _type, string _name, string _description, string _command);
    void setCommand(string _command);
    void draw();
    
    ofPoint getLoc();
    vector <Param> getParams();
    int getPin();
    string getName();
    string getDescription();
    string getCommand();
    
    
    
    
};



#endif
