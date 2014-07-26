#include <iostream>
#include <vector>

using namespace std;

// Class structure of Image 
// Use to encapsulate an RGB image

const int ALPHA  = 0;

typedef vector<unsigned char> OneDIamge;
typedef vector<OneDIamge> TwoDImage;
typedef vector<TwoDImage> ColorImage;

class AlphaData
{
public:
	AlphaData(int x=0, int y=0);
	
	AlphaData(const AlphaData & other);

	bool operator = (const AlphaData & other);

	unsigned char & operator ()(int x ,int y, int z);

	const unsigned char & operator ()(int x ,int y, int z) const;

	bool AlphaDataResize (int x, int y);

	char * giveCharStringForAlpha();

	inline int getAlpDataWidth(){return alpWidth;}

	inline int getAlpDataHeight(){return alpHeight;}

private:
	ColorImage StoredAlpha;
	vector<char> displayAplhaString;
	int alpHeight;
	bool first;
	int alpWidth;
};