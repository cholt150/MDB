// MovieDB.cpp
// Code By Cory Holt

#include "BST.h"

int main() {
	cout << "Movie Database using BST" << endl;
	string filename = "mdb.txt";
	//getline(cin, filename);
	cout << "File to be read is: " << filename << endl;
	//BEGIN FILESTREAM
	ifstream fIn;
	fIn.open(filename);
	if (!fIn)
	{
		cout << "ERROR OPENING FILE. EXITING..." << endl;
		exit(1);
	}
	string title;
	string yearString;
	string trash;
	int year = 0;

	BST DB;
	

	while (!fIn.eof()) {
		Q actors;
		getline(fIn, title, '('); //Read input until delimiter character '(' is reached.
		int slength = title.length();
		if(slength > 0)
			while (title.back() == ' ')
				title.pop_back(); //Clean spaces from the end of the title.
		getline(fIn, yearString, ')');
		year = stoi(yearString);
		getline(fIn, trash);
		while ((fIn.peek() != '\n') && !fIn.eof()) {//loop while the next character is not a newline
			string actor;
			getline(fIn, actor);
			actors.enQ(actor);
		}
		while(fIn.peek() == '\n') // Remove Empty Lines
			getline(fIn, trash);
		DB.addToBST(title, year, actors);
	}
	cout << "Data reading DONE!" << endl;
	DB.printTitles();
	cout << endl;
	cout << endl;
	DB.printActors("Blazing Saddles");
	DB.printActors("Silent Running");
	DB.printActors("The Running Man");
	DB.printActors("Caddyshack");
	DB.printActors("Ferris Bueller's Day Off");
	DB.printMoviesOfActor("Tom Cruise");
	DB.printMoviesOfActor("Carrie Fisher");
	DB.printMoviesOfActor("Roger Moore");
	DB.printMoviesOfActor("Sean Connery");
	DB.printMoviesOfActor("Gene Wilder");
	DB.printMoviesOfYear(1975);
	DB.printMoviesOfYear(1985);
	return(0);
}