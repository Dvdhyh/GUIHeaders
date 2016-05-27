#pragma once
#include "GUICommon.h"

#ifndef GUICOMBOBOX_H
#define GUICOMBOBOX_H

struct AddComboBox {
	HWND ParentHWND, GUIHandle;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText = L" ";

	AddComboBox() {
		gLabelID = CustomSeed;
		CustomSeed++;
	}

	void SetHandle(HWND _hWnd) { ParentHWND = _hWnd; }

	void SetText(LPCWSTR _DefaultText) { DefaultText = _DefaultText; }

	void DrawGUI(int _OriginX, int _OriginY, int _Width, int _Height) {
		DestroyWindow(GUIHandle);

		OriginX = _OriginX;
		OriginY = _OriginY;
		Width = _Width;
		Height = _Height;

		GUIHandle = CreateWindowEx(NULL,
			L"COMBOBOX",
			DefaultText,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | WS_OVERLAPPED |
			CBS_HASSTRINGS | 
			CBS_DROPDOWN,
			OriginX, OriginY, Width, Height, //Height here refers to the size of drop down list
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


	void SetIndex(int _index) {
		SendMessage(GUIHandle, CB_SETCURSEL, (WPARAM)_index, (LPARAM)0);
	}

	int GetCurrentIndex() {
		return SendMessage(GUIHandle, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	}

	void AddString(wchar_t* _INSERTTEXT) {
		SendMessage(GUIHandle, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)_INSERTTEXT);
	}

	void InsertString(wchar_t* _INSERTTEXT, int _index = 0) {
		SendMessage(GUIHandle, (UINT)CB_INSERTSTRING, (WPARAM)_index, (LPARAM)_INSERTTEXT);
	}

	void EditString(wchar_t* _INSERTTEXT, int _index = 0) {
		DeleteAt(_index);
		InsertString(_INSERTTEXT, _index);
	}

	void GetTextAt(WCHAR* _INSERTVAR, int _index = 0) {
		SendMessage(GUIHandle, CB_GETLBTEXT, _index, (LPARAM)_INSERTVAR);
	}

	void DeleteAt(int _index) {
		SendMessage(GUIHandle, CB_DELETESTRING, _index, 0);
	}

	//Select the index to begin searching. Not case sensitive
	void SearchString(WCHAR* _INSERTVAR, int _index = 0) {
		SendMessage(GUIHandle, CB_SELECTSTRING, _index, (LPARAM)_INSERTVAR);
	}

	void Clear() {
		SendMessage(GUIHandle, CB_RESETCONTENT, 0, 0);
	}
};


#endif