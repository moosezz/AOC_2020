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

void genMemPerms(std::bitset<36> bits, std::vector<int> locations, std::vector<std::bitset<36>>* combinations)
{
	auto bit = locations.back();
	locations.pop_back();
	auto tbs = bits;
	auto fbs = bits;
	tbs[bit] = true;
	fbs[bit] = false;
	if (locations.empty())
	{
		combinations->emplace_back(tbs);
		combinations->emplace_back(fbs);
	}
	else
	{
		genMemPerms(tbs, locations, combinations);
		genMemPerms(fbs, locations, combinations);
	}
}

void maskMemoryLocations(int _mem, string _mask, std::vector<long long int>* _adrstore)
{
	std::reverse(_mask.begin(), _mask.end());
	auto adr = std::bitset<36>(_mem);
	std::vector<int> floating_bit_locs;

	for (int i = 0; i < 36; ++i)
	{
		if (_mask[i] == '1') adr[i] = true;
		if (_mask[i] == 'X') floating_bit_locs.emplace_back(i);
	}
	std::vector<std::bitset<36>> combos;

	genMemPerms(adr, floating_bit_locs, &combos);

	std::vector<long long int> values;
	for (auto combo : combos)
	{
		values.emplace_back(combo.to_ullong());
	}

	_adrstore->insert(_adrstore->end(), values.begin(), values.end());
}


int main(int argc, char* argv[])
{
	std::vector<string> input;
	if (!(FileLoader::LoadAsStringVector(argv[1], &input))) return 0;

	std::map<int, long long int> memory;
	std::map<long long int, long long int> p2_memory;
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


	for (auto e : entries)
	{
		for (auto m : e.mem)
		{
			std::vector<long long int> writeLocs;
			maskMemoryLocations(m.first, e.mask, &writeLocs);

			for (auto loc : writeLocs)
			{
				p2_memory.insert_or_assign(loc, m.second);
			}
		}
	}

	long long int p2sum = 0;
	for (auto m : p2_memory)
	{
		p2sum += m.second;
	}

	std::cout << "part 2 sum: " << p2sum << "\n";
}
