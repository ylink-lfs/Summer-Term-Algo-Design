#include <iostream>
#include <algorithm>
#include <string>
#include "huffman.h"

using std::string;
using std::sort;
using std::cerr;

//This function cannot be a member of the class
bool code_cmp(const pair<char, vector<char>>& p1, const pair<char, vector<char>>& p2);

//Public methods

huffman::huffman(const unordered_map<char, int>& char_frequency)
{
	generate_assist_queue(char_frequency);
	huffman_tree_root = build_tree();

	max_code_length = 0;
	vector<char> tmp_board;
	get_huffman_code(huffman_tree_root, tmp_board, huffman_code);
	sort(huffman_code.begin(), huffman_code.end(), code_cmp);
	mapping_position();
}

huffman::~huffman()
{
	clear();
}

void huffman::regeneration(const unordered_map<char, int>& char_frequency)
{
	clear();
	generate_assist_queue(char_frequency);
	huffman_tree_root = build_tree();

	vector<char> tmp_board;
	get_huffman_code(huffman_tree_root, tmp_board, huffman_code);
	sort(huffman_code.begin(), huffman_code.end(), code_cmp);
	mapping_position();
}

void huffman::encryption(ofstream& tar_stream, ifstream& src_stream)
{
	string mid_tran;
	while (getline(src_stream, mid_tran))
	{
		for (int i = 0; i < mid_tran.size(); i++)
		{
			auto it_to_tar_char = char_to_pos.find(mid_tran[i]);
			if (it_to_tar_char != char_to_pos.end())
			{
				for (auto it = huffman_code[it_to_tar_char->second].second.begin();
					it < huffman_code[it_to_tar_char->second].second.end(); it++)
				{
					tar_stream << *it;
				}
			}
			else
			{
				cerr << "No correspondent character record for \'" << mid_tran << "\' in current Huffman code.\n";
				cerr << "Operation terminated.\n";
				return;
			}
		}
	}
}

void huffman::decryption(ofstream& tar_stream, ifstream& src_stream)
{
	vector<char> comparion_board;
	char mid_tran;
	while (src_stream >> mid_tran)
	{
		comparion_board.push_back(mid_tran);
		if (comparion_board.size() > max_code_length)
		{
			cerr << "No correspondent character record for the given string in current Huffman code.\n";
			cerr << "Operation terminated.\n";
			return;
		}

		//Iterate implementation
		int index_in_codevec;
		for (index_in_codevec = 0; index_in_codevec < huffman_code.size(); index_in_codevec++)
		{
			if (comparion_board == huffman_code[index_in_codevec].second)
			{
				break;
			}
		}
		
		
		if (index_in_codevec < huffman_code.size())
		{
			tar_stream << huffman_code[index_in_codevec].first;
			comparion_board.clear();
		}
		else
		{
			continue;
		}
		//Map implementation
		/*
		auto it_to_code_pos = code_to_pos.find(comparion_board);
		if(it_to_code_pos != code_to_pos.end())
		{
			tar_stream << huffman_code[index_in_codevec].first;
			comparion_board.clear();
		}
		else
		{
			cerr << "No correspondent character record for \'" << mid_tran << "\' in current Huffman code.\n";
			cerr << "Operation terminated.\n";
			return;
		}
		*/
	}
}

void huffman::clear()
{
	wipe_tree(huffman_tree_root);
	huffman_code.clear();
	while (!assist_queue.empty())
		assist_queue.pop();
	max_code_length = 0;
	char_to_pos.clear();
	//code_to_pos.clear();
}

//The cost of this function is heavy. However, this implementation can protect
//original code in huffman class
vector<pair<char, vector<char>>> huffman::get_code()
{
	return huffman_code;
}

//Private methods

huffman::tree_node* huffman::build_tree()
{
	tree_node* father = assist_queue.top();
	while (assist_queue.size() > 1)
	{
		tree_node* lchild = assist_queue.top();
		assist_queue.pop();
		tree_node* rchild = assist_queue.top();
		assist_queue.pop();
		tree_node* cache = new tree_node;

		cache->data = '\0';
		cache->current_val = lchild->current_val + rchild->current_val;
		cache->left_branch = lchild;
		cache->right_branch = rchild;

		assist_queue.push(cache);
	}
	father = assist_queue.top();
	assist_queue.pop();
	if (father->left_branch)
	{
		father->current_val = father->left_branch->current_val + father->right_branch->current_val;
	}
	return father;
}

void huffman::get_huffman_code(tree_node* root, vector<char>& board, vector<pair<char, vector<char>>>& res)
{
	if (root->data)
	{
		res.push_back(make_pair(root->data, board));
		if (board.size() > max_code_length)
			max_code_length = board.size();
		return;
	}
	else
	{
		board.push_back('0');
		get_huffman_code(root->left_branch, board, res);
		board.pop_back();
		board.push_back('1');
		get_huffman_code(root->right_branch, board, res);
		board.pop_back();
		return;
	}
}

void huffman::generate_assist_queue(const unordered_map<char, int>& char_frequency)
{
	for (auto it = char_frequency.begin(); it != char_frequency.end(); it++)
	{
		tree_node* cache = new tree_node;
		cache->data = it->first;
		cache->current_val = it->second;
		cache->left_branch = cache->right_branch = nullptr;
		assist_queue.push(cache);
	}
}

void huffman::wipe_tree(tree_node* root)
{
	if (root == nullptr)
		return;
	wipe_tree(root->left_branch);
	wipe_tree(root->right_branch);
	delete root;
}

void huffman::mapping_position()
{
	for (auto it = huffman_code.begin(); it < huffman_code.end(); it++)
	{
		char_to_pos[it->first] = it - huffman_code.begin();
		//code_to_pos[it->second] = it - huffman_code.begin();
	}
}

bool code_cmp(const pair<char, vector<char>>& p1, const pair<char, vector<char>>& p2)
{
	return p1.first < p2.first;
}
