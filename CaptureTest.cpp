//
// CaptureTest.cpp: test the Capture-CWI dll
//
// Created by Fons Kuijk on 13-07-18.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

typedef void(*GetPointCloudFunction)(long *, void **);

int main()
{
	HINSTANCE hInstLibrary;
	GetPointCloudFunction getPointCloud = nullptr;

	hInstLibrary = LoadLibrary(TEXT("multiFrame.dll"));

	if (hInstLibrary)		// the function dll file has been found and is loaded
		getPointCloud = (GetPointCloudFunction)GetProcAddress(hInstLibrary, "getPointCloud");
	else {
		std::cout << "ERROR: no dll file named 'multiFrame.dll' found\n";
		std::cin.get();
	}

	if (getPointCloud) {	// the function 'getPointCloud' has been found in the dll file
		long t = 4;
		void *p = &t;
		std::cout << "===================\neach 'enter' gets you a next pointcloud\nto quit enter a 'q'\n===================\n\n";
		do {
			// call the function that returns the timestamp and pointcloud pointer
			getPointCloud(&t, &p);
			std::cout << "got a pointcloud captured at = " << t << std::endl;
		} while (std::cin.get() != 'q');
	}
	else {
		std::cout << "ERROR: function 'getPointCloud' not found in dll file\n";
		std::cin.get();
	}

	FreeLibrary(hInstLibrary);
	return 0;
}