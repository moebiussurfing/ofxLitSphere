
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
	bShowGui = true;
	bAutoResize = true;
	setupGui();
#endif
}

//--------------------------------------------------------------
void ofxLitSphere::loadFilename(string name) {
	ofDisableArbTex();

	string fileName = pathGlobal + "/MatCapZBrush/Lib/" + name;

	bool b = mapTexture.load(fileName);
	if (!b)
	{
		ofLogError(__FUNCTION__) << "Mat file not found! Load first located mat file.";
		loadAt(0);
	}

	ofEnableArbTex();
}

//--------------------------------------------------------------
void ofxLitSphere::loadAt(int number) {
	ofDisableArbTex();

	string directory = pathGlobal + "/MatCapZBrush/Lib/";
	dir.listDir(directory);

	current = number;
	if (dir.size() <= current) current = 0;

	string fileName = dir.getPath(current);
	ofLogNotice(__FUNCTION__) << "fileName " + fileName;
	mapTexture.load(fileName);

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

	ofLogNotice(__FUNCTION__) << "fileName " + fileName;
	mapTexture.load(fileName);

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
	ofLogNotice(__FUNCTION__) << "fileName " + fileName;
	mapTexture.load(fileName);

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
	shader.setUniformTexture("litsphereTexture", mapTexture, 1);
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
	updateGui();
#endif
}


//--------------------------------------------------------------
void ofxLitSphere::drawGui() {
#ifdef USE_FILE_BROWSER
	if (bShowBrowser && bShowGui) {
		//draw_ImGui();

		//ImGui::SetNextWindowSize(ofVec2f(400, 100), ImGuiCond_FirstUseEver);

		gui_ImGui.begin();
		{
			draw_ImGui(10, 10, 300, 800, 6);//window position, size, amount of thumbs per row
		}
		gui_ImGui.end();
	}
#endif
}

////--------------------------------------------------------------
//void ofxLitSphere::dirRefresh() {
//	//TODO:
//	ofDirectory loadDir;
//	string dataPath = "F:\\openFrameworks\\addons\\ofxLitSphere\\example_Browser\\bin\\data\\";
//	string pathFull = dataPath + inputPath;
//	ofLogNotice(__FUNCTION__) << pathFull;
//	loadDir.open(pathFull);
//	loadDir.allowExt("jpg");
//	loadDir.allowExt("png");
//
//	imgNamesForListBox.clear();
//	for (auto im : loadDir) {
//		imgNamesForListBox.emplace_back(im.getFileName());
//	}
//}

//--------------------------------------------------------------
void ofxLitSphere::setupGui() {

	//gui.addFont("fonts\\Verdana.ttf");
	gui_ImGui.setup();

	//theme
	ModernDarkTheme();

	//inputPath = ofFilePath::getAbsolutePath("input");
	//ofStringReplace(inputPath, "/", "\\");

	ImGui::GetIO().MouseDrawCursor = false;

	//dirRefresh();

	//-

	//populate thumbs
	inputPath = "ofxLitSphere/MatCapZBrush/Lib/";

	string directory = pathGlobal + "/MatCapZBrush/Lib/";
	dirThumbs.listDir(directory);
	dirThumbs.allowExt("png");
	dirThumbs.allowExt("PNG");
	dirThumbs.allowExt("jpg");
	dirThumbs.allowExt("JPG");

	textureSource.clear();
	textureSource.resize(dirThumbs.size());
	textureSourceID.clear();
	textureSourceID.resize(dirThumbs.size());

	for (int i = 0; i < dirThumbs.size(); i++) {
		textureSourceID[i] = gui_ImGui.loadTexture(textureSource[i], dirThumbs.getPath(i));
	}
}

//--------------------------------------------------------------
void ofxLitSphere::updateGui() {
}

////--------------------------------------------------------------
//void ofxLitSphere::draw_ImGui() {
//
//	ImGui::SetNextWindowSize(ofVec2f(400, 100), ImGuiCond_FirstUseEver);
//
//	gui_ImGui.begin();
//	{
//		draw_ImGui(10, 10, 150, 800);//position and size
//	}
//	gui_ImGui.end();
//}

//--------------------------------------------------------------
void ofxLitSphere::draw_ImGui(int x, int y, int w, int h, int amntPerRow) {

	bool guishow = true;

	//thumb size
	float tw, th;
	//tw = th = 100;
	//tw = th = ImGui::GetWindowWidth();

	ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_FirstUseEver);

	if (!bAutoResize) {
		w = w / (float)(amntPerRow - 1);
		tw = th = w * 0.85;
	}
	else {
		tw = th = w / (float)(amntPerRow - 1);
	}



	ImGui::Begin("MAPCAP");
	{
		for (int i = 0; i < dirThumbs.size(); i++) {

			if (ImGui::ImageButton(GetImTextureID(textureSourceID[i]), ImVec2(tw, th)))
			{
				ofLogNotice(__FUNCTION__) << "[ " + ofToString(i) + " ] THUMB : " + dirThumbs.getName(i);

				indexBrowser = i;
				loadAt(indexBrowser);

				mapCapName = "[" + ofToString(getCurrent()) + "] " + getName();
			}

			if (i < amntPerRow-2)	ImGui::SameLine();
			else {
				if (i % amntPerRow != 0) ImGui::SameLine();
			}
		}
	}
	ImGui::End();

	/*
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
	*/
}

//--------------------------------------------------------------
void ofxLitSphere::keyPressed(int key) {
	if (key == OF_KEY_DOWN)
	{
		loadPrevious();
		mapCapName = "[" + ofToString(getCurrent()) + "] " + getName();
	}
	else if (key == OF_KEY_UP)
	{
		loadNext();
		mapCapName = "[" + ofToString(getCurrent()) + "] " + getName();
	}
}

#endif
