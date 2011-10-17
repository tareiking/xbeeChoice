
// @zak, for you work on xmlSettings, I LOVE YOU!
// For your angst against using libraries.. we are neutral again

#include "testApp.h"

vector<string> guiStr;
bool bInCommandMode;
string msg;
int selectionOffsetX;
int selectionOffsetY;
bool bSecondOptions;
string message;
int highlighted;
int highlightedPin;
bool bShowSecondary;

ofPoint(cursorLoc);

void testApp::setup(){    
    // setup serial and check devices
    serial.getDeviceList();
    if( serial.setup(0, 9600) ){ // hard coded, yuck
        printf("==================================-------- \r");        
        printf("Serial - 0, 9600 initiated. \r");
        printf("PRESS SPACE TO ENTER COMMAND MODE...... \r");        
        printf("==================================-------- \r");                
    }; 
        
    specialCommands = loader.getSpecial();
    pinCommands = loader.getPins();
    
    cursorLoc = ofPoint(340, 40);
    
    serial.flush();    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    highlightedPin = 99;
    bShowSecondary = false;
    
    message = "AT";
    
}


char myByte = 0;


void testApp::update(){
    
//    cursorLoc = (mouseX, mouseY);
    
    // check if cursor in  dist of command
    

    updateOutgoing(); // needs to move into OOP class and take serial*
    updateIncoming(); // needs to move into OOP class and take serial*
    
} 

ofColor baseBlue = ofColor(81, 116, 146);

//--------------------------------------------------------------
void testApp::draw(){
    
    ofRectMode(OF_RECTMODE_CORNER);
//    
//    // draw special commands
    ofPushMatrix();
    ofSetColor(255, 255, 255);
    for (int i = 0; i < specialCommands.size(); i++) {
        specialCommands[i]->draw();
    }
    ofPopMatrix();
    
    
    // draw pseudo xbee
    ofPushMatrix();
    for (int i = 0; i < pinCommands.size(); i++) {
        if(ofDist(cursorLoc.x, cursorLoc.y, pinCommands[i]->getLoc().x, pinCommands[i]->getLoc().y)< 10){
            highlighted = i;
        }
        
        if(i == highlightedPin)
            ofSetColor(255, 0, 0);
        else 
            ofSetColor(255, 255, 255);
        
        // draw left side
        if(i<=10){
            pinCommands[i]->drawPin(true);
        }
        // draw right side
        if(i>10){
           pinCommands[i]->drawPin(true);
        }
    }
    ofPopMatrix();
    
    // draw cursor @ pin 20
    ofPushMatrix();
//        findOptionsByPin(int _pin)act
    ofPopMatrix();
    
    // draw message content
    ofPushMatrix();
        ofTranslate(30, ofGetHeight()-60);    
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("MESSAGE TO SEND:  ",0,0);
        ofDrawBitmapString(message,0,20);        
    ofPopMatrix();    
    ofTranslate(400, 500);
    // draw secondary
    if(bShowSecondary){
        ofPushMatrix();
            pinCommands[highlightedPin]->drawParams(0);

        ofPopMatrix();
    }

    
//    
//
//    // draw the pseudo xbee
//    ofPushMatrix();
//    ofTranslate(50, 50);
//
//        ofSetColor(baseBlue);   
//        ofRect(0, 0, 250, 330);
//        ofSetColor(255, 255, 255);
//        ofDrawBitmapString("Select your PIN", 10,20);    
//    
//    int y = 10;
//    int offset = 20;
//    int yBottom = 330;
//    for (int i = 1; i < 11; i++) {
//        ofRectMode(OF_RECTMODE_CENTER);
//        ofSetColor(255, 0, 0);
//
//        
//        ofRect(10,y+offset, 15, 15);
//        ofRect(225,y+offset, 15, 15);        
//        
//        ofSetColor(255, 255, 255);
//        // should get information from xml
//        string tempStrLeft = "PIN " + ofToString(i);
//        ofDrawBitmapString(tempStrLeft, ofPoint(35, y+offset+12));
//        
//        string tempStrRight = "PIN " + ofToString(i+10);
//        ofDrawBitmapString(tempStrRight, ofPoint(170,yBottom-offset+2)); // start from bottom up
//        
//        
//        offset += 30;
//    }
//    ofPopMatrix();    
//
//    
//    // loads the items for the secondary items
//    ofPushMatrix();    
//    
//        ofTranslate(350, 50);
//        ofSetColor(baseBlue);   
//        ofRect(0, 0, 400, 200); // draw bounding box
//        ofSetColor(255, 255, 255);
//        ofDrawBitmapString("Secondary options", 20, 20);
//
//    // TODO:  load values from XML
//        ofDrawBitmapString("'0' - Disbaled", 40, 65);        
//        ofDrawBitmapString("'1' - DIOUT", 40, 85);        
//        ofDrawBitmapString("'2' - DIN", 40, 105);        
//        ofSetColor(255, 0, 0); // draw option boxes
//        ofRect(20, 55, 15, 15);
//        ofRect(20, 75, 15, 15);    
//        ofRect(20, 95, 15, 15);        
//
//    ofPopMatrix();
//    
//    // loads display box to check 
//    
//    ofPushMatrix();
//    ofTranslate(350, 275);
//        ofSetColor(baseBlue);
//        ofRect(0, 0, 400, 100);
//        ofSetColor(255, 255, 255);
//    ofDrawBitmapString("CONSOLE LOG/ SERIAL INFO", 20, 20);
//    ofPopMatrix();
//    
//    
//    // draw the pseudo selection box
//    ofPushMatrix();
//    // move to box center pin 20 (top right)
//    // coords are 300(rect start) + 225 (x), 50 + 20 + offset (10) (y) - offset
//        ofTranslate(selectionOffsetX, selectionOffsetY);
//        ofRectMode(OF_RECTMODE_CENTER);
//        ofSetColor(255, 255, 255);
//        ofRect(0, 0, 18,18);
//    
//    // check global vairables to determine what message to show
//    ofPopMatrix();
    
//    for (int i = 0; i < incomingStr.size(); i++) {
//        printf("%c", incomingStr[i]);
//        msg += incomingStr[i];
//    }
      
    ofDrawBitmapString(msg, ofGetWidth()/2, ofGetHeight()-200);
    
    incomingStr.clear();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    // get current position on screen
    cout << highlighted;

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == 32){
        // go to secondary options
        // get current loop in pin options which equates to the PIN options
        
        
        // search option for the params of that value
        // show params
        // move cursor parameters to secondary screen
    }
    
    if(key == OF_KEY_RETURN){
        // test
        serial.flush();
        printf("Entering Command Mode:  ");
        unsigned char buffer[3];
        buffer[0] = buffer[1] = buffer[2] = '+';
        serial.writeBytes(buffer, 3);        
    }
    
    if(key == OF_KEY_UP){
        cursorLoc.y -= 30;        
        if(cursorLoc.y < 40)
            cursorLoc.y = 40;
//        cout << cursorLoc.y;
    }
    
    if(key == OF_KEY_DOWN){        
        cursorLoc.y += 30;
        if(cursorLoc.y > 350)
            cursorLoc.y = 350;
    }
    
    if(key == OF_KEY_LEFT){
        cursorLoc.x = 57;
    }
    
    if(key == OF_KEY_RIGHT){
        cursorLoc.x = 340;
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
//    for (int i = 0; i < guiPoints.size(); i++) {
//        int _x = guiPoints[i].x;
//        int _y = guiPoints[i].y;
//        int radii = 10;
//        // check in rect
//        if(ofDist(mouseX, mouseY, _x, _y)<radii){
//            cout << guiStr[i] << " : ";
//            outgoingStr = stringToCharVector(guiStr[i], true);
//            ofSetColor(255,255,255);
//            ofCircle(_x, _y, radii);
//            ofDrawBitmapString(guiStr[i], _x+15, _y);
//            
//        }
//        
//        if( i == 0 ){
//            outgoingStr = stringToCharVector(guiStr[i], false);
//            bInCommandMode = true;
//        }
//        
//    }
    
    for(int i=0; i<pinCommands.size(); i++){
        int pinX =pinCommands[i]->getLoc().x;
        int pinY =pinCommands[i]->getLoc().y;
        
//        cout << pinX << x << "\r";
//        cout << pinY << y << "\r";
        if(ofDist(pinX, pinY, x, y) < 20){
            ofSetColor(255, 0,0);
            ofRect(pinX, pinY, 15, 15);
            cout << "in range of " << i <<"\r";
            highlightedPin = i;
            
            bShowSecondary  = true;
            
            pinCommands[highlightedPin]->reportParams();    
            
        }
        
    }

    cout << bShowSecondary;
    
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