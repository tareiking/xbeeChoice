//
//  CommandLoader.cpp
//  emptyExample
//
//  Created by Tarei on 17/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CommandLoader.h"

CommandLoader::CommandLoader(){
    if (xml.loadFile("x.bee"))
        cout << ".bee file loaded";
    else 
        cout << "error loaded .bee file, check data/ folder";

    // make special Options
    xml.pushTag("special");
    for(int i=0; i<xml.getNumTags("command"); i++){
        
        xml.pushTag("command", i);

        string name, description, command;
        name = xml.getValue("name", "");
        description = xml.getValue("description", "");
        command = xml.getValue("command", "");        
        
        // get location
        ofPoint loc;
        xml.pushTag("location");
        loc = ofPoint(xml.getValue("x", 0), xml.getValue("y", 0));
        xml.popTag();
        
        // add to vector
        Option *tmpOpt = new Option(loc, name, description, command);

        // check params
        if( xml.getNumTags("parameter") > 0){
            for (int i=0; i < xml.getNumTags("parameter"); i++){
                xml.pushTag("parameter");
                name = xml.getValue("name", "");
                description = xml.getValue("description", "");
                command = xml.getValue("command", "");
                tmpOpt->addParam(0, name, description, command);
                xml.popTag();
            }
        }
        
        

        xml.popTag();
    }
    xml.popTag();    
    
};