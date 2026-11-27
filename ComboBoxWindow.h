// ComboBoxWindow.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#define COMBO_BOX_WINDOW_CLASS_NAME												WC_COMBOBOX

#define COMBO_BOX_WINDOW_EXTENDED_STYLE											WS_EX_STATICEDGE
#define COMBO_BOX_WINDOW_TEXT													NULL
#define COMBO_BOX_WINDOW_STYLE													( CBS_DROPDOWN | WS_CHILD | WS_VISIBLE )

#define COMBO_BOX_WINDOW_LEFT													0
#define COMBO_BOX_WINDOW_TOP													0
#define COMBO_BOX_WINDOW_WIDTH													PRIMARY_SCREEN_WIDTH
#define COMBO_BOX_WINDOW_HEIGHT													PRIMARY_SCREEN_HEIGHT

#define COMBO_BOX_WINDOW_ABOUT_MENU_ITEM_TEXT									"[About]"

int ComboBoxWindowAddText( LPCTSTR lpszText );

BOOL ComboBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

LRESULT ComboBoxWindowHandleCommandMessage( HWND hWndParent, WPARAM wParam, LPARAM lParam, int( *lpAboutFunction )( HWND hWndParent ) );

BOOL IsComboBoxWindow( HWND hWndSupplied );
