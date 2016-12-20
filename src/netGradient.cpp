#include "netGradient.h"

fann_type* partialNet(FANN::neural_net* net, fann_type* input, int index) {
  fann_type step = 0.0001;
  unsigned int numberInputs = net->get_num_input();
  int signedNumberInputs = (int) numberInputs;
  int signedNumberOutputs = (int) net->get_num_outputs();

  fann_type* inputWithStep = stepInput(input, signedNumberInputs, index, step);
  
  fann_type* output = net->run(input);
  fann_type* outputWithStep = net->run(inputWithStep);

  fann_type* partial = new fann_type[signedNumberOutputs];
  for (int i = 0; i < signedNumberOutputs; i++) {
    partial[i] = (outputWithStep[i] - output[i]) / step;
  }

  delete inputWithStep[];
  return &partial;
}

fann_type* stepInput(fann_type* base, int size, int indexToChange, fann_type step) {
  fann_type* inputWithStep = copyFANN_Type(base,0,size);
  inputWithStep[indexToChange] += step;
  
  return &inputWithStep;
}

fann_type* copyFANN_Type(fann_type* input, int start, int end) {
  fann_type copy = new fann_type[end-start];
  for (int i = start; i < end; i++) {
    copy[i-start] = input[i];
  }

  return &copy;
}
