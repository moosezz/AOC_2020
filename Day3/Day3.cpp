/*
 * Day 3
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

typedef std::string string;
const char CLEAR = '.';
const char TREE = '#';

/**
 * \brief Given a map and the desired slope, calculates how many trees would be hit
 * \param map the map to solve
 * \param slopeX the slope x to solve
 * \param slopeY the slope y to solve
 * \return number of trees hit 
 */
int SolveSlope(std::vector<string> &map, int slopeX, int slopeY)
{
	int map_height = map.size() - 1;
	int map_segment_width = map[0].length();
	int cursor_x = 0;
	int cursor_y = 0;
	int trees_hit = 0;

	std::cout << "\nSLOPE " << slopeX << "RIGHT / " << slopeY << " DOWN."<< std::endl; //dbg
	while (cursor_y < map_height)
	{
		cursor_y += slopeY;
		cursor_x += slopeX;
		if(cursor_y > map_height) cursor_y = map_height;
		if(map[cursor_y][cursor_x % map_segment_width] == TREE) trees_hit++;
		
		string tmpdbg = map[cursor_y];
		tmpdbg[cursor_x % map_segment_width] = '0'; //dbg
		std::cout << tmpdbg << std::endl; //dbg
	}
	return trees_hit;
}

int main(int argc, char* argv[])
{
	string str;
	std::vector<string> content;
	
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
	
	//Read the input file, build the array
	while (std::getline(input, str))
	{
		content.emplace_back(str);
	}

	//Part 2
	std::pair<int,int> slopes[5] = {{1,1},{3,1},{5,1},{7,1},{1,2}};

	int treesHit[5];


	for (int i = 0; i < std::size(slopes); ++i)
	{
		
		treesHit[i] = SolveSlope(content,slopes[i].first,slopes[i].second);
	}
	
	uint64_t treesHitProduct = 1; //damn boy he thicc

	for(int t : treesHit)
	{
		treesHitProduct *= t;
	}
	
	

	std::cout << treesHitProduct << " Trees Hit\n";
	
}
