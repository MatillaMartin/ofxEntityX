#include "ofApp.h"

//--------------------------------------------------------------
ofApp::ofApp()
	:
	//level(Level::LevelInfo(25, 25, 10, 50, false))
	level(Level::LevelInfo(5, 5, 10, 50, true))
{

}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60.0f);
}

//--------------------------------------------------------------
void ofApp::update(){
	level.update(MIN(ofGetLastFrameTime(), 1.0 / ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
	level.render();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	level.onWindowResize(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
