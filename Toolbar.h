// Toolbar.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#include "ComboBoxWindow.h"

#define MAIN_WINDOW_CLASS_NAME													"Main Toolbar Window Class"

#define MAIN_WINDOW_CLASS_STYLE													0
#define MAIN_WINDOW_CLASS_ICON_NAME												IDI_APPLICATION
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_MENU_NAME												NULL
#define MAIN_WINDOW_CLASS_ICON_SMALL											LoadIcon( NULL, MAIN_WINDOW_CLASS_ICON_NAME )

#define MAIN_WINDOW_EXTENDED_STYLE												( WS_EX_TOPMOST | WS_EX_TOOLWINDOW )
#define MAIN_WINDOW_TEXT														"Toolbar"
#define MAIN_WINDOW_STYLE														WS_POPUP

#define MAIN_WINDOW_WIDTH														300
#define MAIN_WINDOW_HEIGHT														32
#define MAIN_WINDOW_RIGHT_BORDER												200
#define MAIN_WINDOW_LEFT														( PRIMARY_SCREEN_WIDTH - ( MAIN_WINDOW_WIDTH + MAIN_WINDOW_RIGHT_BORDER ) )
#define MAIN_WINDOW_TOP															0

#define SHORTCUTS_FILE_NAME														"Shortcuts.txt"

#define ABOUT_MESSAGE_TEXT														"Toolbar\r\n"						\
																				"\r\n"								\
																				"Written by Jim Smith\r\n"			\
																				"\r\n"								\
																				"November 2026"
