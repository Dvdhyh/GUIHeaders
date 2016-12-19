#pragma once
#include "GUICommon.h"

#ifndef GUISCROLLBAR_H
#define GUISCROLLBAR_H

static int  cxChar=1, cxCaps=1, cyChar=1, cxClient, cyClient, iMaxWidth;

struct AddScrollBar {
	HDC         hdc;
	int         i, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd, NUMLINES;

	SCROLLINFO  si;
	TCHAR       szBuffer[10];
	TEXTMETRIC  tm;
	HWND ParentHWND;

	AddScrollBar(HWND _hWnd, int nums) {
		ParentHWND = _hWnd;
		NUMLINES = nums;
	}

	void CreateGUI() {
		hdc = GetDC(ParentHWND);

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(ParentHWND, hdc);

		// Save the width of the three columns

		iMaxWidth = 40 * cxChar + 22 * cxCaps;
	}

	void setRowRange(int nums, int _width, int _height) {
		NUMLINES = nums;
		//onResize(_width, _height);
		SendMessage(ParentHWND, SBM_SETRANGE, (WPARAM)0, (LPARAM)nums);
	}

	void setColumnRange(int nums, int _width, int _height) {
		iMaxWidth = nums + 22 * cxCaps;
		//onResize(_width, _height);
	}

	void onResize(int _width, int _height) {
		// Set vertical scroll bar range and page size

		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = NUMLINES - 1;
		si.nPage = _height / cyChar;
		SetScrollInfo(ParentHWND, SB_VERT, &si, TRUE);

		// Set horizontal scroll bar range and page size

		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 2 + iMaxWidth / cxChar;
		si.nPage = _width / cxChar;
		SetScrollInfo(ParentHWND, SB_HORZ, &si, TRUE);
	}

	void onWheel(int wheel) {
		if (wheel > 0) {
			onVScroll(SB_LINEUP);
		}
		else {
			onVScroll(SB_LINEDOWN);
		}

	}

	void onVScroll(int _input) {
		// Get all the vertical scroll bar information

		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		GetScrollInfo(ParentHWND, SB_VERT, &si);

		// Save the position for comparison later on

		iVertPos = si.nPos;

		switch (_input)
		{
		case SB_TOP:
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;

		case SB_LINEUP:
			si.nPos -= 1;
			break;

		case SB_LINEDOWN:
			si.nPos += 1;
			break;

		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;

		case SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;

		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}
		// Set the position and then retrieve it.  Due to adjustments
		//   by Windows it may not be the same as the value set.

		si.fMask = SIF_POS;
		SetScrollInfo(ParentHWND, SB_VERT, &si, TRUE);
		GetScrollInfo(ParentHWND, SB_VERT, &si);

		// If the position has changed, scroll the window and update it

		if (si.nPos != iVertPos)
		{
			ScrollWindow(ParentHWND, 0, cyChar * (iVertPos - si.nPos), NULL, NULL);
			UpdateWindow(ParentHWND);
		}
	}

	void onHScroll(int _input) {
		// Get all the vertical scroll bar information

		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;

		// Save the position for comparison later on

		GetScrollInfo(ParentHWND, SB_HORZ, &si);
		iHorzPos = si.nPos;

		switch (_input)
		{
		case SB_LINELEFT:
			si.nPos -= 1;
			break;

		case SB_LINERIGHT:
			si.nPos += 1;
			break;

		case SB_PAGELEFT:
			si.nPos -= si.nPage;
			break;

		case SB_PAGERIGHT:
			si.nPos += si.nPage;
			break;

		case SB_THUMBPOSITION:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}

		// Set the position and then retrieve it.  Due to adjustments
		//   by Windows it may not be the same as the value set.

		si.fMask = SIF_POS;
		SetScrollInfo(ParentHWND, SB_HORZ, &si, TRUE);
		GetScrollInfo(ParentHWND, SB_HORZ, &si);

		// If the position has changed, scroll the window 

		if (si.nPos != iHorzPos)
		{
			ScrollWindow(ParentHWND, cxChar * (iHorzPos - si.nPos), 0, NULL, NULL);
		}
	}

	void onPaint(HDC _hdc, PAINTSTRUCT _ps) {
		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		GetScrollInfo(ParentHWND, SB_VERT, &si);
		iVertPos = si.nPos;

		// Get horizontal scroll bar position
		GetScrollInfo(ParentHWND, SB_HORZ, &si);
		iHorzPos = si.nPos;

		// Find painting limits

		iPaintBeg = max(0, iVertPos + _ps.rcPaint.top / cyChar);
		iPaintEnd = min(NUMLINES - 10, iVertPos + _ps.rcPaint.bottom / cyChar);

		WCHAR textPrint[15] = { L"\0" };

		wsprintf(textPrint, L"Hello", 15);
		TextOut(_hdc, 0, cyChar * (10 - iVertPos), textPrint, 15);

		wsprintf(textPrint, L"Hello world", 15);
		TextOut(_hdc, cxChar * (10 - iHorzPos), cyChar * (11 - iVertPos), textPrint, 15);

	}
};
#endif
