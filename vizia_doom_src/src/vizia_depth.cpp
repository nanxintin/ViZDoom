//
// Created by gregory on 22.12.15.
//
#include "vizia_depth.h"

depthBuffer* depthMap = NULL;

depthBuffer::depthBuffer(unsigned int width, unsigned int height) : bufferSize(height*width), bufferWidth(width), bufferHeight(height) {
    buffer = new u_int8_t[bufferSize];
    for(unsigned int i=0;i<bufferSize;i++)
        buffer[i]=0;
}

depthBuffer::~depthBuffer() {
    delete[] buffer;
}

u_int8_t* depthBuffer::getBuffer() { return buffer; }

u_int8_t* depthBuffer::getBufferPoint(unsigned int x, unsigned int y) {
    if( x < bufferWidth && y < bufferHeight )
        return buffer + x + y*bufferWidth;
    else
    return NULL;}

void depthBuffer::setPoint(unsigned int x, unsigned int y) {
    u_int8_t *dpth = getBufferPoint(x, y);
    if(dpth!=NULL)
        *dpth = actualDepth;
}

void depthBuffer::setPoint(unsigned int x, unsigned int y, u_int8_t depth) {
    u_int8_t *dpth = getBufferPoint(x, y);
    if(dpth!=NULL)
        *dpth = depth;
}

void depthBuffer::setActualDepth(u_int8_t depth) {this->actualDepth=depth; }

void depthBuffer::setActualDepthConv(int depth) {
    if(depth>maxDepth)
        this->actualDepth=0;
    else if(depth<minDepth)
        this->actualDepth=255;
    else {
        depth-=minDepth;
        this->actualDepth = 255 - (depth-minDepth) / this->convSteps;
    }
}

void depthBuffer::updateActualDepth(int adsb) {
    int act = this->actualDepth;
    if(act+adsb>255)
        this->actualDepth=255;
    else if(act+adsb<0)
        this->actualDepth=0;
    else
        this->actualDepth+=adsb;
}

void depthBuffer::storeX(int x) {this->tX=x; }

void depthBuffer::storeY(int y) {this->tY=y; }

int depthBuffer::getX() {return this->tX; }

int depthBuffer::getY() {return this->tY; }


unsigned int depthBuffer::getBufferSize(){
    return this->bufferSize;
}

void depthBuffer::setDepthBoundries(int maxDepth, int minDepth) {
    this->maxDepth=maxDepth;
    this->minDepth=minDepth;
    this->convSteps = (maxDepth-minDepth)/255;
}

unsigned int depthBuffer::getBufferWidth(){
    return bufferWidth;
}

unsigned int depthBuffer::getBufferHeight(){
    return bufferHeight;
}

void depthBuffer::clearBuffer() {
    for(unsigned int i=0;i<bufferSize;i++)
        buffer[i]=0;
}

void depthBuffer::clearBuffer(u_int8_t color) {
    for(unsigned int i=0;i<bufferSize;i++)
        buffer[i]=color;
}