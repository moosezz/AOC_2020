#include "FileLoader.h"
#include <string>
#include <vector>

typedef std::string string;

enum op
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	LEFT,
	RIGHT,
	FORWARD,
	NULLOP
};

constexpr op getOp(char c)
{
	switch (c)
	{
	case 'N':
		return NORTH;
	case 'E':
		return EAST;
	case 'S':
		return SOUTH;
	case 'W':
		return WEST;
	case 'L':
		return LEFT;
	case 'R':
		return RIGHT;
	case 'F':
		return FORWARD;
	default: return NULLOP;
	}
}

struct inst
{
public:
	op t;
	int v;

	inst(op _t, int _v)
	{
		t = _t;
		v = _v;
	}
};

class boat
{
public:
	// X = +WEST -EAST
	// Y = +NORTH -SOUTH
	int x = 0;
	int y = 0;
private:
	int facing = 0;

	void rotate(int v)
	{
		int new_r = facing + v;
		if (new_r > 360) new_r -= 360;
		if (new_r < 0) new_r += 360;
		facing = new_r;
	}

	void forward(int v)
	{
		if (facing == 0 || facing == 360) x += v;
		if (facing == 90) y += v;
		if (facing == 180) x -= v;
		if (facing == 270) y -= v;
	}

public:
	void runInst(inst* i)
	{
		switch (i->t)
		{
		case NORTH:
			y += i->v;
			break;
		case EAST:
			x += i->v;
			break;
		case SOUTH:
			y -= i->v;
			break;
		case WEST:
			x -= i->v;
			break;
		case LEFT:
			rotate(i->v);
			break;
		case RIGHT:
			rotate(-(i->v));
			break;
		case FORWARD:
			forward(i->v);
			break;
		}
	}
};

class waypoint
{
public:
	boat* boat;
	//position is always relative to boat.
	int x = 0;
	int y = 0;

	void rotate(int v)
	{
		int r = v % 360 / 90;

		int new_x = x;
		int new_y = y;
		if (r > 0)
		{
			for (int i = 0; i < r; i++)
			{
				int tx = -new_y;
				int ty = new_x;
				new_x = tx;
				new_y = ty;
			}
		}
		if (r < 0)
		{
			for (int i = 0; i < abs(r); i++)
			{
				int tx = new_y;
				int ty = (-new_x);
				new_x = tx;
				new_y = ty;
			}
		}
		x = new_x;
		y = new_y;
	}

	void runInst(inst* i)
	{
		switch (i->t)
		{
		case NORTH:
			y += i->v;
			break;
		case EAST:
			x += i->v;
			break;
		case SOUTH:
			y -= i->v;
			break;
		case WEST:
			x -= i->v;
			break;
		case LEFT:
			rotate(i->v);
			break;
		case RIGHT:
			rotate(-(i->v));
			break;
		case FORWARD:
			for (int a = 0; a < i->v; a++)
			{
				boat->x += x;
				boat->y += y;
			}
			break;
		}
	}
};

int main(int argc, char* argv[])
{
	std::vector<string> input;
	std::vector<inst> instructions;
	if (!FileLoader::LoadAsStringVector(argv[1], &input)) return 0;

	for (auto value : input)
	{
		op o = getOp(value[0]);
		int v = std::stoi(value.substr(1, value.length() - 1));

		instructions.emplace_back(o, v);
	}

	boat boatboy;
	waypoint wp;
	wp.x = 10;
	wp.y = 1;
	wp.boat = &boatboy;
	for (auto instruction : instructions)
	{
		wp.runInst(&instruction);
	}
	std::cout << "part 2 manhattan position " << abs(boatboy.x) + abs(boatboy.y) << "\n";
	/*
		for (auto instruction : instructions)
		{
			
			boatboy.runInst(&instruction);
			std::cout << "new position: (" << boatboy.x << "," << boatboy.y << ") \n";
		}
	
		std::cout << "part 1 manhattan position " << abs(boatboy.x) + abs(boatboy.y) << "\n" ;
	*/
}
