#ifndef _SuperClass_h_
#define _SuperClass_h_ value

#include "ProcessKey.h"
#include "base_sqlite.h"
#include "sorts.h"
#include <chrono>
#include <iostream>
#include <cstring>

class SuperClass : BD_Sorts, Sorts, ProcessKey{
	public:
		void createTables();
		void actionMeas();
		void actionList();
		void actionExport();
		void baseInLinkedList();		
		SuperClass(int argc, char** argv);
};

#endif