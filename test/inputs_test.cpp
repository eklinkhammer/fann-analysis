#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "inputs.h"
#include <iostream>

class InputsTest : public::testing::Test {

};

TEST_F(InputsTest,testScalarPermutationsCountOne) {
  PermutationSettings settings;
  settings.scalar = 2;
  settings.count = 1;
  settings.step = 0.2;

  inputs output = scalarPermutations(oneA_NW_zeroP, settings);
  inputs expected = {{0,2.0,0,0,0,0,0,0}};

  for (int i = 0; i < expected.size(); i++) {
    for (int j = 0; j < expected[0].size(); j++) {
      EXPECT_FLOAT_EQ(expected[i][j], output[i][j]);
    }
  }
  
}

TEST_F(InputsTest,testScalarPermutationsCountTwo) {
  PermutationSettings settings;
  settings.scalar = 2;
  settings.count = 2;
  settings.step = 0.2;

  inputs output = scalarPermutations(oneA_NW_zeroP, settings);
  inputs expected = {{0,2.0,0,0,0,0,0,0},
		     {0,2.2,0,0,0,0,0,0}};

  for (int i = 0; i < expected.size(); i++) {
    for (int j = 0; j < expected[0].size(); j++) {
      EXPECT_FLOAT_EQ(expected[i][j], output[i][j]);
    }
  }
}

TEST_F(InputsTest,testScalarPermutationsRepeat) {
  PermutationSettings settings;
  settings.scalar = 2;
  settings.count = 2;
  settings.step = 0.2;

  inputs output = scalarPermutations(oneA_NW_zeroP, settings);
  settings.scalar = 3;
  inputs output2 = scalarPermutations(oneA_NW_zeroP, settings);

  
  inputs expected  = {{0,2.0,0,0,0,0,0,0},
		      {0,2.2,0,0,0,0,0,0}};
  inputs expected2 =  {{0,3.0,0,0,0,0,0,0},
		      {0,3.2,0,0,0,0,0,0}};

  for (int i = 0; i < expected.size(); i++) {
    for (int j = 0; j < expected[0].size(); j++) {
      EXPECT_FLOAT_EQ(expected[i][j], output[i][j]);
    }
  }

  for (int i = 0; i < expected2.size(); i++) {
    for (int j = 0; j < expected2[0].size(); j++) {
      EXPECT_FLOAT_EQ(expected2[i][j], output2[i][j]);
    }
  }
}

TEST_F(InputsTest, testVectorCombinationsSingleVector) {
  inputs single = {zeros};
  inputs empty;

  inputs output = vectorCombinations(single, empty);

  for (int i = 0; i < output.size(); i++) {
    for (int j = 0; j < output[0].size(); j++) {
      EXPECT_FLOAT_EQ(output[i][j], single[i][j]);
    }
  }
}

TEST_F(InputsTest, testVectorCombinationsTwoSingleVector) {
  inputs a = {oneA_NW_zeroP};
  inputs b = {oneA_SW_zeroP};

  inputs output = vectorCombinations(a, b);

  inputs expected = {{0,1.0,1.0,0,0,0,0,0}};
  for (int i = 0; i < output.size(); i++) {
    for (int j = 0; j < output[0].size(); j++) {
      EXPECT_FLOAT_EQ(expected[i][j], output[i][j]);
    }
  }
}

TEST_F(InputsTest, testVectorCombinationsTwoDoubleVectors) {
  inputs a = {oneA_NW_zeroP, zeroA_oneP_SE};
  inputs b = {oneA_SW_zeroP, oneA_NW_zeroP};

  inputs output = vectorCombinations(a, b);

  inputs expected = {{0,1.0,1.0,0,0,0,0,0},
		     {0,2.0,0.0,0.0,0,0,0},
		     {0,0,1.0,0,0,0,0,1.0},
		     {0,1.0,0,0,0,0,0,1.0}};
  for (int i = 0; i < output.size(); i++) {
    for (int j = 0; j < output[0].size(); j++) {
      EXPECT_FLOAT_EQ(expected[i][j], output[i][j]);
    }
  }
}

TEST_F(InputsTest, testResponseInput) {
  components a = {oneA_NW_zeroP, zeroA_oneP_NW};
  PermutationSettings settings;
  settings.scalar = 2;
  settings.count = 2;
  settings.step = 0.5;

  inputs output = responseInput(a, settings);

  inputs expected = {{0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0},
		     {0.0, 2.0, 0.0, 0.0, 0.0, 2.5, 0.0, 0.0},
		     {0.0, 2.5, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0},
		     {0.0, 2.5, 0.0, 0.0, 0.0, 2.5, 0.0, 0.0}};

   for (int i = 0; i < output.size(); i++) {
    for (int j = 0; j < output[0].size(); j++) {
      EXPECT_FLOAT_EQ(expected[i][j], output[i][j]);
    }
  }
}

TEST_F(InputsTest, testResponse) {
  components a = {oneA_NW_zeroP, zeroA_oneP_NW};
  PermutationSettings settings;
  settings.scalar = 2;
  settings.count = 2;
  settings.step = 0.5;
  PartialSettings partialSettings;
  partialSettings.count = 1;
  partialSettings.stepSize = 1;
  partialSettings.posInput = 0;
  
  const std::string configurationFile = "../input/agent.policy";
  FANN::neural_net* net = new FANN::neural_net(configurationFile);
  FANN_Wrapper* wrapper = new FANN_Wrapper(net);

  std::vector<InputResponse> output = response(a, wrapper, settings, partialSettings);
  inputs expected = {{0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0},
		     {0.0, 2.0, 0.0, 0.0, 0.0, 2.5, 0.0, 0.0},
		     {0.0, 2.5, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0},
		     {0.0, 2.5, 0.0, 0.0, 0.0, 2.5, 0.0, 0.0}};
  for (const auto v : expected) {
    for (const auto i : wrapper->run(v)) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
}
