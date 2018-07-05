#pragma once
#include <queue>
#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>

using std::priority_queue;
using std::pair;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::unordered_map;

class huffman
{
private:
	struct tree_node
	{
		char data;
		int current_val;
		tree_node* left_branch;
		tree_node* right_branch;
	};
	struct queue_cmp
	{
		bool operator()(tree_node* node1, tree_node* node2)
		{
			return node1->current_val > node2->current_val;
		}
	};

	priority_queue<tree_node*, vector<tree_node*>, queue_cmp> assist_queue;

	tree_node* huffman_tree_root;

	vector<pair<char, vector<char>>> huffman_code;

	unordered_map<char, int> char_to_pos;

	//unordered_map<vector<char>, int> code_to_pos;

	int max_code_length;

	tree_node* build_tree();
	void wipe_tree(tree_node* root);
	void generate_assist_queue(const unordered_map<char, int>& char_frequency);
	void get_huffman_code(tree_node* root, vector<char>& board, vector<pair<char, vector<char>>>& res);
	void mapping_position();
	
public:
	huffman() : huffman_tree_root(nullptr) {}
	huffman(const unordered_map<char, int>& char_frequency);
	~huffman();

	huffman& operator=(const huffman&) = delete;
	huffman(const huffman&) = delete;

	void regeneration(const unordered_map<char, int>& char_frequency);

	void encryption(ofstream& tar_stream, ifstream& src_stream);
	void decryption(ofstream& tar_stream, ifstream& src_stream);

	vector<pair<char, vector<char>>> get_code();

	void clear();
};
