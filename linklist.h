#ifndef _linklist_h_
#define _linklist_h_

#include <fstream>
#include <iostream>
#include <cstring>

struct Data {
	int countRes;
	char** fieldName;
	char** fieldValue;
	void show();
 	void setData(int, char**, char**);
	Data();
	~Data();
};

struct Node {
	Node* next;
	int nameNode = 0;
	static int countNodes;
	Data *data;
	Node(Data*);
	Node();
	~Node();
};

class LinkedList {
	private :
		Node* head;
		Node* tail;
		Node* cur;
	public :
		LinkedList();
		~LinkedList();
		bool setHead(Data&);
		bool setNext(Data&);
		/* добавить элемент в конец списка */ 

		void showLL();

		void putToEnd(Data* data);
//		void putToEnd(const Data& data);
		/*добавить элемент вначало списка */
		void putToFront(const Data& data);
		/* извлечь элемент из начала списка */
		bool getFromFront(Data& data) const;
		/* извлечь элемент из конца списка */
		bool getFromEnd(Data& data) const;
		/* удалить первый элемент */
		void popFront();
		/* удалить последний элемент */
		void popBack();
		/* удалить N элементов начиная с позиции pos */
		void removeElements(int pos, int N);
		/* извлечь элемент из позиции pos списка*/
		void insertElements(int pos, const Data& data);
		/* записать элементы в файл начиная с головы 
		 * формат: [номер элемента]\t:\t[структура Data]\n
		 */
		void writeToFileFromHead() const;
		/* записать элементы в файл начиная с хвоста 
		 * формат файла: [номер элемента]\t:\t[структура Data]\n
		 * пути решения:
		 *		1. можно создать новый список, в который записать элементы наобором (требуется экстра память)
		 *		2. можно перебирать все элементы с каждым разом уменьшая на 1 перебираемые элементы 
		 */
		void writeToFileFromTail() const;
};

#endif
