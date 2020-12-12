#include "FileLoader.h"
#include <vector>
#include <algorithm>
int Day10(int argc, char* argv[])
{
	std::vector<int> input;
	if (FileLoader::LoadAsIntVector(argv[1], &input) == false) return 0;

	input.emplace_back(0); //The rating of the power outlet
	
	std::sort(input.begin(),input.end());

	int phonerating = *std::max_element(input.begin(),input.end()) + 3;
	input.emplace_back(phonerating);
	
	int jd_3 = 0;
	int jd_1 = 0;

	for(auto it = input.begin(); it != input.end() - 1; ++it)
	{
		std::cout << *(it+1) << " - " << *it << " = " << *(it+1) - *it << "\n";
		switch(*(it+1) - *it)
		{
		case 1:
			jd_1++;
			break;
		case 3:
			jd_3++;
			break;
		}
	}

	std::cout << "3j differences: " << jd_3 << "\n1j differences: " << jd_1 << "\nproduct: " << jd_1*jd_3 << "\n";
}
