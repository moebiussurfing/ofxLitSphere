#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetDataPathRoot("../../../../../data/");//put data outisde the project to share data folder between all example projects
    
    ofDisableArbTex();
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    litSphere.setup();
    ofSetConeResolution(40, 40, 40);
}

//--------------------------------------------------------------
void ofApp::update(){
	litSphere.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    ofPushMatrix();
    ofScale(2, 2);
    ofBackgroundGradient(ofColor(180), ofColor(70), OF_GRADIENT_CIRCULAR);
    ofPopMatrix();
    
    litSphere.begin();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateX(ofGetFrameNum());
    ofDrawCone(100, 140);
    ofDrawSphere(200, 0, 70);
    ofDrawBox(-200, 0, 0, 80);
    litSphere.end();
    
	litSphere.draw();

    ofDrawBitmapStringHighlight("click to change sourse", ofPoint(0, 0));
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    litSphere.loadNext();
}

void ofApp::keyPressed(int key)
{
    if (key == ' ')
        litSphere.loadNext();
}

