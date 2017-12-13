#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


//#include <windows.h>
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cColours.h"
#include "cMaterial.h"
#include "cLight.h"
#include "cFontMgr.h"
#include "cCamera.h"
#include "cInputMgr.h"
#include "cModel.h"
#include "cSceneMgr.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{
    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;

    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	static cSceneMgr* theScene = cSceneMgr::getInstance();

    //The example OpenGL code
    windowOGL theOGLWnd;

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);


    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	// load game fonts
	// Load Fonts
	LPCSTR gameFonts[3] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf", "Fonts/doctor_who.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);
	theFontMgr->addFont("DrWho", gameFonts[2], 48);

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	//set up actions and axis
	InputAction* ia = new InputAction();
	ia->name = "SpeedBoost";
	ia->keys = {VK_SHIFT};//c
	theInputMgr->addInputAction(*ia);
	InputAxis* iAxis = new InputAxis();
	iAxis->name = "Vertical";
	iAxis->keysPos = { 'W' };
	iAxis->keysNeg = { 'S' };
	theInputMgr->addInputAxis(*iAxis);
	iAxis = new InputAxis();
	iAxis->name = "Horizontal";
	iAxis->keysPos = { 'D' };
	iAxis->keysNeg = { 'A' };
	theInputMgr->addInputAxis(*iAxis);

	theInputMgr->resetMouseDelta();
	theInputMgr->cleanInputActions();
	theInputMgr->cleanInputAxis();

	cSceneMgr::getInstance()->begin();

	float tCount = 0.0f;
	string outputMsg;

	std::string versionGL = (char*)(glGetString(GL_VERSION));
	
	OutputDebugString(std::string("\nOPENGL VERSION: " + versionGL).c_str());
	OutputDebugString(std::string("\nGLEW_VERSION: " + to_string(GLEW_VERSION_MAJOR)).c_str());
	OutputDebugString(std::string("\nGLEW_VERSION_MINOR: " + to_string(GLEW_VERSION_MINOR)).c_str());

   //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events
		theInputMgr->updateInputActions();
		theInputMgr->updateInputAxis();

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();
		
		// Lab code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cSceneMgr::getInstance()->update(elapsedTime);

		cSceneMgr::getInstance()->render();

		//theOGLWnd.setOrtho2D(windowWidth, windowHeight);
		//theFontMgr->getFont("DrWho")->printText("Tardis Wars", FTPoint(10, 35, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		//theFontMgr->getFont("DrWho")->printText(outputMsg.c_str(), FTPoint(850, 35, 0.0f), colour3f(255.0f, 255.0f, 0.0f)); // uses c_str to convert string to LPCSTR

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_PRESSED_BUFFER);
		theInputMgr->resetMouseDelta();
		theInputMgr->cleanInputActions();
		theInputMgr->cleanInputAxis();

		pgmWNDMgr->swapBuffers();

		tCount += elapsedTime;
	}

	cSceneMgr::getInstance()->releaseResources();
	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
