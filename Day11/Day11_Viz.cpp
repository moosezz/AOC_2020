#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "FileLoader.h"
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

		while (running)
		{
			//Avoid checking cells which don't exist
			if (offX + cellX > boundX || offX + cellX < 0 || offY + cellY > boundY || offY + cellY < 0)
			{
				running = false;
				break;
			}
			if ((*input)[cellY + offY][cellX + offX] == '.')
			{
				offX += o.first;
				offY += o.second;
			}
			else if ((*input)[cellY + offY][cellX + offX] == 'L')
			{
				running = false;
			}
			else if ((*input)[cellY + offY][cellX + offX] == '#')
			{
				adjacent++;
				running = false;
			}
			else
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
		for (int x = 0; x < (*input)[1].size(); x++)
		{
			bstring += checkCell(input, x, y);
		}
		r_vec.push_back(bstring);
	}
	return r_vec;
}

class Viz : public olc::PixelGameEngine
{
public:
	bool paused = true;
	std::vector<string> v_data;
	std::vector<string> o_data;
	const olc::Pixel p_occupied{255, 0, 0};
	const olc::Pixel p_empty{0, 255, 0};
	const olc::Pixel p_floor{0, 0, 255};

	Viz()
	{
		
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		v_data = o_data;
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if(GetKey(olc::SPACE).bPressed) paused =! paused;
		if(paused) return true;
		std::vector<string> newData = runTest(&v_data);
				
		if (v_data == newData)
		{

		}
		else
		{
			v_data = newData;
		}
		
		for (int y = 0; y < v_data.size(); y++)
			for (int x = 0; x < v_data[1].size(); x++){
				switch (v_data[y][x])
				{
				case 'L':
					Draw(x, y, p_empty);
					break;
				case '#':
					Draw(x, y, p_occupied);
					break;
				case '.':
					Draw(x, y, p_floor);
					break;
				default:
					break;
					
				}
			}
		Sleep(50);
		return true;
	}
};

int main(int argc, char* argv[])
{
	Viz demo;
	FileLoader::LoadAsStringVector(argv[1], &demo.o_data);
	if (demo.Construct(128, 128, 10, 10))
		demo.Start();
	return 0;
}
