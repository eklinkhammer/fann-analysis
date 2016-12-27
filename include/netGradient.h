#ifndef _NETGRAD_H
#define _NETGRAD_H

#include <vector>
#include <fann.h>
#include <fann_cpp.h>
#include "wrapper.h"
#include <math.h>

std::vector<std::vector<float> > partialNetFunction(FANN_Wrapper*, std::vector<float>, int, float, int);
std::vector<float> partialNet(FANN_Wrapper*, std::vector<float>, int,float);
std::vector<std::vector<float> > gradNet(FANN_Wrapper*, std::vector<float>,float);
std::vector<float> stepInput(std::vector<float>,int,float);
float orientation(std::vector<float>);
float norm(std::vector<float>);
#endif
