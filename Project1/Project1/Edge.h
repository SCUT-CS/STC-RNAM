#pragma once
#include "Corner_Vertex.h"
class Region;
class Edge
{
public:
	Edge* PreLink;
	Edge* SucLink;
	Region* Reg;
	Corner_Vertex* First;
	Corner_Vertex* Last;
};

