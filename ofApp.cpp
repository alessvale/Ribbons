#include "ofApp.h"

#define N  1000
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::lightGray);
    ofToggleFullscreen();
    ofHideCursor();

    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    pos = ofVec2f(ofRandom(-ofGetWidth() * 0.5, ofGetWidth() * 0.5), ofRandom(-ofGetHeight() * 0.5, ofGetHeight() * 0.5));

    ofEnableDepthTest();
    ofEnableLighting();

    material.setDiffuseColor(ofColor::white);
    material.setAmbientColor(ofColor::white);

    material.setShininess(128);
}

//--------------------------------------------------------------
void ofApp::update(){
    t += 10;
    theta += ofRandom(0.0, 0.01);

   
        ofVec2f target = ofVec2f(ofGetMouseX() - ofGetWidth() * 0.5, ofGetMouseY() - ofGetHeight() * 0.5);
        ofVec2f  dir = target - pos;
        float m = dir.length();
        dir.normalize();
        dir = dir.getScaled(20);
        pos = pos + dir;
        ofVec2f ort = ofVec2f(-pos.y, pos.x);
        ort.normalize();
        ort = ort.getScaled(20 + (m * (0.3 + 0.2 * sin(theta * 2 * PI))));

        int n = mesh.getNumVertices();
        if (n < N) {
            float c = 1;
            ofVec3f v0 = ofVec3f(pos.x, pos.y, t * c);
            ofVec3f v1 = ofVec3f(pos.x + ort.x, pos.y + ort.y, t * c);
            mesh.addVertex(v0);
            mesh.addVertex(v1);
        }
        else {
            mesh.removeVertex(0);
            mesh.removeVertex(0);
        }
   
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::lightGray);
    light.enable();
    material.setDiffuseColor(ofColor(255 * sin(theta * 0.04 * 2 * PI), 102, 102));
    material.setAmbientColor(ofColor(255 * sin(theta * 0.04 * 2 * PI), 12, 102));
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5, -t);
    material.begin();
    mesh.draw();
    material.end();
    ofPopMatrix();
    light.disable();
}
