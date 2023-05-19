#ifndef _SuperClass_h_
#define _SuperClass_h_ value

#include "ProcessKey.h"
#include "base_sqlite.h"
#include "sorts.h"
#include <chrono>
#include <iostream>
#include <cstring>

class SuperClass{
	private:
		ProcessKey* keys;
		BD_Sorts* bd;
		Sorts* sorts;
		void baseInLinkedList();		
	public:
		void actionMeas();
		void actionList();
		void actionExport();
		SuperClass(int argc, char** argv);
		~SuperClass();
};

#endif