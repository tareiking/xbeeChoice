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
}

void Option::report(){
    cout << "============== option details============\r"
    << "name: " << name << "\r"
    << "pin: " << pin << "\r"
    << "description: " << description << "\r"    
    << "command: " << command << "\r"    
    << "params count: " << params.size() << "\r"    ;
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