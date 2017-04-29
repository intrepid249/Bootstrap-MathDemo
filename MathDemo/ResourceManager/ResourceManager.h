/////////////////////////////////////////////////////////////////////////////////
////		Created By:		Jack McCall and Sebastian Toy
////		Date Created:	31-03-2017
////		Description:	Provides 3 templated functions that
////						can be utilised to load a variety of
////						resource types as either type of smart pointer
////						or a raw pointer.



#pragma once
#include "Texture.h"
#include "Audio.h"
#include "Font.h"
#include <stdarg.h>
#include "ErrorManager.h"
#include <fstream>
#include <ios>
#include <memory>

class ResourceManager {
public:
	// Make a default constructor to allow an instance of the Resource Manager to be created
	ResourceManager() {}
	~ResourceManager() {}



	/*
	Function returns an std::unique_ptr specified by the type T when calling the function
	e.g. loadUniqueResource<type>(parameters);
	*/
	template <typename T, typename... Args>
	static std::unique_ptr<T> loadUniqueResource(const char *fileName, Args...args) {
#if 0
		//=================================================================================

		/*
		If there is no definitive first argument (const char *fileName, ) then using a tuple
		is a method of being able to access any indexed element of the variadic argument package
		*/

		auto tuple = std::tuple<Args...>(args...); // create a tuple from a variadic list

		// The filename is the 0th index of the tuple (first argument)
		std::tuple_element<0, decltype(tuple)>::type fileName = std::get<0>(tuple);

		//=================================================================================
#endif

		// Try to open the file to see if it exists
		std::fstream test(fileName, std::ios::in);
		if (!test) {
			// If the file doesn't exist then output to the console/error file and crash the program
			char errMsg[256];
			sprintf_s(errMsg, "Could not find file: %s", fileName);
			ErrorManager::PrintSystemFail(errMsg); // handles error output and forces a crash
		}

		return std::unique_ptr<T>(new T(fileName, args...));
	}



	/*
	Function returns an std::shared_ptr specified by the type T when calling the function
	e.g. loadUniqueResource<type>(parameters);
	*/
	template <typename T, typename... Args>
	static std::shared_ptr<T> loadSharedResource(const char *fileName, Args...args) {
		// Try to open the file to see if it exists
		std::fstream test(fileName, std::ios::in);
		if (!test) {
			// If the file doesn't exist then output to the console/error file and crash the program
			char errMsg[256];
			sprintf_s(errMsg, "Could not find file: %s", fileName);
			ErrorManager::PrintSystemFail(errMsg); // handles error output and forces a crash
		}

		return std::make_shared<T>(fileName, args...);
	}



	/*
	Function returns a standard raw pointer of type T
	Memory will have to be cleaned up manually
	*/
	template <typename T, typename... Args>
	static T* loadRawResource(const char *fileName, Args...args) {
		// Try to open the file to see if it exists
		std::fstream test(fileName, std::ios::in);
		if (!test) {
			// If the file doesn't exist then output to the console/error file and crash the program
			char errMsg[256];
			sprintf_s(errMsg, "Could not find file: %s", fileName);
			ErrorManager::PrintSystemFail(errMsg); // handles error output and forces a crash
		}

		return new T(fileName, args...);
	}
};

