#include "netGradient.h"
#include <iostream>


std::vector<std::vector<float> > gradNet(FANN_Wrapper* wrapper, std::vector<float> input, float stepSize) {
  std::vector<std::vector<float> > gradient;

  for (int i = 0; i < wrapper->getNumberInputs(); i++) {
    gradient.push_back(partialNet(wrapper, input, i, stepSize));
  }

  return gradient;
}

// index must be less than input.size()
std::vector<float> partialNet(FANN_Wrapper* wrapper, std::vector<float> input, int index, float stepSize) {

  std::vector<float> inputWithStep = stepInput(input, index, stepSize);

  std::vector<float> outputBase = wrapper->run(input);
  std::vector<float> outputStep = wrapper->run(inputWithStep);
  
  std::vector<float> partial;
  for (int i = 0; i < outputBase.size(); i++) {
    partial.push_back( (outputStep[i] - outputBase[i]) / stepSize);
  }

  return partial;
}

std::vector<float> stepInput (std::vector<float> input, int indexToChange, float stepSize) {
  std::vector<float> copy;
  for (const auto x : input) {
    copy.push_back(x);
  }

  copy[indexToChange] += stepSize;

  return copy;
}
