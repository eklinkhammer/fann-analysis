#include "netGradient.h"
#include <iostream>

const std::string configurationFile = "/Users/klinkhae/research/cpp_ws/fann-analysis/input/agent.policy";

int main() {

  FANN::neural_net* net = new FANN::neural_net(configurationFile);

  float one_poi[8] = {0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0};
  std::vector<float> input;
  for (int i = 0; i < 8; i++) {
    input.push_back(one_poi[i]);
  }

  FANN_Wrapper* wrapper = new FANN_Wrapper(net);
  std::vector<std::vector<float> > grad = gradNet(wrapper, input, 10);
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      std::cout << grad[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return 1;
}
