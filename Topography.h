#ifndef TOPO_H 
#define TOPO_H
#include <iostream>
#include <vector>
#include "Helper.h"
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

const string saveFile="Weights.txt";

class Neuron{
private:
	vector<float> outputWeights;
	float output;
	bool isSigmoid;
public:
	Neuron(bool sigma):isSigmoid(sigma){}
	float getOutput(){return output;}
	float computeOutput(float weightedInput)
	{
		if (!isSigmoid)
			output= weightedInput;
		else 
			output= getSigmoid(weightedInput);
		return output;
	}
	bool setOutput(const float & out){output=out;return true;}
	bool setNumberOfConnections(int size) {outputWeights.resize(size); return true;};
	int  getNumberOfConnections() {return outputWeights.size(); };
	bool setWeightToConnection(int num, float weight) {outputWeights[num]=weight;return true;};
	float getWeightToConnection(int num) {return outputWeights[num];};
};


class Layer{
public:
	Layer(bool isSig)
	{
		sigmoid=isSig;
	}
	vector<Neuron> Neurons;
	bool sigmoid;
	
};
typedef vector<Layer>  Topology;

class Topography
{
public:	
	Topography(const vector<int> & layers);
	~Topography();
	Topology topology;
};

#endif