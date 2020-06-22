#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const char* explanation =
	"This program is relevant to a certain mathematical problem:\n"
	"\n"
	" Let a \"prime factor connection\" be a connection from two whole numbers A and B, such that:\n"
	"	* A and B share a common prime factor C\n"
	"	* A plus C equals B\n"
	"	* A divided by C is not prime\n"
	"\n"
	" For any whole number N, let the \"prime connected set\" of N be the set of all whole numbers that satisfy the following:\n"
	"	* For any number X in this set, N is part of its prime connected set\n"
	"	* All numbers prime connected to N are in this set\n"
	"	* this set is the minimum possible size given the first two requirements\n"
	"\n"
	" Let S(N) be the size of the prime connected set of N\n"
	"\n"
	"The main program of this project calculates S(N) and records the prime connected set of N in the \"log.hex\" file\n"
	"This program reads the log.hex file\n"
	"\n"
;

int main()
{
	ifstream log ("log.hex", ifstream::binary);
	if (!log) return -1;

	log.seekg(0, log.end);
	unsigned long length = log.tellg();
	log.seekg(0, log.beg);

	char * buffer = new char [length];

	log.read(buffer, length);

	if (!log) return -1;
	
	if (length % 2 != 0) return -2;

	vector<unsigned short> starters;
	vector<unsigned> start_spots;
	bool new_set = true;

	start:
	cout << "\e[1;1H\e[2J" << explanation;

	for (unsigned short i = 0; i < length/2; i++)
	{
		if (new_set)
		{
			starters.push_back((unsigned short)buffer[i*2] + ((unsigned short)(buffer[i*2+1]) << 8));
			new_set = false;
		}
		if (buffer[i*2] == (char)0 && buffer[i*2+1] == (char)0)
		{
			new_set = true;
			start_spots.push_back(i*2);
		}
	}
	if (!new_set || starters.size() != start_spots.size()) return -2;

	cout << "There are " << starters.size() << " entries in the log: \n";

	for (unsigned short i = 0; i < starters.size(); i++)
	{
		cout <<
		"\n" <<
		(start_spots[i]-(i == 0 ? 0 : start_spots[i-1]))/2 <<
		(start_spots[i]-(i == 0 ? 0 : start_spots[i-1])==UINT16_MAX*2 ? "+ " : " ") <<
		"possibilities found coming from " <<
		starters[i] <<
		"\n";
	}

	ask1:
	cout << "\nWould you like to list any of them? (1/0): ";
	string ans;
	cin >> ans;
	if (ans == "0") {
		cout << "\nAll done.\n" << "\e[1;1H\e[2J";
		delete[] buffer;
		return 0;
	}
	if (ans != "1")
		goto ask1;
	
	unsigned short entry;
	unsigned short entry_num = -1;

	ask2:
	cout << "\nEntry to list: ";
	cin >> entry;
	cout << "\n";

	for (unsigned short i = 0; i < starters.size(); i++)
	{
		if (starters[i] == entry)
			entry_num = i;
	}

	if (entry_num > starters.size())
		goto ask2;
	
	bool concat = false;
	unsigned short list_size = (start_spots[entry_num]-(entry_num == 0 ? 0 : start_spots[entry_num-1]))/2;
	
	if (list_size > 64)
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

	cout << (unsigned short)buffer[start_spots[entry_num-1]] + ((unsigned short)(buffer[start_spots[entry_num-1]+1]) << 8);
	
	for (unsigned short i = 0; i < list_size; ++i)
	{
		if (i > 32 && i < list_size - 32 && concat)
		{
			cout << ",\n...";
			i = list_size - 32;
		}
		cout << ",\n" << (unsigned short)buffer[i*2+start_spots[entry_num-1]] + ((unsigned short)(buffer[i*2+1]) << 8);
	}

	cout << "\n\n";
	ask4:
	cout << "Read another entry? (1/0): ";
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