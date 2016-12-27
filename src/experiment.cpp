#include "inputs.h"
#include <iostream>


// basic idea
// Define basis for input space (which values are nonzero)
// Get list of policy inputs based on input space
// For each input, get partial derivative along each component
int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cout << "Unexpected number of args. Must pass filename for policy." << std::endl;
  }
  
  std::string configFile = argv[1];

  FANN::neural_net* net = new FANN::neural_net(configFile);
  FANN_Wrapper* wrapper = new FANN_Wrapper(net);

  std::cout << "Wrapper created." << std::endl;
  
  PermutationSettings permSettings;
  permSettings.scalar = 2;
  permSettings.count = 15;
  permSettings.step = 0.25;

  PartialSettings partialSettings;
  partialSettings.count = 25;
  partialSettings.stepSize = 0.25;

  std::vector<components> comps;
  
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
  nwa.push_back(oneA_SW_zeroP);
  comps.push_back(swa);

  // SE Agent Responses
  components sea;
  nwa.push_back(oneA_SE_zeroP);
  comps.push_back(sea);
  
  // NE Agent Responses
  components nea;
  nwa.push_back(oneA_NE_zeroP);
  comps.push_back(nea);
  
  // NW POI Responses
  components nwp;
  nwa.push_back(zeroA_oneP_NW);
  comps.push_back(nwp);
  
  // SW POI Responses
  components swp;
  nwa.push_back(zeroA_oneP_SW);
  comps.push_back(swp);
  
  // SE POI Responses
  components sep;
  nwa.push_back(zeroA_oneP_SE);
  comps.push_back(sep);
  
  // NE POI Responses
  components nep;
  nwa.push_back(zeroA_oneP_NE);
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

  std::cout << "All sets of components created." << std::endl;
  
  std::vector<InputResponse> allResponses;
  
  for (const auto c : comps) {
    std::cout << "Before response." << std::endl;
    
    std::vector<InputResponse> resp = response(c, wrapper, permSettings, partialSettings);
    std::cout << "After response." << std::endl;
    for (const auto inp : resp) {
      allResponses.push_back(inp);
    }
  }

  for (const auto r : allResponses) {
    std::cout << "Input Vector: ";
    for (const auto x_i : r.i) {
      std::cout << x_i << " ";
    }
    std::cout << std::endl;

    std::cout << "Partial with respect to: " << r.index << std::endl;
    for (const auto vec : r.partialValues) {
      for (const auto dx : vec) {
	std::cout << dx << " ";
      }
      std::cout << "\t";
    }
    std::cout << std::endl;
  }

  return 1;
}
