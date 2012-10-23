#include "ofxOptixContext.h"

ofxOptixContext::ofxOptixContext()
{
    //optixContext = NULL;
    //ctor
}

ofxOptixContext::~ofxOptixContext()
{
    //dtor
}
/*
void ofxOptixContext::create(  RTcontext optixContext, unsigned int num_ray_types, unsigned int num_entry_points) {

    RT_CHECK_ERROR( rtContextCreate( &optixContext ) ) ;
    RT_CHECK_ERROR( rtContextSetRayTypeCount( optixContext, num_ray_types ) ) ;
    RT_CHECK_ERROR( rtContextSetEntryPointCount( optixContext, num_entry_points) );

}
*/
void ofxOptixContext::create( RTcontext* context, unsigned int num_ray_types, unsigned int num_entry_points) {

     rtContextCreate( context )  ;
     rtContextSetRayTypeCount( *context, num_ray_types )  ;
     rtContextSetEntryPointCount( *context, num_entry_points) ;

}
 //RTcontext optixContext;
