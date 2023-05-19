#include "SuperClass.h"

SuperClass::SuperClass(int argc, char** argv){

	keys = new ProcessKey(argc, argv);
	bd = new BD_Sorts();
	sorts = new Sorts();

    switch(keys->getAction()){
    	case ACTION::meas:
    		actionMeas();
    		break;
    	case ACTION::list:
    		actionList();
    		break;
    	case ACTION::expor:
    		actionExport();
    		break;
    }
}

SuperClass::~SuperClass(){
	delete keys;
	delete bd;
	delete sorts;
}

void SuperClass::baseInLinkedList(){
	const int* numSorts = keys->getNumSorts();
	for (int curStep = keys->getSteps(); curStep <= keys->getSize(); curStep += keys->getSteps()){
		for (int i = 0; i < keys->getCountSort(); i++){
			bd->selectInLinkedList(keys->getNameSortById(numSorts[i]).c_str(), curStep);
		}
	}
}

void SuperClass::actionMeas(){
	std::string nameSort;
    const int* numSorts = keys->getNumSorts();
	int time, idSort, idSizeAr, idResSort;
    for (int i = 0; i < keys->getCountSort(); i++){
    	idSort = 0;
    	nameSort = keys->getNameSortById(numSorts[i]);
    	bd->selectIdfromSorts(nameSort.c_str(), idSort);

    	if (!idSort){
    		bd->insertIntoSorts(numSorts[i], nameSort.c_str());
    	}
    }

	for (int curStep = keys->getSteps(); curStep <= keys->getSize(); curStep += keys->getSteps()) {
		idSizeAr = 0;
		for (int i = 0; i < keys->getCountSort(); i++) {
			idResSort = 0;			
			bd->selectIdfromSorts(keys->getNameSortById(numSorts[i]).c_str(), idSort);

			bd->selectIdfromSizeArs(curStep, idSizeAr);
			if (!idSizeAr){
				bd->insertIntoSizeArs(curStep);
				bd->selectIdfromSizeArs(curStep, idSizeAr);	
			}

			bd->selectIdfromResSorts(idSort, idSizeAr, idResSort);
			if (!idResSort){
				time = sorts->get_time_ms(sorts->getSortById(numSorts[i]-1), curStep);
				bd->insertIntoResSorts(idSort, idSizeAr, time);
			}
		}
	}
}

void SuperClass::actionList(){
	baseInLinkedList();
	bd->showLL();
}

void SuperClass::actionExport(){
	baseInLinkedList();
	bd->writeLLToFile();
}