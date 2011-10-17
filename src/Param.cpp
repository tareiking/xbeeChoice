//
//  Param.cpp
//  emptyExample
//
//  Created by Tarei on 17/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Param.h"

Param::Param(){
    name = "param name";
}

Param::Param(int _type, string _name, string _description, string _command){
    type = _type;
    name = _name;
    description = _description;
    command = _name;
  
//    cout << "param addedd: " << description << "\r";
    // needs PIN identifier
}

string Param::getName(){
    return name;
}

int Param::getType(){
    return type;
}

string Param::getDescription(){
    return description;
}

string Param::getCommand(){
    return command;
}

int Param::getPin(){
    return parentPin;
}

Param::~Param(){};