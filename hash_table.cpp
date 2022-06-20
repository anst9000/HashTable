#include "hash_table.h"
#include <iostream>
#include <algorithm>

hash_table::item::item() :
		name("empty"), drink("empty"), next(NULL)
{
}

hash_table::item::item(std::string name, std::string drink) :
		name(name), drink(drink), next(NULL)
{
}

hash_table::hash_table()
{
	for (size_t el = 0; el < tableSize; el++)
	{
		hashTable[el] = new item();
	}
}

int hash_table::create(std::string key)
{
	int index = 0;
	int hash = 0;

	for (size_t i = 0; i < key.length(); i++)
	{
		hash += ((int) key[i]) * (i + 5) ^ (i + 3);
	}

	index = hash % tableSize;
	return index;
}

void hash_table::add_item(std::string name, std::string drink)
{
	int index = create(name);

	if (hashTable[index]->name == "empty")
	{
		hashTable[index]->name = name;
		hashTable[index]->drink = drink;
	}
	else
	{
		item *temp = hashTable[index];
		item *n = new item(name, drink);

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = n;
	}
}

size_t hash_table::bucket_size(size_t index)
{
	size_t count = 0;

	if (hashTable[index]->name != "empty")
	{
		count++;
		item *temp = hashTable[index];

		while (temp->next != NULL)
		{
			count++;
			temp = temp->next;
		}
	}

	return count;
}

void hash_table::print()
{
	int number;
	for (size_t el = 0; el < tableSize; el++)
	{
		number = bucket_size(el);

		std::cout << "----------------------" << std::endl;
		std::cout << "Bucket = " << el << std::endl;
		std::cout << hashTable[el]->name << std::endl;
		std::cout << hashTable[el]->drink << std::endl;
		std::cout << "# of items = " << number << std::endl;
		std::cout << "----------------------" << std::endl;
	}
}

void hash_table::printBucket(size_t index)
{
	item *temp = hashTable[index];

	if (temp->name == "empty")
	{
		std::cout << "Bucket " << index << " is empty.\n";
	}
	else
	{
		std::cout << "Bucket " << index << " contains following:\n";

		while (temp != NULL)
		{
			std::cout << "----------------------" << std::endl;
			std::cout << temp->name << std::endl;
			std::cout << temp->drink << std::endl;
			std::cout << "----------------------" << std::endl;

			temp = temp->next;
		}
	}
}

void hash_table::findDrink(std::string name)
{
	size_t index = create(name);
	bool foundName = false;
	std::string drink;

	item *temp = hashTable[index];

	while (temp != NULL)
	{
		if (temp->name == name)
		{
			foundName = true;
			drink = temp->drink;
		}

		temp = temp->next;
	}

	if (foundName == true)
	{
		std::cout << "Favorite drink = " << drink << std::endl;
	}
	else
	{
		std::cout << name << "'s info was not found in the hash table."
				<< std::endl;
	}
}

void hash_table::remove(std::string name)
{
	size_t index = create(name);
	item *delPtr;
	item *p1;
	item *p2;

	// Case 0 - bucket is empty
	if (hashTable[index]->name == "empty" && hashTable[index]->drink == "empty")
	{
		std::cout << name << " was not found in the hash table." << std::endl;
	}

	// Case 1 - only 1 item contained in bucket and has matching name
	else if (hashTable[index]->name == name && hashTable[index]->next == NULL)
	{
		hashTable[index]->name = "empty";
		hashTable[index]->drink = "empty";

		std::cout << name << " was removed from the hash table." << std::endl;
	}

	// Case 2 - match is located in the first item in the bucket, but
	// 			there are more items in the bucket
	else if (hashTable[index]->name == name)
	{
		delPtr = hashTable[index];
		hashTable[index] = hashTable[index]->next;
		delete delPtr;

		std::cout << name << " was removed from the hash table." << std::endl;
	}

	// Case 3 - bucket contains items but first item is not a match
	else
	{
		p1 = hashTable[index]->next;
		p2 = hashTable[index];

		while (p1 != NULL && p1->name != name)
		{
			p2 = p1;
			p1 = p1->next;
		}

		// Case 3.a - no match
		if (p1 == NULL)
		{
			std::cout << name << " was not found in the hash table."
					<< std::endl;
		}

		// Case 3.b - match is found
		else
		{
			delPtr = p1;
			p1 = p1->next;
			p2->next = p1;

			delete delPtr;
			std::cout << name << " was removed from the hash table."
					<< std::endl;
		}
	}

}

