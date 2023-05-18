#include "SuperClass.h"

SuperClass::SuperClass(int argc, char** argv){

    processKey(argc, argv);

    createTables();

    switch(getAction()){
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

void SuperClass::createTables(){
	createSorts();	
	createSizeArs();
    createResSorts();

    std::string nameSort;
    const int* numSorts = getNumSorts();
    int idSort;
    for (int i = 0; i < getCountSort(); i++){
    	idSort = 0;
    	nameSort = getNameSortById(numSorts[i]);
    	selectIdfromSorts(nameSort.c_str(), idSort);

    	if (!idSort){
    		insertIntoSorts(numSorts[i], nameSort.c_str());
    	}
    }
}

void SuperClass::baseInLinkedList(){
	const int* numSorts = getNumSorts();
	for (int curStep = getSteps(); curStep <= getSize(); curStep += getSteps()){
		for (int i = 0; i < getCountSort(); i++){
			selectInLinkedList(getNameSortById(numSorts[i]).c_str(), curStep);
		}
	}
}

void SuperClass::actionMeas(){
	int time, idSort, idSizeAr, idResSort;
	const int* numSorts = getNumSorts();
	for (int curStep = getSteps(); curStep <= getSize(); curStep += getSteps()) {
		idSizeAr = 0;
		for (int i = 0; i < getCountSort(); i++) {
			idResSort = 0;			
			selectIdfromSorts(getNameSortById(numSorts[i]).c_str(), idSort);

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

	Data dt;
	LL->setHead(dt);
	do{
		dt.show();
	}while(LL->setNext(dt));
}

void SuperClass::actionExport(){
	baseInLinkedList();
	LL->writeToFileFromHead();
}