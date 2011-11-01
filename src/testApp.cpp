
// @zak, for you work on xmlSettings, I LOVE YOU!
// For your angst against using libraries.. we are neutral again

#include "testApp.h"

vector<string> guiStr;
bool bInCommandMode;

int selectionOffsetX;
int selectionOffsetY;
bool bSecondOptions;
string message, incomingMsg, alertMessage;
int highlightedCommand;
int highlightedPin;
int highlightedSecondary;

bool bShowSecondary, bDrawIncoming, bAlert;
vector<ofPoint> secondaryLoc;
char myByte = 0;

int timer, originalTimer;
bool bConnected;


ofPoint(cursorLoc);

ofColor baseBlue = ofColor(81, 116, 146);
ofColor darkGrey = ofColor(33,33,33);
ofColor lightGrey = ofColor(222, 222, 222);

//! Response is made for storing param values when receiving information from the xbee.
struct response{
    //! (int) option to be retrieved
    int option;  
    //! (int) param to be retrieved
    int param;   
    //! (string) details of the parameter name, description and command    
    string report;  

};

vector<response> responses;

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
    }
    else {
        printf("error connecting to serial port [0]\r");  
    }
    specialCommands = loader.getSpecial();
    pinCommands = loader.getPins();
    
    cout << pinCommands[0]->getName() << " set to: " << pinCommands[0]->getParamName(2) << "\r";
    
//    response *temp = new reponse;
//    temp.option = pinCommands[0]->getName();
    cursorLoc = ofPoint(340, 40);
        
    highlightedPin = 99; // used to determine pin or special command
    bShowSecondary = bConnected = false;
    
    serial.flush();    

    message = "AT";
    
    font.loadFont("font.ttf", 10);
    largeFont.loadFont("font.ttf", 16);
    timer = originalTimer = ofGetSeconds();
    
    bAlert = false;
}
int timeSinceLastSend;

void testApp::update(){

    updateOutgoing(); // needs to move into OOP class and take serial*
    updateIncoming(); // needs to move into OOP class and take serial*

    if (incomingMsg.size()>0)
        bDrawIncoming = true;
    else
        bDrawIncoming = false;
} 


void testApp::draw(){
    
    ofRectMode(OF_RECTMODE_CORNER);
    ofSetColor(87,87,87);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(lightGrey);
    
    // draw special commands
    ofPushMatrix();
    largeFont.drawString("Special Commands", 0, 20);
    for (int i = 0; i < specialCommands.size(); i++) {
        if(i == highlightedCommand)
            specialCommands[i]->draw(true);
        else 
            ofSetColor(255, 255, 255);
        specialCommands[i]->draw(false);
    }
    ofPopMatrix();
    
    
    // draw PIN commands
    ofPushMatrix();
    largeFont.drawString("PIN Commands",250, 20);
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
        ofPushMatrix();
        largeFont.drawString("Options", 450, 20);
        ofPopMatrix();
        
        // check which pin is selected
        if(highlightedPin != 99 && pinCommands[highlightedPin]->getParams().size()>0){
            secondaryLoc.empty();
            
            pinCommands[highlightedPin]->drawParams(460, highlightedSecondary);
            secondaryLoc= pinCommands[highlightedPin]->getParamsLoc();
        }
        else{
            secondaryLoc.empty();
            specialCommands[highlightedCommand]->drawParams(460, highlightedSecondary);      
            secondaryLoc= specialCommands[highlightedCommand]->getParamsLoc();
        }

    }    
    
    // draw message content
    ofPushMatrix();
        ofTranslate(30, ofGetHeight()-80);    
        ofSetColor(255, 255, 255);            
        ofRect(0, -20, 450, 45);
        font.drawString("MESSAGE TO SEND (or roll your own)", 2, -30);

        ofSetColor(125, 125, 125);       
        largeFont.drawString(message, 10, 10);
    ofPopMatrix();    
    
    if(incomingMsg.length() > 60)
        incomingMsg = "";
    
    for (int i = 0; i < incomingStr.size(); i++) {
        printf("%c", incomingStr[i]);
        incomingMsg += incomingStr[i];
     }
    
    
    // draw alert message
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2-400, ofGetHeight()/2+40);

    if(bAlert){
//        ofSetColor(whiteColor);
        alertMessage = "IN COMMAND MODE: Select command with MOUSE";
        largeFont.drawString(alertMessage, 0, 0);
        largeFont.drawString("Press ENTER to send to Xbee", 0, 24);
    }
    else{
        alertMessage = "PRESS SPACE TO ENTER COMMAND MODE";
        largeFont.drawString(alertMessage, 0, 0);
    }
    ofPopMatrix();
        
    
    // draw incoming message
    ofPushMatrix();
        ofTranslate(ofGetWidth()/2+40, ofGetHeight()-80);
        ofSetColor(255, 255, 255);            
        ofRect(0, -20, 375, 45);    
        font.drawString("MESSAGE RECEIVED", 0, -30);
        //font.drawString(incomingMsg, ofGetWidth()/2, ofGetHeight()-200);

        ofSetColor(125, 125, 125);       
        largeFont.drawString(incomingMsg, 10, 10);
        incomingStr.clear();
    ofPopMatrix();
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
        timer = ofGetElapsedTimef();
        bAlert = true;
    }
    
    else if(key == OF_KEY_RETURN){
        cout << "\rMessage sent: " << message << "\r";
        
        vector<char> chars = stringToCharVector(message, true);
        unsigned char buffer[chars.size()];
        for (int i =0; i<chars.size(); i++){
            buffer[i]=chars[i];
        }
        outgoingStr = chars;
        message = "AT";
//        timer = ofGetSeconds();
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
//    cout << "mouse x: " << x << " y: " << y;
    
    for(int i=0; i<pinCommands.size(); i++){
        for(int j=0; j<specialCommands.size(); j++){
            
            
            if ( ofDist(pinCommands[i]->getLoc().x,  pinCommands[i]->getLoc().y, mousePosition.x, mousePosition.y)<10){
//                ofLog(OF_LOG_ERROR,"mouse clicked in pin command \r");   
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
//                ofLog(OF_LOG_ERROR,"close to special command \r");  
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
        
        mousePosition.x = 460;
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

