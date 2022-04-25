#pragma once
#include "Headers.h"
#include "Edge.h"
#include "Region.h"
class Segment
{
public:
	static void split(Segment* UpperLeft, int Size, int direction);
	static void regionSegm(Segment* UpperLeft, Segment*& UpperRight, Segment*& PreLowerLeft, SegmentParamI spi, Region** all_region, vector<colorListStandard>& P, vector<doubleCoordinate>& C, vector<char> Q, int& num);
	static void leafOperation(Segment* UpperLeft, Segment*& UpperRight, Segment*& PreLowerLeft, SegmentParamI spi, vector<colorListStandard>& P, vector<doubleCoordinate>& C, Region** all_region);
	Segment* PreLink;
	Segment* SucLink;
	int Length;
	Edge* ActiveELink;
};

