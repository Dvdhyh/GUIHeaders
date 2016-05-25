#pragma once
#include "GUICommon.h"

#ifndef GUISTATUSBAR_H
#define GUISTATUSBAR_H

struct AddStatusBar {
	HWND ParentHWND, GUIHandle;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText;

	AddStatusBar() {
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
			STATUSCLASSNAME,
			DefaultText,
			WS_VISIBLE | WS_CHILD,
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

	void SetNumberOfColumns(int cParts) {
		HLOCAL hloc;
		PINT paParts;
		RECT rcClient;
		GetClientRect(ParentHWND, &rcClient);

		// Allocate an array for holding the right edge coordinates.
		hloc = LocalAlloc(LHND, sizeof(int) * cParts);
		paParts = (PINT)LocalLock(hloc);

		// Calculate the right edge coordinate for each part, and
		// copy the coordinates to the array.
		int nWidth = rcClient.right / cParts;
		int rightEdge = nWidth;
		for (int i = 0; i < cParts; i++) {
			paParts[i] = rightEdge;
			rightEdge += nWidth;
		}

		// Tell the status bar to create the window parts.
		SendMessage(GUIHandle, SB_SETPARTS, (WPARAM)cParts, (LPARAM)paParts);

		// Free the array, and return.
		LocalUnlock(hloc);
		LocalFree(hloc);
	}


	void SetText(int _col, LPCWSTR _text) {
		SendMessage(GUIHandle, SB_SETTEXT, (WPARAM)_col, (LPARAM)_text);
	}

	void GetText(int _col, WCHAR* _text) {
		SendMessage(GUIHandle, SB_GETTEXT, (WPARAM)_col, (LPARAM)_text);
	}

	void SetBackgroundColor(COLORREF _color) {
		SendMessage(GUIHandle, SB_SETBKCOLOR, 0, (LPARAM)_color);
	}

};


#endif