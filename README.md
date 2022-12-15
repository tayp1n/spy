# spy

The **Spy** program is written in C++ in Visual Studio using the Windows API. It listens for events from menus, child windows, mouse and keyboard, and displays information about the messages being monitored. The message itself *(WM_COMMAND type)* is displayed, as well as the values of the first *(wParam)* and second *(lPara)* parameters.

The program window consists of several areas. Below is the Edit control, which displays information about the message. Top center is another Edit control where the user can type. And the unoccupied area belongs to the main window.
At the very beginning, the program creates a map of monitored messages. For this, *std::unordered_map<UINT, string>* is used. It maps the message number to the line with that message *(like WM_COMMAND -> “WM_COMMAND”)*. There about 20 events are tracked *(see the MainWindow::MainWindow constructor)*. There is a window procedure - *MainWindow::WndProc* - in which all messages are processed. So, before processing the message, the program checks if the message is in the map, then display information about it in the lower Edit control.

**There are several files in the project:**
*Main.cpp* is the entry point to the program. An instance of the MainWindow class is created there.
*MainWindow.h* and *MainWindow.cpp* - here all the main functionality of the program is concentrated.
**Menu** and related functions:
Menu processing occurs through the *WM_COMMAND* message in the *OnCommand* function.
1. **File**:
-Capture Events - turns on or off the display of messages (you can also press and hold Alt, and then alternately press F and C).
-Exit – exit the program.

2. **Help**:
-About - about the program
![Безымянный](https://user-images.githubusercontent.com/100195623/207938344-6c92deb2-396f-4181-8e96-8193dee84381.png)

if you have any questions don't hesitate to <a href="mailto:holy.mail.100@gmail.com">contact me</a>. Looking forward to hearing from you. 

## My account LinkedIn
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/nazar-arshinskiy/)

If you want to distribute a closed-source modification or service based on software_release_install_tools, then please consider <a href="mailto:holy.mail.100@gmail.com">purchasing an exception</a> . As with the methods above, this will help support continued development.