#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    video[0].loadMovie( "test.m4v" );
    
    for (int i=0; i<NUM; i++) {
        video[i].play();
    }
    
    int x = 0;
    int y = 0;
    
    int w[NUM];
    int h[NUM];
    for (int i=0; i<NUM; i++) {
        w[i] = video[i].width;
        h[i] = video[i].height;
        fbo[i].allocate(w[i], h[i]);
        
        warper[i].setSourceRect( ofRectangle( 0, 0, w[i], h[i] ) );
        warper[i].setTopLeftCornerPosition( ofPoint( x, y ) );
        warper[i].setTopRightCornerPosition( ofPoint( x + w[i] * 0.15, y ) );
        warper[i].setBottomLeftCornerPosition( ofPoint( x, y + h[i] * 0.15 ) );
        warper[i].setBottomRightCornerPosition( ofPoint( x + w[i] * 0.15, y + h[i] * 0.15 ) );
        warper[i].setup();
        
        x+=100;
        y+=100;
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i=0; i<NUM; i++) {
        video[i].update();
    }
    
    if(ofGetFrameNum()){
        return;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    
    for (int i=0; i<NUM; i++) {
        fbo[i].begin();{
            video[i].draw(0, 0);
        }
        fbo[i].end();
        
        ofMatrix4x4 mat = warper[i].getMatrix();
        
        glPushMatrix();
        glMultMatrixf(mat.getPtr());
        {
            fbo[i].draw(0, 0);
        }
        glPopMatrix();
        
        ofSetColor(100, 100, 100);
        ofSetLineWidth(2);
        warper[i].draw();
        
        ofSetColor( ofColor :: white );
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == 'l' ){
        for (int i=0; i<NUM; i++) {
            warper[i].toggleShow();
        }
    }
    if( key == '0' ){
        for (int i=0; i<NUM; i++) {
            video[i].firstFrame();
        }
    }
    if (key == 'f') {
        ofToggleFullscreen();
    }

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
