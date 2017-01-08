#include "pgxx.h"

bool tableExists(pqxx::work* W, std::string tableName) {
  std::string command = "SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_name = '" + tableName + "')";
  
  pqxx::result E = W->exec(command);

  std::string t = "t";
  for (auto row : E) {
    int comp = t.compare(row[0].c_str());
    return comp == 0;
  }

  return false;
}

bool createTable(pqxx::work* W, std::string tableName, std::string columns) {
  try {
    std::string command = "CREATE TABLE " + tableName + " " + columns;
    W->exec(command);
    W->commit();
  } catch (const std::exception &e) {
    return false;
  }

  return true;
}

bool dropTable(pqxx::work* W, std::string tableName) {
  try {
    std::string command = "DROP TABLE " + tableName;
    W->exec(command);
  } catch (const std::exception &e) {
    return false;
  }
  return true;
}

pqxx::connection* createConnection(std::string user, std::string host, std::string password, std::string dbname, std::string port) {
  pqxx::connection* conn;
  std::string userS = "user=" + user + " ";
  std::string hostS = "host=" + host + " ";
  std::string passwordS = "password=" + password + " ";
  std::string dbnameS = "dbname=" + dbname + " ";
  std::string portS = "port=" + port + " ";
  
  conn = new pqxx::connection(
			      userS +
			      hostS +
			      passwordS +
			      dbnameS +
			      portS);
  return conn;
}

