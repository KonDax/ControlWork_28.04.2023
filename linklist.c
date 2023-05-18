#include "linklist.h"

int Node::countNodes = 0;

Node::Node(){
	next = nullptr;
	data = nullptr;
	nameNode = countNodes;
	countNodes++;
}

Node::Node(Data* d){
	next = nullptr;
	data = d;
	nameNode = countNodes;
	countNodes++;
}
Node::~Node() {
	if (data != nullptr){
		delete data;
	}
	if (next != nullptr){
		delete next;
	}
}

Data::Data(int count){
	countRes = count;
	fieldName = new char* [countRes];
	fieldValue = new char* [countRes];
}

Data::Data(){
	countRes = 0;
	fieldName = nullptr;
	fieldValue = nullptr;
}

Data::~Data() {
	if (fieldName != nullptr){
		for (int i = 0; i < countRes; i++){
			delete [] fieldName[i];
			delete [] fieldValue[i];
		delete [] fieldName;
		delete [] fieldValue;
		}
	}
}

void Data::show(){
	for (int i = 0; i < countRes; i++){
		std::cout << fieldName[i] << " : " << fieldValue[i] << "\t";
	}
	std::cout << std::endl;
}

void LinkedList::showLL(){
    Data dt;
    setHead(dt);
    do{
        dt.show();
    }while(setNext(dt));
}

LinkedList::LinkedList(){
	head = nullptr;
	tail = nullptr;
}
LinkedList::~LinkedList() {
	if (head != nullptr)
		delete head;
}

bool LinkedList::setHead(Data& d){
	if (head == nullptr)
		return 0;
	cur = head;
	d = *cur->data;
	return 1;
}

bool LinkedList::setNext(Data& d){
	if (cur->next == nullptr)
		return 0;
	cur = cur->next;
	d = *cur->data;
	return 1;
}


void LinkedList::putToEnd(Data* data) {
	Node* temp = new Node(data);
	if (head == nullptr){
		head = temp;
		tail = temp;
		return;
	}
	tail->next = temp;
	tail = temp;
}

/*
void LinkedList::putToEnd(const Data& data) {
	Data* d = new Data();
	*d = data;
	Node* temp = new Node(d);
	if (head == nullptr){
		head = temp;
		tail = temp;
		return;
	}
	tail->next = temp;
	tail = temp;
}
*/
void LinkedList::putToFront(const Data& data) {
	Data* d = new Data();
	*d = data;
	Node* temp = new Node(d);
	if (tail == nullptr)
		tail = temp;
	temp->next = head;
	head = temp;
}

bool LinkedList::getFromFront(Data& data) const {
	if (head == nullptr)
		return 1;
	data = *head->data;
	return 0;
}

bool LinkedList::getFromEnd(Data& data) const {
	if (tail == nullptr)
		return 1;
	data = *tail->data;
	return 0;
}

void LinkedList::popFront() {
	if (head == nullptr)
		return;
	Node* temp = head;
	head = head->next;
	temp->next = nullptr;
	delete temp;
}

void LinkedList::popBack() {
	if (tail == nullptr)
		return;
	tail = head;
	while(tail->next->next != nullptr){
		tail = tail->next;
	}
	delete tail->next;
	tail->next = nullptr;
}

void LinkedList::removeElements(int pos, int count) {
	Node* temp = head;
	Node* temp1;
	for (int i = 0; i < count+pos-1; i++){
		if (i == pos-1)
			temp1 = temp;
		temp = temp->next;
	}
	Node* temp2 = temp->next;
	temp->next = nullptr;
	delete temp1->next;
	temp1->next = temp2;
}

void LinkedList::insertElements(int pos, const Data& data) {
	Data* d = new Data();
	Node* newNode = new Node(d);
	Node* temp = head;
	for (int i = 0; i < pos-2; i++){
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
}

void LinkedList::writeToFileFromHead() const {
	Node* temp = head;
	FILE* f = fopen("text.txt", "w");
	for(int i = 1; temp != nullptr; i++){
		fprintf(f, "%d\t", i);
		for (int j = 0; j < temp->data->countRes; j++){
			int count = fprintf(f, "%s : %s\t", temp->data->fieldName[j], temp->data->fieldValue[j]);
		}
		fprintf(f, "\n");
		temp = temp->next;
	}
	fflush(f);
	fclose(f);
}

void LinkedList::writeToFileFromTail() const {
	FILE* f = fopen("text.txt", "w");
	for (int i = 0; i < head->countNodes; i++){
		Node* temp = head;
		for (int j = i; j < head->countNodes-1; j++){
			temp = temp->next;
		}
		int count = fprintf(f, "%d\t:\t%p\n", i+1, temp->data);
	}
	fflush(f);
	fclose(f);
}
