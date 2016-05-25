#pragma once
#include "GUICommon.h"

#ifndef GUILISTVIEW_H
#define GUILISTVIEW_H

struct AddListView {
	HWND ParentHWND, GUIHandle, HBuddy;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText = L" ";
	LVCOLUMN lvCol;
	LVITEM lvItem;

	AddListView() {
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
			WC_LISTVIEW,
			DefaultText,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD |
			WS_VSCROLL | ES_AUTOVSCROLL | LVS_REPORT | LVS_EDITLABELS,
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


	//Always declare width unless it the last column you intend to add
	void AddColumn(wchar_t* _INSERTTEXT, int _ColNumber, int _width = LVSCW_AUTOSIZE_USEHEADER, int _textLength = 256) {
		lvCol.pszText = _INSERTTEXT; //Title of the Column
		SendMessage(GUIHandle, LVM_INSERTCOLUMN, (WPARAM)_ColNumber, (LPARAM)&lvCol);
		SendMessage(GUIHandle, LVM_SETCOLUMNWIDTH, (WPARAM)_ColNumber, (LPARAM)_width); //Pixel width

		lvItem.mask = LVIF_TEXT; //Without can't see text
		lvItem.cchTextMax = _textLength;
	}

	//Add to columns.  Can't skip indexes 
	void AddString(wchar_t* _INSERTTEXT, int _ColNumber, int _index) {
		lvItem.iItem = _index;                 //Select index  
		lvItem.iSubItem = _ColNumber;          // Select column
		lvItem.pszText = _INSERTTEXT;
		if (_ColNumber == 0)
			SendMessage(GUIHandle, LVM_INSERTITEM, (WPARAM)0, (LPARAM)&lvItem);
		else
			SendMessage(GUIHandle, LVM_SETITEM, (WPARAM)0, (LPARAM)&lvItem);
	}
};


#endif