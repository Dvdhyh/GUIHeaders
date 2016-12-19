#ifndef GUIBUTTONCHECK_H
#define GUIBUTTONCHECK_H

struct AddCheckBox {
	HWND ParentHWND, GUIHandle;
	int OriginX, OriginY, Width, Height, gLabelID;
	LPCWSTR DefaultText;

	AddCheckBox() {
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
			BS_AUTOCHECKBOX,
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

	bool GetState() {
		return SendMessage(GUIHandle, BM_GETCHECK, 0, 0) == BST_CHECKED ? true : false;
	}

	void SetState(bool On) {
		if (On)
			SendMessage(GUIHandle, BM_SETCHECK, BST_CHECKED, 0);
		else
			SendMessage(GUIHandle, BM_SETCHECK, BST_UNCHECKED, 0);
	}

};



#endif