#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
//Queue class for actors
class Q {
public:
	Q();
	//~Q();

	void enQ(string name);
	int deQ(string& name);
	//int deQEnd(int& time, string& name, int& items);

	int length();
	string name();
	void print();

private:
	struct node
	{
		string name;

		node* next;
		node* prev;
	};
	typedef node* nodePtr;

	node* head;
	node* tail;
	int total;
};

//Tree class for DB

class BST {
public:
	BST(); //Constructor
	~BST(); //Destructor

	void addToBST(string title, int year, Q& actors);
	void printAll();
	void printTitles();
	void printActors(string title);
	void printMoviesOfActor(string name);
	void printMoviesOfYear(int year);
private:
	struct treenode {
		string title;
		int year;
		Q actors;

		treenode* left;
		treenode* right;
	};
	treenode* root;
	void lumberjack(treenode* root);//Recursively delete the tree.
	void printInOrder(treenode* t);
	void Titles(treenode* t);
	void printActorsR(treenode* t, string title);
	void printMoviesOfActorR(treenode* t, string name);
	void printMoviesOfYearR(treenode* t, int year);
};

#endif // !BST_H

