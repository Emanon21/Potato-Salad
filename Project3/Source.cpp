#include <iostream>
#include <string>
#include <fstream>
#include "GroceryItem.h"
#include <set>
using namespace std;


// Set function that reads a file and put that file into a set
// @param is a string reference
// @return a set
set<GroceryItem> readFile(const string& fileName) {
	ifstream file;
	ofstream datafile;
	file.open(fileName);

	set<GroceryItem> items;

	if (!file.is_open()) {
		cout << "Could not open file" << endl;
		return items;
	}


	/*A while loop that will iterate until the end of the file is read
	* read the name of the item and pass it into the Constructor with one param
	* find the data using the pointer reference and if not in set add it in the set
	* copy the name and quantity and pass it into the constructor with two param
	*/
	string itemName;
	while (!file.eof()) {
		file >> itemName;
		GroceryItem* itemPtr = new GroceryItem(itemName);
		auto existingItem = items.find(*itemPtr);

		if (existingItem != items.end()) {
			string existingName = existingItem->getName();
			int existingQuantity = existingItem->getQuantity();
			items.erase(existingItem);
			itemPtr = new GroceryItem(existingName, existingQuantity);
		}

		itemPtr->addItem();
		items.insert(*itemPtr);
		delete itemPtr;

	}
	file.close();

	datafile.open("frequency.txt");

	// Write set into frequency.txt file
	for (GroceryItem itemPtr : items) {
		datafile << itemPtr.getName() << " " << itemPtr.getQuantity() << endl;
	}

	
	datafile.close();
	return items;
};


/*
do while loop that will show the options first before input
switch case to switch between choices base on userChoice
case 1 is to find item in set and print name and quantity
case 2 print all item and quantity
case 3 print item name and the number of stars base on quantity
try and catch to output if there is a invalid input
*/
int main() {
	string userItem;
	int userChoice;
	bool found = false;
	set<GroceryItem> items = readFile("inventory.txt");
	
	do
	{
		cout << "1. Search for an item" << endl;
		cout << "2. Display all frequencies" << endl;
		cout << "3. Print histogram" << endl;
		cout << "4. Exit" << endl;
		cout << "Select choice: " << endl;
		cin >> userChoice;
	
		try {
			switch (userChoice)
			{
			case 1:
				items;
				cout << "Enter the name of the item to search for" << endl;
				cin >> userItem;
				found = false;

				for (GroceryItem item : items) {
					if (item.getName() == userItem) {
						cout << userItem << " " << item.getQuantity() << endl;
						found = true;
					}
				}

				if (!found) {
					throw runtime_error("Item not in inventory");
				}
				break;
			case 2:
				items;
				for (GroceryItem item : items) {
					cout << item.getName() << " " << item.getQuantity() << endl;
				}
				break;
			case 3:
				items;
				for (GroceryItem item : items) {
					cout << item.getName() << " " << string(item.getQuantity(), '*') << endl;
				}
				break;
			case 4:
				cout << "Good Bye!" << endl;
				break;
			default:
				throw runtime_error("Invalid number");
				break;
			}
		}
		catch(runtime_error& excpt){
			cout << excpt.what() << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (userChoice != 4);
}