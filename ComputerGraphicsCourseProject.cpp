// OpenGLPractice.cpp : Defines the entry point for the application.
//

#include <Windows.h>
#include "framework.h"
#include "ComputerGraphicsCourseProject.h"
#include "BresenhamCircleAlgorithm.hpp"
#include <vector>
#include <conio.h>
#include <mciapi.h>
#include "Vertex.h"
#include "Util.hpp"

#pragma comment (lib,"Winmm.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")

#define MAX_LOADSTRING 100
#define XAXIS 1.0f,0.0f,0.0f
#define YAXIS 0.0f,1.0f,0.0f
#define ZAXIS 0.0f,0.0f,1.0f


LPCWSTR const Sound_File_Open1 = L"open ./havent_you_heared.mp3 type mpegvideo alias Current_Sound_Command1";
LPCWSTR const Sound_File_Open2 = L"open ./ya_taiba.mp3 type mpegvideo alias Current_Sound_Command2";
LPCWSTR const Sound_File_Open3 = L"open ./saout_safeer.mp3 type mpegvideo alias Current_Sound_Command3";
void PlaySong1()
{
	MCIERROR open = mciSendString(Sound_File_Open1, NULL, 0, NULL);
	MCIERROR play = mciSendString(L"play Current_Sound_Command1 repeat", NULL, 0, NULL);
}

void StopSong1()
{
	MCIERROR open = mciSendString(Sound_File_Open1, NULL, 0, NULL);
	MCIERROR stop = mciSendString(L"stop Current_Sound_Command1", NULL, 0, NULL);
}

void PlaySong2()
{
	MCIERROR open = mciSendString(Sound_File_Open2, NULL, 0, NULL);
	MCIERROR play = mciSendString(L"play Current_Sound_Command2 repeat", NULL, 0, NULL);
}

void StopSong2()
{
	MCIERROR open = mciSendString(Sound_File_Open2, NULL, 0, NULL);
	MCIERROR stop = mciSendString(L"stop Current_Sound_Command2", NULL, 0, NULL);
}

void PlaySong3()
{
	MCIERROR open = mciSendString(Sound_File_Open3, NULL, 0, NULL);
	MCIERROR play = mciSendString(L"play Current_Sound_Command3 repeat", NULL, 0, NULL);
}

void StopSong3()
{
	MCIERROR open = mciSendString(Sound_File_Open3, NULL, 0, NULL);
	MCIERROR stop = mciSendString(L"stop Current_Sound_Command3", NULL, 0, NULL);
}


float houseColor[] = { 0.3, 0.7, 0.5 };
float bikeColor[] = { 0.0f, 0.0f, 0.0f };
float beamsColor[] = { 1.0f, 0.0f, 0.0f };
float wheelColor[] = { 0.0f, 0.0f, 0.7f };
float gray[] = { 0.3f, 0.3f, 0.3f };
float black[] = { 0.0f, 0.0f, 0.0f };
float brown[] = { 0.5f, 0.35f, 0.05f };

float ztheta = 0.0f, xtheta = -20.0f, ytheta = 30.0f;

float xpos = 0.0f, ypos = -0.5f, zpos = 0.0f;

Vertex bikeCenter = { 0.55f, -0.17f, 0.0f };

float wheeltheta = 0.0f;
float frontwheeltheta = 90.0f;
float bikeCirculationTheta = 360.0f;
bool bikeCirculation = false;

float windowtheta = 0.0f;
float windowRotationAxis = 0.025f;

float doortheta = 0.0f;


void ApplySceneTransformations()
{
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(xpos, ypos, zpos);

	glRotatef(xtheta, XAXIS);
	glRotatef(ytheta, YAXIS);
}

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_COMPUTERGRAPHICSCOURSEPROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}




	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COMPUTERGRAPHICSCOURSEPROJECT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COMPUTERGRAPHICSCOURSEPROJECT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_COMPUTERGRAPHICSCOURSEPROJECT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
		1,                     // version number  
		PFD_DRAW_TO_WINDOW |   // support window  
		PFD_SUPPORT_OPENGL |   // support OpenGL  
		PFD_DOUBLEBUFFER,      // double buffered  
		PFD_TYPE_RGBA,         // RGBA type  
		24,                    // 24-bit color depth  
		0, 0, 0, 0, 0, 0,      // color bits ignored  
		0,                     // no alpha buffer  
		0,                     // shift bit ignored  
		0,                     // no accumulation buffer  
		0, 0, 0, 0,            // accum bits ignored  
		32,                    // 32-bit z-buffer  
		0,                     // no stencil buffer  
		0,                     // no auxiliary buffer  
		PFD_MAIN_PLANE,        // main layer  
		0,                     // reserved  
		0, 0, 0                // layer masks ignored  
	};

	int  iPixelFormat;
	static int w, h;

	HDC hdc = GetDC(hWnd);
	static HGLRC hgl;
	PAINTSTRUCT ps;



	static std::vector<Vertex> cube{
		{-0.25, 0.25, -0.25},
		{0.25, 0.25, -0.25},
		{-0.25, -0.25, -0.25},
		{0.25, -0.25, -0.25},
		{-0.25, 0.25, 0.25},
		{0.25, 0.25, 0.25},
		{-0.25, -0.25, 0.25},
		{0.25, -0.25, 0.25},
	};
	static std::vector<Vertex> roof{
		{0.0, 0.25, 0.0},
		{0.0, 0.25, 0.0},
		{-0.25, -0.25, -0.25},
		{0.25, -0.25, -0.25},
		{0.0, 0.25, 0.0},
		{0.0, 0.25, 0.0},
		{-0.25, -0.25, 0.25},
		{0.25, -0.25, 0.25},
	};



	int ibikeCircultaionTheta;
	char c;
	static int x = 1;

	switch (message)
	{
	case WM_CREATE:

		hdc = GetDC(hWnd);
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);
		hgl = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hgl);
		glClearColor(0, 0, 0, 0);

		glEnable(GL_DEPTH_TEST);
		
		SetTimer(hWnd, 0, 10, NULL);
		break;

	case WM_TIMER: // +++++++++++++++++++++++++++++++++++++ RENDER LOOP +++++++++++++++++++++++++++++++++++++

		if (bikeCirculation)
		{
			ibikeCircultaionTheta = (int)bikeCirculationTheta;

			if (ibikeCircultaionTheta % 30 == 0)
				windowtheta = 120.0f;
			else if (ibikeCircultaionTheta % 50 == 0)
				windowtheta = 0.0f;


			wheeltheta += 5.0f;
			bikeCirculationTheta -= 1.0f;
			if (bikeCirculationTheta <= 0.0f)
				bikeCirculationTheta = 360.0f;
		}
		else
		{
			if (bikeCirculationTheta != 360.0f)
			{
				windowtheta = 0.0f;

				wheeltheta += 10.0f;
				bikeCirculationTheta -= 2.0f;
				if (bikeCirculationTheta <= 0.0f)
					bikeCirculationTheta = 360.0f;
			}
		}


		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		ApplySceneTransformations();


		// house
		houseColor[0] = 1.0f; houseColor[1] = 1.0f; houseColor[2] = 1.0f;

		glTranslatef(0.0f, 0.125f, 0.0f);
		DrawBeam(0.0f, 0.0f, 0.0f, 1.0f, 1.5f, 1.2f, cube, houseColor);
		glTranslatef(0.0f, -0.125f, 0.0f);

		houseColor[0] = 1.0f; houseColor[1] = 1.0f; houseColor[2] = 0.0f;

		glTranslatef(0.0f, 0.875f, 0.0f);
		DrawBeam(0.0f, 0.0f, 0.0f, 1.0f, 1.5f, 1.2f, cube, houseColor);
		glTranslatef(0.0f, -0.875f, 0.0f);

		glTranslatef(0.0f, 1.5f, 0.0f);
		DrawBeam(0.0f, 0.0f, 0.0f, 1.5f, 1.5f, 1.5f, roof, brown);
		glTranslatef(0.0f, -1.5f, 0.0f);


		// ++++++++++++++++++++++++++++++++++++ windows ++++++++++++++++++++++++++++++++++++ 

		// black inside right
		glTranslatef(0.245f, 0.9f, 0.2f + 0.035f);
		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, black);
		glTranslatef(-0.245f, -0.9f, -0.2f - 0.035f);

		glTranslatef(0.245f, 0.9f, 0.2f - 0.035f);
		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, black);
		glTranslatef(-0.245f, -0.9f, -0.2f + 0.035f);


		// actual window right
		glTranslatef(0.255f, 0.9f, 0.2f + 0.035f);

		glTranslatef(0.0f, 0.0f, windowRotationAxis);
		glRotatef(-windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -windowRotationAxis);

		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, gray);

		glTranslatef(0.0f, 0.0f, windowRotationAxis);
		glRotatef(windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -windowRotationAxis);

		glTranslatef(-0.255f, -0.9f, -0.2f - 0.035f);


		glTranslatef(0.255f, 0.9f, 0.2f - 0.035f);

		glTranslatef(0.0f, 0.0f, -windowRotationAxis);
		glRotatef(windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, windowRotationAxis);

		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, gray);

		glTranslatef(0.0f, 0.0f, -windowRotationAxis);
		glRotatef(-windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, windowRotationAxis);

		glTranslatef(-0.255f, -0.9f, -0.2f + 0.035f);




		// black inside left
		glTranslatef(0.245f, 0.9f, -0.2f + 0.035f);
		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, black);
		glTranslatef(-0.245f, -0.9f, 0.2f - 0.035f);

		glTranslatef(0.245f, 0.9f, -0.2f - 0.035f);
		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, black);
		glTranslatef(-0.245f, -0.9f, 0.2f + 0.035f);


		// actual window left
		glTranslatef(0.255f, 0.9f, -0.2f + 0.035f);

		glTranslatef(0.0f, 0.0f, windowRotationAxis);
		glRotatef(-windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -windowRotationAxis);

		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, gray);

		glTranslatef(0.0f, 0.0f, windowRotationAxis);
		glRotatef(windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -windowRotationAxis);

		glTranslatef(-0.255f, -0.9f, 0.2f - 0.035f);


		glTranslatef(0.255f, 0.9f, -0.2f - 0.035f);

		glTranslatef(0.0f, 0.0f, -windowRotationAxis);
		glRotatef(windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, windowRotationAxis);

		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, gray);

		glTranslatef(0.0f, 0.0f, -windowRotationAxis);
		glRotatef(-windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, windowRotationAxis);

		glTranslatef(-0.255f, -0.9f, 0.2f + 0.035f);




		// black inside right
		glTranslatef(0.245f, 0.3f, 0.2f + 0.035f);
		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, black);
		glTranslatef(-0.245f, -0.3f, -0.2f - 0.035f);

		glTranslatef(0.245f, 0.3f, 0.2f - 0.035f);
		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, black);
		glTranslatef(-0.245f, -0.3f, -0.2f + 0.035f);


		// actual window right
		glTranslatef(0.255f, 0.3f, 0.2f + 0.035f);

		glTranslatef(0.0f, 0.0f, windowRotationAxis);
		glRotatef(-windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -windowRotationAxis);

		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, gray);

		glTranslatef(0.0f, 0.0f, windowRotationAxis);
		glRotatef(windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -windowRotationAxis);

		glTranslatef(-0.255f, -0.3f, -0.2f - 0.035f);


		glTranslatef(0.255f, 0.3f, 0.2f - 0.035f);

		glTranslatef(0.0f, 0.0f, -windowRotationAxis);
		glRotatef(windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, windowRotationAxis);

		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, gray);

		glTranslatef(0.0f, 0.0f, -windowRotationAxis);
		glRotatef(-windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, windowRotationAxis);

		glTranslatef(-0.255f, -0.3f, -0.2f + 0.035f);





		// black inside left
		glTranslatef(0.245f, 0.3f, -0.2f + 0.035f);
		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, black);
		glTranslatef(-0.245f, -0.3f, 0.2f - 0.035f);

		glTranslatef(0.245f, 0.3f, -0.2f - 0.035f);
		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, black);
		glTranslatef(-0.245f, -0.3f, 0.2f + 0.035f);


		// actual window left
		glTranslatef(0.255f, 0.3f, -0.2f + 0.035f);

		glTranslatef(0.0f, 0.0f, windowRotationAxis);
		glRotatef(-windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -windowRotationAxis);

		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, gray);

		glTranslatef(0.0f, 0.0f, windowRotationAxis);
		glRotatef(windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -windowRotationAxis);

		glTranslatef(-0.255f, -0.3f, 0.2f - 0.035f);


		glTranslatef(0.255f, 0.3f, -0.2f - 0.035f);

		glTranslatef(0.0f, 0.0f, -windowRotationAxis);
		glRotatef(windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, windowRotationAxis);

		DrawBeam(0.0f, 90.0f, 0.0f, 0.15f, 0.5f, 0.025f, cube, gray);

		glTranslatef(0.0f, 0.0f, -windowRotationAxis);
		glRotatef(-windowtheta, YAXIS);
		glTranslatef(0.0f, 0.0f, windowRotationAxis);

		glTranslatef(-0.255f, -0.3f, 0.2f + 0.035f);










		// door


		// black inside left
		glTranslatef(0.248f, 0.1f, 0.0f);
		DrawBeam(0.0f, 0.0f, 0.0f, 0.02f, 1.2f, 0.3f, cube, black);
		glTranslatef(-0.248f, -0.1f, 0.0f);


		// actual window left
		glTranslatef(0.255f, 0.05f, 0.0f);

		glTranslatef(0.0f, 0.0f, 0.08f);
		glRotatef(-doortheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -0.08f);

		DrawBeam(0.0f, 0.0f, 0.0f, 0.02f, 1.4f, 0.35f, cube, brown);

		glTranslatef(0.0f, 0.0f, 0.08);
		glRotatef(doortheta, YAXIS);
		glTranslatef(0.0f, 0.0f, -0.08);

		glTranslatef(-0.255f, -0.05f, 0.0f);


		// ++++++++++++++++++++++++++++++++++++ END windows ++++++++++++++++++++++++++++++++++++ 

		// floor

		glBegin(GL_TRIANGLES);
		glColor3f(0.7f, 0.7f, 0.7f); glVertex3f(2.25, -0.25, 2.25); // top right
		glColor3f(0.7f, 0.7f, 0.7f); glVertex3f(2.25, -0.25, -2.25); // bottom right
		glColor3f(0.7f, 0.7f, 0.7f); glVertex3f(-2.25, -0.25, -2.25); // bottom left

		glColor3f(0.7f, 0.7f, 0.7f); glVertex3f(-2.25, -0.25, 2.25); // top left
		glColor3f(0.7f, 0.7f, 0.7f); glVertex3f(2.25, -0.25, 2.25); // top right
		glColor3f(0.7f, 0.7f, 0.7f); glVertex3f(-2.25, -0.25, -2.25); // bottom left
		glEnd();


		glTranslatef(0.0f, -0.34f, 0.0f);
		glRotatef(90.0f, XAXIS);
		glOrtho(-200, 200, -200, 200, -100, 100);

		BresenhamCircleAlgorithm::Draw({ 0.0f, 0.0f, 0.0f }, 130.0f, 20.0f, gray);



		// BYCYCLE



		// whole scene coordinates
		ApplySceneTransformations();

		// front wheel

		// object specific trnsformations'
		glRotatef(bikeCirculationTheta, YAXIS);
		glTranslatef(bikeCenter.x, bikeCenter.y, bikeCenter.z + 0.1f);
		glRotatef(frontwheeltheta, YAXIS);
		glRotatef(wheeltheta, ZAXIS);
		glScalef(0.1f, 0.1f, 0.1f);

		DrawBeam(0.0f, 0.0f, 0.0f, 3.0f, 0.25f, 0.25f, cube, beamsColor);
		DrawBeam(0.0f, 0.0f, 90, 3.0f, 0.25f, 0.25f, cube, beamsColor);
		DrawBeam(0.0f, 0.0f, 135.0f, 3.0f, 0.25f, 0.25f, cube, beamsColor);
		DrawBeam(0.0f, 0.0f, 225.0f, 3.0f, 0.25f, 0.25f, cube, beamsColor);

		glOrtho(-200, 200, -200, 200, -100, 100);

		BresenhamCircleAlgorithm::Draw({ 0.0f, 0.0f, 0.0f }, 150, 5.0f, bikeColor);




		// whole scene coordinates
		ApplySceneTransformations();

		// back wheel

		// object specific trnsformations
		glRotatef(bikeCirculationTheta, YAXIS);
		glTranslatef(bikeCenter.x, bikeCenter.y, bikeCenter.z - 0.1f);
		glRotatef(90.0f, YAXIS);
		glRotatef(wheeltheta, ZAXIS);
		glScalef(0.1f, 0.1f, 0.1f);

		DrawBeam(0.0f, 0.0f, 0.0f, 3.0f, 0.25f, 0.25f, cube, beamsColor);
		DrawBeam(0.0f, 0.0f, 90, 3.0f, 0.25f, 0.25f, cube, beamsColor);
		DrawBeam(0.0f, 0.0f, 135.0f, 3.0f, 0.25f, 0.25f, cube, beamsColor);
		DrawBeam(0.0f, 0.0f, 225.0f, 3.0f, 0.25f, 0.25f, cube, beamsColor);


		glOrtho(-200, 200, -200, 200, -100, 100);

		BresenhamCircleAlgorithm::Draw({ 0.0f, 0.0f, 0.0f }, 150, 5.0f, bikeColor);



		// whole scene coordinates
		ApplySceneTransformations();

		// bike body

		// object specific trnsformations
		glRotatef(bikeCirculationTheta, YAXIS);
		glTranslatef(bikeCenter.x, bikeCenter.y + 0.08, bikeCenter.z);
		// 1
		glRotatef(90.0f, YAXIS);
		glScalef(0.1f, 0.1f, 0.1f);

		// main body
		DrawBeam(0.0f, 0.0f, 0.0f, 7.0f, 0.5f, 0.25f, cube, bikeColor);
		// revert 1
		glScalef(10.f, 10.f, 10.f);
		glRotatef(-90.0f, YAXIS);

		// seat
		glTranslatef(0.0f, 0.05f, -0.08f);
		glRotatef(90.0f, YAXIS);
		glScalef(0.1f, 0.1f, 0.1f);
		DrawBeam(0.0f, 0.0f, 90.0f, 2.0f, 0.5f, 1.0f, cube, bikeColor);

		// revert 1
		glScalef(10.f, 10.f, 10.f);
		glRotatef(-90.0f, YAXIS);

		// handle
		glTranslatef(0.0f, 0.0f, 0.18f);
		glRotatef(frontwheeltheta, YAXIS);

		glScalef(0.1f, 0.1f, 0.1f);
		DrawBeam(0.0f, 0.0f, 90.0f, 2.0f, 0.25f, 0.25f, cube, bikeColor);
		glScalef(10.0f, 10.0f, 10.0f);

		glTranslatef(0.0f, 0.05f, 0.0f);
		glScalef(0.1f, 0.1f, 0.1f);
		DrawBeam(0.0f, 90.0f, 0.0f, 2.0f, 0.25f, 0.25f, cube, bikeColor);
		glScalef(10.0f, 10.0f, 10.0f);


		glLoadIdentity();


		glFlush();
		SwapBuffers(hdc);

		break; // +++++++++++++++++++++++++++++++++++++ END RENDER LOOP +++++++++++++++++++++++++++++++++++++

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		//s.Draw(hdc);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		w = LOWORD(lParam);
		h = HIWORD(lParam);
		glViewport(0, 0, w, h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;

	case WM_KEYDOWN: // +++++++++++++++++++++++++++++++++++++ PROCESS INPUT +++++++++++++++++++++++++++++++++++++
		if (GetAsyncKeyState(VK_RIGHT) & 0x01)
		{
			ytheta += 1.0f;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x01)
		{
			ytheta -= 1.0f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x01)
		{
			xtheta -= 1.0f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x01)
		{
			xtheta += 1.0f;
		}
		if (GetAsyncKeyState(0x58) & 0x01) // X key
		{
			bikeCenter.x += 0.01f;
		}
		if (GetAsyncKeyState(0x5A) & 0x01) // Z key
		{
			bikeCenter.x -= 0.01f;
		}
		if (GetAsyncKeyState(0x57) & 0x01) // W key
		{
			ypos -= 0.01f;
		}
		if (GetAsyncKeyState(0x53) & 0x01) // S key
		{
			ypos += 0.01f;
		}
		if (GetAsyncKeyState(0x41) & 0x01) // A key
		{
			xpos += 0.01f;
		}
		if (GetAsyncKeyState(0x44) & 0x01) // D key
		{
			xpos -= 0.01f;
		}
		if (GetAsyncKeyState(0x46) & 0x01) // F key
		{
			if (!bikeCirculation)
			{
				bikeCenter.z += 0.01f;
				wheeltheta += 5.0f;
			}

		}
		if (GetAsyncKeyState(0x42) & 0x01) // B key
		{
			if (!bikeCirculation)
			{
				bikeCenter.z -= 0.01f;
				wheeltheta -= 5.0f;
			}
		}
		if (GetAsyncKeyState(0x52) & 0x01) // R key
		{
			if (!bikeCirculation)
				frontwheeltheta += 30.0f;
		}
		if (GetAsyncKeyState(0x4C) & 0x01) // L key
		{
			if (!bikeCirculation)
				frontwheeltheta -= 30.0f;
		}

		break; // +++++++++++++++++++++++++++++++++++++ END PROCESS INPUT +++++++++++++++++++++++++++++++++++++

	case WM_RBUTTONDOWN:
		if (bikeCirculation)
		{
			bikeCirculation = false;
			frontwheeltheta += 30.0f;

			StopSong1();
		}
		break;
	case WM_LBUTTONDOWN:
		if (!bikeCirculation)
		{
			bikeCirculation = true;
			bikeCenter.z = 0.0f;
			frontwheeltheta -= 30.0f;
			PlaySong1();
		}
		break;
	case WM_CHAR:
		c = wParam;
		if (c == 'O')
		{
			windowtheta = 120.0f;
		}
		if (c == 'C')
		{
			windowtheta = 0.0f;
		}
		if (c == 'o')
		{
			doortheta = 80.0f;
		}
		if (c == 'c')
		{
			doortheta = 0.0f;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hgl);
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
