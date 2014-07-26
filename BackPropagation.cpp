#include "BackPropagation.h"
#include <iomanip>

BackPropagation::BackPropagation(const Topography & inputTopology,const vector<MyAlpha>& inputMatrices, const vector<int>& inputLabels):Arrangement(inputTopology),imageMatrices(inputMatrices),imageLabels(inputLabels)
{
	inputVector.resize(Arrangement.topology[0].Neurons.size());
	//cout<<inputVector.size()<<endl;
	/*
	cout <<"input values" ;

	for (int i =0; i<Arrangement.topology.size();i++)
		{
			for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)
			{
				
				for (int k=0;k<Arrangement.topology[i].Neurons[j].getNumberOfConnections();k++)
				{
					cout<< "layer: "<<i<< "nueron:"<<j<<"connection to :"<<k<<"weight :"<<Arrangement.topology[i].Neurons[j].getWeightToConnection(k)<<endl;
				}
			}
		}
	
	for (int i=0;i<inputVector.size();i++)
	{
		inputVector[i]=(float)rand()/RAND_MAX;
		cout <<inputVector[i];
	}
	*/
	
	/*
	for (int i=0;i<inputVector.size();i++)
	{
		cout <<inputVector[i]<<endl;
	}
	*/

	updatedWieghts.resize(Arrangement.topology.size());
	prevWieghts.resize(Arrangement.topology.size());
	for(int i=0;i<Arrangement.topology.size();i++)
	{
		updatedWieghts[i].resize(Arrangement.topology[i].Neurons.size());	
		prevWieghts[i].resize(Arrangement.topology[i].Neurons.size());
		for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)
		{
			updatedWieghts[i][j].resize(Arrangement.topology[i].Neurons[j].getNumberOfConnections());	
			prevWieghts[i][j].resize(Arrangement.topology[i].Neurons[j].getNumberOfConnections());	
			for (int k=0;k<Arrangement.topology[i].Neurons[j].getNumberOfConnections();k++)
			{
				updatedWieghts[i][j][k]=0.0;
				prevWieghts[i][j][k]=0.0;
			}
		}
	}
	cout<<"constructor!!"<<endl;
}

bool BackPropagation::loopOverPass()
{
	int count=0;
	
	for (int loop=0;loop<imageMatrices.size() && count< 2*imageMatrices.size();loop=(loop+1)%imageMatrices.size())
	{
		inputVector.resize(0);	
		inputVector.resize(784);	
		//inputVector.insert(inputVector.begin(),imageMatrices[loop].getImageData(),imageMatrices[loop].getImageData()+784);
		//cout <<"inputVector"<< inputVector.size()<<endl;
		//cout<<"number =" <<imageLabels[loop]<<endl;
		for (int i=0;i<imageMatrices[loop].getHeight();i++)	
			{
				for (int j=0;j<imageMatrices[loop].getWidth();j++)
				{
					inputVector[(i*imageMatrices[loop].getHeight())+j]=((float)imageMatrices[loop].Data(j,i,0)/255);
					//cout<<inputVector[(i*imageMatrices[loop].getHeight())+j]<<" ";
				}
				//cout<<endl;
			}
		
		/*
		expectedOutput.resize(0);
		expectedOutput.resize(4,0.0);

			if (loop==0)
			{
			inputVector[0]=1.0;
			inputVector[1]=0.0;
			inputVector[2]=0.0;
			inputVector[3]=0.0;
			expectedOutput[0]=1.0;
			expectedOutput[1]=0.0;
			expectedOutput[2]=0.0;
			expectedOutput[3]=0.0;
			}
			else if (loop==1)
			{
			inputVector[0]=1.0;
			inputVector[1]=1.0;
			inputVector[2]=0.0;
			inputVector[3]=0.0;
			expectedOutput[0]=0.0;
			expectedOutput[1]=1.0;
			expectedOutput[2]=0.0;
			expectedOutput[3]=0.0;
			}

			else if (loop==2)
			{
			inputVector[0]=1.0;
			inputVector[1]=1.0;
			inputVector[2]=1.0;
			inputVector[3]=0.0;
			expectedOutput[0]=0.0;
			expectedOutput[1]=0.0;
			expectedOutput[2]=1.0;
			expectedOutput[3]=0.0;
			}
			else
			{
			inputVector[0]=1.0;
			inputVector[1]=1.0;
			inputVector[2]=1.0;
			inputVector[3]=1.0;
			expectedOutput[0]=0.0;
			expectedOutput[1]=0.0;
			expectedOutput[2]=0.0;
			expectedOutput[3]=1.0;
			}
			
			
			*/
			
		expectedOutput.resize(0);
		expectedOutput.resize(10,0.0);
		expectedOutput[imageLabels[loop]]=1.0;
		
		/*
			for (int i=0;i<expectedOutput.size();i++)
				if (expectedOutput[i])
				cout<<"expectedOutput="<<i<<endl;
				*/

		ForwardPass();
		ReversePass();
			/*
			for (int i=0; i<Arrangement.topology.size();i++)// for each layer
			{
				for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)//for each Neuron
				{
					
					if (i==Arrangement.topology.size()-1 )
						cout<<"output for layer: "<< i<<" neuron:"<<j<<" = "<<Arrangement.topology[i].Neurons[j].getOutput()<<endl;
				}
			}
			*/
		cout<<count++<<endl;;
		//expectedOutput[1]=1.0;
		//
		//inputVector[0]=0.35;
		//inputVector[1]=0.9;
		//expectedOutput=0.5;
	}
	

		/*
		inputVector[0]=0.35;
		inputVector[1]=0.9;
		expectedOutput.resize(1,0.5);
		//expectedOutput=0.5;
		ForwardPass();
		ReversePass();
		ForwardPass();
		*/
	return true;
}

bool BackPropagation::getResult( vector<MyAlpha>& testMatrices,vector<int>& outputs)
{

	int count=0;
	for (int loop=0;loop<testMatrices.size();loop++)
	{
		inputVector.resize(0);
		inputVector.resize(784);
		for (int i=0;i<imageMatrices[loop].getHeight();i++)	
			{
				for (int j=0;j<imageMatrices[loop].getWidth();j++)
				{
					inputVector[(i*imageMatrices[loop].getHeight())+j]=((float)imageMatrices[loop].Data(j,i,0)/255);
				}
				
			}
		//inputVector.insert(inputVector.begin(),testMatrices[loop].getImageData(),testMatrices[loop].getImageData()+784);
		/*
		for (int i=0;i<imageMatrices[loop].getHeight();i++)	
			{
				for (int j=0;j<imageMatrices[loop].getWidth();j++)
				{
					//inputVector[(i*imageMatrices[loop].getHeight())+j]=(imageMatrices[loop].Data(j,i,0));
					cout<<inputVector[(i*imageMatrices[loop].getHeight())+j]<<" ";
				}
				cout<<endl;
			}
			*/
		
		ForwardPass();	
		float max=0;
		int pos=-1;
		for (int i=Arrangement.topology.size()-1 ; i<Arrangement.topology.size();i++)// for each layer
			{
				for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)//for each Neuron
				{
						//cout<<"output for layer: "<< i<<" neuron:"<<j<<" = "<<Arrangement.topology[i].Neurons[j].getOutput()<<endl;
						if (Arrangement.topology[i].Neurons[j].getOutput()>max)
						{
							max=Arrangement.topology[i].Neurons[j].getOutput();
							pos=j;
							//cout<<"max at:" <<pos<<endl;
						}
				}
			}
		//cout<<"output= "<<pos<<endl;;
		outputs.push_back(pos);
		
		count++;
		
	}
	return true;

}

bool BackPropagation::ForwardPass()
{
	for (int i=0; i<Arrangement.topology.size();i++)// for each layer
	{
		for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)//for each Neuron
		{
			// generate output
			//cout<<"caclulations: ";
			float weightedInput=0.0;
			if (i==0)//first layer
				Arrangement.topology[i].Neurons[j].setOutput(inputVector[j]);
			else
			{
				for (int p=0;p<Arrangement.topology[i-1].Neurons.size();p++)// compute weighted input for each neuron in current layer
				{
				//	cout<<"\tweights: "<<Arrangement.topology[i-1].Neurons[p].getWeightToConnection(j)<<"*"<<Arrangement.topology[i-1].Neurons[p].getOutput();
					weightedInput+=(Arrangement.topology[i-1].Neurons[p].getWeightToConnection(j))*(Arrangement.topology[i-1].Neurons[p].getOutput());
				}
				//cout<<endl;
				//cout<<"weightedInput : "<<weightedInput<<endl;
				Arrangement.topology[i].Neurons[j].computeOutput(weightedInput);
			}
			
			/*
			if (i==Arrangement.topology.size()-1 )
				cout<<"output for layer: "<< i<<" neuron:"<<j<<" = "<<Arrangement.topology[i].Neurons[j].getOutput()<<endl;
				*/
				
				
		}
	}
	return true;
}

bool BackPropagation::ReversePass()
{
	vector<float> outputLayerDeltas;
	vector<float> hiddenLayerDeltas;
	//cout<<"expectedOutput"<<expectedOutput<<endl;
	for(int i=0;i<Arrangement.topology.size();i++)
	{
		for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)
		{
			for (int k=0;k<Arrangement.topology[i].Neurons[j].getNumberOfConnections();k++)
			{
				updatedWieghts[i][j][k]=0.0;
			}
		}
	}
	for (int i=Arrangement.topology.size()-2;i>=0;i--)
	{
		
		if (i==Arrangement.topology.size()-2)//update weights for outputlayer
		{
			//cout<<"output layer"<<endl;
			//calculate delta for output 
			outputLayerDeltas.resize(0,0.0);
			outputLayerDeltas.resize(Arrangement.topology[i+1].Neurons.size()); // 1 delta for 1 ouput

			for (int j=0;j<outputLayerDeltas.size();j++)
			{
				float output=Arrangement.topology[i+1].Neurons[j].getOutput();
				float sigmoidDerivative=output *(1-output);
				outputLayerDeltas[j]=(sigmoidDerivative*(expectedOutput[j]-output));
				//cout<<"layer :"<<i<<" difference: " << expectedOutput[j]-output << " output delta = " <<sigmoidDerivative*(expectedOutput[j]-output)<<endl;
			}

			// now apply error margins to current layer weights

			for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)
			{
				for (int k=0;k<Arrangement.topology[i+1].Neurons.size();k++)
				{
					float weight= Arrangement.topology[i].Neurons[j].getWeightToConnection(k);
					float newWeight=Eta*outputLayerDeltas[k]*Arrangement.topology[i].Neurons[j].getOutput();//+alpha*prevWieghts[i][j][k];
					//cout<<"new weight:"<<weight<<"+ ("<<outputLayerDeltas[k]<<"*"<<Arrangement.topology[i].Neurons[j].getOutput()<<") ="; 
					prevWieghts[i][j][k]=newWeight;
					newWeight+=weight;
					//cout<<newWeight<<endl;
					updatedWieghts[i][j][k]=newWeight;
					//Arrangement.topology[i].Neurons[j].setWeightToConnection(k,newWeight);
				}
			}
		}

		else
		{
			//cout<<"hidden layer"<<endl;
			hiddenLayerDeltas.resize(0,0.0); // 1 delta for 1 ouput
			hiddenLayerDeltas.resize(Arrangement.topology[i+1].Neurons.size()); // 1 delta for 1 ouput
			for (int j=0;j<Arrangement.topology[i+1].Neurons.size();j++)
			{
				float output=Arrangement.topology[i+1].Neurons[j].getOutput();
				float sigmoidDerivatiove= output*(1-output);
				float errorWights=0.0;
				//cout<<"errors for hidden layers: "<<endl;
				for (int k=0;k<outputLayerDeltas.size();k++)
				{
					errorWights+=(outputLayerDeltas[k]*Arrangement.topology[i+1].Neurons[j].getWeightToConnection(k));
				//	cout<< outputLayerDeltas[k] <<" "<< Arrangement.topology[i+1].Neurons[j].getWeightToConnection(k);
				}
				hiddenLayerDeltas[j]=errorWights*sigmoidDerivatiove;
				//cout<<" "<< errorWights*sigmoidDerivatiove<<endl;
			}

			//update hidden layer wieghts

			for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)
			{
				for (int k=0;k<Arrangement.topology[i+1].Neurons.size();k++)
				{
					float weight= Arrangement.topology[i].Neurons[j].getWeightToConnection(k);
					float newWeight=Eta*hiddenLayerDeltas[k]*Arrangement.topology[i].Neurons[j].getOutput();
					//cout<<"new weight:"<<weight<<"+ ("<<hiddenLayerDeltas[k]<<"*"<<Arrangement.topology[i].Neurons[j].getOutput()<<") ="; 
					newWeight+=weight;
					//cout << newWeight<<endl;
					//Arrangement.topology[i].Neurons[j].setWeightToConnection(k,newWeight);
					updatedWieghts[i][j][k]=newWeight;
				}
			}
		}
	}

	
	for (int i =0; i<Arrangement.topology.size()-1;i++)
		{
			for (int j=0;j<Arrangement.topology[i].Neurons.size();j++)
			{	
				for (int k=0;k<Arrangement.topology[i+1].Neurons.size();k++)
				{
					Arrangement.topology[i].Neurons[j].setWeightToConnection(k,updatedWieghts[i][j][k]);
					//cout<< "layer: "<<i<< " nueron:"<<j<<" connection to :"<<k<<" weight :"<<Arrangement.topology[i].Neurons[j].getWeightToConnection(k)<<endl;
				}
			}
		}
		
	return true;
}
	
BackPropagation::~BackPropagation()
{
}