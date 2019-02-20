#include "ofxTPCompoundSprite.h"

ofxTPCompoundSprite::ofxTPCompoundSprite()
{
	_internalName = "NOTSET";
	_textureAtlas = NULL;
	_isGui = false;
	_isDrawable = true;
}

ofxTPCompoundSprite::ofxTPCompoundSprite(ofxTPSpritePtr TPSprite, std::string name, bool isDrawable, bool isGui)
{
	_internalName = name;
	_primitiveMesh = TPSprite->getMesh();
	_textureAtlas = TPSprite->getTexture();
	_isGui = isGui;
	_isDrawable = isDrawable;
}

ofxTPCompoundSprite::~ofxTPCompoundSprite()
{
	_textureAtlas = nullptr;
}


void ofxTPCompoundSprite::update()
{
}

void ofxTPCompoundSprite::draw()
{
	_primitiveMesh.draw();
	for (size_t numChilds = 0; numChilds < _childs.size(); numChilds++)
	{
		_childs.at(numChilds)->draw();
	}
}

bool ofxTPCompoundSprite::addChild(shared_ptr<ofxTPCompoundSprite> child)
{
	//Traverse child to determinate if the current object is not a child to avoid A->B->A
	if (checkSanity(child) == true)
	{
		child->_parent = this->_parent;
		child->_primitiveMesh.setParent(this->_primitiveMesh);
		_childs.push_back(child);//TODO: Check.
		return true;
	}
	return false;
}

bool ofxTPCompoundSprite::addChild(std:: string name, ofxTPSpritePtr TPSprite)
{
	ofxTPCompoundSprite tempSprite(TPSprite, name);
	addChild(std::make_shared<ofxTPCompoundSprite>(tempSprite));
	return true;
}

shared_ptr<ofxTPCompoundSprite> ofxTPCompoundSprite::getChildByName(std::string name)
{
	shared_ptr<ofxTPCompoundSprite> temp;
	for (size_t i = 0; i < _childs.size(); i++)
	{
		if (_childs.at(i)->_internalName == name)
		{
			temp = _childs.at(i);
			break;
		}
		//if (_childs.at(i))
	}
	return temp;
}

void ofxTPCompoundSprite::updateMesh()
{
}


void ofxTPCompoundSprite::setTint(ofColor color)
{
	auto vertices = _primitiveMesh.getMeshPtr()->getVertices();
	_primitiveMesh.getMeshPtr()->setColorForIndices(0, _primitiveMesh.getMeshPtr()->getVertices().size(), color);
}

void ofxTPCompoundSprite::setDrawable(bool drawable)
{
	_isDrawable = drawable;
}

void ofxTPCompoundSprite::isGui(bool guiMode)
{
	_isGui = guiMode;
}


int ofxTPCompoundSprite::getNumChilds()
{
	return _childs.size();
}

void ofxTPCompoundSprite::setPosition(glm::vec3 position)
{
	_primitiveMesh.setPosition(position);
}

void ofxTPCompoundSprite::move(glm::vec3 amount)
{
	_primitiveMesh.move(amount);
}

void ofxTPCompoundSprite::rotateDeg(float amountDeg, glm::vec3 axis)
{
	_primitiveMesh.rotateDeg(amountDeg, axis);
}

ofMesh ofxTPCompoundSprite::getGlobalTransformedMesh()
{
	return ofMesh();
}

ofMesh ofxTPCompoundSprite::getLocalTransformedMesh()
{
	return ofMesh();
}

std::vector<shared_ptr<ofxTPCompoundSprite>> ofxTPCompoundSprite::getChilds()
{
	return _childs;
}

weak_ptr<ofxTPCompoundSprite> ofxTPCompoundSprite::getParent()
{
	return _parent;
}

bool ofxTPCompoundSprite::checkSanity(shared_ptr<ofxTPCompoundSprite>)
{
	return true;
}


