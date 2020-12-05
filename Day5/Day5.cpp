/*
*Day 5
*Code for second part isnt really good. code in general is very messy. 
*o well
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>

typedef std::string string;

const int ROW_COUNT = 128;
const int COL_COUNT = 8;
//AOC Boilerplate
void GetInput(char* file, std::vector<string> *content)
{
	std::ifstream input(file); //Open file specified in args

	if (input.is_open() == false) //Make sure we've opened it successfully
	{
		std::cout << "Failed to read file\n";
	}
	else{

	string str;
	

	//Read the input file, build the array
	while (std::getline(input, str))
	{
		content->emplace_back(str);	
	}
	
	input.close();
	}
}

std::pair<int,int> GetPosition(string d)
{
	int row,column;
	string ir = d.substr(0,7);
	string ic = d.substr(7,9);

	std::replace(ir.begin(),ir.end(),'F','0');
	std::replace(ir.begin(),ir.end(),'B','1');
	std::replace(ic.begin(),ic.end(),'R','1');
	std::replace(ic.begin(),ic.end(),'L','0');
	row = std::stoi(ir,nullptr,2);
	column = std::stoi(ic,nullptr,2);

	return {row, column};
	
}
int main(int argc, char* argv[])
{
	//AOC Boilerplate
	if (argc != 2)
	{
		std::cout << "Specify Input File\n";
		return 0;
	}
	std::vector<string> input;
	std::vector<int> seat_ids;
	std::vector<std::pair<int,int>> seats;
	std::vector<std::pair<int,int>> missingSeats;
	GetInput(argv[1],&input);

	//Begin Daily Code

	for (auto value : input)
	{
		auto x = GetPosition(value);
		seats.emplace_back(x);
		seat_ids.push_back(x.first * 8 + x.second);
	}

	int curHighest = 0;
	for(int id: seat_ids)
	{
		if(id > curHighest) curHighest = id;
	}

	std::cout << "Highest Seat ID: " << curHighest << std::endl;

	//Find my seats ID

	std::sort(seats.rbegin(),seats.rend());

	for (int i = 0; i < 128; ++i)
	{
		for(int c = 0; c < 8; ++c)
		{
			std::pair<int,int> targ{i,c};
			if(std::find(seats.begin(),seats.end(),targ) == seats.end())
			{
				missingSeats.emplace_back(targ);
			}
		}
	}

	//find seat which the seat before  exists
	for (auto seat : missingSeats)
	{
		auto checkseat = seat;
		checkseat.first -= 1;
		checkseat.second -= 1;
		
		if(std::find(seats.begin(),seats.end(),checkseat) != seats.end())
		{
			std::cout << "My Seat is: " << seat.first << "," << seat.second << " ID: " << (seat.first * 8 + seat.second) << std::endl;
		}
	}
	
}

