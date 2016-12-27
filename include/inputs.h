#ifndef _INPUTS_H
#define _INPUTS_H

#include "netGradient.h"

using vectorF = std::vector<float>;
using vectorFs = std::vector<vectorF>;

using component = vectorF;
using components = std::vector<component>;

using input = vectorF;
using inputs = std::vector<input>;

struct PermutationSettings {
float scalar;
int count;
float step;
};

struct PartialSettings {
int count;
float stepSize;
int posInput;
};

struct InputResponse {
input i;
vectorFs partialValues;
int index;
};

// All scalar multiples of a vector
inputs scalarPermutations(const component&,PermutationSettings);

// All possible combinations under addition of two sets of vectors
inputs vectorCombinations(const inputs&, const inputs&);

// Points defined in space with components as basis vectors
inputs responseInput(components,PermutationSettings);

std::vector<InputResponse> response(components,FANN_Wrapper*,PermutationSettings,PartialSettings);
vectorF vectorAdd(const vectorF&, const vectorF&);
vectorF scalarMult(const vectorF&, float);

const component oneA_NW_zeroP = {0,1,0,0,0,0,0,0};
const component oneA_NE_zeroP = {1,0,0,0,0,0,0,0};
const component oneA_SW_zeroP = {0,0,1,0,0,0,0,0};
const component oneA_SE_zeroP = {0,0,0,1,0,0,0,0};

const component zeroA_oneP_NW = {0,0,0,0,0,1,0,0};
const component zeroA_oneP_NE = {0,0,0,0,1,0,0,0};
const component zeroA_oneP_SW = {0,0,0,0,0,0,1,0};
const component zeroA_oneP_SE = {0,0,0,0,0,0,0,1};

const component zeros         = {0,0,0,0,0,0,0,0};

#endif
