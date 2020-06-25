#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

unsigned char const primes[54] =
{
	2,
	3,
	5,
	7,
	11,
	13,
	17,
	19,
	23,
	29,
	31,
	37,
	41,
	43,
	47,
	53,
	59,
	61,
	67,
	71,
	73,
	79,
	83,
	89,
	97,
	101,
	103,
	107,
	109,
	113,
	127,
	131,
	137,
	139,
	149,
	151,
	157,
	163,
	167,
	173,
	179,
	181,
	191,
	193,
	197,
	199,
	211,
	223,
	227,
	229,
	233,
	239,
	241,
	251
};

const char* explanation =
	"This program is relevant to a certain mathematical problem:\n"
	"\n"
	" Let a \"prime factor connection\" be a connection from two whole numbers A and B, such that:\n"
	"  * A and B share a common prime factor C\n"
	"  * A plus C equals B\n"
	"  * A divided by C is not prime\n"
	"\n"
	" For any whole number N, let the \"prime connected set\" of N be the set of all whole numbers that satisfy the following:\n"
	"  * For any number X in this set, N is part of its prime connected set\n"
	"  * All numbers prime connected to N are in this set\n"
	"  * This set is the minimum possible size given the first two requirements\n"
	"\n"
	" Let S(N) be the size of the prime connected set of N\n"
	"\n"
	"The MOVE program of this project interactively demondtrates this concept.\n"
	"This program will calculate the value of S(N) and records it to the \"log.hex\" file\n"
	"The \"log.hex\" file can be read by the READ program\n"
;

unsigned short step(unsigned short num)
{
	vector<unsigned short> factors;
	unsigned short fac_num = num;
	for (unsigned short i = 0; i < 54; i++)
	{
		if(primes[i] > sqrt(fac_num))
			break;
		fac:
		if(fac_num%primes[i] == 0)
		{
			factors.push_back(primes[i]);
			fac_num/=primes[i];
			goto fac;
		}
	}
	if(fac_num > 1)
		factors.push_back(fac_num);
	switch (factors.size())
	{
	case 0:
		return 1;
	case 1:
		return num*2;
	case 2:
		if(rand()%2 || factors[0] == 3)
			return num-factors[0];
		return num-factors[1];
	default:
		mv:
		unsigned short rand_num = rand() % (factors.size()*2);
		if(rand()%2==0)
			return num+factors[rand_num>>1];
		unsigned short check = (num/factors[rand_num>>1])-1;
		for (unsigned short i = 0; i < 54; i++)
		{
			if (primes[i] == check)
				goto mv;
			if (primes[i] > check)
				break;
		}
		return num-factors[rand_num>>1];
	}
}

int main()
{
	std::vector<unsigned short> queue_calcs;
	start:
	cout << "\e[1;1H\e[2J" << explanation;
	unsigned short start;
	cout << "\nStart at: ";
	cin >> start;
	queue:
	cout << "\nWould you like to queue another calculation? (1/0): ";
	string que_str;
	cin >> que_str;
	if (que_str == "1") {
		unsigned short queue_num;
		cout << "\nNumber to queue: ";
		cin >> queue_num;
		queue_calcs.push_back(queue_num);
	}
	if (que_str != "0")
		goto queue;
	calc:
	cout << "\e[1;1H\e[2J";
	cout << "\nCalculating: " << start;
	unsigned short current = start;
	unsigned short reached[UINT16_MAX];
	reached[0] = start;
	unsigned short num_reached = 1;
	unsigned timer = 0x4000000;
	while(timer --> 0)
	{
		if(timer % 0x4000 == 0)
		{
			cout << "\033[H" << "\n\n\n" << "PROGRESS:\n|";
			for (unsigned short i = 0; i < 128; i++)
			{
				if (i < 128 - timer/0x80000)
					cout << '=';
				else if (i == 128 - timer/0x80000)
					cout << '>';
				else
					cout << ' ';
			}
			if (timer > 0x80000)
				cout << "| " << 0x80 - timer/0x80000 << " of 128";
			else if (timer > 0)
				cout << "| COMPLETE!        \n";
		}
		current = step(current);
		bool new_num = true;
		for (unsigned short i = 0; i < num_reached; i++)
			if (reached[i] == current)
			{
				new_num = false;
				break;
			}
		if (new_num)
		{
			if (num_reached == UINT16_MAX)
				goto end;
			reached[num_reached] = current;
			num_reached++;
		}
	}
	end:
	cout << "\n\n" << num_reached << (num_reached==UINT16_MAX ? "+ " : " ") << "possibilities found coming from " << start << "\n\n";
	bool concat = false;
	string ans1;
	if (queue_calcs.size() > 0)
		goto pre_ask2;
	ask1:
	cout << "List them? (1/0): ";
	cin >> ans1;
	if (ans1 == "0")
		goto pre_ask2;
	if (ans1 != "1")
		goto ask1;
	cout << "\n\n";
	if (num_reached > 0x40)
	{
		cout << "There are a lot of items to list\n";
		ask3:
		cout << "Concatenate? (1/0): ";
		string ans1;
		cin >> ans1;
		if (ans1 == "0")
			concat = false;
		else if (ans1 == "1")
			concat = true;
		else
			goto ask3;
	}
	cout << "\n" << reached[0];
	
	for (unsigned short i = 1; i < num_reached; i++)
	{
		if (i > 0x20 && i < num_reached - 0x20 && concat)
		{
			cout << ",\n...";
			i = num_reached - 0x20;
		}
		cout << ",\n" << reached[i];
	}
	pre_ask2:
	ofstream log("log.hex", ios_base::app);
	for (unsigned short i = 0; i < num_reached; i++)
		log << (char)reached[i] << (char)(reached[i]>>8);
	log << (char)0 << (char)0;
	cout << "\nFile recorded in \"log.hex\" in little endian, terminated by a 0\n\n";
	if (queue_calcs.size() > 0) {
		start = queue_calcs[queue_calcs.size()-1];
		queue_calcs.pop_back();
		goto calc;
	}
	ask2:
	cout << "Try another number? (1/0): ";
	string ans2;
	cin >> ans2;
	if (ans2 == "1")
	{
		cout << "\nDoing it again.\n\n";
		goto start;
	}
	if (ans2 == "0")
	{
		cout << "\nAll done.\n" << "\e[1;1H\e[2J";
		return 0;
	}
	goto ask2;
}
