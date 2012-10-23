#pragma once

#include "ofMain.h"
#include "ofxOptix.h"
#include <optix.h>

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxOptixContext optixContext;
		ofxOptixProgram optixProgram;
		ofxOptixBuffer optixBuffer;

		RTcontext context;
		RTprogram ray_gen_program;
		RTbuffer buffer;

		RTresult result;

        /* Parameters */
        RTvariable result_buffer;
        RTvariable draw_color;

        unsigned int width  ;
        unsigned int height ;

        char filename;
         GLvoid* imageData;

};
