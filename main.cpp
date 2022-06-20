#include <iostream>
#include <cstdlib>
#include <string>

#include "hash_table.h"

using namespace std;

int main()
{
	hash_table table;
	std::string name = "";

	table.add_item("Paul", "Locha");
	table.add_item("Kim", "Iced mocha");
	table.add_item("Emma", "Strawberry smoothie");
	table.add_item("Annie", "Hot chocolate");
	table.add_item("Sarah", "Passion tea");
	table.add_item("Pepper", "Caramel mocha");
	table.add_item("Mike", "Chai tea");
	table.add_item("Steve", "Apple cider");
	table.add_item("Bill", "Root beer");
	table.add_item("Marie", "Skinny latte");
	table.add_item("Susan", "Water");
	table.add_item("Joe", "Green tea");

	while (name != "exit")
	{
		std::cout << "Search for: ";
		std::cin >> name;

		if (name != "exit")
		{
			table.findDrink(name);
		}
	}
	return 0;
}
