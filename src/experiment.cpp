#include "netGradient.h"
#include <iostream>

const std::string configurationFile = "/Users/klinkhae/research/cpp_ws/fann-analysis/input/agent.policy";

int main() {

  FANN::neural_net* net = new FANN::neural_net(configurationFile);

  std::cout << net->get_num_input();
  return 1;
}
