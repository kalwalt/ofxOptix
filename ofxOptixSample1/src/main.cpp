#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 512, 384, OF_WINDOW);
	window.setGlutDisplayString("rgb float depth alpha samples>=4");
	ofRunApp(new testApp()); // start the app
}