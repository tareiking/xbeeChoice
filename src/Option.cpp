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
    params.push_back(temp);
}

void Option::draw(bool selected){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(215, 215, 215);
    int width = 15;
    ofNoFill();
    ofRect(loc.x, loc.y, width, width);
    ofDrawBitmapString(name, loc.x + 20, loc.y + 5);
    ofFill();
    
    if (selected){
        ofSetColor(210,0,0);
        ofRect(loc.x, loc.y, width-3, width-3);
    }
    ofSetRectMode(OF_RECTMODE_CORNER);

}

void Option::drawPin(bool selected){
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    int width = 15;
      

        ofRect(loc.x, loc.y, width, width);
        ofDrawBitmapString(name, loc.x + 40, loc.y + 5);
        ofDrawBitmapString(ofToString(pin), loc.x+15, loc.y+5);

        ofSetRectMode(OF_RECTMODE_CORNER);
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
    }    cout <<"\r";
}

void Option::drawParams(int x, int selected){
    int offset = 30;
    ofSetRectMode(OF_RECTMODE_CENTER);
    for (int i=0; i<params.size(); i++){
        ofSetColor(232, 230, 237);
        
        ofNoFill();
        ofRect(x, offset, 15, 15);
        if(i == selected){
            ofSetColor(215, 0, 0);
            ofFill();
            ofRect(x, offset, 12, 12);
            ofSetColor(255,255,255);
            ofNoFill();
        }
        ofSetColor(232, 230, 237);
        ofDrawBitmapString(name, loc.x + 20, loc.y + 5);
        ofFill();

        string msg = "[";
        msg += params[i]->getName();
        msg += "] ";
        msg += params[i]->getDescription();
        ofDrawBitmapString(msg, x+20, offset);
        
        params[i]->setLoc(x, offset);
        offset += 30;
    
    }
    ofSetRectMode(OF_RECTMODE_CORNER);    
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

ofPoint Option::getLoc(){
    return loc;
}

vector <Param *> Option::getParams(){
    return params;
}

vector <ofPoint> Option::getParamsLoc(){
    vector<ofPoint> pLocs;
    // get param loc
    for (int i=0; i<getParams().size(); i++) {
        ofPoint temp = params[i]->getLoc();
        pLocs.push_back(temp);
    }

    return pLocs;
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