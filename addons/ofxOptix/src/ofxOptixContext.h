#pragma once

#include <optix.h>
//#include "ofxOptixUtils.h"



class ofxOptixContext
{
    public:
        ofxOptixContext();
        ~ofxOptixContext();
        void create( RTcontext* context, unsigned int num_ray_types, unsigned int num_entry_points);



    protected:
                //RTcontext optixContext;
    private:
};


