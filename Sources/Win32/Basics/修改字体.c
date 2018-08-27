HFONT hfont = CreateFont(16, 0, 0, 0, 0, FALSE, FALSE, FALSE, 1, 0, 0, 0, 0, "Consolas");
SendMessage(hwnd,WM_SETFONT,(WPARAM)hfont,(LPARAM)0);