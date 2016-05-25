#pragma once
#include "GUICommon.h"

#ifndef GUILISTBOX_H
#define GUILISTBOX_H

struct AddListBox {
	HWND ParentHWND, GUIHandle, HBuddy;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText = L" ";

	AddListBox() {
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

		GUIHandle = CreateWindowEx(WS_EX_CLIENTEDGE,
			WC_LISTBOX,
			DefaultText,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD |
			WS_VSCROLL | ES_AUTOVSCROLL,
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


	void AddString(wchar_t* _INSERTTEXT) {
		SendMessage(GUIHandle, LB_ADDSTRING, (WPARAM)0, (LPARAM)_INSERTTEXT);
	}

	//if index is -1 inserts at the end
	void InsertAt(wchar_t* _INSERTTEXT, int _index = -1) {
		SendMessage(GUIHandle, LB_INSERTSTRING, (WPARAM)_index, (LPARAM)_INSERTTEXT);
	}

	void DeleteAt(int _index) {
		SendMessage(GUIHandle, LB_DELETESTRING, (WPARAM)_index, (LPARAM)0);
	}

	void Clear() {
		SendMessage(GUIHandle, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
	}

	//Get the number of items in the LB
	int GetCount() {
		return SendMessage(GUIHandle, LB_GETCOUNT, (WPARAM)0, (LPARAM)0);
	}

	//Get the index of the item currently selected
	int GetCurrentIndex() {
		return SendMessage(GUIHandle, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	}

	void GetCurrentItem(wchar_t* _INSERTTEXT) {
		SendMessage(GUIHandle, LB_GETTEXT, (WPARAM)GetCurrentIndex(), (LPARAM)_INSERTTEXT);
	}
};


#endif