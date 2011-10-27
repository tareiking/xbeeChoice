#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

/*! \mainpage XBEE CONFIGURATION TOOL 0.08
 *
 * \section Installation
 *
 * This has been compiled for Mac OS X 10.7 as an application. Source code is where its at and its available for download at: <a href="https://github.com/tareiking/xbeeChoice" />github</a> to compile yourself.
 *
 * \section install_sec Usage
 *
 * \subsection step1 Step 1: Connect xbee
 * This application gets information from what ever is in port 0. If your xbee + uart is not connected there is no error checking to tell you so. Apart from absolute failure. 
 *
 * \subsection step2 Step 2: Run application 
 * \subsection step3 Step 3: In app
 * 'SPACEBAR' enters command mode: You will need to be quick. By default you have 3 seconds before it automatically logs you out of command mode
 * 'MOUSE CLICK' chooses parameters to change on the xbee
 * 'ENTER' to send command to xbee.
 *
 * \subsection step4 Note: Your messages should automatically be appended to the previous command. If its looking weird, roll your own message!
 * \subsection step5 Step 4: Roll your own
 * If the built in messages aren't enough you can either type the commands manually on screen or create / edit the x.bee file (which is just valid xml)
 * 
 * \section Video
 * See it in action :)
 * <iframe width="420" height="315" src="http://www.youtube.com/embed/kjBralkAkjM" frameborder="0" allowfullscreen></iframe>
 *
 *
 */

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 900,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}

