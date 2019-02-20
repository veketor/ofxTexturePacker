// ------------------------------------------------------------------
// ofxTPSpriteCore.h
// ofxTexturePacker - https://www.github.com/danoli3/ofxTexturePacker
// Created by Daniel Rosser and Colin Friend on 9/06/2014.
// ------------------------------------------------------------------

#pragma once
#include "ofMain.h"
#include "ofxTPTypes.h"

//-----------------------------------------------------
class ofxTPSpriteCore {
public:
    
    ofxTPSpriteCore() : texture(), type(OFX_TP_SPRITE), name("") { }
    virtual void draw(int x, int y) {}
    virtual void update(int x, int y) {}
    
    bool compareName(const string & otherName) const;
    
    void setTexture(shared_ptr<ofTexture> tex);
    virtual void setName(const string& sName);
    
    virtual void setDebugMode(bool debugMode){};
    
    virtual const string& getName() const;
    ofxTPSpriteType getType() const;
	shared_ptr<ofTexture> getTexture() { return texture; }
protected:
    shared_ptr<ofTexture> texture;
    ofxTPSpriteType type;
    string name;
};

//-------
inline bool ofxTPSpriteCore::compareName(const string & otherName) const { return (getName() == otherName); }
//-------
inline void ofxTPSpriteCore::setName(const string& sName) { name = sName; }
inline void ofxTPSpriteCore::setTexture(shared_ptr<ofTexture> tex) { texture = tex; }
//------- Getters
inline const string& ofxTPSpriteCore::getName() const { return name; }
inline ofxTPSpriteType ofxTPSpriteCore::getType() const { return type; }

