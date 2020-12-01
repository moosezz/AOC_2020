
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
/*
* Day One
*/

int main(int argc, char *argv[])
{
    //Settings
    int target = 2020;
   
    if (argc != 2)
    {
        std::cout << "Specify Input File\n";
        return 0;
    }

    std::ifstream input ( argv[1] ); //Open file specificed in args

    if (input.is_open() == false) //Make sure we've opened it successfully
    {
        std::cout << "Failed to read file";
        return 0;
    }

    std::string str;
    std::vector<int> content;
    std::pair<int, int> pair;
    int triplet[3];

    //Read the input file, build the array
    while (std::getline(input, str)) 
    {
        content.push_back(std::stoi(str));
    }

    //Solve Part 1 
    for (int i = 0; i < content.size(); i++)
    {
        int num_1 = content[i];
        for (int x = 0; x < content.size(); x++)
        {
            int num_2 = content[x];
            if (num_2 + num_1 == target && num_1 != num_2)
            {
                pair =  std::pair<int, int>(num_1, num_2);
                break;
            }
        }
    }

    //Solve Part 2
    for (int a = 0; a < content.size(); a++) 
    {
        int num_1 = content[a];
        for (int b = 0; b < content.size(); b++)
        {
            int num_2 = content[b];
            if (b != a && (num_1 + num_2) < 2020) { // Any pairs where a+b > 2020 will not have a third number and cannot solve part 2
                for (int c = 0; c < content.size(); c++)
                {
                    int num_3 = content[c];
                    if ((num_1 + num_2 + num_3) == 2020 && (c != a && c != b))
                    {
                        triplet[0] = num_1;
                        triplet[1] = num_2;
                        triplet[2] = num_3;
                        break;
                    }
                }
            }
        }
    }
    //Print result
        std::cout << "Valid Pair: " + std::to_string(pair.first) + " and " + std::to_string(pair.second) + "\n";
        std::cout << "Product of Pair: " + std::to_string(pair.first * pair.second) + "\n";

        std::cout << "Valid Triplet: " + std::to_string(triplet[0]) + " and " + std::to_string(triplet[1]) + " and " + std::to_string(triplet[2]) + "\n";
        std::cout << "Product of Triplet: " + std::to_string(triplet[0] * triplet[1] * triplet[2]) + "\n";
    
        return 0;
    
}
