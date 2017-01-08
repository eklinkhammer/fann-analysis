#include "inputs.h"
#include <iostream>
#include <pqxx/pqxx>
#include "pgxx.h"

const std::string USER = "docker";
const std::string HOST = "0.0.0.0";
const std::string PW = "docker";
const std::string DB = "docker";
const std::string PORT = "32769";
const std::string SQL_COLUMNS = "(x1 float, x2 float, x3 float, x4 float, x5 float, x6 float, x7 float, x8 float, wrt int, y1 float, y2 float)";

void insertInputResponse(pqxx::connection* conn, std::string db, InputResponse inputR) {

  std::string i;
  for (const auto inp : inputR.i) {
    i = i + std::to_string(inp) + ", ";
  }

  i = i + std::to_string(inputR.index) + ", " + std::to_string(inputR.partialValues[0]) + ", " + std::to_string(inputR.partialValues[1]);
  
  std::string command = "INSERT INTO \"" + db + "\" (x1,x2,x3,x4,x5,x6,x7,x8,wrt,y1,y2) VALUES (" + i + ")";
  try {
    pqxx::work W(*conn);
    W.exec(command);
    W.commit();
  } catch (const std::exception& e) {

  }
}

// basic idea
// Define basis for input space (which values are nonzero)
// Get list of policy inputs based on input space
// For each input, get partial derivative along each component
int main(int argc, char *argv[]) {
  
  if (argc != 3) {
    std::cout << "Unexpected number of args. Must pass filename for policy and table name" << std::endl;
    exit(1);
  }
  
  std::string configFile = argv[1];
  std::string dbName = argv[2];

  std::cout << "Opening connection to database..." << std::endl;
  pqxx::connection* conn = createConnection(USER, HOST, PW, DB, PORT);
  pqxx::work W(*conn);

  if (tableExists(&W, dbName)) {
    std::cout << "Already have information on this policy." << std::endl;
    exit(1);
  } else {
    createTable(&W, dbName, SQL_COLUMNS);
  }
  
  std::cout << "Loading neural net from file..." << std::endl;
  FANN::neural_net* net = new FANN::neural_net(configFile);
  FANN_Wrapper* wrapper = new FANN_Wrapper(net);

  std::cout << "Getting input settings..." << std::endl;
  PermutationSettings permSettings = getDefaultPermutationSettings();
  PartialSettings partialSettings = getDefaultPartialSettings();
  std::vector<components> comps;
  addInputs(comps);

  std::cout << "Beginning Partial Calculations..." << std::endl;
  // For each set of unit vectors
  for (const auto c : comps) {
    std::vector<InputResponse> resp = response(c, wrapper, permSettings, partialSettings);

    //    std::cout << "Have responses. Inserting into database." << std::endl;
    for (const auto inputResponse : resp) {
      insertInputResponse(conn, dbName, inputResponse);
    }
    std::cout << ".";
  }

  std::cout << "Partial Calculations complete. There may be duplicate points." << std::endl;
  return 1;
}
