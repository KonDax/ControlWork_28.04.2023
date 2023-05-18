#ifndef _ProcessKey_h_
#define _ProcessKey_h_ value

#include <iostream>
#include <cstring>
#include <map>

enum ACTION {
	meas = 1,
	list = 2,
	expor = 3,
};

class ProcessKey{
	private:
		std::map<std::string, int> sorts;
		std::map<int, std::string> sortsNameById;
		int action;
		int size;
		int steps;
		int numSortsToSort[6];
		int countSort;
	public:

		int getIdSort(const std::string& sortName) const { return sorts.at(sortName); }
		std::string getNameSortById(int idSort) const { return sortsNameById.at(idSort); }
		int getAction() const { return action; }
		int getSize() const { return size; }
		int getSteps() const { return steps; }
		const int* getNumSorts() const { return &numSortsToSort[0]; }
		int getCountSort() const { return countSort; }

		ProcessKey(int argc, char** argv);
		void procKey(const std::string key);
};

void test_ProcessKey();

#endif