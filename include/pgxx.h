#ifndef _PQHELP_H
#define _PQHELP_H


#include <iostream>
#include <pqxx/pqxx>
#include <vector>

// General Postgres wrapper functions
bool tableExists(pqxx::work* W, std::string tableName);
bool createTable(pqxx::work* W, std::string tableName, std::string columns);
bool dropTable(pqxx::work* W, std::string tableName);
pqxx::connection* createConnection(std::string,std::string,std::string,std::string,std::string);

#endif
