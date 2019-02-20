// ------------------------------------------------------------------
// ofxTPSprite.cpp
// ofxTexturePacker - https://www.github.com/danoli3/ofxTexturePacker
// Created by Daniel Rosser and Colin Friend on 9/06/2014.
// ------------------------------------------------------------------
#include "ofxTPSprite.h"

ofxTPSprite::ofxTPSprite(ofxTPSpriteDataPtr theData) :
    data(theData)
{
}

float ofxTPSprite::getWidth(){
    return data->getW();
}
/*
ofxTPSpriteDataPtr ofxTPSprite::getData()
{
	return data;
}
*/
float ofxTPSprite::getHeight()
{
	return data->getHeight();
}

void ofxTPSprite::draw(int x, int y, int z) {
    if(data->isRotated()) {
        ofPushMatrix();
            ofTranslate(x, y, z); // translate Draw position
            x = y = z = 0;
            ofPushMatrix();
        
//            if(data->isDebugMode()){
//                ofPushStyle();      //----------- Draw original unrotated texture
//                ofSetColor(255, 0, 0, 128);
//                ofNoFill();
//                ofRect(x+data->getOffsetY(), y+data->getOffsetX(), data->getOffsetHeight(), data->getOffsetWidth());
//                if(texture != NULL) {
//                   texture->drawSubsection(x+data->getOffsetY(), y+data->getOffsetX(), data->getW(), data->getH(), data->getX(), data->getY(), data->getW(), data->getH());
//                }
//                ofPopStyle();
//            }
            ofTranslate(data->getOffsetX(), data->getOffsetHeight()-data->getOffsetY());
            ofRotateDeg(-90);
            if(data->isDebugMode()){
                ofPushStyle();
                ofSetColor(0, 255, 0, 128);
                ofNoFill();
                ofDrawRectangle(x-data->getOffsetY(), y-data->getOffsetX(), data->getOffsetHeight(), data->getOffsetWidth());
                ofPopStyle();
            }
        
    } else {
        x += data->getOffsetX();
        y += data->getOffsetY();
    }
    
    if(data->isDebugMode()){
        if(!data->isRotated()){
            ofPushStyle();
            ofNoFill();
            ofDrawRectangle(x-data->getOffsetX(), y-data->getOffsetY(), data->getOffsetWidth(), data->getOffsetHeight());
            ofPopStyle();
        }
    }
    if(texture != NULL) {
        ofPushMatrix();
        //ofLog() << data->getPX() << " " << data->getW();
        ofTranslate(-data->getPX() * data->getW(), -data->getPY() * data->getH(), z);
        texture->drawSubsection(x, y, data->getW(), data->getH(), data->getX(), data->getY(), data->getW(), data->getH());
		ofNoFill();
		//ofDrawRectangle(x, y, data->getW(), data->getH());
		ofFill();
        ofPopMatrix();
    }
    
    if(data->isRotated()) {
            ofPopMatrix();
         ofPopStyle();
         ofPopMatrix();
    }
}

ofMesh ofxTPSprite::getMesh()
{
	ofMesh tempMesh;
	if (data != NULL) 
	{
		//Texture UV
		float textureOffsetX = data->getX();
		float textureOffsetY = data->getY();
		float anchorX = data->getPX();
		float anchorY = data->getPY();
		//Mesh-Texture dimensions
		float width = data->getW();
		float height = data->getH();
		//Mesh translation
		float xOffset = data->getOffsetX() - anchorX*width;
		float yOffset = data->getOffsetY() - anchorY*height;
		
		tempMesh.setMode(OF_PRIMITIVE_TRIANGLES);
		tempMesh.addVertex(ofDefaultVertexType(xOffset, yOffset, 0));
		tempMesh.addTexCoord(ofVec2f(textureOffsetX, textureOffsetY));
		tempMesh.addVertex(ofDefaultVertexType(xOffset, yOffset + height, 0));
		tempMesh.addTexCoord(ofVec2f(textureOffsetX, textureOffsetY + height));
		tempMesh.addVertex(ofDefaultVertexType(xOffset + width, yOffset, 0));
		tempMesh.addTexCoord(ofVec2f(textureOffsetX + width, textureOffsetY));
		tempMesh.addVertex(ofDefaultVertexType(xOffset + width, yOffset + height, 0));
		tempMesh.addTexCoord(ofVec2f(textureOffsetX + width, textureOffsetY + height));
		tempMesh.enableIndices();
		tempMesh.addIndex(0);
		tempMesh.addIndex(1);
		tempMesh.addIndex(2);
		tempMesh.addIndex(2);
		tempMesh.addIndex(1);
		tempMesh.addIndex(3);
	}
	return tempMesh;
}

of3dPrimitive ofxTPSprite::getPrimitive()
{
	of3dPrimitive tempPrimitive;
	ofMesh tempMesh = getMesh();
	ofMesh *tempMeshOf3dPrimitivePTR = tempPrimitive.getMeshPtr();
	tempMeshOf3dPrimitivePTR = &tempMesh;
	return tempPrimitive;
}
