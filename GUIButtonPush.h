#pragma once
#include "GUICommon.h"

#ifndef GUIBUTTONPUSH_H
#define GUIBUTTONPUSH_H

struct AddPushButtons {
	HWND ParentHWND, GUIHandle;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText;

	AddPushButtons() {
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
			WS_TABSTOP | WS_VISIBLE | WS_CHILD |
			BS_DEFPUSHBUTTON,
			OriginX, OriginY, Width, Height,
			ParentHWND,
			(HMENU)gLabelID,
			GetModuleHandle(NULL),
			NULL);
	}

	void CreateGUI(HWND _hWnd, int _OriginX, int _OriginY, int _Width, int _Height, LPCWSTR _DefaultText = L" ") {
		SetHandle(_hWnd);
		SetText(_DefaultText);
		DrawGUI(_OriginX, _OriginY, _Width, _Height);
	}
};

#endif