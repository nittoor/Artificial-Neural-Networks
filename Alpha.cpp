//*****************************************************************************
//
// Image.cpp : Defines the class operations on images
//
// Author - Prashant Rao Nittoor
// 
//
//*****************************************************************************

#include "Alpha.h"
#include <cmath>

FILE*   MyAlpha::InputFile=NULL;


// Constructor and Desctructors
MyAlpha::MyAlpha(int w,int h):Width(w),Height(h)
{
}

MyAlpha::~MyAlpha()
{
	
}


// Copy constructor
MyAlpha::MyAlpha( MyAlpha *otherImage)
{
	Height = otherImage->Height;
	Width  = otherImage->Width;
	strcpy(otherImage->ImagePath, ImagePath );
	Data	= otherImage->Data;
	

}



// = operator overload
MyAlpha & MyAlpha::operator= (const MyAlpha &otherImage)
{
	Height = otherImage.Height;
	Width  = otherImage.Width;
	strcpy( (char *)otherImage.ImagePath, ImagePath );
	Data= otherImage.Data;
	
	return *this;
	
}


// MyImage::ReadImage
// Function to read the image given a path
bool MyAlpha::ReadImage()
{

	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	if ( IN_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	
	Data.AlphaDataResize(Width,Height);

	for (int z=0;z>=0;z--)
	{
		for (int y=0;y<Height;y++)
		{
			for (int x=0;x<Width;x++)
			{
				Data(x,y,z)=fgetc(InputFile);
				//cout<<(int)Data(x,y,z);
			}
		}
	}

	InputFile=IN_FILE;


	return true;

}

bool MyAlpha::ReadNextImage()
{

	// Verify ImagePath
	
	// Create a valid output file pointer
	
	Data.AlphaDataResize(Width,Height);

	for (int z=0;z>=0;z--)
	{
		for (int y=0;y<Height;y++)
		{
			for (int x=0;x<Width;x++)
			{
				Data(x,y,z)=(fgetc(InputFile));
				//cout<<(int)Data(x,y,z)<<" ";
			}
			//cout<<endl;
		}
		//cout<<endl;
	}
	
	
	return true;
}



// MyImage functions defined here
bool MyAlpha::WriteImage()
{
	// Verify ImagePath
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *OUT_FILE;
	OUT_FILE = fopen(ImagePath, "wb");
	if ( OUT_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	for (int z=0;z>=0;z--)
	{
		for (int y=0;y<Height;y++)
		{
			for (int x=0;x<Width;x++)
			{
				fputc(Data(x,y,z), OUT_FILE);
			}
		}
	}

	fclose(OUT_FILE);

	return true;

}
