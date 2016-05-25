#ifndef GUITOOLTIPS_H
#define GUITOOLTIPS_H

struct AddToolTip {
	HWND ParentHWND, GUIHandle;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPWSTR DefaultText;
	TOOLINFO toolInfo;

	AddToolTip() {}

	void SetHandle(HWND _hWnd) { ParentHWND = _hWnd; }

	void SetText(LPWSTR _DefaultText = L" ") { DefaultText = _DefaultText; }

	void DrawGUI(int _OriginX, int _OriginY, int _Width, int _Height) {
		DestroyWindow(GUIHandle);

		GUIHandle = CreateWindowEx(0,
			TOOLTIPS_CLASS,
			NULL,
			WS_POPUP | TTS_ALWAYSTIP | TTS_ALWAYSTIP,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			ParentHWND,
			NULL,
			GetModuleHandle(NULL),
			NULL);
	}

	void SetTarget(HWND _targetHandle, LPWSTR _DefaultText) {
		// Associate the tooltip with the tool.
		toolInfo = { 0 };
		toolInfo.cbSize = TTTOOLINFOA_V1_SIZE;
		toolInfo.hwnd = ParentHWND;
		toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
		toolInfo.uId = (UINT_PTR)_targetHandle;
		toolInfo.lpszText = _DefaultText;

		SendMessage(GUIHandle, TTM_ACTIVATE, TRUE, 0); //Will add the Tool Tip on Control
		SendMessage(GUIHandle, TTM_ADDTOOL, 0, (LPARAM)&toolInfo); //Will add the Tool Tip on Control
	}

	void CreateGUI(HWND _hWnd, HWND _targetHandle, int _OriginX, int _OriginY, int _Width, int _Height, LPWSTR _DefaultText = L" ") {
		SetHandle(_hWnd);
		SetText(_DefaultText);
		DrawGUI(_OriginX, _OriginY, _Width, _Height);
		SetTarget(_targetHandle, _DefaultText);
	}

	void DeleteToolTip() {
		SendMessage(GUIHandle, TTM_DELTOOL, 0, (LPARAM)&toolInfo);
	}

	void SetBackgroundColor(COLORREF _color) {
		SendMessage(GUIHandle, TTM_SETTIPBKCOLOR, (WPARAM)_color, 0);
	}

	void SetTextColor(COLORREF _color) {
		SendMessage(GUIHandle, TTM_SETTIPTEXTCOLOR, (WPARAM)_color, 0);
	}
};


#endif