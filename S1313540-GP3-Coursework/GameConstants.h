#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

#define GLM_FORCE_RADIANS
//Define the string to appear in the top left corner of the window
#define WINDOW_TITLE "S1313540-GamesProgramming3"

// Windows & OpenGL 
#include "GL\glew.h"
#include <stdlib.h>
#include <Windows.h>
#include "GL\glut.h"
#include <iostream>
#include <string>
#include <ctime>

// Image Texture loading library
#include "SOIL/SOIL.h"

// Font
#include "FTGL\ftgl.h"

// Maths functions
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\geometric.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\quaternion.hpp"

// STL Container & Algorithms
#include <vector>
#include <map>
#include <algorithm>

// Textures
#include "cTexture.h"

#include "cInputMgr.h"
#include "inputHandle.h"

const std::string ASSETPATH = "assets/";
const std::string TEXTUREPATH = ASSETPATH + "textures/";
const std::string MODELPATH = ASSETPATH + "models/";
const std::string SHADERPATH = ASSETPATH + "shaders/";


struct lightColour4
{
	lightColour4(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 0.0f) : r(_r), g(_g), b(_b), a(_a) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
	float a;	// Alpha
};

struct colour3f
{
	colour3f(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f) : r(_r), g(_g), b(_b) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
};

struct mdlDimensions{
	float s_mdlWidth, s_mdlheight, s_mdldepth;
};

const float PLAYFIELDX = 100.0f;
const float PLAYFIELDZ = 300.0f;

extern int drawMode;
extern float rotationAngle;
extern float translationZ;
extern bool fire;


#endif