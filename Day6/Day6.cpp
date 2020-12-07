#include <map>

#include "FileLoader.h"
#include "string"
#include "vector"

typedef std::string string;


struct answer_set
{
	answer_set(string d, int rc)
	{
		data = d;
		for (char c : data)
		{
			auto iter = char_frequency.find(c);
			if (iter != char_frequency.end())
			{
				iter->second += 1;
			}
			else
			{
				char_frequency.emplace(c, 1);
			}
		}
		score = char_frequency.size();
		respondent_count = rc;
	}

	explicit operator string() const
	{
		return data;
	}

	int get_part2_score()
	{
		int v = 0;
		for (auto pv : char_frequency)
		{
			if (pv.second == respondent_count) v++;
		}
		return v;
	}

	string data;
	int respondent_count;
	std::map<char, int> char_frequency;
	int score;
};

int main(int argc, char* argv[])
{
	std::vector<string> data_unprocessed;
	if (FileLoader::LoadAsStringVector(argv[1], &data_unprocessed) == false)
	{
		return 0;
	}

	std::vector<answer_set> data;

	string cur_entry = "";
	int respondent_count = 0;

	for (auto v : data_unprocessed)
	{
		if (v.empty())
		{
			data.emplace_back(answer_set(cur_entry, respondent_count));
			cur_entry.clear();
			respondent_count = 0;
		}
		else
		{
			respondent_count += 1;
			cur_entry += v;
		}
	}

	//Find Total Score of all answer sets
	int data_sum = 0;

	for (answer_set value : data)
	{
		data_sum += value.score;
	}

	std::cout << "Total Score: " << data_sum << "\n";

	//Find Part 2 Answer
	int data2_sum = 0;

	for (auto value : data)
	{
		data2_sum += value.get_part2_score();
	}

	std::cout << "Total Score for Part 2: " << data2_sum << "\n";
}
