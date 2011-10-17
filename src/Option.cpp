//
//  option.cpp
//  For xbee configuration script
//
//  Created by Tarei on 16/10/11.



#include "Option.h"

Option::Option(){
    name = "default name";
}

Option::Option(ofPoint _loc, int _pin, string _name, string _description, string _command){
    loc = _loc;
    pin = _pin;
    name = _name;
    description = _description;
    command = _command;
}

Option::Option(ofPoint _loc, string _name,  string _description, string _command){
       loc = _loc;
       name = _name;
       description = _description;
       command = _command;   
       pin = 999;
}

// add parameter to params vector for later 
void Option::addParam(int _type, string _name, string _description, string _command){
    Param *temp = new Param(_type, _name, _description, _command);
//    temp->getName();
    params.push_back(temp);
}

void Option::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    int width = 15;
    ofRect(loc.x, loc.y, width, width);
    ofDrawBitmapString(name, loc.x + 20, loc.y + 5);
}

void Option::drawPin(bool right){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    int width = 15;
    
    if(right == false){
        ofRect(loc.x, loc.y, width, width);
        ofDrawBitmapString(name, loc.x + 20, loc.y + 5);
        ofDrawBitmapString(ofToString(pin), loc.x-30, loc.y+5);        
    }
    
    if(right == true){
        ofRect(loc.x, loc.y, width, width);
        ofDrawBitmapString(name, loc.x + 40, loc.y + 5);
        ofDrawBitmapString(ofToString(pin), loc.x+15, loc.y+5);
    }
}

void Option::report(){
    cout << "============== option details============\r"
    << "name: " << name << "\r"
    << "pin: " << pin << "\r"
    << "description: " << description << "\r"    
    << "command: " << command << "\r"    
    << "params count: " << params.size() << "\r"    ;
}

void Option::reportParams(){
    cout << "params: ";
    for (int i=0; i<params.size(); i++){
        cout << "[" << params[i]->getName() << "]";        
        cout << "" << params[i]->getDescription() << "  ";
    }
    cout <<"\r";
}

void Option::drawParams(int x){
    int offset = 30;
    for (int i=0; i<params.size(); i++){
        ofSetColor(255, 255, 255);
        ofRect(x, offset, 15, 15);
//        ofDrawBitmapString(", x+20, offset);
        
        offset += 30;
    }
}
// MORE FUCKEN SETTERS

void Option::setLoc(ofPoint &_loc){
    loc = _loc;
}

void Option::setPin(int _pin){
    pin = _pin;
}

void Option::setName(string _name){
    name = _name;
}

void Option::setDescription(string _description){
    description = _description;
}

void Option::setCommand(string _command){
    command = _command;
}

// A FUCK LOAD OF GETTERS
ofPoint Option::getLoc(){
    return loc;
}

vector <Param *> Option::getParams(){
    return params;
}

int Option::getPin(){
    return pin;
}

string Option::getName(){
    return name;
}

string Option::getDescription(){
    return description;
}

string Option::getCommand(){
    return command;
}

Option::~Option(){
}