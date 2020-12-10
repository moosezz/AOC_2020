#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef std::string string;

class FileLoader
{
public:
	static bool LoadAsStringVector(char* file, std::vector<string>* content)
	{
		std::ifstream input(file); //Open file specified in args

		if (input.is_open() == false) //Make sure we've opened it successfully
		{
			std::cout << "Failed to read file\n";
			return false;
		}
		string str;


		//Read the input file, build the array
		while (std::getline(input, str))
		{
			content->emplace_back(str);
		}

		input.close();
		return true;
	}
	static bool LoadAsLongLongIntVector(char* file, std::vector<long long int>* content)
	{
		std::ifstream input(file); //Open file specified in args

		if (input.is_open() == false) //Make sure we've opened it successfully
		{
			std::cout << "Failed to read file\n";
			return false;
		}
		string str;


		//Read the input file, build the array
		while (std::getline(input, str))
		{
			content->emplace_back(std::stoll(str));
		}

		input.close();
		return true;
	}
};
