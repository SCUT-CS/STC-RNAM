#include "Algo.h"

/** Judge if blocks are the same for STC algorithm
  * @author CuiYuxin
  * @param double epsilon
  * @param Mat img
  * @param DoubleDots dots
  * @return bool isSame */
bool Algo::JudgeSameBlock(double epsilon, Mat img, DoubleDots dots)
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

/** Bulid tree for STC algorithm
  * @author CuiYuxin
  * @param Mat img
  * @param treeIterator it
  * @param vector<colorListStandard>& P
  * @param vector<DoubleDots>& C
  * @param int& num
  * @param double epsilon
  * @param DoubleDots dots */
void Algo::BuildTree(Mat img, treeIterator it, vector<colorListStandard>& P, vector<DoubleDots>& C, int& num, double epsilon, DoubleDots dots)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* ptr = (uchar*)(img.data);
	colorListStandard temp;
	DoubleDots tempc;
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
		if (JudgeSameBlock(epsilon, img, DoubleDots(x1, y1, x2, (y1 + y2 - 1) / 2)))
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
			BuildTree(img, it.getNwChild(), P, C, num, epsilon, DoubleDots(x1, y1, x2, (y1 + y2 - 1) / 2));
		}
		num = 0;
		if (JudgeSameBlock(epsilon, img, DoubleDots(x1, (y1 + y2 + 1) / 2, x2, y2))) //判断下半部分:nechild
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
			BuildTree(img, it.getNeChild(), P, C, num, epsilon, DoubleDots(x1, (y1 + y2 + 1) / 2, x2, y2));
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
		if (JudgeSameBlock(epsilon, img, DoubleDots(x1, y1, (x1 + x2 - 1) / 2, y2)))  //判断左半部分:nwchild
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
			BuildTree(img, it.getNwChild(), P, C, num, epsilon, DoubleDots(x1, y1, (x1 + x2 - 1) / 2, y2));
		}
		num = 1;
		if (JudgeSameBlock(epsilon, img, DoubleDots((x1 + x2 + 1) / 2, y1, x2, y2))) //判断右半部分:nechild
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
			BuildTree(img, it.getNeChild(), P, C, num, epsilon, DoubleDots((x1 + x2 + 1) / 2, y1, x2, y2));
		}
	}
	return;
}

/** Make Imggest for STC algorithm
  * @author CuiYuxin
  * @param Mat imggest
  * @param vector<colorListStandard>& P
  * @param vector<DoubleDots>& C */
void Algo::MakeImggest(Mat imggest, vector<colorListStandard>& P, vector<DoubleDots> C)
{
	uchar g1 = 0, g2 = 0, g3 = 0, g4 = 0;
	for (unsigned int i = 0; i < P.size(); i++)
	{
		g1 = P[i].g1; g2 = P[i].g2;
		g3 = P[i].g3; g4 = P[i].g4;
		int x1 = C[i].dot1.first;
		int y1 = C[i].dot1.second;
		int x2 = C[i].dot2.first;
		int y2 = C[i].dot2.second;
		if (x1 == x2 && y1 == y2)
		{
			uchar* ptr = (uchar*)(imggest.data + y1 * imggest.step);
			ptr[x1] = g1;
		}
		else if (x1 == x2)
		{
			for (int y = y1; y <= y2; y++)
			{
				double i1 = (double)(y - y1) / (double)(y2 - y1);
				(imggest.data + imggest.step * y)[x1] = (int)(g1 + (g2 - g1) * i1);
			}
		}
		else if (y1 == y2)
		{
			for (int x = x1; x <= x2; x++)
			{
				double i2 = (double)(x - x1) / (double)(x2 - x1);
				(imggest.data + y1 * imggest.step)[x] = (int)(g1 + (g2 - g1) * i2);
			}
		}
		else
		{
			for (int y = y1; y <= y2; y++)
			{
				uchar* ptr = (uchar*)(imggest.data + y * imggest.step);
				for (int x = x1; x <= x2; x++)
				{
					double i1 = (double)(y - C[i].dot1.second) / (C[i].dot2.second - C[i].dot1.second);
					double i2 = (double)(x - C[i].dot1.first) / (C[i].dot2.first - C[i].dot1.first);
					double g5 = g1 + (g2 - g1) * i2;
					double g6 = g3 + (g4 - g3) * i2;
					ptr[x] = g5 + (g6 - g5) * i1;
				}
			}
		}
	}
}

/** Encode matrix for DP algorithm
  * @author CuiYuxin
  * @param Mat* R
  * @param Size s
  * @param vector<char>& Q */
void Algo::EnCode(Mat R, Size s, vector<char>& Q)
{
	int c = 0;
	int offsetValue = 0;
	int count = 0;
	int height = s.height;
	int width = s.width;
	for (int i = 0; i < height; i++)
	{
		c = 0;
		offsetValue = 0;
		count = 0;
		for (int j = 0; j < width; j++)
		{
			int value = R.at<uchar>(i, j);
			if (0 == value)
			{
				if (j == width - 1)
				{
					Q.push_back('0');
				}
			}
			else
			{
				if (1 == value)
				{
					Q.push_back('1');
					Q.push_back('1');
				}
				else if (2 == value)
				{
					Q.push_back('1');
					Q.push_back('0');
					Q.push_back('1');
				}
				else if (3 == value)
				{
					Q.push_back('1');
					Q.push_back('0');
					Q.push_back('0');
				}
				//位置从1开始 不是从0开始 所以多减去1
				int b = ceil(log((double)(width - c - count)) / log(2.0f));
				if (0 == count)
				{
					offsetValue = j;
				}
				else
				{
					offsetValue = j - c - 1;
				}
				b = (b == 0) ? 1 : b;
				count = 1;
				c = j;
				for (int v = b - 1; v >= 0; v--)
				{
					if ((offsetValue & (1 << v)) == 0)
					{
						Q.push_back('0');
					}
					else
					{
						Q.push_back('1');
					}
				}
			}
		}
	}


}

/** Judge if blocks are the same for DP algorithm
  * @author CuiYuxin
  * @param Mat img
  * @param DoubleDots dots
  * @param int margin
  * @return bool isSame */
bool Algo::IsSameBlock(const Mat img, DoubleDots dots, int margin)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* gy1 = (uchar*)img.data + y1 * img.step;
	uchar* g1 = gy1 + x1;
	uchar* g2 = gy1 + x2;
	uchar* gy2 = (uchar*)img.data + y2 * img.step;
	uchar* g3 = gy2 + x1;
	uchar* g4 = gy2 + x2;
	bool returnValue = true;

	if (x1 == x2 && y1 == y2)
	{
		returnValue = true;
	}
	else if (y1 == y2)
	{
		for (int x = x1 + 1; x < x2; x++)
		{
			double i2 = (double)(x - x1) / (double)(x2 - x1);
			double g = *g1 + (*g4 - *g1) * i2;
			uchar* gValue = gy1 + x;
			if (abs(*gValue - g) > margin)
			{
				returnValue = false;
				break;
			}

		}
	}
	else if (x1 == x2)
	{
		for (int y = y1 + 1; y < y2; y++)
		{
			double i1 = (double)(y - y1) / (double)(y2 - y1);
			double g = *g1 + (*g4 - *g1) * i1;
			uchar* gy = (uchar*)img.data + y * img.step;
			uchar* gValue = gy + x1;
			if (abs(*gValue - g) > margin)
			{
				returnValue = false;
				break;
			}
		}
	}
	else
	{
		for (int x = x1; x <= x2; x++)
		{
			for (int y = y1; y <= y2; y++)
			{
				double i1 = (double)(y - y1) / (double)(y2 - y1);
				double i2 = (double)(x - x1) / (double)(x2 - x1);
				double g5 = *g1 + (*g2 - *g1) * i2;
				double g6 = *g3 + (*g4 - *g3) * i2;
				double g = g5 + (g6 - g5) * i1;
				uchar* gy = (uchar*)img.data + y * img.step;
				uchar* gValue = gy + x;
				if (abs(*gValue - g) > margin)
				{
					returnValue = false;
					break;
				}
			}
		}
	}

	return returnValue;
}

/** Find same block
  * @author CuiYuxin
  * @param const Mat img
  * @param Mat markMatrix
  * @param Mat R
  * @param int x1,y1
  * @param double margin,ratio
  * @return DoubleDots */
DoubleDots Algo::FindSameBlock(const Mat img, Mat markMatrix, Mat R, int x1, int y1, double margin, double ratio)
{
	int x2(x1), y2(y1);
	while (x2 < img.size().width && y2 < img.size().height && (markMatrix.data + y1 * markMatrix.step)[x2] == 0 && (markMatrix.data + y2 * markMatrix.step)[x1] == 0)
	{
		if (!IsSameBlock(img, DoubleDots(x1, y1, x2, y2), margin))
			break;
		x2++;
		y2++;
	}
	x2--;
	y2--;
	int endX = x2;
	int maxX = ratio == 0 ? INT_MAX : (y2 - y1 + 1) * ratio;
	while (x2 < img.size().width && (x2 - x1 < maxX) && (markMatrix.data + y1 * markMatrix.step)[x2] == 0)
	{
		if (!IsSameBlock(img, DoubleDots(x1, y1, x2, y2), margin))
		{
			break;
		}
		x2++;
	}
	x2--;
	int tempX = x2;
	int tempY = y2;
	x2 = endX;
	int maxY = ratio == 0 ? INT_MAX : (x2 - x1 + 1) * ratio;
	while (y2 < img.size().height && (y2 - y1 < maxY))
	{
		if (!IsSameBlock(img, DoubleDots(x1, y1, x2, y2), margin))
		{
			break;
		}

		y2 = y2 + 1;
	}
	y2--;
	if (/*ratio !=0 &&*/((tempX - x1 + 1) * (tempY - y1 + 1) >= (x2 - x1 + 1) * (y2 - y1 + 1)))
	{
		x2 = tempX;
		y2 = tempY;
	}
	return DoubleDots(x1, y1, x2, y2);
}

/** Restore Image
  * @author CuiYuxin
  * @param Mat img
  * @param Mat markMatrix
  * @param Mat R
  * @param vector<ColorNode> cn
  * @param Size s */
void Algo::RestoreImage(Mat img, Mat markMatrix, Mat R, vector<ColorNode> cn, Size s)
{
	int width = s.width;
	int height = s.height;
	int x1(0), x2(0), y1(0), y2(0);
	for (vector<ColorNode>::iterator it = cn.begin(); it != cn.end(); it++)
	{
		int i = 0;
		//先查找下一个未计算的分块 起点坐标
		while (x2 < width)
		{
			if ((markMatrix.data + markMatrix.step * y2)[x2++] == 1)
				break;
			if (x2 == width)
			{
				x1 = x2 = 0;
				y1 = ++y2;
			}
		}
		x1 = --x2;
		//再查找出这个块的 (x1,y1) (x2,y2)
		if (0 == (*it).kind)
		{
			while (x2 < width)
			{
				//x2要先走一步
				if ((R.data + R.step * y2)[++x2] != 0 || (markMatrix.data + markMatrix.step * y2)[x2] == 0)
					break;
			}
			x2--;
			while (y2 < height)
			{
				if ((R.data + R.step * y2)[x2] == 2 || (markMatrix.data + markMatrix.step * y2)[x2] == 0)
					break;
				y2++;
			}
		}
		else if (1 == (*it).kind)
		{
			while (x2 < width)
			{
				if ((R.data + R.step * y2)[++x2] == 2)
					break;
			}
		}
		else if (2 == (*it).kind)
		{
			while (y2 < height)
			{
				if ((R.data + R.step * y2)[x2] == 2)
					break;
				y2++;
			}
		}
		//cout<<"("<<x1<<","<<y1<<")("<<x2<<","<<y2<<")"<<endl;
		RestoreImageValue(img, *it, DoubleDots(x1, y1, x2, y2));
		//Mark
		SetMarkMatrix(markMatrix, DoubleDots(x1, y1, x2, y2), 0);
		x1 = x2;
		y2 = y1;
	}
}

/** Restore Image Value
  * @author CuiYuxin
  * @param Mat img
  * @param DoubleDots */
void Algo::RestoreImageValue(Mat img, ColorNode node, DoubleDots dots)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* upPtr = (uchar*)(img.data + img.step * y1);
	uchar* downPtr = (uchar*)(img.data + img.step * y2);
	if (3 == node.kind)
	{
		upPtr[x1] = node.g1;
	}
	else if (1 == node.kind)
	{
		upPtr[x1] = node.g1;
		upPtr[x2] = node.g2;
		for (int x = x1 + 1; x < x2; x++)
		{
			double i2 = (double)(x - x1) / (double)(x2 - x1);
			upPtr[x] = (int)(node.g1 + (node.g2 - node.g1) * i2);
		}
	}
	else if (2 == node.kind)
	{
		upPtr[x1] = node.g1;
		downPtr[x1] = node.g2;
		for (int y = y1 + 1; y < y2; y++)
		{
			double i1 = (double)(y - y1) / (double)(y2 - y1);
			(img.data + img.step * y)[x1] = (int)(node.g1 + (node.g2 - node.g1) * i1);
		}
	}
	else
	{
		for (int x = x1; x <= x2; x++)
		{
			for (int y = y1; y <= y2; y++)
			{
				double i1 = (double)(y - y1) / (double)(y2 - y1);
				double i2 = (double)(x - x1) / (double)(x2 - x1);
				double g5 = node.g1 + (node.g2 - node.g1) * i2;
				double g6 = node.g3 + (node.g4 - node.g3) * i2;
				(img.data + img.step * y)[x] = (int)(g5 + (g6 - g5) * i1);
			}
		}
		upPtr[x1] = node.g1;
		upPtr[x2] = node.g2;
		downPtr[x1] = node.g3;
		downPtr[x2] = node.g4;
	}
}

/** Set Mark Matrix
  * @author CuiYuxin
  * @param Mat markMatrix
  * @param DoubleDots
  * @param int value */
void Algo::SetMarkMatrix(Mat markMatrix, DoubleDots dots, int value)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	for (int y = y1; y <= y2; y++)
	{
		for (int x = x1; x <= x2; x++)
		{
			(markMatrix.data + markMatrix.step * y)[x] = value;
		}
	}
}

/** Start Nam Cut
  * @author CuiYuxin
  * @param const Mat img
  * @param Mat markMatrix
  * @param Mat R
  * @param vector<DoubleDots>& ColorList
  * @param vector<DoubleDots>& LocList
  * @param Size size
  * @param double margin
  * @param int& num
  * @param double ratio */
void Algo::StartNamCut(const Mat img, Mat markMatrix, Mat R, vector<ColorNode>& ColorList, vector<DoubleDots>& LocList, Size size, double margin, int& num, double ratio)
{
	int height = size.height;
	int width = size.width;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if ((markMatrix.data + row * markMatrix.step)[col] == 0)
			{
				num++;
				DoubleDots loc = FindSameBlock(img, markMatrix, R, col, row, margin, ratio);
				LocList.push_back(loc);
				//Mark
				SetMarkMatrix(markMatrix, loc, 1);
				//R
				if (loc.dot1.first == loc.dot2.first && loc.dot1.second == loc.dot2.second)
				{
					uchar* g = R.data + R.step * loc.dot1.second;
					g[loc.dot1.first] = 3;
					ColorNode node(3, ((uchar*)img.data + img.step * loc.dot1.second)[loc.dot1.first]);
					ColorList.push_back(node);
				}
				else if (loc.dot1.first == loc.dot2.first)
				{
					for (int j = loc.dot1.second; j <= loc.dot2.second; j++)
					{
						uchar* g = R.data + R.step * j;
						g[loc.dot1.first] = 0;
					}
					(R.data + R.step * loc.dot1.second)[loc.dot1.first] = 1;
					(R.data + R.step * loc.dot2.second)[loc.dot1.first] = 2;
					ColorNode node(2, ((uchar*)img.data + img.step * loc.dot1.second)[loc.dot1.first], ((uchar*)img.data + img.step * loc.dot2.second)[loc.dot1.first]);
					ColorList.push_back(node);
				}
				else
				{
					for (int i = loc.dot1.second; i <= loc.dot2.second; i++)
					{
						for (int j = loc.dot1.first; j <= loc.dot2.first; j++)
						{
							(R.data + R.step * i)[j] = 0;
						}
					}
					if (loc.dot1.second == loc.dot2.second)
					{
						ColorNode node(1, ((uchar*)img.data + img.step * loc.dot1.second)[loc.dot1.first], ((uchar*)img.data + img.step * loc.dot1.second)[loc.dot2.first]);
						ColorList.push_back(node);
					}
					else
					{
						ColorNode node(0, ((uchar*)img.data + img.step * loc.dot1.second)[loc.dot1.first], ((uchar*)img.data + img.step * loc.dot1.second)[loc.dot2.first],
							((uchar*)img.data + img.step * loc.dot2.second)[loc.dot1.first], ((uchar*)img.data + img.step * loc.dot2.second)[loc.dot2.first]);
						ColorList.push_back(node);
					}
					(R.data + R.step * loc.dot1.second)[loc.dot1.first] = 1;
					(R.data + R.step * loc.dot2.second)[loc.dot2.first] = 2;
				}
			}
		}
	}
}

/** Decode matrix for DP algorithm
  * @author CuiYuxin
  * @param Mat* R
  * @param Size s
  * @param const vector<char>& Q */
void Algo::Decode(Mat R, Size s, const vector<char>& Q)
{
	int n = 0;
	int count = 0;
	//上个非零元素的位置
	int c = 0;
	int row = 0;
	int num = 0;
	int height = s.height;
	int width = s.width;
	for (int pos = 0; pos < Q.size(); pos++)
	{
		if ('1' == Q[pos])
		{
			pos++;
			if ('1' == Q[pos])
			{
				n = 1;

			}
			else
			{
				pos++;
				if ('1' == Q[pos])
				{
					n = 2;
				}
				else
				{
					n = 3;
				}
			}
		}
		else
		{
			row++;
			count = 0;
			c = 0;
			num = 0;
			continue;
		}
		int b = ceil(log((double)(width - c - count)) / log(2.0f));
		b = b == 0 ? 1 : b;
		count = 1;
		int value = 0;
		for (int i = b - 1; i >= 0; i--)
		{
			pos++;
			if ('1' == Q[pos])
			{
				value += 1 << i;
			}
		}
		if (num == 0)
		{
			c = c + value;
		}
		else
		{
			c = c + value + 1;
		}
		num++;
		R.at<uchar>(row, c) = n;
		if (c == (width - 1))
		{
			row++;
			count = 0;
			c = 0;
			num = 0;
		}
	}
}

