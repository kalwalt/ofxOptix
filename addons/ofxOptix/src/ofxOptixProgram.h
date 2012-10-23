#pragma once

#include <optix.h>
#include "ofMain.h"
//#include "ofxOptixUtils.h"


class ofxOptixProgram
{
    public:
        ofxOptixProgram();
        ~ofxOptixProgram();
        void createFromPTX(RTcontext context,const char* filename, const char* cu_filename, unsigned int entry_point_index, RTprogram* ray_gen_program );
    protected:
    private:
};

