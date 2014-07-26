#include "Topography.h"
#include "Alpha.h"

using namespace std;

const float Eta=0.1;
const float alpha=0.5;

class BackPropagation
{
public:
	BackPropagation(const Topography & inputTopology,const vector<MyAlpha>& inputMatrices, const vector<int>& inputLabels);
	bool loopOverPass();
	bool ForwardPass();
	bool ReversePass();
	bool getResult( vector<MyAlpha>& inputMatrices,vector<int>& outputs);
	~BackPropagation();

private:
	Topography Arrangement;
	vector<MyAlpha> imageMatrices;
	vector<int> imageLabels;
	vector<float> inputVector;
	vector<float> expectedOutput;
	vector<vector<vector<float> > > updatedWieghts;
	vector<vector<vector<float> > > prevWieghts;
};