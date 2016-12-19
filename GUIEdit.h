#pragma once
#include "GUICommon.h"

#ifndef GUIEDIT_H
#define GUIEDIT_H

struct AddEditButtons {
	HWND ParentHWND, GUIHandle;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText;

	AddEditButtons() {
		gLabelID = CustomSeed;
		CustomSeed++;
	}

	void SetHandle(HWND _hWnd) { ParentHWND = _hWnd; }

	void SetDefaultText(LPCWSTR _DefaultText = L"") { DefaultText = _DefaultText; }

	void DrawGUI(int _OriginX, int _OriginY, int _Width, int _Height) {
		DestroyWindow(GUIHandle);

		OriginX = _OriginX;
		OriginY = _OriginY;
		Width = _Width;
		Height = _Height;

		GUIHandle = CreateWindowEx(WS_EX_CLIENTEDGE,
			L"EDIT",
			DefaultText,
			WS_CHILD | WS_VISIBLE |
			ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			OriginX, OriginY, Width, Height,
			ParentHWND,
			(HMENU)gLabelID,
			GetModuleHandle(NULL),
			NULL);
	}

	void CreateGUI(HWND _hWnd, int _OriginX, int _OriginY, int _Width, int _Height, LPCWSTR _DefaultText = L" ") {
		SetHandle(_hWnd);
		SetDefaultText(_DefaultText);
		DrawGUI(_OriginX, _OriginY, _Width, _Height);
	}

	void SetText(wchar_t* stringVar) {
		SendMessage(GUIHandle, WM_SETTEXT, (WPARAM)0, (LPARAM)stringVar);
	}

	void GetText(wchar_t* stringVar, int _length) {
		SendMessage(GUIHandle, WM_GETTEXT, (WPARAM)_length, (LPARAM)stringVar);
	}

	void AppendText(wchar_t* stringVar) {
		SendMessage(GUIHandle, EM_REPLACESEL, (WPARAM)0, (LPARAM)stringVar);
	}

	int GetInt() {
		return GetDlgItemInt(ParentHWND, gLabelID, NULL, 0);
	}

	void SetInt(int _IntNum) {
		SetDlgItemInt(ParentHWND, gLabelID, (WPARAM)_IntNum, false);
	}

	void SetReadOnly(bool _state = false) { //Set to read only
		SendMessage(GUIHandle, EM_SETREADONLY, (WPARAM)_state, (LPARAM)NULL);
	}
};

#endif