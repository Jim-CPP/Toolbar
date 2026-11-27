cls

del *.exe

g++ -mwindows -m64 -static -Wall -Wextra Toolbar.cpp ComboBoxWindow.cpp -o Toolbar.exe
