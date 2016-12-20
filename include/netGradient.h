#ifndef _NETGRAD_H
#define _NETGRAD_H

#include <vector>
#include <fann.h>
#include <fann_cpp.h>

fann_type* partialNet(FANN::neural_net*, fann_type*, int);
std::vector<fann_type*> gradNet(FANN::neural_net*, fann_type*);

fann_type* stepInput(fann_type*,int,int);

fann_type* copyFANN_Type(fann_type*, int, int);
#endif
