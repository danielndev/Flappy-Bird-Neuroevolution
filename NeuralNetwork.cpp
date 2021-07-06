#include <iostream>
#include <cstdlib> 
#include <vector>
#include <math.h>
#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int numInputs, int numHidden, int numOutputs) {
	generateNodes(numInputs, numHidden, numOutputs);
	generateWeights(numInputs, numHidden, numOutputs);
}

void NeuralNetwork::generateNodes(int numInputs, int numHidden, int numOutputs) {
    for (int i = 0; i < numInputs; i++) {
		inputNodeValues.push_back(NULL);
    }
	for (int i = 0; i < numHidden; i++) {
		hiddenNodeValues.push_back(NULL);
		hiddenNodeBiases.push_back(2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - 1);
	}
	for (int i = 0; i < numOutputs; i++) {
		outputNodeValues.push_back(NULL);
		outputNodeBiases.push_back(2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - 1);
	}
}

void NeuralNetwork::generateWeights(int numInputs, int numHidden, int numOutputs){
	for (int i = 0; i < numInputs; i++) {
		inputToHiddenWeights.push_back(std::vector<float>());
		for (int j = 0; j < numHidden; j++) {
			inputToHiddenWeights[i].push_back(2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - 1);
		}
	}
	for (int i = 0; i < numHidden; i++) {
		hiddenToOutputWeights.push_back(std::vector<float>());
		for (int j = 0; j < numOutputs; j++) {
			hiddenToOutputWeights[i].push_back(2 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - 1);
		}
	}
}

std::vector<float> NeuralNetwork::findOutputs(std::vector<float> inputs) {
	if (inputs.size() != inputNodeValues.size()) {
		std::cout << "Wrong number of inputs" << std::endl;
		return {};
	}

	for (int i = 0; i < inputs.size(); i++) {
		inputNodeValues[i] = inputs[i];
	}

	moveToNextLayer(1);
	moveToNextLayer(2);

	return outputNodeValues;
}

void NeuralNetwork::moveToNextLayer(int layerNum) {
	std::vector<float> nodes;
	std::vector<float> bias;
	std::vector<std::vector<float>> weights;
	std::vector<float>* nextLayer;

	if (layerNum == 1) {
		nodes = inputNodeValues;
		bias = hiddenNodeBiases;
		weights = inputToHiddenWeights;
		nextLayer = &hiddenNodeValues;
	}
	else {
		nodes = hiddenNodeValues;
		bias = outputNodeBiases;
		weights = hiddenToOutputWeights;
		nextLayer = &outputNodeValues;
	}

	for (int i = 0; i < (*nextLayer).size(); i++) {
		(*nextLayer)[i] = 0;
		for (int j = 0; j < weights.size(); j++) {
			(*nextLayer)[i] += weights[j][i] * nodes[j];
		}

		(*nextLayer)[i] = sigmoid((*nextLayer)[i] + bias[i]);
	}


}

float NeuralNetwork::sigmoid(float value) {
	return(1 / (1 + exp(-value)));
}

NeuralNetwork NeuralNetwork::mutate() {
	float mutationStrength = 0.05;
	float mutationRate = 0.1;

	for (int i = 0; i < inputToHiddenWeights.size(); i++) {
		for (int j = 0; j < inputToHiddenWeights[i].size(); j++) {
			if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < mutationRate) {
				inputToHiddenWeights[i][j] += static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * mutationStrength - mutationStrength / 2;
			}
		}
	}

	for (int i = 0; i < hiddenToOutputWeights.size(); i++) {
		for (int j = 0; j < hiddenToOutputWeights[i].size(); j++) {
			if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < mutationRate) {
				hiddenToOutputWeights[i][j] += static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * mutationStrength - mutationStrength / 2;
			}
		}
	}

	for (int i = 0; i < hiddenNodeBiases.size(); i++) {
		hiddenNodeBiases[i] += static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * mutationStrength - mutationStrength / 2;
	}

	for (int i = 0; i < outputNodeBiases.size(); i++) {
		outputNodeBiases[i] += static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * mutationStrength - mutationStrength / 2;
	}

	return *this;
}

