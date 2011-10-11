#include "testApp.h"

vector<string> guiStr;
bool bInCommandMode;
string msg;


void testApp::setup(){

    // setup serial and check devices
    serial.getDeviceList();
    if( serial.setup(0, 9600) ){ // hard coded, yuck
        printf("==================================-------- \r");        
        printf("Serial - 0, 9600 initiated. \r");
        printf("PRESS SPACE TO ENTER COMMAND MODE...... \r");        
    }; 
    
    serial.flush();    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    

    // setup gui items
    guiPoints.push_back(ofPoint(ofGetWidth()/2, 20));
//    guiPoints.push_back(ofPoint(50, 20));
//    guiPoints.push_back(ofPoint(50, 50));
//    guiPoints.push_back(ofPoint(50, 80));    
//    guiPoints.push_back(ofPoint(50, 120));
//    guiPoints.push_back(ofPoint(50, 160));
//    guiPoints.push_back(ofPoint(50, 200));
    
//    guiStr.push_back("+++");
    
// baud rates    
    guiStr.push_back("ATBD0");
    guiStr.push_back("ATBD1");
    guiStr.push_back("ATBD2");    
    guiStr.push_back("ATBD3");    
    guiStr.push_back("ATBD4");    
    guiStr.push_back("ATBD5");    
    guiStr.push_back("ATBD6");    
    guiStr.push_back("ATBD7");
    
// D0 hard codes
    guiStr.push_back("ATD00");    
    guiStr.push_back("ATD01");    
    guiStr.push_back("ATD02");    
    guiStr.push_back("ATD03");    
    
    guiStr.push_back("ATD04");    
    guiStr.push_back("ATD05");    
// D1 hard codes    
    guiStr.push_back("ATD10");    
    guiStr.push_back("ATD11");    
    guiStr.push_back("ATD12");    
    guiStr.push_back("ATD13");    
    guiStr.push_back("ATD14");    
    guiStr.push_back("ATD15");    
    
// Command codes
    guiStr.push_back("ATHV");
    guiStr.push_back("ATWR");
    guiStr.push_back("ATDL");
    guiStr.push_back("ATWR");
    guiStr.push_back("ATHV");
    guiStr.push_back("ATHV");
    
    
    // generate guiPoints on the fly
    int y = 20;
    for (int i = 0; i < guiStr.size(); i++){
            if (i < 11){
                guiPoints.push_back(ofPoint(50, y));
            } 
            if (i > 12 && i < 20){
                guiPoints.push_back(ofPoint(200, y));
            }
        
            if (i > 21 && i < 39){
                guiPoints.push_back(ofPoint(350, y));
            }        
        y +=30;
        if (y >= 350)
            y = 20;
        }
    
        
}


char myByte = 0;


void testApp::update(){

    updateOutgoing(); // needs to move into OOP class and take serial*
    updateIncoming(); // needs to move into OOP class and take serial*
    
} 

//--------------------------------------------------------------
void testApp::draw(){

//    ofRect(10, 10, 100, 30);
    if(bInCommandMode) 
        ofSetColor(125, 125, 125, 25);
    else
        ofSetColor(255, 255, 255);
    
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    for (int i = 0; i < incomingStr.size(); i++) {
        printf("%c", incomingStr[i]);
        msg += incomingStr[i];
    }
    
    for (int i = 0; i < guiPoints.size(); i++) {
        ofRectMode(OF_RECTMODE_CENTER);
        int _x = guiPoints[i].x;
        int _y = guiPoints[i].y;
        int radii = 10;
        // check in rect
        if(ofDist(mouseX, mouseY, _x, _y)<radii)
        ofSetColor(255, 255, 255);
        else
            ofSetColor(255, 0, 0);
        
        ofCircle(_x, _y, radii);
        ofSetColor(0,0,0);
        ofDrawBitmapString(guiStr[i], _x+15, _y);
    }

    

    
    ofDrawBitmapString(msg, ofGetWidth()/2, ofGetHeight()-200);
    
    incomingStr.clear();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == 32){
        // test
        serial.flush();
        printf("Entering Command Mode:  ");
        unsigned char buffer[3];
        buffer[0] = buffer[1] = buffer[2] = '+';
        serial.writeBytes(buffer, 3);
    }
    
    if(key == OF_KEY_UP){
        serial.flush();
        cout << "up pressed, sent:  ";
        unsigned char buffer[6];
        buffer[0]='A';
        buffer[1]='T';
        buffer[2]='D';        
        buffer[3]='0';        
        buffer[4]='5';                
        buffer[5]='\r';
        serial.writeBytes(buffer,6);
    }
    
    if(key == OF_KEY_DOWN){
        serial.flush();
        cout << "down pressed, sent:  ";
//        outgoingStr = stringToCharVector("ATVR", true);
//        outgoingStr = stringToCharVector("ATID", true);
        outgoingStr.clear();
        outgoingStr = stringToCharVector("ATD15", true);
        
    }
    
    if(key == OF_KEY_LEFT){
        serial.flush();
        cout << "down pressed, sent:  ";
//        outgoingStr = stringToCharVector("ATVR", true);
//        outgoingStr = stringToCharVector("ATID", true);
        outgoingStr.clear();
        outgoingStr = stringToCharVector("ATD05", true);        
    }
    
}

#pragma mark
#pragma mark ADDED FUNCTIONS
#pragma mark

vector<char> testApp::stringToCharVector(string _incoming, bool _addCarriageReturn){
    vector<char> result;
//    cout << _incoming.size(); // check

    int size = _incoming.size();
    char newstr[size]; // heres the fucken problem, was char *newstr = new char[size]; size pointer is 4bytes long?
    
//    cout<< sizeof(newstr);
    strcpy( newstr, _incoming.c_str() );
    
    for (int i = 0; i < sizeof(newstr); i ++) {
//        printf("%c", (char)newstr[i]); // check
        result.push_back((char)newstr[i]);
    }
    
    if(_addCarriageReturn == true)
        result.push_back((char)13);
    
    return result;          
    
}


void testApp::updateOutgoing(){
    // check if something is set to go out
    if (outgoingStr.size() > 0){
        
        for (int i = 0; i < outgoingStr.size(); i++) {
            // send the thing
            serial.writeByte(outgoingStr[i]);
            //            printf("%c", outgoingStr[i]); // check its going
        }
        // clear string if sent
        outgoingStr.clear();
    }
}

void testApp::updateIncoming(){
    myByte = serial.readByte(); 
    
    
    if ( myByte == OF_SERIAL_NO_DATA )
        
        //        printf("no data was read");
        incomingStr.clear();
    
    else if ( myByte == OF_SERIAL_ERROR )
        
        printf("an error occurred");
    
    else
    {
        //        printf("%d", myByte);
        incomingStr.push_back(myByte);
    }
    
}

    
#pragma mark


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    for (int i = 0; i < guiPoints.size(); i++) {
        int _x = guiPoints[i].x;
        int _y = guiPoints[i].y;
        int radii = 10;
        // check in rect
        if(ofDist(mouseX, mouseY, _x, _y)<radii){
            cout << guiStr[i] << " : ";
            outgoingStr = stringToCharVector(guiStr[i], true);
            ofSetColor(255,255,255);
            ofCircle(_x, _y, radii);
            ofDrawBitmapString(guiStr[i], _x+15, _y);
            
        }
        
        if( i == 0 ){
            outgoingStr = stringToCharVector(guiStr[i], false);
            bInCommandMode = true;
        }
        
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}