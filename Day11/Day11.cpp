#include "FileLoader.h"
#include <string>
#include <vector>

typedef std::string string;

const std::pair<int, int> check_os[8]{{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}};

char checkCell(std::vector<string>* input, int cellX, int cellY)
{
	char thischar = (*input)[cellY][cellX];
	if (thischar == '.') return '.';
	
	int boundY = (*input).size() - 1;
	int boundX = (*input)[1].size();
	int adjacent = 0;

	for (auto o : check_os)
	{
		bool running = true;
		int offX = o.first;
		int offY = o.second;
		
		while(running)
		{
			//Avoid checking cells which don't exist
			if (offX + cellX > boundX || offX + cellX < 0 || offY + cellY > boundY || offY + cellY < 0)
			{
				running = false;
				break;
			}
			if((*input)[cellY + offY][cellX + offX] == '.')
			{
				offX += o.first;
				offY += o.second;
			}else if ((*input)[cellY + offY][cellX + offX] == 'L')
			{
				running = false;
			}else if((*input)[cellY + offY][cellX + offX] == '#')
			{
				adjacent++;
				running = false;
			}else
			{
				running = false;
			}
		}
	}

	if (thischar == 'L' && adjacent == 0)
	{
		return '#';
	}
	if (thischar == '#' && adjacent >= 5)
	{
		return 'L';
	}
	return thischar;
}

std::vector<string> runTest(std::vector<string>* input)
{
	std::vector<string> r_vec;
	for (int y = 0; y < input->size(); y++)
	{
		std::string bstring;
		for (int x = 0; x < (*input)[1].size() ; x++)
		{
			bstring += checkCell(input, x, y);
		}
		r_vec.push_back(bstring);
	}
	return r_vec;
}


int main(int argc, char* argv[])
{
	std::vector<string> input;
	FileLoader::LoadAsStringVector(argv[1], &input);


	bool solved = false;

	

	while (solved == false)
	{
		int occupiedSeats = 0;
		int totalSeats = 0;
		for (auto str : input)
		{
			totalSeats += str.length();
			for (auto cr : str)
			{
				if (cr == '#') occupiedSeats++;
			}
		}

		std::cout << "Occupied seats: " << occupiedSeats << "/" << totalSeats << "\n" ;
		
		std::vector<string> newinput;

		newinput = runTest(&input);
		if (newinput == input)
		{
			solved = true;
			break;
		}
		input = newinput;
		
		
	}
}
