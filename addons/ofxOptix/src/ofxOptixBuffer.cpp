#include "ofxOptixBuffer.h"


 ofxOptixBuffer::ofxOptixBuffer()
{
    //ctor
}

 ofxOptixBuffer::~ofxOptixBuffer()
{
    //dtor
}

void ofxOptixBuffer::create( RTcontext context, unsigned int bufferdesc,RTformat  format, unsigned int width, unsigned int height, RTbuffer*  buffer)
{
     rtBufferCreate( context, bufferdesc, buffer ) ;
     rtBufferSetFormat( *buffer, format) ;
     rtBufferSetSize2D( *buffer, width, height ) ;
     //rtBufferGetContext( buffer, &context );


}
