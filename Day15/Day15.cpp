#include <vector>
#include <iostream>
#include <map>


struct turn
{
	int tid;
	int num;
	bool newNumber;
	int numberLastUsed;
	turn(int _tid, int _n, bool _new,int _nlu = 0)
	{
		tid = _tid;
		num = _n;
		newNumber = _new;
		numberLastUsed = _nlu;
	}
};

int main(int argc, char* argv[])
{
	std::vector<int> input {19,20,14,0,9,1};

	std::map<int, int> kvp; // { Number, age }
	std::vector<turn> turns;
	int prev;
	int ti = 1;

	for (int i = 0; i < input.size(); ++i)
	{
		kvp.insert({input[i],ti});
		prev = input[i];
		turns.emplace_back(turn(ti,input[i],true));
		ti++;
	}

	while (turns.size() < 2020)
	{
		auto prevturn = turns.back();
		if(prevturn.newNumber)
		{
			turns.emplace_back(turn(ti,0,false /* zero is never new */,kvp[0]));
			kvp.insert_or_assign(0,ti);
		}else
		{
			int nn = kvp[prevturn.num] - prevturn.numberLastUsed;
			bool newnum;
			if(kvp.count(nn) == 1)
			{
				newnum = false;
				turns.emplace_back(ti,nn,newnum,kvp[nn]);
				kvp[nn] = ti;
			}
			else
			{
				newnum = true;
				kvp.insert_or_assign(nn,ti);
				turns.emplace_back(ti,nn,newnum,ti);
			}
			
		}

		ti++;
	}
	std::cout << turns[2019].num << "\n"; 
	
}
