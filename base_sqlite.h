//
// Created by Tr on 13.01.2023.
//

#ifndef USEPROFILER_BASE_SQLITE_H
#define USEPROFILER_BASE_SQLITE_H

#include <iostream>
#include <cstring>
#include <assert.h>
#include "linklist.h"

#include "sqlite3.h"

class BD{
	private:
		static sqlite3 *bd;
	public:
		void testBd();
		bool openBd(const char* bdName);
		bool closeBd();
		bool request_insert_create(const char* sqlString);
		int getLastRowId();
		bool request_select(const char* sqlSting, int (*callback)(void*, int, char**, char**), void*);
		BD();
		virtual ~BD() = 0;
};

class BD_Sorts : BD {
        private:
		LinkedList* LL;
                void createSorts();
                void createSizeArs();
                void createResSorts();
	public:
		static int callback_LL(void* outputStruct, int countRec, char** argv, char** colName);
		static int callback_selectId(void* outputStruct, int countRec, char** argv, char** colName);

		LinkedList getLinkedList() const { return *LL;}

		int selectInLinkedList(const char*, int);
		int selectIdfromSorts(const char*, int&);
		int selectIdfromSizeArs(int, int&);
		int selectIdfromResSorts(int, int, int&);
		void insertIntoSorts(int, const char*);
		void insertIntoSizeArs(int);
		void insertIntoResSorts(int, int, int);

		BD_Sorts();
		~BD_Sorts();
};

#endif //USEPROFILER_BASE_SQLITE_H
