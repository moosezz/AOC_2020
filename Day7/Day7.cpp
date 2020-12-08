#include <map>
#include <queue>
#include "FileLoader.h"
#include <vector>
#include <string>
#include <unordered_map>


typedef std::string string;

struct bag
{
	bag(string d)
	{
		string ss;
		for (auto c : d)
		{
			if (c == ' ' || c == '.')
			{
				data.emplace_back(ss);
				ss.clear();
			}
			else ss += c;
		}
		name = data[0] + data[1];

		for (int i = 0; i < data.size(); ++i)
		{
			if (data[i].length() == 1)
			{
				string tar = data[i + 1] + data[i + 2];
				_contains.emplace(tar, std::stoi(data[i]));
			}
		}
	}

	void build_contents(std::vector<bag*>* baglist)
	{
		for (auto pair : _contains)
		{
			auto o = std::find_if(baglist->begin(), baglist->end(), [&](bag* bg) { return bg->name == pair.first; });
			bag* bb = *(o);
			contains.emplace(bb, pair.second);
			bb->containedBy.emplace(this, pair.second);
		}

		_contains.clear();
	}

	std::vector<string> data;
	string name;
	bool checked = false;
	bool containsGold = false;
	bool containedByGold = false;
	std::map<string, int> _contains;
	std::map<bag*, int> contains;
	std::map<bag*, int> containedBy;
};

int main(int argc, char* argv[])
{
	
	std::vector<string> input;
	std::vector<bag*> bags;
	if (FileLoader::LoadAsStringVector(argv[1], &input) == false)
	{
		return 0;
	}
	for (auto cs : input)
	{
		bags.emplace_back(new bag(cs));
	}
	for (auto value : bags)
	{
		value->build_contents(&bags);
	}
	auto o = std::find_if(bags.begin(), bags.end(), [&](bag* bg) { return bg->name == "shinygold"; });
	bag* shinyGold = *o;

	//Reverse search to find all possible bags which contain shiny gold bag (part 1)
	std::queue<bag*> queue;
	int goldContainers = 0;

	for (auto pair : shinyGold->containedBy)
	{
		queue.emplace(pair.first);
		pair.first->containsGold = true;
		goldContainers++;
	}

	while (queue.empty() == false)
	{
		auto cur = queue.front();
		queue.pop();
		if (cur->checked == true) break;
		for (auto ct : cur->containedBy)
		{
			queue.emplace(ct.first);
		}
		if (cur->containsGold == false)
		{
			cur->containsGold = true;
			goldContainers++;
		}
	}

	std::cout << "part 1: " << goldContainers << "\n";


	//Forward search from gold bag (part 2)

	int totalBags = 0;
	std::queue<std::pair<bag*, int>> q2;
	for (auto pair : shinyGold->contains)
	{
		q2.emplace(pair);
	}
	while (q2.empty() == false)
	{
		auto cur = q2.front();
		q2.pop();
		for (auto ct : cur.first->contains)
		{
			ct.second *= cur.second;
			q2.emplace(ct);
		}
		if constexpr (true)
		{
			cur.first->containedByGold = true;
			totalBags += cur.second;
		}
	}
	std::cout << "part 2: " << totalBags << "\n";
}
