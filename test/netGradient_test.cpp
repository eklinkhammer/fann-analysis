#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "netGradient.h"
#include "inputs.h"

class NetGradientTest : public::testing::Test {
public:
  const std::string file = "/Users/klinkhae/research/cpp_ws/fann-analysis/input/agent.policy";
};

TEST_F(NetGradientTest, testOrientation) {
  // TODO
}

TEST_F(NetGradientTest, testNorm) {
  // TODO
}

TEST_F(NetGradientTest, testStepInput) {
  std::vector<float> input = {1,2,3,4};
  std::vector<float> output = stepInput(input, 0, 2.5);
  std::vector<float> expected = {3.5,2,3,4};

  EXPECT_EQ(expected.size(), output.size());
  
  for (int i = 0; i < expected.size(); i++) {
    EXPECT_FLOAT_EQ(expected[i], output[i]);
  }
}

TEST_F(NetGradientTest, testStepInputCopy) {
  std::vector<float> input = {1,2,3,4};
  std::vector<float> output = stepInput(input, 0, 2.5);
  std::vector<float> expected = {1,2,3,4};

  EXPECT_EQ(expected.size(), input.size());
  
  for (int i = 0; i < expected.size(); i++) {
    EXPECT_FLOAT_EQ(expected[i], input[i]);
  }
}

TEST_F(NetGradientTest, testPartialNet) {
  FANN::neural_net* net = new FANN::neural_net(this->file);
  FANN_Wrapper* wrapper = new FANN_Wrapper(net);

  input in     = {0,0,0,0,1,1,0,0};
  input output = partialNet(wrapper, in, 0, 3);

  input expected = {-0.024786731, -0.0075013638};

  for (int i = 0; i < expected.size(); i++) {
    EXPECT_FLOAT_EQ(expected[i], output[i]);
  }
}

TEST_F(NetGradientTest, testPartialNetFunction) {
  FANN::neural_net* net = new FANN::neural_net(this->file);
  FANN_Wrapper* wrapper = new FANN_Wrapper(net);

  input in     = {0,0,0,0,1,1,0,0};
  inputs output = partialNetFunction(wrapper, in, 0, 3, 2);
  inputs expected = {{-0.024786731, -0.0075013638},
		    {0.00084412098, 0.0001432697}};

  for (int i = 0; i < expected.size(); i++) {
    for (int j = 0; j < expected[0].size(); j++) {
      EXPECT_FLOAT_EQ(expected[i][j], output[i][j]);
    }
  }
}
