
// @zak, for you work on xmlSettings, I LOVE YOU!
// For your angst against using libraries.. we are neutral again

#include "testApp.h"

vector<string> guiStr;
bool bInCommandMode;
string msg;
int selectionOffsetX;
int selectionOffsetY;
bool bSecondOptions;

ofPoint(cursorLoc);

void testApp::setup(){
    // test option

//    int yOffset = 10;
//    for (int i = 1; i < 20; i++){
//        ofPoint tempPnt =  ofPoint(10, yOffset);
//        Option *opt = new Option(tempPnt, 1, "PIN01", "Controls something in PIN01", "0");
//        opt->addParam(0, "enable", "  ", "1");
//        opt->addParam(0, "disable", "  ", "2");    
//        
//        options.push_back(opt);     
//        yOffset += 20;
//    }
//    
//    if(xml.loadFile("x.bee")){
//        cout << "File loaded \r"; 
//    } else {
//        cout << "File not loaded, check data/ folder";
//    }
//
//    
//    // load misc commands .bee (xml)
//    xml.pushTag("special");
//    for(int i=0; i<xml.getNumTags("command"); i++){
//        xml.pushTag("command", i);
//        cout << "\r" << xml.getValue("name", "") << "\r";
//        xml.popTag();
//    }
//    xml.popTag();
//    xml.popTag();
    
    // setup serial and check devices
    serial.getDeviceList();
    if( serial.setup(0, 9600) ){ // hard coded, yuck
//        printf("==================================-------- \r");        
//        printf("Serial - 0, 9600 initiated. \r");
//        printf("PRESS SPACE TO ENTER COMMAND MODE...... \r");        
    }; 
    
    serial.flush();    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    selectionOffsetX = 273;
    selectionOffsetY = 80;

    bg.loadImage("honey.png");
        
}


char myByte = 0;


void testApp::update(){
    
    cursorLoc.set(selectionOffsetX, selectionOffsetY);
//    if(serialPortSelected)

    updateOutgoing(); // needs to move into OOP class and take serial*
    updateIncoming(); // needs to move into OOP class and take serial*
    
} 

ofColor baseBlue = ofColor(81, 116, 146);

//--------------------------------------------------------------
void testApp::draw(){
    
    for (int i = 0; i < options.size(); i++) {
        options[i]->draw();
    }
//    // draw message content
//    ofPushMatrix();
//        ofTranslate(ofGetWidth()/2+bg.width/2+30, ofGetHeight()/2-bg.height/4);    
//        ofDrawBitmapString("Pin 20 / parameters: 0-5",0,0);        
//    ofPopMatrix();    
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
        selectionOffsetY -= 30;        
        if(selectionOffsetY < 80)
            selectionOffsetY = 80;
        
//        serial.flush();
//        cout << "up pressed, sent:  ";
//        unsigned char buffer[6];
//        buffer[0]='A';
//        buffer[1]='T';
//        buffer[2]='D';        
//        buffer[3]='0';        
//        buffer[4]='5';                
//        buffer[5]='\r';
//        serial.writeBytes(buffer,6);
    }
    
    if(key == OF_KEY_DOWN){        
        selectionOffsetY += 30;
        if(selectionOffsetY > 350)
            selectionOffsetY = 350;
        cout << selectionOffsetY;
//        serial.flush();
//        cout << "down pressed, sent:  ";
//        outgoingStr.clear();
//        outgoingStr = stringToCharVector("ATD15", true);
        
    }
    
    if(key == OF_KEY_LEFT){
        selectionOffsetX = 57;
        cout << selectionOffsetX;
//        serial.flush();
//        cout << "left pressed, sent:  ";
//        outgoingStr.clear();
//        outgoingStr = stringToCharVector("ATD05", true);        
    }
    
    if(key == OF_KEY_RIGHT){
        selectionOffsetX = 273;
        //        serial.flush();
        //        cout << "left pressed, sent:  ";
        //        outgoingStr.clear();
        //        outgoingStr = stringToCharVector("ATD05", true);        
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
    
    // draw rect that is too the right and high enough
    ofRect(0, 0, 100, 50);
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(0, 0, 255);

    cout << "pressed";
    ofPopMatrix();
    
    
    
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