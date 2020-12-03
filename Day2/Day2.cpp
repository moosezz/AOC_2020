/*
* Day 2
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

typedef std::string string;

struct password
{
	//Construct Password given a string containing the word and its requirements 
	password(string data)
	{
		charMin = std::stoi(data.substr(0,data.find('-')));
		charMax = std::stoi(data.substr(data.find('-') + 1, data.find(' ') - 1));
		requiredCharacter = data[data.find(' ') + 1];
		word = data.substr(data.find(':') + 2, data.length());
	}

	string to_string()
	{	
		string value = "Requires " + std::to_string(charMin) + " to " + std::to_string(charMax) + " of " + requiredCharacter + " in " + word;
		return value;
	}
	
	string word; //Password
	//Password requirements
	char requiredCharacter;
	int charMin;
	int charMax; 
};

int main(int argc, char* argv[])
{
	

	if (argc != 2)
	{
		std::cout << "Specify Input File\n";
		return 0;
	}
	std::ifstream input(argv[1]); //Open file specified in args
	if (input.is_open() == false) //Make sure we've opened it successfully
	{
		std::cout << "Failed to read file\n";
		return 0;
	}
	string str;
	std::vector<password> content;
	int valid_passwords = 0;
	int part_2_valid_passwords = 0;
	//Read the input file, build the array
	while (std::getline(input, str))
	{
		content.emplace_back(password(str));
	}

	for(auto pw : content )
	{
		int count = 0;
		for(char c : pw.word)
		{
			if(c == pw.requiredCharacter) count++;
		}
		if(count <= pw.charMax && count >= pw.charMin ) valid_passwords++;
	}

	for(auto pw : content)
	{
		int ct = 0;
		if(pw.word[pw.charMin - 1] == pw.requiredCharacter) ct++;
		if(pw.word[pw.charMax - 1] == pw.requiredCharacter) ct++;

		if(ct == 1) part_2_valid_passwords++;
	}
	std::cout << std::endl << "Valid passwords found: " << valid_passwords << std::endl;
	std::cout << std::endl << "Valid passwords found for part 2: " << part_2_valid_passwords << std::endl;
}


