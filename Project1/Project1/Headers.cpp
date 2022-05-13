#include "Headers.h"

/** Set first half Value
  * @author CuiYuxin
  * @param uchar c1
  * @param uchar c2 */
void colorListStandard::setFirstHalf(uchar c1, uchar c2)
{
	g1 = c1;
	g2 = c2;
}

/** Set Last half Value
  * @author CuiYuxin
  * @param uchar c3
  * @param uchar c4 */
void colorListStandard::setLastHalf(uchar c3, uchar c4)
{
	g3 = c3;
	g4 = c4;
}

/** Constructor: Set Dots Coordinate
  * @author CuiYuxin
  * @param int x1, y1, x2, y2 */
DoubleDots::DoubleDots(int x1, int y1, int x2, int y2)
{
	dot1 = make_pair(x1, y1);
	dot2 = make_pair(x2, y2);
}

/** Set Dots Coordinate
  * @author CuiYuxin
  * @param int x1, y1, x2, y2 */
void DoubleDots::setCoordinate(int x1, int y1, int x2, int y2)
{
	dot1 = make_pair(x1, y1);
	dot2 = make_pair(x2, y2);
}

/** Set Segment Params
  * @author CuiYuxin
  * @param int x, y, l, h */
SegmentParamI::SegmentParamI(int x, int y, int l, int h)
{
	xLeft = x;
	yupper = y;
	len = l;
	width = h;
}
