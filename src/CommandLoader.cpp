//
//  CommandLoader.cpp
//  emptyExample
//
//  Created by Tarei on 17/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CommandLoader.h"

CommandLoader::CommandLoader(){
    ofSetDataPathRoot("../Resources/");
    
    if (xml.loadFile("x.bee"))
        cout << ".bee file loaded" << "\r";
    else 
        cout << "error loaded .bee file, check data/ folder\r" ;

    // make special Options
    // make special Options  // clean up   
    xml.pushTag("special");
    int loop = xml.getNumTags("command");
    
    for(int i=0; i<loop; i++){
        
        xml.pushTag("command", i);

        string name, description, command;
        name = xml.getValue("name", "");
        description = xml.getValue("description", "");
        command = xml.getValue("ATCommand", "");        
        
        // get location
        ofPoint loc;
        xml.pushTag("location");
        loc = ofPoint(xml.getValue("x", 0), xml.getValue("y", 0));
        xml.popTag();
        
        // add to vector
        Option * tmpOpt = new Option(loc, name, description, command);

        if (xml.getNumTags("parameter") > 0){
            for (int j=0; j <=xml.getNumTags("parameter")-1; j++){
            xml.pushTag("parameter", j);
            tmpOpt->addParam(0, xml.getValue("name", "-"),
                                xml.getValue("description", "-"),
                                xml.getValue("command", "-"));
//                cout << xml.getValue("name", "");
            xml.popTag();
            }
        }
        
//        tmpOpt->report();
        special.push_back(tmpOpt);
        xml.popTag();
    }
    
    xml.popTag();    
    
    
    
    // make special options
    // make special Options // clean up
    xml.pushTag("pin");
    loop = xml.getNumTags("command");
    
    for(int i=0; i<loop; i++){
        
        xml.pushTag("command", i);
        
        string name, description, command;
        int pin;
        name = xml.getValue("name", "");
        description = xml.getValue("description", "");
        command = xml.getValue("ATCommand", "");    
        pin = xml.getValue("pin", 500);
        
        // get location
        ofPoint loc;
        xml.pushTag("location");
        loc = ofPoint(xml.getValue("x", 0), xml.getValue("y", 0));
        xml.popTag();
        
        // add to vector
        Option * tmpOpt = new Option(loc, pin, name, description, command);
        
        if (xml.getNumTags("parameter") > 0){
            for (int j=0; j <=xml.getNumTags("parameter")-1; j++){
                xml.pushTag("parameter", j);
                tmpOpt->addParam(0, xml.getValue("name", "-"),
                                 xml.getValue("description", "-"),
                                 xml.getValue("command", "-"));
//                cout << xml.getValue("name", "");
                xml.popTag();
            }
            
        }
        
//        tmpOpt->report();
//        tmpOpt->reportParams();
        pins.push_back(tmpOpt);
        xml.popTag();
    }
    xml.popTag();    
};

vector<Option *> CommandLoader::getSpecial(){
    return special;
}

vector<Option *> CommandLoader::getPins(){
    return pins;
}
