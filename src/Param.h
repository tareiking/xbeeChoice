/// Params are valid arguments to augment options when sending to xbee
//
// Tarei King 2011
/// Loads the sub-option level named Param's from XML 
/// converts to objects to use in memory


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
    
    void setLoc(int x, int y);
    
    ofPoint getLoc();    
    string getName();
    int getType();
    string getDescription();
    string getCommand();
    int getPin();
 
    virtual  ~Param();
};


#endif
