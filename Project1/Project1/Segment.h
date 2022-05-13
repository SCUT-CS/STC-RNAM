#pragma once
#include "Headers.h"
#include "Region.h"
#include "Variables.h"
class Segment
{
public:
	static void regionSegm(Segment* UpperLeft, Segment*& UpperRight, Segment*& PreLowerLeft, SegmentParamI spi, Region** all_region, vector<char> Q, int& num, Varialbes& vars);
	Segment* PreLink;
	Segment* SucLink;
	int Length;
	Edge* ActiveELink;
private:
	static void split(Segment* UpperLeft, int Size, int direction);
	static void leafOperation(Segment* UpperLeft, Segment*& UpperRight, Segment*& PreLowerLeft, SegmentParamI spi, Region** all_region, Varialbes& vars);
};

