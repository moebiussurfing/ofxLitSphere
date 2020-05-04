
#include "ofxLitSphere.h"

//--------------------------------------------------------------
void ofxLitSphere::setup() {
	ofDisableArbTex();

	ofEnableNormalizedTexCoords();
	ofDisableNormalizedTexCoords();
	ofEnableAlphaBlending();

	current = 0;

	shader.load(pathGlobal + "/shaders/litsphere/vert.glsl", pathGlobal + "/shaders/litsphere/frag.glsl");
	loadNext();
	loadPrevious();

	ofEnableArbTex();

#ifdef USE_FILE_BROWSER
	setupGuiBroser();
#endif
}

//--------------------------------------------------------------
void ofxLitSphere::loadAt(int number) {
	ofDisableArbTex();

	string directory = pathGlobal + "/MatCapZBrush/Lib/";
	dir.listDir(directory);

	current = number;
	if (dir.size() <= current) current = 0;

	string fileName = dir.getPath(current);
	ofLogVerbose("ofxLitSphere", "fileName " + fileName);
	texture.load(fileName);

	ofEnableArbTex();
}

//--------------------------------------------------------------
void ofxLitSphere::loadNext() {
	ofDisableArbTex();

	string directory = pathGlobal + "/MatCapZBrush/Lib/";
	dir.listDir(directory);

	current++;
	if (dir.size() <= current) current = 0;

	string fileName = dir.getPath(current);
	ofLogVerbose("ofxLitSphere", "fileName " + fileName);
	texture.load(fileName);

	matName = fileName;

	ofEnableArbTex();
}

//--------------------------------------------------------------
void ofxLitSphere::loadPrevious() {
	ofDisableArbTex();

	string directory = pathGlobal + "/MatCapZBrush/Lib/";
	dir.listDir(directory);

	current--;
	if (current < 0) current = dir.size() - 1;

	string fileName = dir.getPath(current);
	ofLogVerbose("ofxLitSphere", "fileName " + fileName);
	texture.load(fileName);

	matName = fileName;

	ofEnableArbTex();
}

//--------------------------------------------------------------
int ofxLitSphere::getCurrent() {
	return current;
}


//--------------------------------------------------------------
void ofxLitSphere::begin() {
	ofEnableNormalizedTexCoords();
	ofEnableTextureEdgeHack();
	shader.begin();
	shader.setUniformTexture("litsphereTexture", texture, 1);
}

//--------------------------------------------------------------
void ofxLitSphere::end() {
	shader.end();
	ofDisableNormalizedTexCoords();
	ofDisableTextureEdgeHack();
}

//--------------------------------------------------------------
void ofxLitSphere::reload() {
	shader.load(pathGlobal + "/shaders/litsphere/vert.glsl", pathGlobal + "/shaders/litsphere/frag.glsl");
}

//---

#ifdef USE_FILE_BROWSER

//--------------------------------------------------------------
void ofxLitSphere::update() {
#ifdef USE_FILE_BROWSER
	updateGuiBroser();
#endif
}


//--------------------------------------------------------------
void ofxLitSphere::draw() {
#ifdef USE_FILE_BROWSER
	if (bShowBrowser)
		drawGuiBroser();
#endif
}


//--------------------------------------------------------------
void ofxLitSphere::dirRefresh() {

	ofDirectory loadDir;
	//TODO:
	string dataPath = "F:\\openFrameworks\\addons\\ofxLitSphere\\example_Browser\\bin\\data\\";
	string pathFull = dataPath + inputPath;
	ofLog() << pathFull;
	loadDir.open(pathFull);
	loadDir.allowExt("jpg");
	loadDir.allowExt("png");

	imgNamesForListBox.clear();
	for (auto im : loadDir) {
		imgNamesForListBox.emplace_back(im.getFileName());
	}
}


//--------------------------------------------------------------
void ofxLitSphere::setupGuiBroser() {

	//gui.addFont("fonts\\Verdana.ttf");
	guiBrowser.setup();


	//inputPath = ofFilePath::getAbsolutePath("input");
	//ofStringReplace(inputPath, "/", "\\");

#define WIDTH 256
#define HEIGHT 256

	inputPath = "ofxLitSphere/MatCapZBrush/Lib/";

	//dirRefresh();

	//inputFilename = "1D3FCC_051B5F_81A0F2_5579E9-512px.png";
	inputFilename = "944_large_remake2.jpg";
	//inputFilename = "myredmetal_zbrush_matcap_by_digitalinkrod.jpg";



	//load your own ofImage
	string str = inputPath + inputFilename;
	ofLogNotice() << str;

	imageButtonSource.load(str);
	imageButtonID = guiBrowser.loadImage(imageButtonSource);

	ofLog() << "imageButtonID: " << imageButtonID;

	////or have the loading done for you if you don't need the ofImage reference
	//imageButtonID = gui.loadImage("of.png");

	////can also use ofPixels in same manner
	//ofLoadImage(pixelsButtonSource, inputPath + inputFilename);
	//pixelsButtonID = guiBrowser.loadPixels(pixelsButtonSource);

	////and alt method
	////pixelsButtonID = guiBrowser.loadPixels("of_upside_down.png");

	////pass in your own texture reference if you want to keep it
	//textureSourceID = guiBrowser.loadTexture(textureSource, inputPath + inputFilename);

	//or just pass a path
	//textureSourceID = guiBrowser.loadTexture("of_upside_down.png");


	//ofLogNotice() << "textureSourceID: " << textureSourceID;
}


//--------------------------------------------------------------
void ofxLitSphere::updateGuiBroser() {

	//fbo.begin();
	//ofClear(0, 0, 0, 0);
	//tex.draw(5, 5);
	//fbo.end();

}


//--------------------------------------------------------------
void ofxLitSphere::drawGuiBroser() {
	ofSetColor(255);

	if (imgMain.isAllocated()) {
		imgMain.draw(0, 0);
	}

	guiBrowser.begin();
	drawGuiBrowser(400, 20, 600, 600);
	guiBrowser.end();


}

//--------------------------------------------------------------
void ofxLitSphere::drawGuiBrowser(int x, int y, int w, int h) {

	bool guishow = true;

	ImGui::Begin("img viewer");

	//GetImTextureID is a static function define in Helpers.h that accepts ofTexture, ofImage, or GLuint
	if (ImGui::ImageButton(GetImTextureID(imageButtonID), ImVec2(200, 200)))
	{
		ofLog() << "PRESSED";
	}

	ImGui::End();

	////fbo
	//ImGui::Begin("Albedo", &guishow, 0);
	//ImGui::ImageButton((ImTextureID)(uintptr_t)fbo.getTexture(0).getTextureData().textureID, ImVec2(300, 300));
	//ImGui::End();


	//ofFill(); // It needs to be if previously was called ofNoFill
	//ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_FirstUseEver);
	//ImGui::Begin("img viewer");
	//tempStrStream.str(std::string());
	//tempStrStream << "input path: " << inputPath;



	//if (ImGui::Selectable(tempStrStream.str().c_str())) {
	//	ofFileDialogResult result = ofSystemLoadDialog("select input folder", true);
	//	if (result.bSuccess) {
	//		inputPath = result.getPath();

	//		ofDirectory loadDir;
	//		loadDir.open(inputPath);
	//		loadDir.allowExt("jpg");
	//		loadDir.allowExt("png");

	//		imgNamesForListBox.clear();
	//		for (auto im : loadDir) {
	//			imgNamesForListBox.emplace_back(im.getFileName());
	//		}
	//	}
	//}

	//if (imgNamesForListBox.size() > 0) {
	//	ImGui::Text(("Nr of files: " + ofToString(imgNamesForListBox.size())).c_str());
	//}

	//ImGui::PushItemWidth(200);
	////ImGui::ListBox("##imgfiles", &indexImgFile, imgNamesForListBox, 10);
	//ofxImGui::VectorListBox("##imgfiles", &indexImgFile, imgNamesForListBox);
	//if (indexImgFile >= 0) {
	//	if (indexImgFile != prevIndexImgFile) {
	//		string str = inputPath + "/" + imgNamesForListBox[indexImgFile];

	//		imgMain.loadImage(inputPath + "/" + imgNamesForListBox[indexImgFile]);


	//		////fbo
	//		//ofLoadImage(tex, str);

	//		prevIndexImgFile = indexImgFile;

	//		stringstream ss;
	//		ss << "name:" << imgNamesForListBox[indexImgFile] << endl;
	//		ss << "size:" << imgMain.getWidth() << "," << imgMain.getHeight() << endl;
	//		imgDescr = ss.str();
	//	}
	//}

	//ImGui::PopItemWidth();
	//ImGui::SameLine(); ImGui::Text(imgDescr.c_str());
	//ImGui::End();
}


//--------------------------------------------------------------
void ofxLitSphere::keyPressed(int key) {


	if (key == OF_KEY_DOWN)
	{
		loadPrevious();
		mapCapName = "[" + ofToString(getCurrent()) + "] " + getName();
	}
	if (key == OF_KEY_UP)
	{
		loadNext();
		mapCapName = "[" + ofToString(getCurrent()) + "] " + getName();
	}

}

#endif
