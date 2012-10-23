#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    width  = 512u;
    height = 384u;
    optixContext.create(&context,1,1);

    optixBuffer.create(context, RT_BUFFER_OUTPUT, RT_FORMAT_FLOAT4, width, height, &buffer);

    //rtBufferCreate( context, RT_BUFFER_OUTPUT, &buffer ) ;
    // rtBufferSetFormat( buffer, RT_FORMAT_FLOAT4 ) ;
    // rtBufferSetSize2D( buffer, width, height ) ;

    rtContextDeclareVariable( context, "result_buffer", &result_buffer ) ;
    rtVariableSetObject( result_buffer, buffer ) ;
      rtBufferGetContext( buffer, &context );


    //filename = ofToDataPath("/home/walter/openframeworks0071/examples/Optix/ofxOptixSample1/bin/data/sample1_generated_draw_color.cu.ptx").c_str();
    optixProgram.createFromPTX(context, "/home/walter/openframeworks0071/examples/Optix/ofxOptixSample1/bin/data/sample1_generated_draw_color.cu.ptx", "draw_solid_color", 0, &ray_gen_program);
    //rtProgramCreateFromPTXFile( context, "/home/walter/openframeworks0071/examples/Optix/Sample1/Sample1/bin/data/sample1_generated_draw_color.cu.ptx", "draw_solid_color", &ray_gen_program ) ;
     rtProgramDeclareVariable( ray_gen_program, "draw_color", &draw_color ) ;
    rtVariableSet3f( draw_color, 0.462f, 0.725f, 0.0f ) ;
     //rtContextSetRayGenerationProgram( context, 0, ray_gen_program ) ;


    //rtProgramDeclareVariable( rayprogram, "draw_color", &draw_color ) ;
    //rtVariableSet3f( draw_color, 0.462f, 0.725f, 0.0f ) ;
    //rtContextSetRayGenerationProgram( context, 0, rayprogram ) ;

    rtContextValidate( context ) ;
     rtContextCompile( context ) ;
     rtContextLaunch2D( context, 0 , width, height ) ;

     result = rtBufferMap(buffer, &imageData);
     if (result != RT_SUCCESS) {
    // Get error from context
    RTcontext context;
    const char* error;
    rtBufferGetContext(buffer, &context);
    rtContextGetErrorString(context, result, &error);
    fprintf(stderr, "Error mapping image buffer: %s\n", error);
    exit();
  }

  /* Clean up */
     rtBufferDestroy( buffer ) ;
     rtProgramDestroy( ray_gen_program ) ;
     rtContextDestroy( context ) ;

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
 glDrawPixels(512, 384, GL_RGBA,GL_FLOAT, imageData);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

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
