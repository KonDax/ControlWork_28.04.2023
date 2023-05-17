//
// Created by Tr on 13.01.2023.
// c-style, in a future put property, function to class
//

#include "base_sqlite.h"

sqlite3* BD::bd = nullptr;

void BD_Sorts::createSorts(){
    request_insert_create("CREATE table if not exists Sorts(id integer primary key, nameSort text);");
}

void BD_Sorts::createSizeArs(){
    request_insert_create("CREATE table if not exists SizeArs(id integer primary key, SizeAr integer);");
}

void BD_Sorts::createResSorts(){
    request_insert_create("CREATE table if not exists ResSorts(id integer primary key, idSort integer, idSizeAr integer, durSort_ms integer, foreign key (idSort) references Sorts(ID) on update cascade on delete cascade, foreign key (idSizeAr) references SizeArs(ID) on update cascade on delete cascade);");
}

BD::BD(){
    openBd("Res.bd\0");
}

BD_Sorts::BD_Sorts(){
	LL = new LinkedList();
}

BD_Sorts::~BD_Sorts(){
	delete LL;
};

BD::~BD(){
    closeBd();
}

int BD_Sorts::callback_LL(void* outS, int countRec, char** argv, char** colName){
    LinkedList* temp = static_cast<LinkedList*>(outS);
    
    Data* data = new Data();

    data->countRes = countRec;
    data->fieldName = new char* [countRec];
    data->fieldValue = new char* [countRec];
 
    for (int i = 0; i < countRec; i++){
        data->fieldName[i] = new char [strlen(colName[i])];
        data->fieldValue[i] = new char [strlen(argv[i])];

        strcpy(data->fieldName[i], colName[i]);
        strcpy(data->fieldValue[i], argv[i]);
    }

    temp->putToEnd(data);

    return 0;
}

int BD_Sorts::selectInLinkedList(const char* nameSort, int SizeAr){

    std::string sqlString = "select idSort, nameSort, idSizeAr, SizeAr, durSort_ms from ResSorts rs\n";
    sqlString += "join Sorts ON rs.idSort = Sorts.id\n";
    sqlString += "join SizeArs ON rs.idSizeAr = SizeArs.id WHERE Sorts.nameSort = '";
    sqlString += (std::string)nameSort + "' and SizeArs.SizeAr = " + std::to_string(SizeAr);

    request_select(sqlString.c_str(), callback_LL, LL);
    return 0;
}

int BD_Sorts::callback_selectId(void* outS, int countRec, char** argv, char** colName){
    int* temp = (int*) outS;
    *temp = std::stoi(argv[0]);
    return 0;
}

int BD_Sorts::selectIdfromSizeArs(int SizeAr, int& answer){
    std::string sqlString = "SELECT id from SizeArs where SizeAr = '" + std::to_string(SizeAr) + "'";
    return request_select(sqlString.c_str(), callback_selectId, &answer);
}

int BD_Sorts::selectIdfromSorts(const char* nameSort, int& answer){
    std::string sqlString = "SELECT id from Sorts where nameSort = '" + (std::string)nameSort + "'";
    return request_select(sqlString.c_str(), callback_selectId, &answer);
}

int BD_Sorts::selectIdfromResSorts(int idSort, int idSizeAr, int& answer){
    std::string sqlString = "SELECT id from ResSorts where idSort = " + std::to_string(idSort);
    sqlString += " and idSizeAr = " + std::to_string(idSizeAr);
    return request_select(sqlString.c_str(), callback_selectId, &answer);
}

void BD_Sorts::insertIntoSorts(const char* nameSort){
    std::string sqlString = "INSERT INTO Sorts(nameSort) values ('" + (std::string)nameSort + "');";
    request_insert_create(sqlString.c_str());
}

void BD_Sorts::insertIntoSizeArs(int SizeAr){
    std::string sqlString = "INSERT INTO SizeArs(SizeAr) Values (" + std::to_string(SizeAr) + ");";
    request_insert_create(sqlString.c_str());
}

void BD_Sorts::insertIntoResSorts(int idSort, int idSizeAr, int durSort_ms){
    std::string sqlString = "INSERT INTO ResSorts(idSort, idSizeAr, durSort_ms) Values (";
    sqlString += std::to_string(idSort) + "," + std::to_string(idSizeAr) + "," +  std::to_string(durSort_ms) + ");";
    request_insert_create(sqlString.c_str());
}

void BD::testBd() {
    openBd("test.bd\0");
    request_insert_create("CREATE TABLE IF NOT EXISTS temp(id integer primary key autoincrement, name varchar(32));");
    request_insert_create("INSERT INTO temp(name) VALUES ('test'),('test1'),('test2'),('test3');");

    closeBd();
}
/*
 *  opend base data with name
 */
bool BD::openBd(const char* bdName) {
    int status = sqlite3_open(bdName, &bd);
    assert(status == SQLITE_OK);

    return status;
}

bool BD::closeBd() {
    int status = sqlite3_close(bd);
    assert(status == SQLITE_OK);
    return status;
}

bool BD::request_insert_create(const char* sqlString) {
    char* errMsg;
    int er = sqlite3_exec(bd, sqlString, nullptr, nullptr, &errMsg);
    if (er) {
        std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;   //std::cout
    }

    return er;
}
int BD::getLastRowId() {
    int last_id = sqlite3_last_insert_rowid(bd);
    return last_id;
}

bool BD::request_select(const char* sqlString, int (*callback)(void*, int, char**, char**), void* outputStruct) {
    char* errMsg;
    int er = sqlite3_exec(bd, sqlString, callback, outputStruct /*input arguments*/, &errMsg);

    if (er != SQLITE_OK) {
        std::cerr << "error request " << sqlString << " : " << errMsg << std::endl;
    }
    assert(er == SQLITE_OK);

    return er;
}
