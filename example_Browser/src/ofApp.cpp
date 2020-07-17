#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//ofSetDataPathRoot("../../../../../data/");//put data outisde the project to share data folder between all example projects

	ofDisableArbTex();
	ofEnableDepthTest();
	ofSetVerticalSync(true);
	litSphere.setup();

	ofSetConeResolution(40, 40, 40);

	indexScene = 0;
	meshForm.load("basic_form.ply");
	//meshForm.load("head.obj.ply");
	
	primFloor.set(1000, 1000);
	//primFloor.setPosition(0, -500, 0);
	primFloor.rotateDeg(90, { 1,0,0 });

	//cam.lookAt(glm::vec3(0, 0, 0));
	//cam.setPosition(glm::vec3(0, 2000, 0));
}

//--------------------------------------------------------------
void ofApp::update() {
	if (ofGetFrameNum() == 5) {//cam bug..
		bEnableMouseCam = false;
		cam.disableMouseInput();
	}

#ifdef USE_FILE_BROWSER
	litSphere.update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofClear(32);
	//ofPushMatrix();
	//ofScale(2, 2);
	//ofBackgroundGradient(ofColor(32), ofColor(0), OF_GRADIENT_CIRCULAR);
	//ofPopMatrix();

	//-

	ofEnableDepthTest();
	
	cam.begin();
	
	//ofLight light; // also works with ofNode
	//light.setPosition(glm::vec3(4, 2.8, 5));
	//light.lookAt(glm::vec3(0, 0, 0));

	litSphere.begin();
	{
		if (indexScene == 0) {
			ofPushMatrix();
			{
				//ofTranslate(0, 300, 0);
				ofRotateX(ofGetFrameNum());
				ofDrawCone(100, 140);
				ofDrawSphere(200, 0, 70);
				ofDrawBox(-200, 0, 0, 80);
			}
			ofPopMatrix();
		}
		else if (indexScene == 1) {
			////ofTranslate(0, 500);
			//primFloor.draw();

			ofPushMatrix();
			float scale = 250;
			ofScale(scale, scale, scale);
			ofRotateYDeg(75);

			meshForm.draw();

			ofPopMatrix();
		}
	}
	litSphere.end();

	cam.end();

	//-

	ofDisableDepthTest();

#ifdef USE_FILE_BROWSER
	litSphere.drawGui();
#endif

	if (!litSphere.isVisibleGui()) ofDrawBitmapStringHighlight("CLICK TO CHANGE SOURSE", ofPoint(0, -200));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (!litSphere.isVisibleGui()) litSphere.loadNext();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_CONTROL) {
		bEnableMouseCam = true;
		cam.enableMouseInput();
	}

	else if (key == ' ') litSphere.loadNext();
	else if (key == 'g') litSphere.setToggleVisibleGui();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == OF_KEY_CONTROL) {
		bEnableMouseCam = false;
		cam.disableMouseInput();
	}
}

