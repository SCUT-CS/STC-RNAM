#include "Algo.h"

/** Judge if blocks are the same
  * @author CuiYuxin
  * @param double epsilon
  * @param Mat img
  * @param doubleCoordinate dots
  * @return bool isSame */
bool Algo::JudgeSameBlock(double epsilon, Mat img, doubleCoordinate dots)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* ptrtemp = (uchar*)(img.data + y1 * img.step);
	uchar g1 = ptrtemp[x1];
	uchar g2 = ptrtemp[x2];
	ptrtemp = (uchar*)(img.data + y2 * img.step);
	uchar g3 = ptrtemp[x1];
	uchar g4 = ptrtemp[x2];
	for (int y = y1; y <= y2; y++)
	{
		uchar* ptr = (uchar*)(img.data + y * img.step);
		for (int x = x1; x <= x2; x++)
		{
			uchar g = ptr[x];
			double i1 = (double)(y - y1) / (y2 - y1);
			double i2 = (double)(x - x1) / (x2 - x1);
			double g5 = g1 + (g2 - g1) * i2;
			double g6 = g3 + (g4 - g3) * i2;
			double gest = g5 + (g6 - g5) * i1;
			if (g - gest >= -epsilon && g - gest <= epsilon)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

/** Bulid tree
  * @author CuiYuxin
  * @param Mat img
  * @param treeIterator it
  * @param vector<colorListStandard>& P
  * @param vector<doubleCoordinate>& C
  * @param int& num
  * @param double epsilon
  * @param doubleCoordinate dots */
void Algo::BuildTree(Mat img, treeIterator it, vector<colorListStandard>& P, vector<doubleCoordinate>& C, int& num, double epsilon, doubleCoordinate dots)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* ptr = (uchar*)(img.data);
	colorListStandard temp;
	doubleCoordinate tempc;
	Tree::addchild(it, nw);
	Tree::addchild(it, ne);
	if (num % 2 == 1) //num不为2的整数倍，水平分隔
	{
		num = 0;
		if (y1 == y2)
		{
			Tree::setConfirm(it, '1');
			Tree::deleteChildNode(it, nw);
			Tree::deleteChildNode(it, ne);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[x2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, y1, x2, y2);
			C.push_back(tempc);
			return;
		}
		if (JudgeSameBlock(epsilon, img, doubleCoordinate(x1, y1, x2, (y1 + y2 - 1) / 2)))
		{
			Tree::setChildConfirm(it, '1', nw);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[x2]);
			ptr = (uchar*)(img.data + (y1 + y2 - 1) / 2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, y1, x2, (y1 + y2 - 1) / 2);
			C.push_back(tempc);
		}
		else //若非同类块则递归调用
		{
			BuildTree(img, it.getNwChild(), P, C, num, epsilon, doubleCoordinate(x1, (y1 + y2 + 1) / 2, x2, y2));
		}
		num = 0;
		if (JudgeSameBlock(epsilon, img, doubleCoordinate(x1, (y1 + y2 + 1) / 2, x2, y2))) //判断下半部分:nechild
		{
			Tree::setChildConfirm(it, '1', ne);
			ptr = (uchar*)(img.data + (y1 + y2 + 1) / 2 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[x2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, (y1 + y2 + 1) / 2, x2, y2);
			C.push_back(tempc);
		}
		else //递归调用
		{
			BuildTree(img, it.getNeChild(), P, C, num, epsilon, doubleCoordinate(x1, (y1 + y2 + 1) / 2, x2, y2));
		}
	}
	else if (num % 2 == 0)  //num是2的整数倍，垂直分隔
	{
		num = 1;
		int vx2 = 0;
		if (x1 == x2)
		{
			Tree::setConfirm(it, '1');
			Tree::deleteChildNode(it, nw);
			Tree::deleteChildNode(it, ne);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[x2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, y1, x2, y2);
			C.push_back(tempc);
			return;
		}
		if (JudgeSameBlock(epsilon, img, doubleCoordinate(x1, y1, (x1 + x2 - 1) / 2, y2)))  //判断左半部分:nwchild
		{
			Tree::setChildConfirm(it, '1', nw);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[(x1 + x2 - 1) / 2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[(x1 + x2 - 1) / 2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, y1, (x1 + x2 - 1) / 2, y2);
			C.push_back(tempc);
		}
		else //若非同类块则递归调用
		{
			BuildTree(img, it.getNwChild(), P, C, num, epsilon, doubleCoordinate(x1, y1, (x1 + x2 - 1) / 2, y2));
		}
		num = 1;
		if (JudgeSameBlock(epsilon, img, doubleCoordinate((x1 + x2 + 1) / 2, y1, x2, y2))) //判断右半部分:nechild
		{
			Tree::setChildConfirm(it, '1', ne);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[(x1 + x2 + 1) / 2], ptr[x2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[(x1 + x2 + 1) / 2], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate((x1 + x2 + 1) / 2, y1, x2, y2);
			C.push_back(tempc);
		}
		else //递归调用
		{
			BuildTree(img, it.getNeChild(), P, C, num, epsilon, doubleCoordinate((x1 + x2 + 1) / 2, y1, x2, y2));
		}
	}
	return;
}
