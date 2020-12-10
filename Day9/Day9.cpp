#include <algorithm>

#include "FileLoader.h"
#include <vector>
#include <string>
#include <numeric>
typedef std::string string;


int iv = 25;


int main(int argc, char* argv[])
{
	std::vector<long long int> input;
	if (FileLoader::LoadAsLongLongIntVector(argv[1], &input) == false) return 0;

	
	int idx = 0;
	bool running = true;

	//start from index 25.
	idx += 25;

	long long int outlier;
	while(running)
	{
		bool outlier_found = true;
		std::vector<long long int> buffer;
		for (int i = 1; i < iv+1; i++)
		{
			buffer.emplace_back(input[idx - i]);
		}

		for (auto it1 = buffer.begin(); it1 != buffer.end(); ++it1)
		{
			for(auto it2 = buffer.begin(); it2 != buffer.end(); ++it2)
			{
				if(it1 != it2 && *it1+*it2 == input[idx])
				{
					outlier_found = false;
					break;
					
				}
			}
		}
		if(outlier_found)
		{
		std::cout << "found outlier: " << input[idx] << "\n";
		outlier = input[idx];
		running = false;
		}
		
		idx++;
	}

	for (auto it = input.begin(); it != input.end(); ++it)
	{
		std::vector<long long int> buffer;
		buffer.emplace_back(*it);

		int i = 1;
		
		while (std::accumulate(buffer.begin(),buffer.end(),0) < outlier)
		{
			buffer.emplace_back(*(it+i));
			i++;
			
		}
		if(std::accumulate(buffer.begin(),buffer.end(),0) == outlier)
		{
			std::cout << "found string of numbers: ";
			for (auto value : buffer)
			{
				std::cout << value << " ";
			}
			std::cout << "\n";
			auto min = std::min_element(buffer.begin(),buffer.end());
			auto max = std::max_element(buffer.begin(),buffer.end());
			std::cout << "min: " << *min << "\n" << "max: " << *max << "\n" << "sum: " << *min+*max << "\n";
			break;
		}
		
	}

	
}
