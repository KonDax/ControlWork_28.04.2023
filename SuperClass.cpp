#include "SuperClass.h"

SuperClass::SuperClass(int argc, char** argv){

	keys = new ProcessKey(argc, argv);

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
}

void SuperClass::baseInLinkedList(){
	const int* numSorts = keys->getNumSorts();
	for (int curStep = keys->getSteps(); curStep <= keys->getSize(); curStep += keys->getSteps()){
		for (int i = 0; i < keys->getCountSort(); i++){
			selectInLinkedList(keys->getNameSortById(numSorts[i]).c_str(), curStep);
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
    	selectIdfromSorts(nameSort.c_str(), idSort);

    	if (!idSort){
    		insertIntoSorts(numSorts[i], nameSort.c_str());
    	}
    }

	for (int curStep = keys->getSteps(); curStep <= keys->getSize(); curStep += keys->getSteps()) {
		idSizeAr = 0;
		for (int i = 0; i < keys->getCountSort(); i++) {
			idResSort = 0;			
			selectIdfromSorts(keys->getNameSortById(numSorts[i]).c_str(), idSort);

			selectIdfromSizeArs(curStep, idSizeAr);
			if (!idSizeAr){
				insertIntoSizeArs(curStep);
				selectIdfromSizeArs(curStep, idSizeAr);	
			}

			selectIdfromResSorts(idSort, idSizeAr, idResSort);
			if (!idResSort){
				time = get_time_ms(sortF[numSorts[i]-1], curStep);
				insertIntoResSorts(idSort, idSizeAr, time);
			}
		}
	}
}

void SuperClass::actionList(){
	baseInLinkedList();
	showLL();
}

void SuperClass::actionExport(){
	baseInLinkedList();
	writeLLToFile();
}