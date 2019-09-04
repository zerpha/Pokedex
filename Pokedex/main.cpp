// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by Team #11

#include "BinarySearchTree.h"  // BST ADT
#include "pokemon.h"
#include "HashTable.h"
#include "stack.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cctype>

using namespace std;

void searchHash(HashTable<string, Pokemon>& obj)
{
    string key;
    Pokemon value, returnItem;

    cout << "Enter a key to search for: ";
    cin >> key;

    value.setID(key);

    if (obj.search(key, value, returnItem))
    {
        cout << "Item Found: " << returnItem;
    }
    else
    {
        cout << "Can't find the object\n";
    }
}

// display function to pass to BST traverse functions
void display(Pokemon* anItem)
{
    //cout << "Displaying - " << anItem->getID() << " " << anItem->getName() << endl;
    cout << setw(10) << left << anItem->getID() << "  "
         << setw(10) << left << anItem->getName() << "  ";
    cout << fixed << setprecision(1) << setw(10) << right << anItem->getWeight() << "   ";
    cout << setw(10) << left << anItem->getType() << "  "
         << setw(10) << left << anItem->getGender() << "  ";
    cout << fixed << setprecision(1) << setw(10) << right << anItem->getHeight()
         << endl;
}

void check(bool success)
{
    if (success)
        cout << "Done." << endl;
    else
        cout << " Entry not in tree." << endl;
}

int IDCompare(Pokemon* poke1, Pokemon* poke2)
{
    int result;

    if (poke1->getID() < poke2->getID())
        result = 1;
    else if(poke1->getID() == poke2->getID())
        result = -1;
    else
        result = 0;

    return result;
}

int nameCompare(Pokemon* poke1, Pokemon* poke2)
{
    int result;

    if (poke1->getName() < poke2->getName())
        result = 1;
    else if(poke1->getName() == poke2->getName())
        result = -1;
    else
        result = 0;

    return result;
}


void printMenu(); //prints menu
void printHeader(); //prints header when displaying data
void about(); //prints names of developers
void undoDeletePrompt(); //prints the prompt for undoDelete (still need to work on that function)
void depthFirst(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2);
void removePokemon(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2, HashTable<string, Pokemon>& hashtable, Stack<Pokemon>& undo);
void indentedTree(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2);
void searchPokemon(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2, HashTable<string, Pokemon>& hashtable);
void undoDelete(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2, HashTable<string, Pokemon>& hastable, Stack<Pokemon>& undo);
void fileDisplay(Pokemon* anItem);
void insertPokemon(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2, HashTable<string, Pokemon>& hashtable);

int main()
{
	cout << "hello" << endl;
    Pokemon* list[50];
    BinarySearchTree<Pokemon*> tree1;
    BinarySearchTree<Pokemon*> tree2;
    Stack<Pokemon> undo;

    string ID, name, type, input, gender, option2;
    double weight;
    double height;
    char letter = '!', letter2 ='!', letter3 = '!';
    int count = 0; //counter for reading Pokemon.txt

    string inputfilename = "pokemon.txt";
    ifstream inputfile;
    inputfile.open(inputfilename);

    int filesize = 0;
    while(!inputfile.eof()) {
        getline(inputfile, input);
        filesize++;
    }
    inputfile.close();
    HashTable<string, Pokemon> hashtable(filesize);

    inputfile.open(inputfilename);
    if (inputfile.fail()) {
        cout << "\nError opening the input file: " << inputfilename << endl;
     //   exit(EXIT_FAILURE);
    }

    while (!inputfile.eof())
    {
        inputfile >> ID;
        inputfile.ignore(); //skip extra space
        getline(inputfile, name, ';');
        inputfile >> weight >> type >> gender >> height;
        Pokemon object(ID, name, weight, type, gender, height);
        hashtable.insert(object.getID(), object);

        //data read into dynamic memory
        list[count] = new Pokemon;
        list[count]->setID(ID);
        list[count]->setName(name);
        list[count]->setWeight(weight);
        list[count]->setType(type);
        list[count]->setGender(gender);
        list[count]->setHeight(height);
        tree1.insert(list[count], IDCompare);
        tree2.insert(list[count], nameCompare);
    }

    printMenu();

    while(letter != 'E')    // OPTIONS
    {
        cout << "\nYou are at the menu. To print the menu again, type 'H'.";
        cout << "\nPlease select an option: ";
        cin >> letter;
        letter = toupper(letter);

        switch(letter) {
            case 'D': {// print out the BST in Inorder, preorder, and postorder
                depthFirst(tree1, tree2);
                break;
            } //end case 'D' for Depth-First Traversals

            case 'B': {
                cout << "*****************************************************" << endl;
                cout << "\t\tBREADTH ORDER DISPLAY" << endl;
                cout << "*****************************************************" << endl;
                cout << "Which tree would you like to traverse?" << endl;
                cout << "\n1 - Tree 1" << endl;
                cout << "2 - Tree 2" << endl;
                cout << "\nPlease pick your tree: ";
                cin >> letter2;

                switch(letter2) {
                    case '1': {
                        if(tree1.isEmpty() == 0) {
                            printHeader();
                            tree1.BreadthOrder(display);
                            cout << endl;
                        }
                        else
                            cout << "BST is empty" << endl;
                        break;
                    }
                    case '2': {
                        if(tree2.isEmpty() == 0) {
                            printHeader();
                            tree2.BreadthOrder(display);
                            cout << endl;
                        }
                        else
                            cout << "BST is empty" << endl;
                        break;
                    }
                    default: {
                        cout << "Invalid number. Please try again." << endl;
                        break;
                    }
                } //end switch letter2
                break;
            } //end switch case B - Breadth First

            case 'S': {
                searchPokemon(tree1, tree2, hashtable);
                break;
            } //ends switch case S - Search

            case 'M': {
                Pokemon* finder;
                cout << "*****************************************************" << endl;
                cout << "\t\tSMALLEST POKEMON" << endl;
                cout << "*****************************************************" << endl;

                if(tree1.isEmpty() == 0)
                {
                    tree1.getSmallest(finder);
                    printHeader();
                    cout << setw(10) << left << finder->getID() << "  "
                         << setw(10) << left << finder->getName() << "  ";
                    cout << fixed << setprecision(1) << setw(10) << right << finder->getWeight() << "   ";
                    cout << setw(10) << left << finder->getType() << "  "
                         << setw(10) << left << finder->getGender() << "  ";
                    cout << fixed << setprecision(1) << setw(10) << right << finder->getHeight()
                         << endl;
                }
                else {
                    cout << "BST is empty" << endl << endl;
                }
                break;
            } //end switch case M - smallest pokemon

            case 'X': {
                Pokemon* finder;
                cout << "*****************************************************" << endl;
                cout << "\t\tLARGEST POKEMON" << endl;
                cout << "*****************************************************" << endl;
                if(tree1.isEmpty() == 0) // get largest node by unique key(ID)
                {
                    tree1.getLargest(finder);
                    printHeader();
                    cout << setw(10) << left << finder->getID() << "  "
                         << setw(10) << left << finder->getName() << "  ";
                    cout << fixed << setprecision(1) << setw(10) << right << finder->getWeight() << "   ";
                    cout << setw(10) << left << finder->getType() << "  "
                         << setw(10) << left << finder->getGender() << "  ";
                    cout << fixed << setprecision(1) << setw(10) << right << finder->getHeight()
                         << endl;
                }
                else
                    cout << "BST is empty" << endl;

                break;
            } //ends switch case X - largest pokemon

            case 'T': {
                indentedTree(tree1, tree2);
                break;
            } //ends switch case T - indented tree prints

            case 'K': {
                cout << "*****************************************************" << endl;
                cout << "\t\tHASHTABLE" << endl;
                cout << "*****************************************************" << endl;
                hashtable.display();
                cout << endl;
                cout << "The load factor for the hash table is: " << hashtable.loadFactor() << " %"<< endl;
                break;
            }

            case 'I': {
                insertPokemon(tree1, tree2, hashtable);
                break;
            }

            case 'A': {
                about();
                break;
            }

            case 'F': {
                tree1.inOrder(fileDisplay);
                cout << "You have successfully saved the Pokemon to your own Pokedex." << endl;
                break;
            }
            case 'R': {
                removePokemon(tree1, tree2, hashtable, undo);
                break;
            }

            case 'U': {
                undoDelete(tree1, tree2, hashtable, undo);
                break;
            }

            case 'H': {
                printMenu();
                break;
            }

            case 'E': {
                continue;
            }
            default: {
                cout << "Invalid entry. Please try again." << endl;
                continue;
            }
        } //end switch letter
    } //end while loop
} //end main
///////////////////////////////////////////////////////////////////////////End of main//////////////////////////////////////////////////////////////////////////////////////////////////////

void printMenu() {
    cout << "\n\t******************************************" << endl;
    cout << "\t*\tWELCOME TO YOUR POKEDEX          *" << endl;
    cout << "\t******************************************" << endl;
    cout << "\n\tD - Depth-First Traversals" << endl;
    cout << "\tB - Tree Breadth-First Traversals: Print by level" << endl;
    cout << "\tS - Search for a Pokemon" << endl;
    cout << "\tM - Find the smallest Pokemon" << endl;
    cout << "\tX - Find the largest Pokemon" << endl;
    cout << "\tT - Print the BST as an indented list" << endl;
    cout << "\tU - Undo a delete" << endl;
    cout << "\tI - Insert a new Pokemon" << endl;
    cout << "\tK - HashTable Functions" << endl;
    cout << "\tR - Delete a Pokemon" << endl;
    cout << "\tH - Help / Display Menu again" << endl;
    cout << "\tE - Exit" << endl;
}

void about() {
    cout << "\tProject done by:" << endl;
    cout << "\t- Amir Alaj" << endl;
    cout << "\t- Henry Nguyen" << endl;
    cout << "\t- Ehsan" << endl;
    cout << "\t- Kristi Luu" << endl;
}

void undoDeletePrompt() {
    cout << "This will be the undo-delete function." << endl;
    cout << "The user can undo the delete in the reverse order of the delete sequence." << endl;
    cout << "When the user selects “Save to file”, the undo stack is cleaned out " << endl;
    cout << "(no undo possible unless more delete occurs first)." << endl
    << "Add one more option to the menu: “Undo delete”. " << endl;
}

void depthFirst(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2) {
    char letter2 = '!', letter3 = '!';
    BinarySearchTree<Pokemon*> *treeSelected;

    cout << "*****************************************************" << endl;
    cout << "\t\tDEPTH-FIRST TRAVERSAL" << endl;
    cout << "*****************************************************" << endl;

    while (letter2 != '3') {
        cout << "\nWhich tree would you like to traverse?" << endl;
        cout << "\n1 - Tree 1" << endl;
        cout << "2 - Tree 2" << endl;
        cout << "Type 3 to exit." << endl;
        cout << "\nPlease pick your tree: ";
        cin >> letter2;

        switch(letter2) {
            case '1': {
                treeSelected = &tree1;
                break;
            }
            case '2': {
                treeSelected = &tree2;
                break;
            }
            case '3': {
                continue;
            }
            default: {
                cout << "Invalid number entered." << endl;
                continue;
            }
        }
        cout << "\nWhich order would you like to print?" << endl;
        cout << "\nI - Inorder" << endl;
        cout << "R - Preorder" << endl;
        cout << "P - Postorder" << endl;
        cout << "\nPlease pick your print order: ";
        cin >> letter3;
        letter3 = toupper(letter3);
            switch(letter3) {
                case 'I': {
                    if (treeSelected->isEmpty() == 0) {
                        printHeader();
                        treeSelected->inOrder(display);
                    }
                    else
                        cout << "BST is empty" << endl;
                    break;
                }
                case 'R': {
                    if (treeSelected->isEmpty() == 0) {
                        printHeader();
                        treeSelected->preOrder(display);
                    }
                    else
                        cout << "BST is empty" << endl;
                    break;
                }
                case 'P': {
                    if (treeSelected->isEmpty() == 0) {
                        printHeader();
                        treeSelected->postOrder(display);
                    }
                    else
                        cout << "BST is empty" << endl;
                    break;
                }
                default: {
                    cout << "This letter is not available. Please try again" << endl;
                    continue;
                }
            } //end switch letter3
    } //end while
}

void removePokemon(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2, HashTable<string, Pokemon>& hashtable, Stack<Pokemon>& undo){
    char letter2 = '!';
    Pokemon *temp = new Pokemon;
    Pokemon temp2;
    int foundCounter = 0;

    cout << "*****************************************************" << endl;
    cout << "\t\tREMOVE A POKEMON" << endl;
    cout << "*****************************************************" << endl;

    while (letter2 != 'E') {
        cout << "\nHow would you like to delete a Pokemon?" << endl;
        cout << "If you enter the wrong letter, you will be returned to the main menu." << endl;
        cout << "\nI - By ID" << endl;
        cout << "N - By Name" << endl;
        cout << "Type E to return to the main menu" << endl;
        cout << "\nEnter your option: ";
        cin >> letter2;
        letter2 = toupper(letter2);

            switch(letter2) {
                case 'I': {
                    string input;
                    cout << "\nDeleting by ID. . ." << endl;
                    cout << "Please enter the ID: ";
                    cin >> input;
                    cout << endl;
                    temp->setID(input);
                    while (tree1.remove(temp, IDCompare)) {
                        cout << temp->getID() << " has been deleted." << endl;
                        tree2.remove(temp, nameCompare);
                        hashtable.remove(input, temp2);
                        undo.push(*temp);
                    }
                    cout << "\nTree 2 is now. . ." << endl;
                    printHeader();
                    tree2.inOrder(display);
                    cout << endl;
                    cout << "Tree 1 is now. . ." << endl;
                    printHeader();
                    tree1.inOrder(display);
                    break;
                }
                case 'N': {
                    string input;
                    cout << "\nDeleting by name. . . " << endl;
                    cout<< "Please enter the name: ";
                    cin >> input;
                    cout << endl;
                    temp->setName(input);

                    while(tree2.remove(temp, nameCompare)) {
                        cout << temp->getName() << " "<< temp->getID() << " has been deleted." << endl;
                        tree1.remove(temp, IDCompare);
                        hashtable.remove(temp->getID(), temp2);
                        undo.push(*temp);
                        foundCounter++;
                    }
                    cout << "\nTree 2 is now. . ." << endl;
                    printHeader();
                    tree2.inOrder(display);
                    cout << endl;
                    cout << "Tree 1 is now. . ." << endl;
                    printHeader();
                    tree1.inOrder(display);

                    if(foundCounter == 0) {
                        cout << input << "was not found." << endl;
                    }

                    break;
                }
                case 'E': {
                    continue;
                }
                default: {
                    cout << "Incorrect letter entry. Please try again." << endl;
                    continue;
                }
            }
    }
    //delete temp;
}

void indentedTree(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2) {
    char letter2 = '!';

    cout << "*****************************************************" << endl;
    cout << "\t\t INDENTED POKEMON TREE" << endl;
    cout << "*****************************************************" << endl;

    while (letter2 != '3') {
        cout << "Which tree would you like to see?" << endl;
        cout << "\n1 - Tree 1" << endl;
        cout << "2 - Tree 2" << endl;
        cout << "Type 3 to return to the main menu" << endl;
        cout << "\nPlease select a tree: ";
        cin >> letter2;
            switch (letter2) {
                case '1': {
                    if(tree1.isEmpty() == 0) {
                        cout << "\nIndented Tree 1. . ." << endl;
                        tree1.print();
                        cout << endl;
                    }
                    else
                        cout << "BST is empty" << endl;
                    break;
                }
                case '2': {
                    if(tree2.isEmpty() == 0) {
                        cout << "\nIndented Tree 2. . ." << endl;
                        tree2.print();
                        cout << endl;
                    }
                    else
                        cout << "BST is empty" << endl;
                        break;
                    }
                case '3': {
                    continue;
                }
                default: {
                    cout << "Invalid option. Please try again." << endl;
                    continue;
                }
            }
    }
}

void searchPokemon(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2, HashTable<string,
                                                                                        Pokemon>& hashtable) {
    Pokemon* finder;
    char letter2 = '!', letter3 = '!';
    string ID, name;

    cout << "*****************************************************" << endl;
    cout << "\t\tSEARCH" << endl;
    cout << "*****************************************************" << endl;

    while (letter2 != 'E') {
        cout << "Where would you like to search?" << endl;
        cout << "\nT - Trees" << endl;
        cout << "H - HashTable" << endl;
        cout << "Type E to return to the main menu" << endl;
        cout << "\nPlease pick your option: ";
        cin >> letter2;
        letter2 = toupper(letter2);

        switch(letter2) {
            case 'T': {
                while (letter3 != 'E') {
                cout << "How would you like to search?" << endl;
                cout << "\nI - ID" << endl;
                cout << "N - Name" << endl;
                cout << "Type E to return to the main menu" << endl;

                cout << "\nPlease pick your option: ";
                cin >> letter3;
                letter3 = toupper(letter3);
                    switch(letter3) { //PICK ID OR NAME
                        case 'I': {
                            Pokemon temp;
                            cout << "\nType E to return to the main menu";
                            cout << "--------------------------" << endl;
                            cout << "\nPlease enter the ID: ";
                            cin >> ID;
                            temp.setID(ID);
                            if(tree1.getEntry(&temp, finder, IDCompare)) {
                                cout << "\nID " << finder->getID() << " was found!\n";
                                cout << "-------------------------" << endl;
                                cout << "Pokemon ID: " << finder->getID() << endl
                                        << "Pokemon Name: " << finder->getName() << endl
                                        << "Weight: " << finder->getWeight() << endl
                                        << "Type: " << finder->getType() << endl
                                        << "Gender: " << finder->getGender() << endl
                                        << "Height: " << finder->getHeight() << endl;
                                cout << "-------------------------" << endl;
                                }
                            else
                                cout << ID << " is not found" << endl;

                            break;
                            } //ends switch case I (letter3)
                        case 'N': {
                            Pokemon temp;
                            cout << "\nType E to return to the main menu" << endl;
                            cout << "--------------------------" << endl;
                            cout << "Please enter the name: ";
                            cin >> name;
                            temp.setName(name);
                            if(tree2.getEntry(&temp, finder, nameCompare)) {
                                cout << endl << finder->getName() << " was found!\n";
                                cout << "-------------------------" << endl;
                                cout << "Pokemon ID: " << finder->getID() << endl
                                        << "Pokemon Name: " << finder->getName() << endl
                                        << "Weight: " << finder->getWeight() << endl
                                        << "Type: " << finder->getType() << endl
                                        << "Gender: " << finder->getGender() << endl
                                        << "Height: " << finder->getHeight() << endl;
                                cout << "-------------------------" << endl << endl;
                            }
                            else
                                cout << name << " is not found" << endl;

                            break;
                        } //ends switch case N
                        case 'E': {
                            continue;
                        }
                        default: {
                            cout << "Invalid letter. Please try again." << endl;
                            continue;
                        }
                    } //end switch letter3
                } //end while loop for ID or Name
                break;
            } //end removing from Tree

            case 'H': {
                searchHash(hashtable);
                break;
            }
            case 'E': {
                continue;
            }

            default: {
                cout << "Invalid letter. Please try again." << endl;
                continue;
            }
        }
    }
}

void printHeader() {
    cout << "***********************************************************************" << endl;
    cout << "ID\t" << "    NAME\t" << "    WEIGHT" << "  TYPE\t" << " GENDER\t" << "\t WEIGHT";
    cout << "\n***********************************************************************" << endl;
}

void fileDisplay(Pokemon* anItem)
{
	static bool firstTime = true;
	ofstream fout;
	if (firstTime) {
		firstTime = false;
		fout.open("PersonalPokedex.txt");
	}
	else {
		fout.open("PersonalPokedex.txt", ios::app);
	}
	fout << anItem->getID() << " " << anItem->getName() << "; " << anItem->getWeight() << " "
		<< anItem->getType() << " " << anItem->getGender() << " " << anItem->getHeight() << endl;
	fout.close();
}

void insertPokemon(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2,
	HashTable<string, Pokemon>& hashtable)
{
	Pokemon* temp = new Pokemon;
	string ID, name, type, gender;
	double weight;
	double height;
    cout << "\n*************************";
	cout << "\nInsert your own Pokemon" << endl;
	cout << "*************************" << endl << endl;
	cout << "Enter the Pokemon ID: ";
	cin >> ID;
	cout << "Enter the Pokemon Name: ";
	cin >> name;
	cout << "Enter the Pokemon Type: ";
	cin >> type;
	cout << "Enter the Pokemon Gender: ";
	cin >> gender;
	cout << "Enter the Pokemon Weight: ";
	cin >> weight;
	cout << "Enter the Pokemon Height: ";
	cin >> height;
	temp->setID(ID);
	temp->setName(name);
	temp->setWeight(weight);
	temp->setType(type);
	temp->setGender(gender);
	temp->setHeight(height);

	tree1.insert(temp, IDCompare);
	tree2.insert(temp, nameCompare);
	hashtable.insert(ID, *(temp));

	cout << "\nTree 2 is now. . ." << endl;
    printHeader();
	tree2.inOrder(display);
	cout << endl;
	cout << "Tree 1 is now. . ." << endl;
    printHeader();
	tree1.inOrder(display);
	cout << endl;
	cout << "Hashtable is now . .  ." << endl;
	hashtable.display();
	cout << endl;
}

void undoDelete(BinarySearchTree<Pokemon*> &tree1, BinarySearchTree<Pokemon*> &tree2, HashTable<string, Pokemon>& hashtable, Stack<Pokemon>& undo)
{
	Pokemon **deletedItem;

	deletedItem = new Pokemon* [undo.getCount()];

	for (int i = 0; i < undo.getCount(); i++)
	{
		deletedItem[i] = new Pokemon;
	}

	const int size = undo.getCount();

	for (int i = 0; i < size; i++)
	{
		undo.pop(*deletedItem[i]);
		display(deletedItem[i]);
		tree1.insert(deletedItem[i], IDCompare);
		tree2.insert(deletedItem[i], nameCompare);
		hashtable.insert(deletedItem[i]->getID(), *deletedItem[i]);

	}

	cout << "Tree1:\n";
    printHeader();
    tree1.inOrder(display);
	cout << "\n\nTree2:\n";
    printHeader();
	tree2.inOrder(display);
	cout << "\n\nHashTable:\n";
	hashtable.display();
}
