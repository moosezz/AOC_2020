#include "FileLoader.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <execution>

typedef std::string string;
//CRT Code from Rosetta Code
template<typename _Ty> _Ty mulInv(_Ty a, _Ty b) {
	_Ty b0 = b;
	_Ty x0 = 0;
	_Ty x1 = 1;
 
	if (b == 1) {
		return 1;
	}
 
	while (a > 1) {
		_Ty q = a / b;
		_Ty amb = a % b;
		a = b;
		b = amb;
 
		_Ty xqx = x1 - q * x0;
		x1 = x0;
		x0 = xqx;
	}
 
	if (x1 < 0) {
		x1 += b0;
	}
 
	return x1;
}
 
template<typename _Ty> _Ty chineseRemainder(std::vector<_Ty> n, std::vector<_Ty> a) {
	_Ty prod = std::reduce(std::execution::seq, n.begin(), n.end(), (_Ty)1, [](_Ty a, _Ty b) { return a * b; });
 
	_Ty sm = 0;
	for (int i = 0; i < n.size(); i++) {
		_Ty p = prod / n[i];
		sm += a[i] * mulInv(p, n[i]) * p;
	}
 
	return sm % prod;
}
//End Stolen Code

struct shuttle
{
	int id;
	int offset;
	int t_time;
	int recent_departure;
	int time_until_next;
	shuttle(int _id, int _ts,int _os)
	{
		id = _id;

		recent_departure = (_ts / id) * id;

		time_until_next = (recent_departure + id) - _ts;
		
		offset = _os;
		if(offset == 0)
		{
			t_time = 0;
		}
		else
		{
			t_time = id + offset;
		}	
	}
	
};
int main(int argc, char* argv[])
{
	
	std::vector<string> input;
	if(!(FileLoader::LoadAsStringVector(argv[1],&input))) return 0;


	int timestamp = std::stoi(input[0]);
	std::vector<shuttle> shuttles;

	
	string sbs = input[1];
	sbs += ',';
	const char delim = ',';
	size_t pos;

	int offsetctr = 0;
	while((pos = sbs.find(delim)) != std::string::npos)
	{
		string buff = sbs.substr(0,pos);

		if(buff == "x") offsetctr--;
		if(buff != "x")
		{
			shuttles.emplace_back(shuttle(std::stoi(buff),timestamp,offsetctr));
			offsetctr--;
		}
		
		sbs.erase(0, pos+1);
	}

	shuttle next_shuttle = shuttles[0];
	for(auto sh : shuttles)
	{
		if( sh.time_until_next < next_shuttle.time_until_next)
		{
			next_shuttle = sh;
		}	
	}

	std::cout << "next shuttle: " << next_shuttle.id << " in " << next_shuttle.time_until_next <<  " mins \n";
	std::cout << "part 1 answer: " << next_shuttle.id * next_shuttle.time_until_next << "\n";

	std::vector<long long int> n;
	std::vector<long long int> a;

	for (auto sh : shuttles)
	{
		n.emplace_back(sh.id);
		a.emplace_back(sh.t_time);
	}

	long long int crt = chineseRemainder(n,a);

	std::cout << "part 2: " << crt << "\n";
	
}
