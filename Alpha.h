//*****************************************************************************
//
// Image.h : Defines the class operations on images
//
// Author - Prashant Rao Nittoor
// Main Image class structure 
//
//*****************************************************************************

#ifndef APLHA_DISPLAY
#define APLHA_DISPLAY

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <vector>
#include "AlphaData.h"

#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;

class MyAlpha 
{

private:
	int		Width;					// Width of Image
	int		Height;					// Height of Image
	char	ImagePath[256];	// Image location
					// RGB data of the image
	static FILE*   InputFile;
	int label;
public:
	// Constructor
	MyAlpha(int w = -1,int h = -1);
	// Copy Constructor
	MyAlpha( MyAlpha *otherImage);
	// Destructor
	~MyAlpha();

	// operator overload
	MyAlpha & operator= (const MyAlpha & otherImage);

	// Reader & Writer functions
	void	setWidth( const int w)  { Width = w; }; 
	void	setHeight(const int h) { Height = h; }; 
	void	setImageData( const AlphaData &img ) { Data = img; };
	void	setImagePath( const char *path) { strcpy(ImagePath, path); }
	void    setInputFile (FILE* input) {InputFile=input;}
	int		getWidth() { return Width; };
	int		getHeight() { return Height; };
	char*	getImageData() { return Data.giveCharStringForAlpha(); };
	char*	getImagePath() { return ImagePath; }
	bool    setLabel(const int & l) {label=l;return true;};
	int     getLabel() {return label;};

	// Input Output operations
	bool	ReadImage();
	bool    ReadNextImage();
	bool	WriteImage();

	AlphaData	Data;	
};

#endif //IMAGE_DISPLAY
