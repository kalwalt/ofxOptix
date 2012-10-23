#include "testApp.h"

void testApp::createGeometry( RTcontext context, RTgeometry* sphere )
{
    RTprogram  intersection_program;
    RTprogram  bounding_box_program;
    RTvariable s;
    float sphere_loc[4] =  {0, 0, 0, 1.5};

    rtGeometryCreate( context, sphere ) ;
    rtGeometrySetPrimitiveCount( *sphere, 1u ) ;


   rtProgramCreateFromPTXFile( context, ofToDataPath("sample5_generated_sphere.cu.ptx",true).c_str(), "bounds", &bounding_box_program) ;
   rtGeometrySetBoundingBoxProgram( *sphere, bounding_box_program ) ;

   rtProgramCreateFromPTXFile( context, ofToDataPath("sample5_generated_sphere.cu.ptx",true).c_str(), "intersect", &intersection_program) ;
   rtGeometrySetIntersectionProgram( *sphere, intersection_program ) ;

   rtGeometryDeclareVariable( *sphere, "sphere" , &s) ;
   rtVariableSet4fv( s, &sphere_loc[0] ) ;
}

void testApp::createInstance( RTcontext context, RTgeometry sphere, RTmaterial material ){

    RTgeometrygroup geometrygroup;
  RTvariable      top_object;
  RTacceleration  acceleration;
  RTgeometryinstance instance;

  /* Create geometry instance */
   rtGeometryInstanceCreate( context, &instance ) ;
   rtGeometryInstanceSetGeometry( instance, sphere ) ;
   rtGeometryInstanceSetMaterialCount( instance, 1 ) ;
   rtGeometryInstanceSetMaterial( instance, 0, material ) ;

  /* Create geometry group */
   rtAccelerationCreate( context, &acceleration ) ;
   rtAccelerationSetBuilder( acceleration, "NoAccel" ) ;
   rtAccelerationSetTraverser( acceleration, "NoAccel" ) ;
   rtGeometryGroupCreate( context, &geometrygroup ) ;
   rtGeometryGroupSetChildCount( geometrygroup, 1 ) ;
   rtGeometryGroupSetChild( geometrygroup, 0, instance ) ;
   rtGeometryGroupSetAcceleration( geometrygroup, acceleration );

   rtContextDeclareVariable( context, "top_object", &top_object ) ;
   rtVariableSetObject( top_object, geometrygroup ) ;


}

void testApp::createMaterial( RTcontext context, RTmaterial* material ){

   RTprogram chp;

   rtProgramCreateFromPTXFile( context, ofToDataPath("sample5_generated_normal_shader.cu.ptx",true).c_str(), "closest_hit_radiance", &chp ) ;

   rtMaterialCreate( context, material ) ;
   rtMaterialSetClosestHitProgram( *material, 0, chp) ;


}

static void cross( const float a[3], const float b[3], float result[3] )
{
  result[0] = a[1]*b[2] - a[2]*b[1];
  result[1] = a[2]*b[0] - a[0]*b[2];
  result[2] = a[0]*b[1] - a[1]*b[0];
}


static float dot( const float a[3], const float b[3] )
{
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}


static void normalize( float a[3] )
{
  float inv_len = 1.0f / sqrtf( dot(a, a) );
  a[0] *= inv_len;
  a[1] *= inv_len;
  a[2] *= inv_len;
}

 RTresult testApp::CalculateCameraVariables( float eye[3],
                                        float lookat[3],
                                        float up[3],
                                        float hfov,
                                        float aspect_ratio,
                                        float U[3],
                                        float V[3],
                                        float W[3] ){


   float ulen, vlen, wlen;
  W[0] = lookat[0] - eye[0];
  W[1] = lookat[1] - eye[1];  /* Do not normalize W -- it implies focal length */
  W[2] = lookat[2] - eye[2];

  wlen = sqrtf( dot( W, W ) );
  cross( W, up, U );
  normalize( U );
  cross( U, W, V );
  normalize( V );
  ulen = wlen * tanf( hfov / 2.0f * 3.14159265358979323846f / 180.0f );
  U[0] *= ulen;
  U[1] *= ulen;
  U[2] *= ulen;
  vlen =  ulen/aspect_ratio;
  V[0] *= vlen;
  V[1] *= vlen;
  V[2] *= vlen;

  return RT_SUCCESS;

                                        }

//--------------------------------------------------------------
void testApp::setup(){

    width  = 1024;
    height = 768;
    optixContext.create(&context,1,1);

    optixBuffer.create(context, RT_BUFFER_OUTPUT, RT_FORMAT_UNSIGNED_BYTE4, width, height, &output_buffer_obj);


    rtContextDeclareVariable( context, "output_buffer" , &output_buffer) ;
    rtContextDeclareVariable( context, "radiance_ray_type" , &radiance_ray_type) ;
    rtContextDeclareVariable( context, "scene_epsilon" , &epsilon) ;

    rtVariableSet1ui( radiance_ray_type, 0u ) ;
    rtVariableSet1f( epsilon, 1.e-4f ) ;

    rtVariableSetObject( output_buffer, output_buffer_obj ) ;
      rtBufferGetContext( output_buffer_obj, &context );

      /* Ray generation program */

   rtProgramCreateFromPTXFile( context, ofToDataPath("sample5_generated_pinhole_camera.cu.ptx",true).c_str(), "pinhole_camera", &ray_gen_program ) ;
   rtContextSetRayGenerationProgram( context, 0, ray_gen_program ) ;
   rtContextDeclareVariable( context, "eye" , &eye) ;
   rtContextDeclareVariable( context, "U" , &U) ;
   rtContextDeclareVariable( context, "V" , &V) ;
   rtContextDeclareVariable( context, "W" , &W) ;


 cam_eye[0]= 0.0f;  cam_eye[1]= 0.0f;  cam_eye[2]= 5.0f;
  lookat[0] = 0.0f;  lookat[1] = 0.0f;  lookat[2] = 0.0f;
  up[0]     = 0.0f;  up[1]     = 1.0f;  up[2]     = 0.0f;
  hfov      = 60.0f;



  aspect_ratio = (float)width/(float)height;
  CalculateCameraVariables( cam_eye, lookat, up, hfov, aspect_ratio, camera_u, camera_v, camera_w );
    //cam_eye[0] = cam.getX(); cam_eye[1] = cam.getY(); cam_eye[2] = cam.getZ();
    //camera_u[0] = cam.getX(); camera_v[1] = cam.getY(); camera_w[2] = cam.getZ();
   rtVariableSet3fv( eye, cam_eye ) ;
   rtVariableSet3fv( U, camera_u ) ;
   rtVariableSet3fv( V, camera_v ) ;
   rtVariableSet3fv( W, camera_w ) ;

  /* Exception program */
   rtContextDeclareVariable( context, "bad_color" , &badcolor) ;
   rtVariableSet3f( badcolor, 1.0f, 1.0f, 0.0f ) ;

   rtProgramCreateFromPTXFile( context, ofToDataPath("sample5_generated_pinhole_camera.cu.ptx",true).c_str(), "exception", &exception_program ) ;
   rtContextSetExceptionProgram( context, 0, exception_program ) ;

  /* Miss program */

   rtProgramCreateFromPTXFile( context, ofToDataPath("sample5_generated_constantbg.cu.ptx",true).c_str() , "miss", &miss_program ) ;
   rtProgramDeclareVariable( miss_program, "bg_color" , &bg_color) ;
   rtVariableSet3f( bg_color, .3f, 0.1f, 0.2f ) ;
   rtContextSetMissProgram( context, 0, miss_program ) ;


    createGeometry( context, &sphere );
    createMaterial( context, &material);
    createInstance( context, sphere, material );

    rtContextValidate( context ) ;
    rtContextCompile( context ) ;
    rtContextLaunch2D( context, 0 , width, height ) ;

    result = rtBufferMap(output_buffer_obj, &imageData);
     if (result != RT_SUCCESS) {
    // Get error from context
    RTcontext context;
    const char* error;
    rtBufferGetContext(output_buffer_obj, &context);
    rtContextGetErrorString(context, result, &error);
    fprintf(stderr, "Error mapping image buffer: %s\n", error);
    exit();
  }

  /* Clean up */
     rtBufferDestroy( output_buffer_obj ) ;
     rtProgramDestroy( ray_gen_program ) ;
     rtContextDestroy( context ) ;

}



//--------------------------------------------------------------
void testApp::update(){
    cam.begin();
     //camera_u[0] = cam.getX(); camera_v[1] = cam.getY(); camera_w[2] = cam.getZ();
    cam_eye[0] = cam.getX(); cam_eye[1] = cam.getY(); cam_eye[2] = cam.getZ();
camera_u = cam.getLookAtDir().x;
    rtVariableSet3fv( eye, cam_eye ) ;
    rtVariableSet3fv( U, camera_u ) ;
    rtVariableSet3fv( V, camera_v ) ;
    rtVariableSet3fv( W, camera_w ) ;
        cam.end();
}

//--------------------------------------------------------------
void testApp::draw(){


    glDrawPixels(1024, 768, GL_BGRA,GL_UNSIGNED_BYTE, imageData);

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
