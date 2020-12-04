/*
 * Day 4!
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

typedef std::string string;
const string RequiredDataFields[7] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};


struct Passport
{
	Passport(string data)
	{
		for (string field : RequiredDataFields)
		{
			int o = data.find(field) + 4;
			int o2 = data.find(' ', o);
			fields.emplace(field, data.substr(o, o2 - o));
		}
		
	}

	bool Validate()
	{
		for (string field : RequiredDataFields)
		{
			if (field == "byr")
			{
				int yr = std::stoi(fields[field]);
				fieldValidity.emplace(field, (yr >= 1920 && yr <= 2002));
			}
			if (field == "iyr")
			{
				int yr = std::stoi(fields[field]);
				fieldValidity.emplace(field, (yr >= 2010 && yr <= 2020));
			}
			if (field == "eyr")
			{
				int yr = std::stoi(fields[field]);
				fieldValidity.emplace(field, (yr >= 2020 && yr <= 2030));
			}
			if (field == "hgt")
			{
				string hgt = fields[field];
				if (hgt.find("cm") != std::string::npos)
				{
					int h = std::stoi(hgt);
					fieldValidity.emplace(field, (h >= 150 && h <= 193));
				}
				else if (hgt.find("in") != std::string::npos)
				{
					int h = std::stoi(hgt);
					fieldValidity.emplace(field, (h >= 59 && h <= 76));
				}
				else fieldValidity.emplace(field, false);
			}
			if (field == "hcl")
			{
				std::regex rx("#+[a-f,0-9,A-F]{6}");
				if( std::regex_match(fields[field],rx)) fieldValidity.emplace(field,true);
				else fieldValidity.emplace(field,false);
			}
			if(field == "ecl")
			{
				std::regex rx("amb|blu|brn|gry|grn|hzl|oth");
				if( std::regex_match(fields[field],rx)) fieldValidity.emplace(field,true);
				else fieldValidity.emplace(field,false);
			}
			if(field == "pid")
			{
				std::regex rx("^[0-9]{9}$");
				if( std::regex_match(fields[field],rx)) fieldValidity.emplace(field,true);
				else fieldValidity.emplace(field,false);
			}
		}
		for (auto field : fieldValidity)
		{
			if(field.second == false) return false;
		}
		return true;
	}

	std::map<string, string> fields;
	std::map<string, bool> fieldValidity;
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
	string str2;
	std::vector<string> content;
	std::vector<Passport> validPassports;
	int fullyValidatedPasports = 0;
	int invalidPassports = 0;

	const string OptionalDataFields[1] = {"cid"};
	//Read the input file, build the array
	while (std::getline(input, str))
	{
		if (str.empty())
		{
			content.emplace_back(str2);
			str2.clear();
		}
		else
		{
			str2 += (' ' + str + ' ');
		}
	}

	//Part 1: Filter passports with missing fields
	for (auto item : content)
	{
		bool valid = true;
		string missingItems;
		for (string field : RequiredDataFields)
		{
			if (item.find(field) == string::npos)
			{
				valid = false;
				missingItems += " " + field + " ";
			}
		}
		if (valid)
		{
			std::cout << item << " VALID." << std::endl;
			validPassports.emplace_back(Passport(item));
		}
		else
		{
			invalidPassports++;
			std::cout << item << " INVALID. MISSING " << missingItems << std::endl;
		}
	}
	for (auto passport : validPassports)
	{
		if(passport.Validate() == true)
		{
			fullyValidatedPasports++;
		}
	}

	std::cout << "\n There are " << validPassports.size() << " valid passports. and " << invalidPassports <<
		" Invalid. Out of " << content.size() << " Total Passports" << std::endl;

	std::cout << "\n For part 2: " << fullyValidatedPasports << " passports are fully valid." << std::endl;
}
