#ifndef _NETGRAD_H
#define _NETGRAD_H

#include <vector>
#include <fann.h>
#include <fann_cpp.h>
#include "wrapper.h"

std::vector<float> partialNet(FANN_Wrapper*, std::vector<float>, int,float);
std::vector<std::vector<float> > gradNet(FANN_Wrapper*, std::vector<float>,float);
std::vector<float> stepInput(std::vector<float>,int,float);

#endif
