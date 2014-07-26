#include "AlphaData.h"

AlphaData::AlphaData(int x, int y):alpHeight(x),alpWidth(y)
	{
		StoredAlpha.resize(1);
		for (int z=0;z<1;z++)
		{
			StoredAlpha[z].resize(alpHeight);
			for (int y=0;y<alpHeight;y++)
				StoredAlpha[z][y].resize(alpWidth,0);

		}
		displayAplhaString.resize(alpHeight*alpWidth*1,0);
		first=false;
	}

AlphaData::AlphaData(const AlphaData & other)
	{
		alpHeight=other.alpHeight;
		alpWidth=other.alpWidth;
		displayAplhaString.resize(alpHeight*alpWidth*1,0);
		StoredAlpha.resize(1);
		for (int z=0;z<1;z++)
		{
			StoredAlpha[z].resize(0);
			StoredAlpha[z].insert(StoredAlpha[z].begin(),other.StoredAlpha[z].begin(),other.StoredAlpha[z].end());
			for (int y=0;y<alpHeight;y++)
			{
				StoredAlpha[z][y].resize(0);
				StoredAlpha[z][y].insert(StoredAlpha[z][y].begin(),other.StoredAlpha[z][y].begin(),other.StoredAlpha[z][y].end());
			}
		}
		first=false;
	}

bool AlphaData::operator = (const AlphaData & other)
	{
		alpHeight=other.alpHeight;
		alpWidth=other.alpWidth;
		displayAplhaString.resize(alpHeight*alpWidth*1,0);
		StoredAlpha.resize(1);
		for (int z=0;z<1;z++)
		{
			StoredAlpha[z].resize(0);
			StoredAlpha[z].insert(StoredAlpha[z].begin(),other.StoredAlpha[z].begin(),other.StoredAlpha[z].end());
			for (int y=0;y<alpHeight;y++)
			{
				StoredAlpha[z][y].resize(0);
				StoredAlpha[z][y].insert(StoredAlpha[z][y].begin(),other.StoredAlpha[z][y].begin(),other.StoredAlpha[z][y].end());
			}
		}
		first=false;
		return true;
	}

unsigned char & AlphaData::operator ()(int x ,int y, int z)
	{
		return StoredAlpha[z][y][x];
	}

const unsigned char & AlphaData::operator ()(int x ,int y, int z) const
	{
		return StoredAlpha[z][y][x];
	}

bool AlphaData::AlphaDataResize (int x, int y)
	{
		alpHeight=y;
		alpWidth=x;
		displayAplhaString.resize(alpHeight*alpWidth*1,0);
		StoredAlpha.resize(1);
		for (int z=0;z<1;z++)
		{
			StoredAlpha[z].resize(alpHeight);
			for (int y=0;y<alpHeight;y++)
			{
				StoredAlpha[z][y].resize(alpWidth,0);
			}
		}
		first=false;
		return true;
	}

char * AlphaData::giveCharStringForAlpha()
	{
		if(!first)
		{
			for (int x=0;x<alpHeight*alpWidth;x++)
			{
				int i,j;
				i=x%alpWidth;
				j=x/alpWidth;
				displayAplhaString[x]  =StoredAlpha[ALPHA][j][i];
			}
			first=true;
		}
	return displayAplhaString.data();
	}