#pragma once
class Edge;
class Region
{
public:
	static Region* FindParent(Region* p);
	double Mean;
	double Var;
	int Size; //边长
	Region* Father;
	int Count; //子孙区域数量
	int SegmentCount; //number of edges shared by the waveform
	Edge* EdgeLink;
};

