#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>

class hash_table
{
public:
	hash_table();
	hash_table(std::string, std::string);

	int create(std::string key);
	void add_item(std::string name, std::string drink);
	size_t bucket_size(size_t index);
	void print();

	void printBucket(size_t index);
	void findDrink(std::string name);

	void remove(std::string name);

private:
	static const int tableSize = 4;

	struct item
	{
		item();
		item(std::string, std::string);

		std::string name;
		std::string drink;
		item *next;
	};

	item *hashTable[tableSize];
};

#endif
