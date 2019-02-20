#pragma once

#include "ofxTPSprite.h"

class ofxTPCompoundSprite
{
public:
	ofxTPCompoundSprite();
	ofxTPCompoundSprite(ofxTPSpritePtr TPSprite, std::string name="", bool isDrawable = true, bool isGui = false);
	~ofxTPCompoundSprite();
	void update();
	void draw();
	bool addChild(shared_ptr<ofxTPCompoundSprite> child);
	bool addChild(std::string name,  ofxTPSpritePtr TPSprite);
	shared_ptr<ofxTPCompoundSprite> getChildByName(std::string name);
	void updateMesh();
	void setTint(ofColor color);
	void setDrawable(bool drawable);
	void isGui(bool guiMode);
	int getNumChilds();
	void setPosition(glm::vec3 position);
	void move(glm::vec3 amount);
	void rotateDeg(float amountDeg, glm::vec3 axis);
	ofMesh getGlobalTransformedMesh();
	ofMesh getLocalTransformedMesh();

	//ToDo
	std::vector<shared_ptr<ofxTPCompoundSprite>> getChilds();
	weak_ptr<ofxTPCompoundSprite> getParent();

private:
	bool _isGui;
	bool _isDrawable;
	std::string _internalName;
	of3dPrimitive _primitiveMesh;
	std::vector<shared_ptr<ofxTPCompoundSprite>> _childs;
	weak_ptr<ofxTPCompoundSprite> _parent;
	bool checkSanity(shared_ptr<ofxTPCompoundSprite>);		//Check that no circular dependencies are made adding a child that became parents of himself
	shared_ptr<ofTexture> _textureAtlas;
};