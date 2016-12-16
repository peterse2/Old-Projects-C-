/*
 * WordTree.ccp
 *
 *  Created on: Mar 5, 2015
 *  Author: Emily Peterson
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node{
	string word = NULL;
	node *left;
	node *right;

	node(string str){
		string word = str;
		node *left;
		node *right;
	}
};

class WordTree {
public:
	WordTree();

	void insert(node *&root, string newWord);
	node createTree(string filename);
	bool search(string key, node *start);
	node *root, *left, *right;
};

WordTree::WordTree(){
	root = NULL;
	left = NULL;
	right = NULL;
}

void WordTree::insert(node *&root, string newWord) {
	if (root == NULL) {
		root = new node(newWord);
		return;
	}
	else if (newWord < root->word) {
		insert(root->left, newWord);
	}
	else {
		insert(root->right, newWord);

	}
}

//read file in and create WordTree
node WordTree::createTree(string filename) {
	WordTree newTree = WordTree();
	ifstream in("filename");

	if (in.is_open()) {
		string word;
		while (in >> word) {
			insert(root, word);
			cout<< word << '\n';
		}
		return *&root;
	}
}

//search
//Case sensitive
bool WordTree::search(string key, node *start) {
	node *temp = start;

	while (temp != NULL)
	{
		if (temp->word == key)
			break;

		if (key > temp->word)
			temp = temp->right;
		else if (key < temp->word)
			temp = temp->left;
	}

	if (temp == NULL)
		return false;

	if (temp->word == key)
		return true;

	return false;
}

int main()
{
	int count = 0;
	WordTree one;
	WordTree two;
	WordTree three;

	one.createTree("TheTempest.txt");
	two.createTree("Hamlet.txt");
	three.createTree("RomeoAndJuliet.txt");

	cout << "Which plays, if any, contain the term ‘Hamlet’?/n"<<endl;
	if(one.search("Hamlet",one.root))
		cout << "The Tempest,";
	if(two.search("Hamlet", two.root))
		cout << " Hamlet, ";
	if(three.search("Hamlet", three.root))
		cout << " Romeo And Juliet, ";
	cout << endl;

	cout << "Which plays, if any, have a ‘friar’ in them?"<<endl;
	if(one.search("friar", one.root))
		cout << "The Tempest,";
	if(two.search("friar", two.root))
		cout << " Hamlet, ";
	if(three.search("friar", three.root))
		cout << " Romeo And Juliet, ";
	cout << endl;

	cout << "Which plays, if any, have a ‘Lady’ in them?"<<endl;
	if(one.search("Lady", one.root))
		cout << "The Tempest,";
	if(two.search("Lady", two.root))
		cout << " Hamlet, ";
	if(three.search("Lady", three.root))
		cout << " Romeo And Juliet, ";
	cout << endl;

	cout << "How many of the plays have the term ‘servant’?"<<endl;
	if(one.search("servant", one.root))
		count++;
	if(two.search("servant", two.root))
		count++;
	if(three.search("servant", three.root))
		count++;
	cout << count << endl;
	count = 0;

	cout << "How many of the plays discuss ‘Italy’?"<<endl;
	if(one.search("Italy", one.root))
		count++;
	if(two.search("Italy", two.root))
		count++;
	if(three.search("Italy", three.root))
		count++;
	cout << count << endl;
	count = 0;

	cout << "How many of the plays discuss ‘England??"<<endl;
	if(one.search("England", one.root))
		count++;
	if(two.search("England", two.root))
		count++;
	if(three.search("England", three.root))
		count++;
	cout << count << endl;
	count = 0;

	return 0;
}

