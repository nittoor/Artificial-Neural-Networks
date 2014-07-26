#include "Helper.h"

float getSigmoid(float x)
{
	return (1/(1+exp(-x)));
}

float getSigmoidFirstDerivative(float x)
{
	return (getSigmoid(x)*(1-getSigmoid(x)));
}

float generateRandom()
{
	return (-1+(float(rand())/(float(RAND_MAX)/2)));
}