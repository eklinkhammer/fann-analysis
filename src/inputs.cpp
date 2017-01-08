#include "inputs.h"
#include <iostream>

/*
void printInputResponse(InputResponse response) {
  std::cout << "Input: ";
  for (const auto x_i : response.i) {
    std:: cout << x_i << " ";
  }
  std::cout << "Position: " << response.index << std::endl;

  for (auto const dy : response.partialValues) {
    std::cout << weightedOrientation(dy) << " ";
  }
  std::cout << std::endl;
  }*/

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
  inputs rInput = responseInput(components, permSettings);

  for (const auto inputVector : rInput) {
    for (int i = 0; i < rInput[0].size(); i++) {
      vectorFs partials = partialNetFunction(net, inputVector, i, partialSettings.stepSize, partialSettings.count);
      for (int partialCount = 0; partialCount < partialSettings.count; partialCount++) {
	InputResponse inputR;
	inputR.i = inputVector;
	inputR.index = i;
	inputR.partialValues = partials[partialCount];
	inputR.i[i] += partialCount * partialSettings.stepSize;
	responses.push_back(inputR);
      }
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

PermutationSettings getDefaultPermutationSettings() {
  PermutationSettings permSettings;
  permSettings.scalar = 2;
  permSettings.count = 15;
  permSettings.step = 0.25;

  return permSettings;
}

PartialSettings getDefaultPartialSettings() {
  PartialSettings partialSettings;
  partialSettings.count = 25;
  partialSettings.stepSize = 0.25;
  return partialSettings;
}

void addInputs(std::vector<components>& comps) {
  // Empty Vector Responses
  components empty;
  empty.push_back(zeros);
  comps.push_back(empty);
  
  // NW Agent Responses
  components nwa;
  nwa.push_back(oneA_NW_zeroP);
  comps.push_back(nwa);

  // SW Agent Responses
  components swa;
  swa.push_back(oneA_SW_zeroP);
  comps.push_back(swa);

  // SE Agent Responses
  components sea;
  sea.push_back(oneA_SE_zeroP);
  comps.push_back(sea);
  
  // NE Agent Responses
  components nea;
  nea.push_back(oneA_NE_zeroP);
  comps.push_back(nea);
  
  // NW POI Responses
  components nwp;
  nwp.push_back(zeroA_oneP_NW);
  comps.push_back(nwp);
  
  // SW POI Responses
  components swp;
  swp.push_back(zeroA_oneP_SW);
  comps.push_back(swp);
  
  // SE POI Responses
  components sep;
  sep.push_back(zeroA_oneP_SE);
  comps.push_back(sep);
  
  // NE POI Responses
  components nep;
  nep.push_back(zeroA_oneP_NE);
  comps.push_back(nep);
  
  // NW,NE Agent - NW POI
  components comb1;
  comb1.push_back(oneA_NW_zeroP);
  comb1.push_back(oneA_NE_zeroP);
  comb1.push_back(zeroA_oneP_NW);
  comps.push_back(comb1);

  // NW, SW Agent, SW POI
  components comb2;
  comb2.push_back(oneA_NW_zeroP);
  comb2.push_back(oneA_SW_zeroP);
  comb2.push_back(zeroA_oneP_SW);
  comps.push_back(comb2);

  // NW, SW Agent - SW, NE, POI
  components comb3;
  comb3.push_back(oneA_NW_zeroP);
  comb3.push_back(oneA_SW_zeroP);
  comb3.push_back(zeroA_oneP_SW);
  comb3.push_back(zeroA_oneP_NE);
  comps.push_back(comb3);

  // NW Agent, NW, NE POI
  components comb4;
  comb4.push_back(oneA_NW_zeroP);
  comb4.push_back(zeroA_oneP_NE);
  comb4.push_back(zeroA_oneP_NW);
  comps.push_back(comb4);

  // SE Agent - NE, SE POI
  components comb5;
  comb5.push_back(oneA_SE_zeroP);
  comb5.push_back(zeroA_oneP_NE);
  comb5.push_back(zeroA_oneP_SE);
  comps.push_back(comb5);
  
  // All Agents - All POIs
  components comb6;
  comb6.push_back(oneA_NW_zeroP);
  comb6.push_back(oneA_NE_zeroP);
  comb6.push_back(oneA_SW_zeroP);
  comb6.push_back(oneA_SE_zeroP);
  comb6.push_back(zeroA_oneP_NW);
  comb6.push_back(zeroA_oneP_NE);
  comb6.push_back(zeroA_oneP_SW);
  comb6.push_back(zeroA_oneP_SE);
  comps.push_back(comb6);


  // All Agents - NW, SW POI
  components comb7;
  comb7.push_back(oneA_NW_zeroP);
  comb7.push_back(oneA_NE_zeroP);
  comb7.push_back(oneA_SW_zeroP);
  comb7.push_back(oneA_SE_zeroP);
  comb7.push_back(zeroA_oneP_NW);
  comb7.push_back(zeroA_oneP_SW);
  comps.push_back(comb7);
  
  // All Agents - NW, NE POI
  components comb8;
  comb8.push_back(oneA_NW_zeroP);
  comb8.push_back(oneA_NE_zeroP);
  comb8.push_back(oneA_SW_zeroP);
  comb8.push_back(oneA_SE_zeroP);
  comb8.push_back(zeroA_oneP_NW);
  comb8.push_back(zeroA_oneP_NE);
  comps.push_back(comb8);
  
  // NW, NE Agent - All POI
  components comb9;
  comb9.push_back(oneA_NW_zeroP);
  comb9.push_back(oneA_NE_zeroP);
  comb9.push_back(zeroA_oneP_NW);
  comb9.push_back(zeroA_oneP_NE);
  comb9.push_back(zeroA_oneP_SW);
  comb9.push_back(zeroA_oneP_SE);
  comps.push_back(comb9);
  
  // NW, SW Agent - All POI
  components comb0;
  comb0.push_back(oneA_NW_zeroP);
  comb0.push_back(oneA_SW_zeroP);
  comb0.push_back(zeroA_oneP_NW);
  comb0.push_back(zeroA_oneP_NE);
  comb0.push_back(zeroA_oneP_SW);
  comb0.push_back(zeroA_oneP_SE);
  comps.push_back(comb0);
}
