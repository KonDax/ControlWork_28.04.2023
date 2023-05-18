#include "ProcessKey.h"

ProcessKey::ProcessKey(int argc, char** argv){
	action = 0;
	countSort = 0;
	size = 1000;
	steps = -1;
	numSortsToSort[0] = -1;
	sorts = {{"bubble", 1}, {"insertion", 2}, {"selection", 3}, {"count", 4},{"quick", 5}, {"merge", 6}};
	sortsNameById = {{1, "bubble"}, {2, "insertion"}, {3, "selection"}, {4, "count"}, {5, "quick"}, {6, "merge"}};
	for (int i = 1; i < argc; i++){
		procKey(argv[i]);
	}
	if (steps == -1){
		steps = size;
	}
	if (numSortsToSort[0] == -1){
		for (int i = 0; i < 6; numSortsToSort[i] = i+1, i++);
			countSort = 6;
	}
}

void ProcessKey::procKey(const std::string key) {
	static std::map<std::string, int> keys = {{"--meas", 1}, {"--list", 2}, {"--size", 5}, {"--steps", 4}, {"--sorts", 6}, {"--export", 3}};
	static int status = 0;
	if (!keys.count(key)) {
		if (status == 1){
			status = 0;
			size = std::stoi(key);
			return;
		}
		if (status == 2){
			status = 0;
			steps = std::stoi(key);
			return;
		}
		if (status == 3 && countSort < 6 && sorts.count(key)){
			numSortsToSort[countSort++] = sorts[key];
			return;
		}
		std::cerr << "nu pipec" << std::endl;
		return;
	}
	status = 0;
	switch (keys[key]){
		case 1:
		case 2 :
		case 3 :
			action = keys[key];
		break;
		case 6 :
			status = 3;
		break;
		case 4:
			status = 2;
		break;
		case 5:
			status = 1;
		break;
		default :
		break;
	}
}

void test_ProcessKey() {
#ifdef TEST_PR_KEY
	{
		int argc = 2;
		char **argv = new char *[5];

		argv[1] = new char [8];
		strcpy(argv[1], "--meas\0");

		ProcessKey keys(argc, argv);

		assert(keys.getAction() == ACTION::meas);
	}
	{
		int argc = 2;
		char **argv = new char *[5];

		argv[1] = new char [8];	// "--list\0";
		strcpy(argv[1], "--list\0");

		ProcessKey keys(argc, argv);

		assert(keys.getAction() == ACTION::list);
	}
	{
		int argc = 2;
		char **argv = new char *[5];

		argv[1] = new char [16];
		strcpy(argv[1], "--export\0");

		ProcessKey keys(argc, argv);

		assert(keys.getAction() == ACTION::expor);
	}
	{
		int argc = 5;
		char **argv = new char *[5];

		argv[1] = new char [16];
		strcpy(argv[1], "--sorts\0");
		argv[2] = new char [16];
		strcpy(argv[2], "bubble\0-");
		argv[3] = new char [16];
		strcpy(argv[3], "quick\0");
		argv[4] = new char [16];
		strcpy(argv[4] , "merge\0");

		ProcessKey keys(argc, argv);

		assert(!strcmp(argv[2], keys.getNameSortById(1).c_str()));
		assert(!strcmp(argv[3], keys.getNameSortById(4).c_str()));
		assert(!strcmp(argv[4], keys.getNameSortById(3).c_str()));

	}
#endif
}