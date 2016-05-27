#pragma once
#include "GUICommon.h"

#ifndef GUIBUTTONRADIO_H
#define GUIBUTTONRADIO_H


struct AddRadioButtons {
	HWND ParentHWND, GUIHandle;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText;

	AddRadioButtons() {
		gLabelID = CustomSeed;
		CustomSeed++;
	}

	void SetHandle(HWND _hWnd) { ParentHWND = _hWnd; }

	void SetText(LPCWSTR _DefaultText = L" ") { DefaultText = _DefaultText; }

	void DrawGUI(int _OriginX, int _OriginY, int _Width, int _Height) {
		DestroyWindow(GUIHandle);

		OriginX = _OriginX;
		OriginY = _OriginY;
		Width = _Width;
		Height = _Height;

		GUIHandle = CreateWindowEx(NULL,
			L"BUTTON",
			DefaultText,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_GROUP | //WS_GROUP is making a parent radio button
			BS_AUTORADIOBUTTON,
			OriginX, OriginY, Width, Height,
			ParentHWND,
			(HMENU)gLabelID,
			GetModuleHandle(NULL),
			NULL);
	}

	// Create Parent radio button
	void CreateGUI(HWND _hWnd, int _OriginX, int _OriginY, int _Width, int _Height, LPCWSTR _DefaultText = L" ") {
		SetHandle(_hWnd);
		SetText(_DefaultText);
		DrawGUI(_OriginX, _OriginY, _Width, _Height);
	}

	//Any child created after a parent is linked. To create another group, create another parent and the child will then fall under the new parent
	void CreateChild(HWND _hWnd, int _OriginX, int _OriginY, int _Width, int _Height, LPCWSTR _DefaultText = L" ") {
		SetHandle(_hWnd);
		SetText(_DefaultText);
		DestroyWindow(GUIHandle);

		OriginX = _OriginX;
		OriginY = _OriginY;
		Width = _Width;
		Height = _Height;

		GUIHandle = CreateWindowEx(NULL,
			L"BUTTON",
			DefaultText,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD |
			BS_AUTORADIOBUTTON,
			OriginX, OriginY, Width, Height,
			ParentHWND,
			(HMENU)gLabelID,
			GetModuleHandle(NULL),
			NULL);
	}
};


#endif