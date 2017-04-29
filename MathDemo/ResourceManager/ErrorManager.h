//////////////////////////////////////////////////////////////////////
////	Created by:		Jack McCall
////	Date Created:	31-03-2017
////	Description:	Provides some function(s) that can be
////					utilised for handling errors and/or outputting
////					a log file



#pragma once
#include <iostream>
#include <fstream>
#include <ios>
#include <Windows.h>

class ErrorManager {
public:
	static void PrintSystemFail(const char * err) {
		// We need to convert from a const char * to a LPCCH (Wide character string)
		wchar_t* wStr = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, err, -1, wStr, 4096);
		// Print an error message to the screen
		MessageBox(NULL, wStr, L"Fatal Error:", MB_OK|MB_TASKMODAL|MB_ICONERROR);

		// And create an error file as well
		std::fstream errFile("error.log", std::ios::out);
		errFile << err << "\n";

		// Force crash the program
		exit(EXIT_FAILURE);
	}
};