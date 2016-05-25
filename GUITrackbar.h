#pragma once
#include "GUICommon.h"

#ifndef COMMCTRL_H
#define COMMCTRL_H
#include "CommCtrl.h"

#endif // !COMMCTRL_H


#ifndef GUITRACKBAR_H
#define GUITRACKBAR_H

struct AddTrackBar {
	HWND ParentHWND, GUIHandle, HBuddy;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText;

	AddTrackBar() {
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
			TRACKBAR_CLASS,
			DefaultText,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD |
			TBS_AUTOTICKS | TBS_ENABLESELRANGE,
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

	void MarkIntervals(int _index) {
		SendMessage(GUIHandle, TBM_SETTICFREQ, (WPARAM)_index, (LPARAM)0);
	}

	void SetRange(int _MinValue, int _MaxValue) {
		SendMessage(GUIHandle, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(_MinValue, _MaxValue));
	}

	void SetPos(int _index) {
		SendMessage(GUIHandle, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)_index);
	}

	int GetPos(int _index) {
		SendMessage(GUIHandle, TBM_GETPOS, (WPARAM)0, (LPARAM)0);
	}

	void DisplayText(wchar_t* _INSERTTEXT, int _right, int _OriginX = 0, int _OriginY = 0, int _Width = 50, int _Height = 30) {
		switch (_right) {
		case 0:
			_right = SS_RIGHT;
			break;
		case 1:
			_right = SS_LEFT;
			break;
		}

		HBuddy = CreateWindowEx(0,
			L"STATIC",
			_INSERTTEXT,
			WS_CHILD | WS_VISIBLE |
			_right,     // SS_RIGHT   SS_LEFT  SS_CENTER
			_OriginX, _OriginY, _Width, _Height,
			ParentHWND,
			NULL,
			GetModuleHandle(NULL), NULL);

		SendMessage(GUIHandle, TBM_SETBUDDY, (WPARAM)TRUE, (LPARAM)HBuddy);
	}

};

#endif