#pragma once

#include <optix.h>
//#include "ofxOptixUtils.h"


class  ofxOptixBuffer
{
    public:
         ofxOptixBuffer();
        ~ ofxOptixBuffer();
        void create( RTcontext context, unsigned int bufferdesc,RTformat  format, unsigned int width, unsigned int height, RTbuffer*  buffer);

    protected:

    private:
};
