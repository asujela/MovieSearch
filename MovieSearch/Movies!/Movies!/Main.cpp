#include "Movie.h"
#include "BST.cpp"
#include "Hash.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void mainMenu(int& choice);
void addIO(BST<Movie>* bst, Hash<Movie>* h);
void removeIO(BST<Movie>* bst, Hash<Movie>* h);
void searchIO(BST<Movie>* bst);
void movieInfo(Movie m);
void fileInput(string filepath, BST<Movie>* bst, Hash<Movie>* h);
void printOutputFile(BST<Movie>* bst);

int main()
{
	std::ofstream ofs("BstEfficiency.txt", std::ios::out | std::ios::trunc);
	ofs.close();
	std::ofstream fout("HashEfficiency.txt", std::ios::out | std::ios::trunc);
	BST<Movie> movieBST;
	Hash<Movie> inputHash;
	int choice, internalChoice;
	string input;
	fileInput("MoviesList.txt", &movieBST, &inputHash);
	do {
		mainMenu(choice);
		if (choice == 1) {
			cout << "====================================" << endl;
			cout << "|             Add Data             |" << endl;
			cout << "====================================" << endl;
			cout << "Would you like to read a file or input data manually?" << endl;
			cout << "(1) Read a file" << endl;
			cout << "(2) Input manually" << endl;
			cout << "------------------------------------" << endl;
			cin >> internalChoice;
			if (internalChoice == 1) {
				cout << "Please enter the full file pathname you would like to use: ";
				cin >> input;
				fileInput(input, &movieBST, &inputHash);
			}
			else if (internalChoice == 2) {
				cout << "Please enter information for every field." << endl;
				addIO(&movieBST, &inputHash);
			}
			else {
				cout << "Please enter valid input." << endl;
			}
		}
		else if (choice == 2) {
			if (movieBST.getDepth() == 0) {
				cout << "Data must be added before anything can be deleted." << endl;
			}
			else {
				cout << "====================================" << endl;
				cout << "|           Delete Data            |" << endl;
				cout << "====================================" << endl;
				removeIO(&movieBST, &inputHash);
			}
		}
		else if (choice == 3) {
			if (movieBST.getDepth() == 0) {
				cout << "Data must be added before anything can be searched." << endl;
			}
			else {
				cout << "====================================" << endl;
				cout << "|         Searching Data           |" << endl;
				cout << "====================================" << endl;
				cout << "Please enter the title of movie you would like to search: " << endl;
				cout << "------------------------------------" << endl;
				searchIO(&movieBST);
			}
		}
		else if (choice == 4) {
			cout << "Listing data in hash table sequence..." << endl;
			inputHash.printAll();
		}
		else if (choice == 5) {
			cout << "Listing data in key sequence..." << endl;
			movieBST.setDisplay(2);
			cout << movieBST;
			cout << endl;
		}
		else if (choice == 6) {
			cout << "Printing indented tree..." << endl;
			movieBST.setDisplay(4);
			cout << movieBST;
			cout << endl;
		}
		else if (choice == 7) {
			cout << "Printing efficiency to file..." << endl;
			printOutputFile(&movieBST);
			inputHash.printAllFile(fout);
		}
		else if (choice == 8) {
			cout << "====================================" << endl;
			cout << "|         Cost vs Revenue          |" << endl;
			cout << "====================================" << endl;
			cout << "Please enter the title of movie you would like to compare: " << endl;
			cout << "------------------------------------" << endl;
			cin.ignore();
			getline(cin, input);
			Movie uMovie(input, "", "", "", "", 0, 0, 0);
			TreeNode<Movie> * result = movieBST.find(uMovie);
			Movie r = result->getData();
			cout << "Movie title: " << r.getTitle() << endl;
			cout << "Ratio of cost to revenue: " << r.getProductionBudget() * 1.0 / r.getWorldGross() << endl;
			system("pause");
		}
		else if (choice == 9) {
			cout << "Thanks for using this program!" << endl;
		}
	} while (choice != 9);

	fout.close();
	system("pause");
	return 0;
}

/*
*Pre: BST<Move> pointer
*Post: adds movie onto the bst
*/
void addIO(BST<Movie>* bst, Hash<Movie>* h)
{
	string t, r, d, g, l, q;
	int  cs, b, ts;

	q = "";

	while (q != "n") {
		cin.ignore();
		std::cout << "TITLE: ";
		getline(cin, t);

		std::cout << "DIRECTOR: ";
		getline(cin, d);

		std::cout << "GENRE: ";
		getline(cin, t);

		std::cout << "RELEASE DATE: ";
		getline(cin, r);

		std::cout << "RUN TIME: ";
		getline(cin, l);

		std::cout << "PRODUCTION BUDGET: ";
		std::cin >> cs;

		std::cout << "DOMESTIC GROSS: ";
		std::cin >> b;

		std::cout << "WORLD GROSS: ";
		std::cin >> ts;

		Movie m(t, r, d, g, l, cs, b, ts);
		Movie m2(t, r, d, g, l, cs, b, ts);
		bst->add(m);
		printOutputFile(bst);
        h->insert(&m2);
		std::cout << "Do you wish to add another movie?(Type 'y' for Yes and 'n' for No)" << std::endl;
		std::cin >> q;
	}

}

/*
*Pre: BST<Move> pointer
*Post: searches movie by title and initiates movieInfo function
*/
void searchIO(BST<Movie>* bst)
{
	string t;
	cin.ignore();
	getline(cin, t);

	Movie m(t, "", "","", "", 0, 0, 0);


	movieInfo((bst->find(m))->getData());
	printOutputFile(bst);
}

/*
*Pre: BST<Move> pointer
*Post: removes a movie by title from the BST
*/
void removeIO(BST<Movie>* bst, Hash<Movie>* h)
{
	string t;
	std::cout << "What is the title of the movie you want to delete? " << std::endl;
	cin >> t;

	Movie m(t, "","", "", "", 0, 0, 0);
	bst->remove(m);
	printOutputFile(bst);
	h->remove(&m);
}

/*
*Pre: Movie object
*Function prints out the data from the Movie Object based on user input
*/
void  movieInfo(Movie m)
{
	int in;
	while (1)
	{
		cout << "What do you want to know about the movie?(Type Number corresponding to Menu)" << endl;
		cout << "[1] Director" << endl;
		cout << "[2] Release Date" << endl;
		cout << "[3] Genre" << endl;
		cout << "[4] Movie Length" << endl;
		cout << "[5] Production Budget" << endl;
		cout << "[6] Domestic Gross" << endl;
		cout << "[7] World Gross" << endl;
		cout << "[8] Quit" << endl;

		cin >> in;

		if (in == 1)
		{
			cout << m.getDirector() << endl;
		}
		else if(in == 2)
		{
			cout << m.getReleaseDate() << endl;
		}
		else if (in == 3)
		{
			cout << m.getGenre() << endl;
		}

		else if (in == 4)
		{
			cout << m.getLength() << endl;
		}
		else if (in == 5)
		{
			cout << m.getProductionBudget()<< endl;
		}
		else if (in == 6)
		{
			cout << m.getDomesticGross() << endl;
		}
		else if (in == 7)
		{
			cout << m.getWorldGross() << endl;
		}
		else if(in == 8)
        {
            cout << "Exiting search..."<<endl;
            break;
        }
	}
}

/*
*Pre: BST<Move> pointer, string filepath
*Post: Adds the movies on the file to the BST
*/
void fileInput(string filepath, BST<Movie>* bst, Hash<Movie>* h)
{
	ifstream fin;
	string s, line;
	string t, r, d, g, l, q;
	int  cs, b, ts;
	int i = 0;

	while (1)
	{
		fin.open(filepath);
		if (!fin.is_open())
		{
			cout << "File not Found. Could you please type your filepath again: ";
			cin >> s;

			filepath = s;
		}
		else
		{
			break;
		}
	}

	while (getline(fin, line))
	{
	
		if (i == 0)
		{
			t = line;
			i++;
		}
		else if(i == 1)
		{
			r = line;
			i++;
		}
		else if (i == 2)
		{
			d = line;
			i++;
		}
		else if (i == 3)
		{
			g = line;
			i++;
		}
		else if (i == 4)
		{
			l= line;
			i++;
		}
		else if (i == 5)
		{
			cs = stoi(line);
			i++;
		}
		else if (i == 6)
		{
			b = stoi(line);
			i++;
		}
		else if (i == 7)
		{
			ts = stoi(line);			
			i = 0;

			Movie m(t, r, d, g, l, cs, b, ts);
			bst->add(m);
			printOutputFile(bst);
			h->insert(&m);
		}
	}

	fin.close();
}

/*
*Pre: BST<Move> pointer
*Prints from bst in order to a ouput file
*/
void printOutputFile(BST<Movie>* bst)
{
	ofstream fout;
	fout.open("BstEfficiency.txt", ios::app);
	fout << "Number of steps it took to finish your process:";
	fout<<bst->getSteps()<<endl;

	fout.close();
}

void mainMenu(int& choice)
{
	cout << "====================================" << endl;
	cout << "|             Main Menu            |" << endl;
	cout << "====================================" << endl;
	cout << "(1) Add new data" << endl;
	cout << "(2) Delete data" << endl;
	cout << "(3) Search data using primary key" << endl;
	cout << "(4) List data in hash table sequence" << endl;
	cout << "(5) List data in key sequence" << endl;
	cout << "(6) Print indented tree" << endl;
	cout << "(7) Efficiency" << endl;
	cout << "(8) Cost versus Revenue" << endl;
	cout << "(9) Quit" << endl;
	cout << "------------------------------------" << endl;
	cin >> choice;
	if (!cin) {
		while (choice < 1 || choice > 9) {
			cin.clear();
			cin.ignore();
			cout << "Please enter a valid integer." << endl;
			cin >> choice;
		}
	}
	system("cls");
}
