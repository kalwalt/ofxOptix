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

        void createGeometry( RTcontext context, RTgeometry* sphere );
        void createMaterial( RTcontext context, RTmaterial* material );
        void createInstance( RTcontext context, RTgeometry sphere, RTmaterial material );


		ofxOptixContext optixContext;
		ofxOptixProgram optixProgram;
		ofxOptixBuffer optixBuffer;

		RTcontext context;
		RTprogram ray_gen_program;
		RTbuffer output_buffer_obj;
		RTgeometry          sphere;
        RTmaterial          material;

  RTprogram  exception_program;
  RTprogram  miss_program;
  RTvariable output_buffer;
  RTvariable radiance_ray_type;
  RTvariable epsilon;

  /* variables for ray gen program */
  RTvariable eye;
  RTvariable U;
  RTvariable V;
  RTvariable W;
  RTvariable badcolor;

  /* variables for miss program */
  RTvariable bg_color;

  /* viewing params */
  float cam_eye[3], lookat[3], up[3];
  float hfov, aspect_ratio;
  float camera_u[3], camera_v[3], camera_w[3];

  RTresult CalculateCameraVariables( float eye[3],
                                        float lookat[3],
                                        float up[3],
                                        float hfov,
                                        float aspect_ratio,
                                        float U[3],
                                        float V[3],
                                        float W[3] );


		RTresult result;

        /* Parameters */
        RTvariable result_buffer;
        RTvariable draw_color;

        unsigned int width  ;
        unsigned int height ;

        char filename;
         GLvoid* imageData;

         //ofEasyCam cam;
         ofCamera cam;

};
