
// @zak, for you work on xmlSettings, I LOVE YOU!
// For your angst against using libraries.. we are neutral again

#include "testApp.h"

vector<string> guiStr;
bool bInCommandMode;
string incomingMsg;
int selectionOffsetX;
int selectionOffsetY;
bool bSecondOptions;
string message;
int highlightedCommand;
int highlightedPin;
int highlightedSecondary;

bool bShowSecondary;
vector<ofPoint> secondaryLoc;
char myByte = 0;

ofPoint(cursorLoc);

ofColor baseBlue = ofColor(81, 116, 146);
ofColor darkGrey = ofColor(33,33,33);
ofColor lightGrey = ofColor(222, 222, 222);

struct response{
    int option;
    int param;
    string description;
};


void testApp::setup(){    
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();

    // setup serial and check devices
    serial.listDevices();

    if( serial.setup(0, 9600) ){ // hard coded, FIXME
        printf("==================================-------- \r");        
        printf("Serial - 0, 9600 initiated. \r");
        printf("PRESS SPACE TO ENTER COMMAND MODE...... \r");        
        printf("==================================-------- \r");                
    }; 
        
    specialCommands = loader.getSpecial();
    pinCommands = loader.getPins();
    
    cursorLoc = ofPoint(340, 40);
        
    highlightedPin = 99; // used to determine pin or special command
    bShowSecondary = false;
    
    serial.flush();    

    message = "AT";
    
    
}


void testApp::update(){
    updateOutgoing(); // needs to move into OOP class and take serial*
    updateIncoming(); // needs to move into OOP class and take serial*
    
} 


void testApp::draw(){
    
    ofRectMode(OF_RECTMODE_CORNER);
    ofSetColor(87,87,87);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(lightGrey);
    
   // draw special commands
    ofPushMatrix();
    for (int i = 0; i < specialCommands.size(); i++) {
        if(i == highlightedCommand)
            specialCommands[i]->draw(true);
        else 
            ofSetColor(255, 255, 255);
        specialCommands[i]->draw(false);
    }
    ofPopMatrix();
    
    
    // draw pseudo xbee
    ofPushMatrix();
    for (int i = 0; i < pinCommands.size(); i++) {
        if(ofDist(cursorLoc.x, cursorLoc.y, pinCommands[i]->getLoc().x, pinCommands[i]->getLoc().y)< 10){
            highlightedPin = i;
        }
        if(i == highlightedPin)
            pinCommands[i]->draw(true);
        else {
            pinCommands[i]->draw(false);
        }
    }
    ofPopMatrix();
    
    // draw secondary options
    if(bShowSecondary){
        // check which pin is selected
        if(highlightedPin != 99 && pinCommands[highlightedPin]->getParams().size()>0){
            secondaryLoc.empty();
            
            pinCommands[highlightedPin]->drawParams(600, highlightedSecondary);
            secondaryLoc= pinCommands[highlightedPin]->getParamsLoc();
        }
        else{
            secondaryLoc.empty();
            specialCommands[highlightedCommand]->drawParams(600, highlightedSecondary);      
            secondaryLoc= specialCommands[highlightedCommand]->getParamsLoc();
        }

    }    
    
    // draw message content
    ofPushMatrix();
        ofTranslate(30, ofGetHeight()-60);    
        if (message == "AT")
            ofSetColor(255, 179, 179);
        else
            ofSetColor(162, 171, 165);
        ofRect(0, -20, 450, 45);
        ofSetColor(13, 13, 13);
        ofDrawBitmapString("MESSAGE TO SEND  ",2,-21);
        ofDrawBitmapString(message,10,10);        
    ofPopMatrix();    
    

    
    

    
    for (int i = 0; i < incomingStr.size(); i++) {
        printf("%c", incomingStr[i]);
        incomingMsg += incomingStr[i];
     }
      
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("FROM XBEE  ",2,-21);
    ofDrawBitmapString(incomingMsg,10,10);        
    ofPopMatrix();  
    
    ofDrawBitmapString(incomingMsg, ofGetWidth()/2, ofGetHeight()-200);
    incomingStr.clear();
    
}

void testApp::keyPressed(int key){}

void testApp::keyReleased(int key){
    if(key == 32){
        // test
        serial.flush();
        printf("Entering Command Mode:  ");
        unsigned char buffer[3];
        buffer[0] = buffer[1] = buffer[2] = '+';
        serial.writeBytes(buffer, 3);             
    }
    
    else if(key == OF_KEY_RETURN){
        cout << "\rMessage sent: " << message << "\r";
        vector<char> chars = stringToCharVector(message, true);
        unsigned char buffer[chars.size()];
        for (int i =0; i<chars.size(); i++){
            buffer[i]=chars[i];
        }
//        serial.writeBytes(buffer, chars.size());
        outgoingStr = chars;
        message = "AT";

    }
    
    else if(key == OF_KEY_UP){
//        cursorLoc.y -= 30;        
//        if(cursorLoc.y < 40)
//            cursorLoc.y = 40;
    }
    
   else if(key == OF_KEY_DOWN){        
//        cursorLoc.y += 30;
//        if(cursorLoc.y > 350)
//            cursorLoc.y = 350;
    }
    
  else  if(key == OF_KEY_LEFT){
//        cursorLoc.x = 57;
    }
    
  else  if(key == OF_KEY_RIGHT){
//        cursorLoc.x = 340;
    }    
    
  else  if(key == 127){ // delete
        message = "AT";
    }
    
    else 
        message += key; // manual override
}

void testApp::mouseMoved(int x, int y ){}

void testApp::mouseDragged(int x, int y, int button){}

void testApp::mousePressed(int x, int y, int button){
    
    ofPoint mousePosition = ofPoint(x, y);
    cout << "mouse x: " << x << " y: " << y;
    
    for(int i=0; i<pinCommands.size(); i++){
        for(int j=0; j<specialCommands.size(); j++){
            
            
            if ( ofDist(pinCommands[i]->getLoc().x,  pinCommands[i]->getLoc().y, mousePosition.x, mousePosition.y)<10){
                ofLog(OF_LOG_ERROR,"mouse clicked in pin command \r");   
                highlightedPin = i;
                highlightedCommand = 99;
                if(pinCommands[i]->getParams().size() > 0)
                    bShowSecondary = true;
                else
                    bShowSecondary = false;
                message += pinCommands[i]->getCommand();
                goto outofloop;
            }
            
            
            if ( ofDist(specialCommands[j]->getLoc().x,  specialCommands[j]->getLoc().y, mousePosition.x, mousePosition.y)<10){
                ofLog(OF_LOG_ERROR,"close to special command \r");  
                highlightedCommand = j;
                highlightedPin = 99;
                if(specialCommands[j]->getParams().size() > 0)
                    bShowSecondary = true;
                else 
                    bShowSecondary = false;
                message += specialCommands[j]->getCommand();
                goto outofloop;
                

            }

        }
    }
    
    
    for(int k=0; k<secondaryLoc.size(); k++){

        ofLog(OF_LOG_ERROR, "mouse in secondary options"); // FIXME:  Might be where the OutOfRange exceptions come from for the secondaryLoc errors??
//        cout << " pinLoc x: " << pinCommands[i]->getLoc().x << " y: " <<pinCommands[i]->getLoc().y << "\r";        
        
        mousePosition.x = 600;
        if ( ofDist(secondaryLoc[k].x,  secondaryLoc[k].y, mousePosition.x, mousePosition.y)<10){
            highlightedSecondary = k;

            if( highlightedPin != 99){
                message += pinCommands[highlightedPin]->params[highlightedSecondary]->getCommand();
//                message += ","; // for command stacking                
                goto outofloop;
            }
            else if ( highlightedPin == 99 ){
                message += specialCommands[highlightedCommand]->params[highlightedSecondary]->getCommand();
//                message += ","; // for command stacking                
                goto outofloop;
            }
            else {
                goto outofloop;
            }

        }
        

        
    }
    
    outofloop:
    ofLog(OF_LOG_VERBOSE, "out of loop");
    
}


void testApp::mouseReleased(int x, int y, int button){}

void testApp::windowResized(int w, int h){}

void testApp::gotMessage(ofMessage msg){}

void testApp::dragEvent(ofDragInfo dragInfo){}

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
        incomingStr.clear();
    else if ( myByte == OF_SERIAL_ERROR )
        printf("an error occurred");
    else
    {
        //        printf("%d", myByte);
        incomingStr.push_back(myByte);
    }
    
}

