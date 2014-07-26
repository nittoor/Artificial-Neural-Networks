#include "Topography.h"

Topography::Topography(const vector<int> & layers)
{
	topology.resize(layers.size(),Layer(true));
	//cout<<"topology size " << topology.size()<<endl;
	for (int i=0;i<layers.size();i++)
	{
		//cout<<"set connections  for layer "<<i<<endl;
		if (i==0)
		{
			topology[i].sigmoid=false;
			topology[i].Neurons.resize(layers[i],false);
		}
		else 
			topology[i].Neurons.resize(layers[i],true);
		
		for (int j=0;j<layers[i];j++)
		{
			if (i==layers.size()-1)//last layer
			{
				topology[i].Neurons[j].setNumberOfConnections(0);
			}
			else
			{
				topology[i].Neurons[j].setNumberOfConnections(layers[i+1]);
			}
			//cout<<"topology number of connections" << topology[i].Neurons[j].getNumberOfConnections()<<endl;
		}

		//cout<<"topology sub size " << topology[i].Neurons.size()<<endl;
	}

	/*
	topology[0].Neurons[0].setWeightToConnection(0,0.1);
	topology[0].Neurons[0].setWeightToConnection(1,0.4);
	topology[0].Neurons[1].setWeightToConnection(0,0.8);
	topology[0].Neurons[1].setWeightToConnection(1,0.6);
	topology[1].Neurons[0].setWeightToConnection(0,0.3);
	topology[1].Neurons[1].setWeightToConnection(0,0.9);
	*/
	/*
	std::ifstream weightsFile;
	string temp;
	weightsFile.open(saveFile,std::ifstream::in);
	
	if (weightsFile.is_open())
	{
		for (int i =0; i<topology.size();i++)
		{
			for (int j=0;j<topology[i].Neurons.size();j++)
			{
				
				getline(weightsFile,temp);
				stringstream temps(temp);
				for (int k=0;k<topology[i].Neurons[j].getNumberOfConnections();k++)
				{
					
					float val; 
					temps >> val;
					topology[i].Neurons[j].setWeightToConnection(k,val);
					cout<< "layer: "<<i<< "nueron: "<<j<<"connection to : "<<k<<"weight : "<<topology[i].Neurons[j].getWeightToConnection(k)<<endl;
				}
			}
		}

		cout<<"wieghts loaded form file"<<endl;
		weightsFile.close();
	}
	
	else
	{
	*/
	for (int i =0; i<topology.size();i++)
		{
			for (int j=0;j<topology[i].Neurons.size();j++)
			{
				
				for (int k=0;k<topology[i].Neurons[j].getNumberOfConnections();k++)
				{
					topology[i].Neurons[j].setWeightToConnection(k,generateRandom());
					//cout<< "layer: "<<i<< "nueron: "<<j<<"connection to : "<<k<<"weight : "<<topology[i].Neurons[j].getWeightToConnection(k)<<endl;
				}
			}
		}	
}

Topography::~Topography()
{
	/*
	std::ofstream weightsFile;
	weightsFile.open(saveFile,std::ofstream::trunc);
	if(weightsFile.is_open())
	{
		for (int i =0; i<topology.size();i++)
		{
			for (int j=0;j<topology[i].Neurons.size();j++)
			{
				
				for (int k=0;k<topology[i].Neurons[j].getNumberOfConnections();k++)
				{
					weightsFile<<topology[i].Neurons[j].getWeightToConnection(k)<<endl;
				}
			}
		}
	}
	*/
}