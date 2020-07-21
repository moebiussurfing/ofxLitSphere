
#include "ofxLitSphere.h"

//--------------------------------------------------------------
void ofxLitSphere::setup() {
	ofDisableArbTex();

	ofEnableNormalizedTexCoords();
	ofDisableNormalizedTexCoords();
	ofEnableAlphaBlending();


#ifdef USE_FILE_BROWSER
	indexBrowser.set("MatCap Index", -1, 0, 1);
	nameMat.set("MatCap name", "");
	sizeThumb.set("THUMB SIZE", 100, 40, 300);
#endif

	indexMat = 0;
	shaderMat.load(pathGlobal + "/shaders/litsphere/vert.glsl", pathGlobal + "/shaders/litsphere/frag.glsl");

	pathDirMats = pathGlobal + "/MatCapZBrush/Lib/";
	dirMats.listDir(pathDirMats);
	sizeDirMats = dirMats.size();
	
#ifdef USE_FILE_BROWSER
	indexBrowser.setMax(dirMats.size() - 1);
#endif

	loadAt(indexMat);

	ofEnableArbTex();

#ifdef USE_FILE_BROWSER
	bShowGui = true;
	//bAutoResize = true;
	setupGui();
#endif
}

//--------------------------------------------------------------
void ofxLitSphere::loadFilename(string name) {
	ofDisableArbTex();

	//string fileName = pathGlobal + "/MatCapZBrush/Lib/" + name;
	string fileName = pathDirMats + name;

	bool b = textureMat.load(fileName);
	if (!b)
	{
		ofLogFatalError(__FUNCTION__) << "Mat file not found! Force load first located mat file...";
		loadAt(0);
	}

	matName = fileName;
	mapCapName = "[" + ofToString(getCurrentIndex()) + "] " + getName();
	nameMat = getName();

	ofEnableArbTex();
}

//--------------------------------------------------------------
void ofxLitSphere::loadAt(int number) {
	ofDisableArbTex();

	pathDirMats = pathGlobal + "/MatCapZBrush/Lib/";
	dirMats.listDir(pathDirMats);
	sizeDirMats = dirMats.size();
	
#ifdef USE_FILE_BROWSER
	indexBrowser.setMax(dirMats.size() - 1);
#endif

	if (dirMats.size() <= 0) {
		ofLogFatalError(__FUNCTION__) << "FILES NOT FOUND! " + pathDirMats;
		sizeDirMats = -1;
	}
	else {
		indexMat = number;

		if (indexMat > dirMats.size() - 1) indexMat = 0;
		//if (indexMat > dir.size() - 1) indexMat = dir.size() - 1;
				
#ifdef USE_FILE_BROWSER
		indexBrowser = indexMat;
#endif

		string fileName = dirMats.getPath(indexMat);
		ofLogNotice(__FUNCTION__) << "fileName " + fileName;
		textureMat.load(fileName);

		matName = fileName;

#ifdef USE_FILE_BROWSER
		mapCapName = "[" + ofToString(getCurrentIndex()) + "] " + getName();
		nameMat = getName();
#endif
	}

	ofEnableArbTex();
}

//--------------------------------------------------------------
void ofxLitSphere::loadNext() {
	//dirMats.listDir(pathGlobal + "/MatCapZBrush/Lib/");
	dirMats.listDir(pathDirMats);

	indexMat++;
	if (indexMat > dirMats.size() - 1) indexMat = 0;
	loadAt(indexMat);
}

//--------------------------------------------------------------
void ofxLitSphere::loadPrevious() {
	//dirMats.listDir(pathGlobal + "/MatCapZBrush/Lib/");
	dirMats.listDir(pathDirMats);

	indexMat--;
	if (indexMat < 0) indexMat = 0;
	loadAt(indexMat);
}

//--------------------------------------------------------------
int ofxLitSphere::getCurrentIndex() {
	return indexMat;
}


//--------------------------------------------------------------
void ofxLitSphere::begin() {
	ofEnableNormalizedTexCoords();
	ofEnableTextureEdgeHack();
	shaderMat.begin();
	shaderMat.setUniformTexture("litsphereTexture", textureMat, 1);
}

//--------------------------------------------------------------
void ofxLitSphere::end() {
	shaderMat.end();
	ofDisableNormalizedTexCoords();
	ofDisableTextureEdgeHack();
}

//--------------------------------------------------------------
void ofxLitSphere::reloadShader() {
	shaderMat.load(pathGlobal + "/shaders/litsphere/vert.glsl", pathGlobal + "/shaders/litsphere/frag.glsl");
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
	if (bShowGui) {
#ifdef USE_FILE_BROWSER
		if (bShowBrowser) {
			gui_ImGui.begin();
			{
				draw_ImGui(10, 10, 300, 800);//window position and size
			}
			gui_ImGui.end();
		}
#endif
	}
}

//--------------------------------------------------------------
void ofxLitSphere::setupGui() {

	//gui.addFont("fonts\\Verdana.ttf");
	gui_ImGui.setup();

	//theme
	ModernDarkTheme();

	//ImGui::GetIO().MouseDrawCursor = false;

	//-

	//scan, load and populate thumbs
	pathDirPreviews = pathGlobal + "/MatCapZBrush/previews/";
	dirThumbs.listDir(pathDirPreviews);
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

//--------------------------------------------------------------
void ofxLitSphere::draw_ImGui(int x, int y, int w, int h) {

	auto mainSettings = ofxImGui::Settings();
	//ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_FirstUseEver);
	//ImGui::Text("ofxLitSphere");

	//--

	if (ofxImGui::BeginWindow("Settings", mainSettings, false))//->required to allow helpers..but do not stores ini settings..
	//ImGui::Begin("Settings");//raw
	{
		ofxImGui::AddParameter(sizeThumb);
		string str0 = ofToString(indexBrowser);
		string str1 = str0 + "/" + ofToString(dirThumbs.size()-1);
		ImGui::Text(str1.c_str());
		ImGui::Text(nameMat.get().c_str());
		//ofxImGui::AddParameter(indexBrowser);
		//ofxImGui::AddParameter(nameMat);
	}
	//ImGui::End();//raw
	ofxImGui::EndWindow(mainSettings);

	//--

	////Displacement
	//if (ofxImGui::BeginWindow("Displacement", mainSettings, false))//->required to allow helpers..but do not stores ini settings..
	//{
	//	ofxImGui::AddGroup(params_Displacement, mainSettings);
	//}
	//ofxImGui::EndWindow(mainSettings);

	//--

	//if (ofxImGui::BeginWindow("MatCap", mainSettings, false))//->required to allow helpers..but do not stores settings..
	ImGui::Begin("MatCap");
	{
		ImVec2 button_sz((float)sizeThumb.get(), (float)sizeThumb.get());

		ImGuiStyle& style = ImGui::GetStyle();
		int buttons_count = dirThumbs.size();
		float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

		for (int n = 0; n < buttons_count; n++)
		{
			ImGui::PushID(n);
			string name = ofToString(n);

			//customize colors
			if (n == indexBrowser)//when selected
			{
				const ImVec4 color1 = ImVec4(0, 0, 0, 1);//changes button color to black
				ImGui::PushStyleColor(ImGuiCol_Button, color1);
			}
			else { //not selected
				const ImVec4 color2 = style.Colors[ImGuiCol_Button];//do not changes the color
				ImGui::PushStyleColor(ImGuiCol_Button, color2);
			}

			//-

			//image button
			if (ImGui::ImageButton(GetImTextureID(textureSourceID[n]), button_sz))
			{
				ofLogNotice(__FUNCTION__) << "[ " + ofToString(n) + " ] THUMB : " + dirThumbs.getName(n);

				indexBrowser = n;
				loadAt(indexBrowser);

				mapCapName = "[" + ofToString(getCurrentIndex()) + "] " + getName();
				nameMat = getName();
			}

			//-

			//customize colors
			ImGui::PopStyleColor();

			float last_button_x2 = ImGui::GetItemRectMax().x;
			float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
			if (n + 1 < buttons_count && next_button_x2 < window_visible_x2) ImGui::SameLine();
			ImGui::PopID();
		}
	}
	ImGui::End();
	//ofxImGui::EndWindow(mainSettings);
}
#endif

//--------------------------------------------------------------
void ofxLitSphere::keyPressed(int key) {
	if (key == OF_KEY_LEFT)
	{
		loadPrevious();
	}
	else if (key == OF_KEY_RIGHT)
	{
		loadNext();
	}
}

