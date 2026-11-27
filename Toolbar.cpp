// Toolbar.cpp

#include "Toolbar.h"

#include <windows.h>

int ShowAboutMessage( HWND hWndOwner )
{
	int nResult;

	MSGBOXPARAMS msgBoxParams;

	// Clear message box parameter structure
	ZeroMemory( &msgBoxParams, sizeof( msgBoxParams ) );

	// Initialise message box parameter structure
	msgBoxParams.cbSize			= sizeof( MSGBOXPARAMS );
	msgBoxParams.hwndOwner		= hWndOwner;
	msgBoxParams.hInstance		= NULL; // Must be null to use standard system-defined icons
	msgBoxParams.lpszText		= ABOUT_MESSAGE_TEXT;
	msgBoxParams.lpszCaption	= ABOUT_MESSAGE_CAPTION;
	msgBoxParams.dwStyle		= ( MB_OK | MB_USERICON );
	msgBoxParams.lpszIcon		= MAIN_WINDOW_CLASS_ICON_NAME;

	// Show message box
	nResult = MessageBoxIndirect( &msgBoxParams );

	return nResult;

} // End of function ShowAboutMessage

LRESULT CALLBACK MainWindowProcedure( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;
			HFONT hFont;

			// Get instance
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Get font
			hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

			// Create combo box window
			if( ComboBoxWindowCreate( hWndMain, hInstance, hFont ) )
			{
				// Successfully created combo box window
			} // End of successfully created combo box window

			// Break out of switch
			break;

		} // End of a create message
		case WM_CLOSE:
		{
			// A close message

			// Destroy main window
			DestroyWindow( hWndMain );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lResult = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lResult;

} // End of function MainWindowProcedure

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow )
{
	MSG msg;

	HWND hWndRunning;

	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Find any running instances of application
	hWndRunning = FindWindow( MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT );

	// See if any running instances of application were found
	if( hWndRunning )
	{
		// Running instances of application were found

		// Close running instance of application were found
		SendMessage( hWndRunning, WM_CLOSE, ( WPARAM )NULL, ( LPARAM )NULL );

	} // End of running instances of application were found
	else
	{
		// No running instances of application were found
		WNDCLASSEX wcMain;

		// Clear message structure
		ZeroMemory( &msg, sizeof( msg ) );

		// Clear main window class structure
		ZeroMemory( &wcMain, sizeof( wcMain ) );

		// Initialise main window class structure
		wcMain.cbSize			= sizeof( WNDCLASSEX );
		wcMain.lpfnWndProc		= MainWindowProcedure;
		wcMain.hInstance		= hInstance;
		wcMain.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
		wcMain.style			= MAIN_WINDOW_CLASS_STYLE;
		wcMain.hIcon			= MAIN_WINDOW_CLASS_ICON;
		wcMain.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
		wcMain.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
		wcMain.lpszMenuName		= MAIN_WINDOW_CLASS_MENU_NAME;
		wcMain.hIconSm			= MAIN_WINDOW_CLASS_ICON_SMALL;

		// Register main window class
		if( RegisterClassEx( &wcMain ) )
		{
			// Successfully registered main window class
			HWND hWndMain;

			// Create main window
			hWndMain = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT, MAIN_WINDOW_STYLE, MAIN_WINDOW_LEFT, MAIN_WINDOW_TOP, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, NULL, NULL, hInstance, NULL );

			// Ensure that main window was created
			if( hWndMain )
			{
				// Successfully created main window

				// Show main window
				ShowWindow( hWndMain, nCmdShow );

				// Update main window
				UpdateWindow( hWndMain );

				// Add text to combo box window
				ComboBoxWindowAddText( "1234567890" );
				ComboBoxWindowAddText( "qwertyuiop" );
				ComboBoxWindowAddText( "asdfghjkl" );
				ComboBoxWindowAddText( "zxcvbnm" );

				// Message loop
				while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
				{
					// Translate message
					TranslateMessage( &msg );

					// Dispatch message
					DispatchMessage( &msg );

				}; // End of message loop

			} // End of successfully created main window

		} // End of successfully registered main window class

	} // End of no running instances of application were found

	return msg.wParam;

} // End of function WinMain
