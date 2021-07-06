#ifndef NN_H
#define NN_H
#include <vector>

class NeuralNetwork {
	private:
		std::vector<float> inputNodeValues;
		std::vector<float> hiddenNodeValues;
		std::vector<float> outputNodeValues;

		std::vector<float> hiddenNodeBiases;
		std::vector<float> outputNodeBiases;

		std::vector<std::vector<float>> inputToHiddenWeights;
		std::vector<std::vector<float>> hiddenToOutputWeights;
	public:
		NeuralNetwork(int numInputs, int numHidden, int numOutputs);
		void generateNodes(int numInputs, int numHidden, int numOutputs);
		void generateWeights(int numInputs, int numHidden, int numOutputs);

		std::vector<float> findOutputs(std::vector<float> inputs);
		void moveToNextLayer(int layerNum);
		float sigmoid(float value);
		NeuralNetwork mutate();

};

#endif
