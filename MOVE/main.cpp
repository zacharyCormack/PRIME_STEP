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
	"This program interactively demonstrates what a prime connection is.\n"
	"The CALC program of this project calculates S(N) and records the prime connected set of N in the \"log.hex\" file\n"
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
	unsigned short next;
	switch (factors.size())
	{
	case 0:
		cout << "FATAL DIVISION ERROR";
		exit (-1);
	case 1:
		cout << "You are at: " << num << "\n";
		c_1_ask:
		cout << "Go to: ";
		cin >> next;
		if (next == 0)
			return next;
		if (next != num*2)
			goto c_1_ask;
		return num*2;
	case 2:
		cout << "You are at: " << num << "\n";
		c_2_ask:
		cout << "Go to: ";
		cin >> next;
		if (next == 0)
			return next;
		if ((next == num-factors[0] && factors[1] != 3) || (next == num-factors[1] && factors[0] != 3))
			return next;
		goto c_2_ask;
	default:
		cout << "You are at: " << num << "\n";
		c_3_ask:
		cout << "Go to: ";
		cin >> next;
		if (next == 0)
			return next;
		unsigned short check = 0;
		for (unsigned short i = 0; i < factors.size(); i++)
			if (num + factors[i] == next || num - factors[i] == next)
				check = next / factors[i];
		if (check == 0)
		{
			cout << "Invalid.\n";
			goto c_3_ask;
		}
		for (unsigned short i = 0; i < 54; i++)
		{
			if (primes[i] == check)
			{
				cout << "Invalid.\n";
				goto c_3_ask;
			}
			if (primes[i] > check)
				break;
		}
		return next;
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
	calc:
	cout << "\e[1;1H\e[2J";
	unsigned short current = start;
	cout << "At any time, type '0' to exit.\n";
	while(current != 0)
		current = step(current);
	cout << "\e[1;1H\e[2J";
	return 0;
}
