#include "Headers.h"
#include "Tree.h"
#include "Algo.h"

int reg_num = 0;
int bitnum = 0;
double thresU = 0;
double thresVar = 0;
int cur_block = -1;

/** Main Function
  * @author CuiYuxin
  * @input 1.程序地址
  * @input 2.原彩图
  * @input 3.转坏灰度图文件名
  * @input 4.转换RNAMC文件名
  * @input 5.同类快阀值
  * @input 6.均值阀值
  * @input 7.方差阀值
  * @input 8.切法 1 水平 0垂直
  */
int main(int argc, char** argv)
{
	int nmb = 0;
	Mat img;
	string imagePath = samples::findFile(argv[1]);
	img = imread(imagePath, 0); //将源彩色图像img转化成目标灰色图像读入
	if (argc == 8 && !img.empty())
	{
		time_t start, end, time, convergeStart, convergeEnd, convergeTime; //计时变量
		Mat imggest = Mat::zeros(img.size(), img.type());
		int num = atoi(argv[7]);
		int M = img.rows; //图像高度
		int N = img.cols; //图像宽度
		double epsilon = atof(argv[4]);
		vector<doubleCoordinate> C; //建立坐标表
		vector<colorListStandard> P; //建立颜色表
		vector<char> Q; //建立线性树表
		Tree tree;
		treeIterator it(tree);
		thresU = atof(argv[5]);
		thresVar = atof(argv[6]);
		Mat sketch(img.size(), CV_8UC1);  //创建素描图像
		start = clock(); //Start building tree
		treeIterator(tree);
		Algo::BuildTree(img, it, P, C, num, epsilon, doubleCoordinate(0, 0, M - 1, N - 1));

		

		
	}



	
}