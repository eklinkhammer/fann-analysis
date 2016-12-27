#include "inputs.h"
#include <iostream>

inputs scalarPermutations(const component &a, PermutationSettings settings) {
  inputs scalarPerms;

  for (int i = 0; i < settings.count; i++) {
    input onePerm = scalarMult(a, settings.scalar + settings.step*i);
    scalarPerms.push_back(onePerm);
  }

  return scalarPerms;
}

inputs vectorCombinations(const inputs &a, const inputs &b) {
  inputs vectorCombs;

  if (a.size() == 0) return b;
  if (b.size() == 0) return a;
  
  for (const auto a1 : a) {
    for (const auto b1 : b) {
      vectorCombs.push_back(vectorAdd(a1, b1));
    }
  }

  return vectorCombs;
}

inputs responseInput(components components, PermutationSettings settings) {
  inputs vectorInputs;

  for (const auto component : components) {
    vectorInputs = vectorCombinations(vectorInputs, scalarPermutations(component, settings));
  }
  
  return vectorInputs;
}

std::vector<InputResponse> response(components components, FANN_Wrapper* net, PermutationSettings permSettings, PartialSettings partialSettings) {

  std::vector<InputResponse> responses;

  std::cout << "In method: response; Number components: " << components.size() << std::endl;
  std::cout << "In method: response; Before calling method: responseInput" << std::endl;
  inputs rInput = responseInput(components, permSettings);
  std::cout << "In method: response; After calling method: responseInput" << std::endl;
  std::cout << "In method: response; Number responseInputs: " << rInput.size() << std::endl;
  for (const auto inp : rInput) {
    for (const auto x_i : inp) {
      std::cout << x_i << " ";
    }
    std::cout << std::endl;
  }

  for (const auto inputVector : rInput) {
    for (int i = 0; i < rInput[0].size(); i++) {
      vectorFs partials = partialNetFunction(net, inputVector, i, partialSettings.stepSize, partialSettings.count);
      InputResponse inputR;
      inputR.i = inputVector;
      inputR.index = i;
      inputR.partialValues = partials;
      responses.push_back(inputR);
    }
  }
  return responses;
}

vectorF vectorAdd(const vectorF& a, const vectorF& b) {

  vectorF result;
  for (int i = 0; i < a.size(); i++) {
    result.push_back(a[i] + b[i]);
  }

  return result;
}

vectorF scalarMult(const vectorF& a, float scalar) {
  vectorF result;
  for (int i = 0; i < a.size(); i++) {
    result.push_back(a[i] * scalar);
  }
  return result;
}
