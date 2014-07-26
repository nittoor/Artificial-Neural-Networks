#include <iostream>
#include "Alpha.h"
#include <string>
#include <sstream>
#include "Topography.h"
#include "BackPropagation.h"

using namespace std;

const int WIDTH =28;
const int HEIGHT=28;




int getNextInt(char * buffer)
{
	int itemsScanned = 0;
	
	itemsScanned += (unsigned char )buffer[0];(itemsScanned <<= 8);
	itemsScanned += (unsigned char )buffer[1];(itemsScanned <<= 8);
	itemsScanned += (unsigned char )buffer[2];(itemsScanned <<= 8);
	itemsScanned += (unsigned char )buffer[3];

	//cout << itemsScanned;
	return itemsScanned;
}

bool loadImagesFromFile(FILE* ImageFile, FILE* labelsFile, int numImages,vector<MyAlpha> & Images,vector<int> & labelVector,bool isTrainingSet=true)
{
	Images.resize(numImages);
	Images[0].setInputFile(ImageFile);

	for (int i =0; i <numImages;i++)
	{
		Images[i].setWidth(WIDTH);
		Images[i].setHeight(HEIGHT);
		Images[i].ReadNextImage();
		if (isTrainingSet)
			Images[i].setLabel((int)fgetc(labelsFile));
		//cout << Images[i].getLabel()<< " ";
		labelVector.push_back(Images[i].getLabel());
	}
	
	cout<<"finished reading all images!"<<endl;
	return true;
}

bool verifyFiles(FILE* imageFile, FILE* labelFile, int & numImages, int & rows, int & cols, bool isTrainingSet=true)
{
	char buffer[4];
	fread(buffer,sizeof(char),4,imageFile);//dummy
	fread(buffer,sizeof(char),4,imageFile);//numImages
	numImages = getNextInt(buffer);
	fread(buffer,sizeof(char),4,imageFile);//rows
	rows= getNextInt(buffer);
	fread(buffer,sizeof(char),4,imageFile);//cols
	cols= getNextInt(buffer);
	cout<<"Number of images = "<<numImages << " row= " <<rows << " cols = " <<cols<<endl;
	if (isTrainingSet)
	{
		int numLables ;
		fread(buffer,sizeof(char),4,labelFile);//dummy
		fread(buffer,sizeof(char),4,labelFile);//numImages
		numLables = getNextInt(buffer);
		cout<<"Number of labels = "<<numLables << endl;

		if (numLables!=numImages)
		{
			cout<<"number of labels donot match with number of images"<<endl;
			exit (1);
		}
	}

	return true;

}


int main (int argc, char * argv[])
{
	int numImages,rows,cols,numLables;
	char	trainImagePath[256];
	char	trainlabelPath[256];
	char	testImagePath[256];
	char	testlabelPath[256];
	
	cout<<"files "<<argv[1]<<endl;

	// Verify ImagePath
	if (argv[1] == 0 || argv[2]==0)
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}

	strcpy(trainImagePath, argv[1]);
	strcpy(trainlabelPath, argv[2]);
	strcpy(testImagePath, argv[3]); 
	strcpy(testlabelPath, argv[4]);
	
	// Create a valid output file pointer
	FILE *imageFile,*labelFile,*testImageFile,*testLabelFile;
	imageFile = fopen(trainImagePath, "rb");
	labelFile = fopen(trainlabelPath, "rb");
	testImageFile= fopen(testImagePath, "rb");
	testLabelFile= fopen(testlabelPath, "rb");
	if ( imageFile == NULL || labelFile==NULL || testImageFile== NULL || testLabelFile==NULL) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	// read image file
	verifyFiles(imageFile, labelFile, numImages, rows, cols);
	verifyFiles(testImageFile, testLabelFile , numImages, rows, cols);//testImages
	vector<MyAlpha>  trainImages; 
	vector<int> trainLabelMatrices;
	vector<MyAlpha>  testImages; 
	vector<int> testLabels;
	vector<int> LabelOutputs;
	
	loadImagesFromFile( imageFile, labelFile, numImages,trainImages, trainLabelMatrices);
	loadImagesFromFile( testImageFile, testLabelFile, numImages,testImages,testLabels);
	//test
	//dislpayAllWindows(testImageMatrices);
	//cout<<trainImages[numImages-1].getLabel();
	//test
	
	int layer[]={784,300,10};
	vector<int> neuronLayers;

	for (int i=0;i<sizeof(layer)/sizeof(int);i++)
	{
		neuronLayers.push_back(layer[i]);
	}

	Topography topologyLayout(neuronLayers);

	BackPropagation BackPropagationObj(topologyLayout,trainImages,trainLabelMatrices);
	BackPropagationObj.loopOverPass();

	//get results

	BackPropagationObj.getResult(testImages,LabelOutputs);
	
	int count=0;
	for (int i=0;i<LabelOutputs.size();i++)
	{
		cout<< "expected output :" <<testLabels[i] <<"output :" <<LabelOutputs[i]<<endl;
		if (testLabels[i] ==LabelOutputs[i])
		{
			cout<<"same"<<endl;
			count++;
		}
		else{
			cout<<"not same"<<endl;
		}
	}

	cout<<"number of matches =" <<count<<endl;
	

	
	fclose(labelFile);
	fclose(imageFile);
	fclose(testImageFile);
	

	return 1;
}