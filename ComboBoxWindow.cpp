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

LRESULT ComboBoxWindowHandleCommandMessage( HWND hWndParent, WPARAM wParam, LPARAM lParam, int( *lpAboutFunction )( HWND hWndParent ) )
{
	LRESULT lResult = 0;

	// Select command
	switch( HIWORD( wParam ) )
	{
		case CBN_SELCHANGE:
		{
			// A combo box window selection change notification
			int nSelectedItem;

			// Get selected item
			nSelectedItem = SendMessage( g_hWndComboBox, CB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

			// Ensure that selected item was got
			if( nSelectedItem != CB_ERR )
			{
				// Successfully got selected item

				// Allocate string memory
				LPTSTR lpszItemText = new char[ STRING_LENGTH + sizeof( char ) ];

				// Get selected item text
				if( SendMessage( g_hWndComboBox, CB_GETLBTEXT, ( WPARAM )nSelectedItem, ( LPARAM )lpszItemText ) != CB_ERR )
				{
					// Successfully got selected item text

					// See if this is the about item
					if( lstrcmp( lpszItemText, COMBO_BOX_WINDOW_ABOUT_MENU_ITEM_TEXT ) == 0 )
					{
						// This is the about item

						// Call the about function
						( *lpAboutFunction )( hWndParent );

					} // End of this is the about item
					else
					{
						// This is not the about item

						// Display selected item text
						MessageBox( hWndParent, lpszItemText, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					} // End of this is not the about item

					// Clear selection
					SendMessage( g_hWndComboBox, CB_SETCURSEL, ( WPARAM )-1, ( LPARAM )NULL );

				} // End of successfully got selected item text

				// Free string memory
				delete [] lpszItemText;

			} // End of successfully got selected item

			// Break out of switch
			break;

		} // End of a combo box window selection change notification
		default:
		{
			// Default command

			// Call default window procedure
			lResult = DefWindowProc( hWndParent, WM_COMMAND, wParam, lParam );

			// Break out of switch
			break;

		} // End of default command

	}; // End of selection for command

	return lResult;

} // End of function ComboBoxWindowHandleCommandMessage

BOOL ComboBoxWindowLoad( LPCTSTR lpszFileName, BOOL bAddAboutItem )
{
	BOOL bResult = FALSE;

	HANDLE hFile;

	// Open file
	hFile = CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	// Ensure that file was opened
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened file
		DWORD dwFileSize;

		// Get file size
		dwFileSize = GetFileSize( hFile, NULL );

		// Ensure that file size was got
		if( dwFileSize != INVALID_FILE_SIZE )
		{
			// Successfully got file size

			// Allocate string memory
			LPTSTR lpszFileText = new char[ dwFileSize + sizeof( char ) ];

			// Read file text
			if(ReadFile( hFile, lpszFileText, dwFileSize, NULL, NULL ) )
			{
				// Successfully read file text
				LPTSTR lpszItem;

				// Terminate file text
				lpszFileText[ dwFileSize ] = ( char )NULL;

				// Clear combo box window
				SendMessage( g_hWndComboBox, CB_RESETCONTENT, ( WPARAM )NULL, ( LPARAM )NULL );

				// See if about item needs to be added to combo box window
				if( bAddAboutItem )
				{
					// About item needs to be added to combo box window

					// Add about item to combo box window
					SendMessage( g_hWndComboBox, CB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )COMBO_BOX_WINDOW_ABOUT_MENU_ITEM_TEXT );

				} // End of about item needs to be added to combo box window

				// Update return value (assume success)
				bResult = TRUE;

				// Get first item from file text
				lpszItem = strtok( lpszFileText, NEW_LINE_TEXT );

				// Loop through all items in file text
				while( lpszItem )
				{
					// Add current item to combo box window
					if( SendMessage( g_hWndComboBox, CB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszItem ) != CB_ERR )
					{
						// Successfully added current item to combo box window

						// Get next item from file text
						lpszItem = strtok( NULL, NEW_LINE_TEXT );

					} // End of successfully added current item to combo box window
					else
					{
						// Unable to add current item to combo box window

						// Update return value
						bResult = FALSE;

						// Force exit from loop
						lpszItem = NULL;

					} // End of unable to add current item to combo box window

				}; // End of loop through all items in file text


				// Update return value
				bResult = TRUE;

			} // End of successfully read file text
			// Free string memory
			delete [] lpszFileText;

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return bResult;

} // End of function ComboBoxWindowLoad

BOOL IsComboBoxWindow( HWND hWndSupplied )
{
	BOOL bResult = FALSE;

	// See if supplied window is combo box window
	if( hWndSupplied == g_hWndComboBox )
	{
		// Supplied window is combo box window

		// Update return value
		bResult = TRUE;

	} // End of supplied window is combo box window

	return bResult;

} // End of function IsComboBoxWindow
