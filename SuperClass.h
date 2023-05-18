#ifndef _SuperClass_h_
#define _SuperClass_h_ value

#include "ProcessKey.h"
#include "base_sqlite.h"
#include "sorts.h"
#include <chrono>
#include <iostream>
#include <cstring>

class SuperClass : BD_Sorts, Sorts, ProcessKey{
	private:
		void baseInLinkedList();		
	public:
		void actionMeas();
		void actionList();
		void actionExport();
		SuperClass(int argc, char** argv);
};

#endif