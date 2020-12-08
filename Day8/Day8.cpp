#include "FileLoader.h"
#include <vector>
#include <string>

typedef std::string string;

enum op
{
	nop,
	acc,
	jmp
};

struct inst
{
	op type;
	int value;
	bool executed = false;
};

class part2
{
public:
	static int solve(std::vector<inst>* instructions)
	{
		for (int i = 0; i < instructions->size(); i++)
		{
			std::vector<inst> inst = *instructions;

			if (inst[i].type == jmp)
			{
				inst[i].type = nop;
				auto test = TrySolution(inst);
				if (test.first == true)
				{
					std::cout << "from jmp to nop: " << i << " acc: " << test.second << "\n";
					return test.second;
				}
				inst[i].type = jmp;
			}
			if (inst[i].type == nop)
			{
				inst[i].type = jmp;
				auto test2 = TrySolution(inst);
				if (test2.first == true)
				{
					std::cout << "from nop to jmp: " << i << " acc: " << test2.second << "\n";
					return test2.second;
				}
				inst[i].type = nop;
			}
		}
	}

	static std::pair<bool, int> TrySolution(std::vector<inst> instructions)
	{
		bool solved = false;
		bool running = true;
		int cursor = 0;
		int acc = 0;
		while (running)
		{
			if (cursor < 0 || cursor > instructions.size())
			{
				running = false;
				solved = false;
				break;
			}
			if (cursor == instructions.size())
			{
				running = false;
				solved = true;
				break;
			}
			if (instructions[cursor].executed)
			{
				running = false;
				solved = false;
				break;
			}
			switch (instructions[cursor].type)
			{
			case nop:
				instructions[cursor].executed = true;
				cursor++;
				break;
			case op::acc:
				instructions[cursor].executed = true;
				acc += instructions[cursor].value;
				cursor++;
				break;
			case jmp:
				instructions[cursor].executed = true;
				cursor += instructions[cursor].value;
				break;
			}
		}

		return {solved, acc};
	}
};

int main(int argc, char* argv[])
{
	std::vector<string> input;
	if (FileLoader::LoadAsStringVector(argv[1], &input) == false) return 0;

	std::vector<inst> instructions;

	for (auto v : input)
	{
		inst in;
		string t = v.substr(0, 3);
		if (t == "nop") in.type = nop;
		else if (t == "acc") in.type = acc;
		else if (t == "jmp") in.type = jmp;

		in.value = std::stoi(v.substr(4, v.length() - 4));

		instructions.emplace_back(in);
	}

	////part 1
	//bool looped = false;
	//int cursor = 0;
	//int acc = 0;
	//while (!looped)
	//{
	//	if (instructions[cursor].executed)
	//	{
	//		looped = true;
	//		break;
	//	}
	//	switch (instructions[cursor].type)
	//	{
	//	case nop:
	//		instructions[cursor].executed = true;
	//		cursor++;
	//		break;
	//	case op::acc:
	//		instructions[cursor].executed = true;
	//		acc += instructions[cursor].value;
	//		cursor++;
	//		break;
	//	case jmp:
	//		instructions[cursor].executed = true;
	//		cursor += instructions[cursor].value;
	//		break;
	//	}
	//}
	//std::cout << "p1: " << acc << "\n";

	part2::solve(&instructions);
}
