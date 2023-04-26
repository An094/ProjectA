#pragma once

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

namespace EngineCore {

	class Common 
	{
	public:
		static std::string get_file_contents(const char* filename);
	};

}
