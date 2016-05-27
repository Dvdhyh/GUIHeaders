# GUIHeaders
Hold my shortcut to make c++ win32 gui
All of the files in here are just Headers
Using WM_USER to create app unique ID for each GUI

To use just include in a project all you need is to

#include "path/GUI.h"

Example

AddRadioButtons _myfirstButton;
_myfirstButton.CreateGUI(hWnd, x pos, y pos, width, height, L"INSERT TEXT");


// Inside case _WM_COMMAND
int wmId = LOWORD(wParam);
int wmEvent = HIWORD(wParam);
            
if (wmEvent == BN_CLICKED) {
	if (wmId == _myfirstButton.gLabelID) {
		::MessageBox(NULL, __T("Button was pushed"), __T("Title for message box"), NULL);
	}
}
