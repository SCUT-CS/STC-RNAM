#include "Segment.h"

/** Split segment
  * @author CuiYuxin
  * @param Segment* upperLeft
  * @param int size
  * @param int direction */
void Segment::split(Segment* upperLeft, int size, int direction)
{
	Segment* late_half = new Segment;
	late_half->ActiveELink = upperLeft->ActiveELink;
	if (direction == 0)
	{
		late_half->Length = (upperLeft->Length + 1) / 2;
		upperLeft->Length /= 2;
	}
	else
	{
		late_half->Length = (upperLeft->Length) / 2;
		upperLeft->Length = (upperLeft->Length + 1) / 2;
	}
	late_half->SucLink = upperLeft;
	late_half->PreLink = upperLeft->PreLink;
	upperLeft->PreLink = late_half;
	if (late_half->PreLink != nullptr)
		late_half->PreLink->SucLink = late_half;
}

/** Region Segment
  * @author CuiYuxin
  * @param Segment* UpperLeft
  * @param Segment*& UpperRight
  * @param Segment*& PreLowerLeft
  * @param SegmentParamI spi
  * @param Region** all_region
  * @param vector<char> Q
  * @param int& num */
void Segment::regionSegm(Segment* UpperLeft, Segment*& UpperRight, Segment*& PreLowerLeft, SegmentParamI spi, Region** all_region, vector<char> Q, int& num, Varialbes& vars)
{
	int Xleft = spi.xLeft;
	int Yupper = spi.yupper;
	int Length = spi.len;
	int Width = spi.width;
	Segment* UR = nullptr;
	Segment* PLL = nullptr;
	Segment* DUMMY = nullptr;
	char bit;
	if (UpperLeft->Length > Width)
	{
		split(UpperLeft, Width, 0);
	}
	if (UpperLeft->SucLink != nullptr && UpperLeft->SucLink->Length > Length)
	{
		split(UpperLeft->SucLink, Length, 1);
	}
	bit = vars.getBit(Q);
	if (bit == '0')
	{
		if (num % 2 == 0) //垂直
		{
			num = 1;
			regionSegm(UpperLeft, UR, PreLowerLeft, SegmentParamI (Xleft, Yupper, Length / 2, Width), all_region, Q, num, vars);
			num = 1;
			regionSegm(UR, UpperRight, DUMMY, SegmentParamI(Xleft + Length / 2, Yupper, Length - Length / 2, Width), all_region, Q, num, vars);
		}
		else //水平
		{
			num = 0;
			regionSegm(UpperLeft, UpperRight, PLL, SegmentParamI(Xleft, Yupper, Length, Width / 2), all_region, Q, num, vars);
			num = 0;
			regionSegm(PLL, UR, PreLowerLeft, SegmentParamI(Xleft, Yupper + Width / 2, Length, Width - Width / 2), all_region, Q, num, vars);
		}
	}
	else
	{
		vars.cur_block++;
		if (Xleft == vars.C[vars.cur_block].dot1.first && Yupper == vars.C[vars.cur_block].dot1.second)
		{
			if ((Xleft + Length - 1) != vars.C[vars.cur_block].dot2.first && (Yupper + Width - 1) != vars.C[vars.cur_block].dot2.second)
			{
				cout << vars.cur_block << endl;
			}
		}
		leafOperation(UpperLeft, UpperRight, PreLowerLeft, SegmentParamI(Xleft, Yupper, Length, Width), all_region, vars);
	}
}

/** Leaf Operation
  * @author CuiYuxin
  * @param Segment* UpperLeft
  * @param Segment*& UpperRight
  * @param Segment*& PreLowerLeft
  * @param SegmentParamI spi
  * @param Region** all_region */
void Segment::leafOperation(Segment* UpperLeft, Segment*& UpperRight, Segment*& PreLowerLeft, SegmentParamI spi, Region** all_region, Varialbes& vars)
{
	int Xleft = spi.xLeft;
	int Yupper = spi.yupper;
	int Length = spi.len;
	int Width = spi.width;
	//find lower left = start_segment;and find prelowerleft
	int side_length = Width;
	Segment* start_segment = UpperLeft;
	while ((side_length = side_length - start_segment->Length) > 0)
	{
		start_segment = start_segment->PreLink;
	}
	PreLowerLeft = start_segment->PreLink;
	side_length = 0;
	//allocate new region,allocate new edge
	Region* cur_region = new Region;
	all_region[vars.cur_block] = cur_region;
	Edge* active_right = new Edge;
	Edge* inactive = new Edge;
	Edge* active_down = new Edge;
	active_right->SucLink = active_down;
	active_right->PreLink = inactive;
	active_right->Reg = cur_region;
	active_down->SucLink = inactive;
	active_down->PreLink = active_right;
	active_down->Reg = cur_region;
	inactive->SucLink = active_right;
	inactive->PreLink = active_down;
	inactive->Reg = nullptr;
	cur_region->Father = nullptr;
	cur_region->Count = 0;
	cur_region->EdgeLink = inactive;
	cur_region->Mean = vars.Ubi();
	cur_region->Var = vars.Varbi();
	cur_region->Size = Length * Width;
	cur_region->SegmentCount = 2;
	vars.reg_num++;
	//遍历每个SEGMENT
	while (true)
	{
		if (start_segment->ActiveELink != nullptr && start_segment->ActiveELink->Reg != nullptr)
		{
			Region* neighbour_region = start_segment->ActiveELink->Reg;
			Region* neighbour_father = Region::FindParent(neighbour_region);
			Region* cur_father = Region::FindParent(cur_region);
			//同一区域
			if (neighbour_father == cur_father){}
			//不同区域
			else
			{
				double varnew = Varc(cur_father->Size, neighbour_father->Size, cur_father->Var, neighbour_father->Var, cur_father->Mean, neighbour_father->Mean);
				//可以合并
				if (neighbour_father->Mean - cur_father->Mean >= -vars.thresU && neighbour_father->Mean - cur_father->Mean <= vars.thresU && varnew <= vars.thresVar)
				{
					neighbour_father->Mean = Uc(cur_father->Size, neighbour_father->Size, cur_father->Mean, neighbour_father->Mean);
					neighbour_father->Size += cur_father->Size;
					neighbour_father->Var = varnew;
					cur_father->Father = neighbour_father;
					vars.reg_num--;
				}
			}
		}
		if ((side_length = side_length + start_segment->Length) == (Length + Width))
		{
			break;
		}
		else
		{
			start_segment = start_segment->SucLink;
		}
	}
	//此块遍历完成,重新构造waveform,Upperright
	if (start_segment != nullptr && start_segment->SucLink != nullptr)
	{
		start_segment = start_segment->SucLink;
	}
	Segment* downseg = new Segment;
	Segment* rightseg = new Segment;
	downseg->ActiveELink = active_down;
	downseg->Length = Length;
	downseg->PreLink = PreLowerLeft;
	if (PreLowerLeft != nullptr)
		PreLowerLeft->SucLink = downseg;
	downseg->SucLink = rightseg;
	rightseg->ActiveELink = active_right;
	rightseg->Length = Width;
	rightseg->PreLink = downseg;
	rightseg->SucLink = start_segment;
	if (start_segment != nullptr)
		start_segment->PreLink = rightseg;
	UpperRight = rightseg;
}
