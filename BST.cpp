#include "BST.h"

Q::Q() //CONSTRUCTOR FOR QUEUE CLASS
{
	head = NULL;
	tail = NULL;
	total = 0;
}
/*
Q::~Q()
{

	node* temp = tail;
	node* toDelete;
	if (temp != NULL) //CHECK TO MAKE SURE TAIL IS NOT NULL
	{
		while (temp != head) //DELETE FROM TAIL IN.
		{
			toDelete = temp;
			if (temp != NULL)
				temp = temp->prev;
			delete toDelete;
		}
	}
}
*/

void Q::enQ(string name)
{
	node* n = new node;
	n->name = name;
	n->next = NULL;//try this
	if (head == NULL)
	{
		head = n;
		tail = n;
	}
	else
	{
		node* oldtail = tail;
		oldtail->next = n;
		n->prev = oldtail;
		tail = n;
	}
	total++;
}

int Q::deQ(string& name)
{
	node* temp = head;
	if (head == NULL)
	{
		cout << "ERROR: DEQUEUE FROM EMPTY QUEUE" << endl;
		return(1);
	}
	if (head->next != NULL)
	{
		name = temp->name;
		head = head->next;
		head->prev = NULL; //Since it is the head of the line, no one is before.
	}
	else
	{
		name = head->name;
		head = NULL;
		tail = NULL;
	}
	total--;
	delete temp;
	return(0);
}



int Q::length() //returns total length of queue
{
	return total;
}

string Q::name() //returns the name that the head of the queue enters the sim.
{
	if (head == NULL)
		return(0);
	else
		return(head->name);
}

void Q::print() //Prints the queue, somewhat formatted
{
	node* ptr = head;
	while ((ptr != NULL) && (total != 0))
	{
		cout << ptr->name << endl;
		ptr = ptr->next;
	}
}



void BST::lumberjack(treenode* root) {
	if (root != NULL) {
		lumberjack(root->left);
		lumberjack(root->right);
		delete root;
	}
}

BST::BST() {
	root = NULL;
}

BST::~BST() {
	lumberjack(root);
}

void BST::addToBST(string title, int year, Q& actors) {
	treenode* temp = new treenode;
	temp->title = title;
	temp->year = year;
	temp->actors = actors;
	temp->left = temp->right = NULL;

	if (root == NULL)
		root = temp;
	else {
		treenode* Treeptr = root;
		treenode* target = NULL;
		while (Treeptr != NULL) {
			target = Treeptr;
			if (title.compare(Treeptr->title) < 0)
				Treeptr = Treeptr->left;
			else if (title.compare(Treeptr->title) > 0)
				Treeptr = Treeptr->right;
			else
				return;
		}
		if (title.compare(target->title) < 0)
			target->left = temp;
		else if (title.compare(target->title) > 0)
			target->right = temp;
		else
			return;
	}
}


void BST::printAll() {
	printInOrder(root);
}

void BST::printInOrder(treenode* t) {
	if (t != NULL) {
		printInOrder(t->left);
		cout << t->title << " (" << t->year << ")" << endl;
		t->actors.print();
		cout << endl;
		printInOrder(t->right);
	}
}

void BST::printTitles() {
	Titles(root);
}

void BST::Titles(treenode* t) {
	if (t != NULL) {
		Titles(t->left);
		cout << t->title << ", ";
		Titles(t->right);
	}
}

void BST::printActors(string title) {
	printActorsR(root, title);
}


void BST::printActorsR(treenode* t, string title) {
	if (t != NULL) {
		if (title < t->title) //Apparently this comparison works as well. Much easier to use than str.compare()
			printActorsR(t->left, title);
		else if (title > t->title)
			printActorsR(t->right, title);
		else if (title == t->title) {
			cout << "Actors in \"" << title << "\":" << endl;
			cout << setfill('=') << setw(25) << "=" << endl;
			t->actors.print();
			cout << endl;
		}
		else
			cout << "No film of that name found. Please try again." << endl;
	}
}

void BST::printMoviesOfActor(string name) {
	cout << "Films starring " << name << ":\n";
	cout << setfill('=') << setw(25) << "=" << endl;
	printMoviesOfActorR(root, name);
	cout << endl;
}

void BST::printMoviesOfActorR(treenode* t, string name) {
	if (t != NULL) {
		printMoviesOfActorR(t->left, name);
		int length = t->actors.length();
		Q temp;
		string actor;
		for (int i = 0; i < length; i++) {//Step through and compare each actor name
			t->actors.deQ(actor);
			if (actor == name)
				cout << t->title << endl;
			temp.enQ(actor);//fill up the temporary queue
		}
		t->actors = temp;//refill the original queue with the names.
		printMoviesOfActorR(t->right, name);
	}
}

void BST::printMoviesOfYear(int year) {
	cout << "Films from the year " << year << ":\n";
	cout << setfill('=') << setw(25) << "=" << endl;
	printMoviesOfYearR(root, year);
	cout << endl;
}

void BST::printMoviesOfYearR(treenode* t, int year) {
	if (t != NULL) {
		printMoviesOfYearR(t->left, year);
		if (year == t->year)
			cout << t->title << endl;
		printMoviesOfYearR(t->right, year);
	}
}