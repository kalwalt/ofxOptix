#include "ofxOptixProgram.h"
#include "stdio.h"


ofxOptixProgram::ofxOptixProgram()
{
    //ctor
}

ofxOptixProgram::~ofxOptixProgram()
{
    //dtor
}

void  ofxOptixProgram::createFromPTX(RTcontext context,const char* filename, const char* cu_filename, unsigned int entry_point_index,RTprogram* ray_gen_program )
{
    rtProgramCreateFromPTXFile( context, filename, cu_filename, ray_gen_program ) ;
    rtContextSetRayGenerationProgram( context, entry_point_index,*ray_gen_program ) ;
    if( rtProgramValidate(*ray_gen_program) != RT_SUCCESS)
    {
        ofLogError("Program is not complete.");
    //printf( "Program is not complete." );
    }



}
