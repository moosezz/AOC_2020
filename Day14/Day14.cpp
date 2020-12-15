#include <bitset>

#include "FileLoader.h"
#include <map>


struct entry
{
	string mask;
	std::vector<std::pair<int, int>> mem;

public:
	void clear()
	{
		mask.clear();
		mem.clear();
	}
};


string parseMask(string str)
{
	size_t p = str.find('=') + 2;
	return str.substr(p);
}

std::pair<int, int> parseMem(string str)
{
	size_t vo = str.find('=') + 1;
	int v = std::stoi(str.substr(vo, str.size() - vo));

	auto brr = str.find(']');
	int adr = std::stoi(str.substr(4, brr - 3));

	return {adr, v};
}

long long int maskInt(int t, string mask)
{
	std::reverse(mask.begin(), mask.end());
	auto tbs = std::bitset<36>(t);
	for (int i = 0; i < mask.length(); i++)
	{
		if (mask[i] == '1')
		{
			tbs[i] = true;
		}
		if (mask[i] == '0')
		{
			tbs[i] = false;
		}
	}

	auto is = tbs.to_ullong();
	return static_cast<long long int>(is);
}


int main(int argc, char* argv[])
{
	std::vector<string> input;
	if (!(FileLoader::LoadAsStringVector(argv[1], &input))) return 0;

	std::map<int, long long int> memory;
	std::vector<entry> entries;

	entry curEntry;

	curEntry.mask = parseMask(input[0]);
	for (int i = 1; i < input.size(); ++i)
	{
		if (input[i][3] == 'k')
		{
			entries.emplace_back(curEntry);
			curEntry.clear();
			curEntry.mask = parseMask(input[i]);
		}
		else
		{
			curEntry.mem.emplace_back(parseMem(input[i]));
		}
		if (i == input.size() - 1)
		{
			entries.emplace_back(curEntry);
			curEntry.clear();
		}
	}


	for (auto e : entries)
	{
		for (auto m : e.mem)
		{
			memory.insert_or_assign(m.first, maskInt(m.second, e.mask));
		}
	}

	long long int sum = 0;
	for (auto m : memory)
	{
		sum += m.second;
	}
	std::cout << "part 1 sum: " << sum << "\n";
}
