#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//ofSetDataPathRoot("../../../../../data/");//put data outisde the project to share data folder between all example projects

	ofDisableArbTex();
	ofEnableDepthTest();
	ofSetVerticalSync(true);
	litSphere.setup();

	bHelp = false;

	//-

	//scene

	bDrawFloor = true;

	//press return to switch scene
	//0:prims or 1:models
	indexScene = 1;

	//prims
	ofSetConeResolution(40, 40, 40);

	//models

	//object
	model.loadModel("obj_free_base_female_head.OBJ", 10);
	//model.loadModel("head.obj", 10);
	//model.loadModel("young_boy_head_obj.obj", 10);

	////mesh
	//meshForm.load("basic_form.ply");
	////meshForm.load("head.obj");//not loading
}

//--------------------------------------------------------------
void ofApp::update() {
	//workaround to bug
	if (ofGetFrameNum() == 5) {
		bEnableMouseCam = false;
		cam.disableMouseInput();
	}

#ifdef USE_FILE_BROWSER
	litSphere.update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw() {
	//background
	ofBackgroundGradient(ofColor(40, 40, 40), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);

	//-

	ofEnableDepthTest();

	cam.begin();
	{
		//test lights
		//ofLight light; // also works with ofNode
		//light.setPosition(glm::vec3(4, 2.8, 5));
		//light.lookAt(glm::vec3(0, 0, 0));

		//draw a grid on the floor
		if (bDrawFloor) {
			ofPushMatrix();
			ofPushStyle();
			ofSetColor(ofColor(60));
			ofTranslate(0, -500, 0);
			ofRotate(90, 0, 0, -1);
			ofDrawGridPlane(500, 5, false);
			ofPopStyle();
			ofPopMatrix();
		}

		litSphere.begin();
		{
			//draw your scene here!...

			//--

			float speedRot = 0.25f;

			if (indexScene == 0) {//prims
				ofPushMatrix();

				//ofTranslate(0, 300, 0);
				ofRotateX(ofGetFrameNum() * speedRot);
				ofDrawCone(100, 140);
				ofDrawSphere(200, 0, 70);
				ofDrawBox(-200, 0, 0, 80);

				ofPopMatrix();
			}

			else if (indexScene == 1) {//models

				ofPushMatrix();

				//mesh
				//float scale = 250;
				//ofScale(scale, scale, scale);
				//ofRotateYDeg(75);
				//meshForm.draw();

				//object
				float scale = 0.5f;
				//ofTranslate(0, -250, 0);
				ofScale(scale, scale, scale);
				ofRotateXDeg(180);
				ofRotateY(ofGetFrameNum() * speedRot);
				//ofRotateYDeg(180);
				model.drawFaces();

				ofPopMatrix();
			}
		}
		litSphere.end();
	}
	cam.end();

	ofDisableDepthTest();

	//--

	//gui

#ifdef USE_FILE_BROWSER
	litSphere.drawGui();
#endif

	if (bHelp) {
		string str = "";
		str += "KEY G: SHOW GUI\n";
		str += "KEY RETURN: CHANGE SCENE PRIMS/MODEL\n";
		str += "KEY CONTROL: ENABLE MOUSE CAMERA\n";
		if (!litSphere.isVisibleGui()) {
			str += "KEY SPACE & MOUSE CLICK: NEXT MatCap FILE " + litSphere.getName();
		}
		ofDrawBitmapStringHighlight(str, ofPoint(300, 20));
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (!litSphere.isVisibleGui()) litSphere.loadNext();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	litSphere.keyPressed(key);

	//press control to move camera
	if (key == OF_KEY_CONTROL) {
		bEnableMouseCam = true;
		cam.enableMouseInput();
	}

	//load next cap
	else if (key == ' ') litSphere.loadNext();

	//enable draw floor
	else if (key == 'f') bDrawFloor = !bDrawFloor;

	//return to change scene
	else if (key == OF_KEY_RETURN) {
		if (indexScene == 0) indexScene++;
		else if (indexScene == 1) indexScene = 0;
	}

	//hide gui to enable disable gui and browse by keys and mouse clicks
	else if (key == 'g' || key == 'G') litSphere.setToggleVisibleGui();

	//hide help
	else if (key == 'h' || key == 'H') bHelp = !bHelp;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	//press control to move camera
	if (key == OF_KEY_CONTROL) {
		bEnableMouseCam = false;
		cam.disableMouseInput();
	}
}

