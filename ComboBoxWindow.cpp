// ComboBoxWindow.cpp

#include "ComboBoxWindow.h"

// Global variables
HWND g_hWndComboBox;

int ComboBoxWindowAddText( LPCTSTR lpszText )
{
	// Add text to combo box window
	return SendMessage( g_hWndComboBox, CB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszText );

} // End of function ComboBoxWindowAddText

BOOL ComboBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont )
{
	BOOL bResult = FALSE;

	// Create combo box window
	g_hWndComboBox = CreateWindowEx( COMBO_BOX_WINDOW_EXTENDED_STYLE, COMBO_BOX_WINDOW_CLASS_NAME, COMBO_BOX_WINDOW_TEXT, COMBO_BOX_WINDOW_STYLE, COMBO_BOX_WINDOW_LEFT, COMBO_BOX_WINDOW_TOP, COMBO_BOX_WINDOW_WIDTH, COMBO_BOX_WINDOW_HEIGHT, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that combo box window was created
	if( g_hWndComboBox )
	{
		// Successfully created combo box window
		RECT rcParent;
		RECT rcComboBox;
		int nWindowWidth;
		int nWindowHeight;

		// Get parent window size
		GetWindowRect( hWndParent, &rcParent );

		// Get combo box window size
		GetClientRect( g_hWndComboBox, &rcComboBox );

		// The combo box was created to be the same size as the window to allow for maximum size when it is open
		// Now we need to set the combo box width to fit the parent window
		// The combo box height is automatic, so we need to resize the window to fit this

		// Update window width and height
		nWindowWidth	= ( rcParent.right - rcParent.left );
		nWindowHeight	= ( rcComboBox.bottom - rcComboBox.top );

		// Move windows
		MoveWindow( hWndParent, rcParent.left, rcParent.top, nWindowWidth, nWindowHeight, TRUE );
		MoveWindow( g_hWndComboBox, rcComboBox.left, rcComboBox.top, nWindowWidth, nWindowHeight, TRUE );

		// Set combo box window font
		SendMessage( g_hWndComboBox, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

		// Update return value
		bResult = TRUE;

	} // End of successfully created combo box window

	return bResult;

} // End of function ComboBoxWindowCreate
