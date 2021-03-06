#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <cctype>
#include "huffman.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::unordered_map;

using std::make_pair;

void get_frequency(unordered_map<char, int>& src, ifstream& ist);
void show_menu(int& lower_flag, int& upperr_flag);
void judge_flag(int& flag, const int lower_flag, const int upper_flag);
bool switch_flag(huffman& hfm, const int flag);
void use_associated_stream(ifstream& ist);

void show_map(const unordered_map<char, int>& mp);

void output_code(const vector<pair<char, vector<char>>>& src);

unordered_map<char, int> frequency_map;

int main(void)
{
	cout << "Welcome to Huffman Encryption and Decryption program.\n";
	cout << "Generating the Huffman code according to the given DataFile.data...\n";

	
	ifstream datafile_stream("DataFile.data", std::ios_base::in);
	get_frequency(frequency_map, datafile_stream);

	huffman opt_huffman(frequency_map);

	cout << "Encrypting data given in ToBeTran.data...\n";
	ifstream tobetran_stream("ToBeTran.data", std::ios_base::in);
	ofstream code_stream("Code.txt");
	opt_huffman.encryption(code_stream, tobetran_stream);
	code_stream.close();
	

	cout << "Decrypting data given in CodeFile.data...\n";
	ifstream codefile_stream("CodeFile.data", std::ios_base::in);
	ofstream textfile_stream("Textfile.txt");
	opt_huffman.decryption(textfile_stream, codefile_stream);
	textfile_stream.close();

	int lower, upper, command_flag;
	cout << "Generation process complete.\n";
	cout << "Here are available operations:\n";
	show_menu(lower, upper);
	cout << "Wait for input:\n";
	cout << ">>";
	while (cin >> command_flag)
	{	
		judge_flag(command_flag, lower, upper);
		bool exit_sentinal = switch_flag(opt_huffman, command_flag);
		if (exit_sentinal)
		{
			break;
		}
		cout << "Type 7 to show menu again.\n";
		cout << "Wait for next input:\n";
		cout << ">>";
	}

	cout << "Program terminated. Bye!\n";
	datafile_stream.close();
	tobetran_stream.close();
	codefile_stream.close();

	system("pause");
	return 0;
}

void get_frequency(unordered_map<char, int>& src, ifstream& ist)
{
	string mid_tran;
	while (getline(ist, mid_tran))
	{
		int space_pos = mid_tran.find(' ', 0);
		string str_char = mid_tran.substr(0, space_pos);
		string str_frequency = mid_tran.substr(space_pos + 1, mid_tran.size() - 1 - space_pos);

		char tar_char;
		//Use digit to represent characters cannot be displayed
		if (str_char.size() != 1)
		{
			tar_char = stoi(str_char);
		}
		//Characters can be showed
		else
		{
			tar_char = str_char[0];
		}
		src.insert(make_pair(tar_char, stoi(str_frequency)));
	}
}

void show_menu(int& lower_flag, int& upperr_flag)
{
	cout << "1: Show source characters and their frequency\n";
	cout << "2: Show the content of ToBeTran.data\n";
	cout << "3: Show the content of Code.txt\n";
	cout << "4: Show the content of CodeFile.data\n";
	cout << "5: Show the content of Textfile.txt\n";
	cout << "6: Show Huffman code of characters\n";
	cout << "7: Show menu again\n";
	cout << "8: Exit\n";
	lower_flag = 1;
	upperr_flag = 8;
}

void judge_flag(int& flag, const int lower_flag, const int upper_flag)
{
	while (flag < lower_flag || flag > upper_flag)
	{
		cout << "Command digit should be bigger than " << lower_flag << " and smaller than " << upper_flag << ".\n";
		cout << "Please retype the command.\n";
		cout << "Wait for input:\n";
		cout << ">>";
		cin >> flag;
	}
}

bool switch_flag(huffman& hfm, const int flag)
{
	ifstream ist;
	switch (flag)
	{
	case 1:
	{
		cout << "The frequency match is showed below:\n";
		show_map(frequency_map);
	}
	break;
	case 2:
	{
		ist.open("ToBeTran.data", std::ios_base::in);
		use_associated_stream(ist);
		cout << endl;
		ist.close();
	}
	break;
	case 3:
	{
		ist.open("Code.txt", std::ios_base::in);
		use_associated_stream(ist);
		ist.close();
		cout << endl;
	}
	break;
	case 4:
	{
		ist.open("CodeFile.data", std::ios_base::in);
		use_associated_stream(ist);
		cout << endl;
		ist.close();
	}
	break;
	case 5:
	{
		ist.open("Textfile.txt", std::ios_base::in);
		use_associated_stream(ist);
		cout << endl;
		ist.close();
	}
	break;
	case 6:
	{
		vector<pair<char, vector<char>>> code_vec = hfm.get_code();
		output_code(code_vec);
	}
	break;
	case 7:
	{
		int dummy1, dummy2;
		show_menu(dummy1, dummy2);
	}
	break;
	case 8:
	{
		return true;
	}
	break;
	}
	return false;
}

void use_associated_stream(ifstream& ist)
{
	string mid_tran;
	while (getline(ist, mid_tran))
	{
		cout << mid_tran;
	}
}

void show_map(const unordered_map<char, int>& mp)
{
	for(auto it = mp.begin(); it != mp.end(); it++)
	{
		if (isalnum(it->first) || ispunct(it->first))
		{
			cout << it->first << '\t';
		}
		else
		{
			cout << "ASCII Code: " << int(it->first) << '\t';
		}
		cout << it->second;
		cout << endl;
	}
}

void output_code(const vector<pair<char, vector<char>>>& src)
{
	cout << "The code match is showed below:\n";
	for (auto it = src.begin(); it < src.end(); it++)
	{
		if (isalnum(it->first) || ispunct(it->first))
		{
			cout << it->first << '\t';
		}
		else
		{
			cout << "ASCII Code: " << int(it->first) << '\t';
		}
		for (auto sub_it = it->second.begin(); sub_it < it->second.end(); sub_it++)
		{
			cout << *sub_it;
		}
		cout << endl;
	}
}