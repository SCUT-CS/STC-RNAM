#include "STCInterface.h"

/** STC algorithm
  * @author CuiYuxin */
bool STCAlgo::STC(String fileDir, String grayDir, String imgDir, int margin, int ratio, int variance, int cutMethod)
{
	Varialbes vars;
	int nmb = 0;
	Mat img;
	img = imread(fileDir, 0); //将源彩色图像img转化成目标灰色图像读入
	if (!img.empty())
	{
		time_t start, end, time, convergeStart, convergeEnd; //计时变量
		Mat imggest = Mat::zeros(img.size(), img.type());
		int num = cutMethod;
		int M = img.rows; //图像高度
		int N = img.cols; //图像宽度
		double epsilon = margin;
		vector<char> Q; //建立线性树表
		Tree tree;
		treeIterator it(tree);
		vars.thresU =ratio;
		vars.thresVar = variance;
		Mat sketch(img.size(), CV_8UC1);  //创建素描图像
		
		start = clock(); //Start building tree
		Algo::BuildTree(img, it, vars.P, vars.C, num, epsilon, doubleCoordinate(0, 0, M - 1, N - 1));
		Tree::LevelOrder(Q, it); //寻找同类块，构造线性树表，颜色表,坐标表
		end = clock();
		codeTime = end - start;
		blockNum = vars.P.size();
		bpp = Calculate::BPP(vars.P, img.size(), Q) ;
		cr =  8.0 / bpp;
		
		convergeStart = clock();
		Region** all_region = new Region * [vars.P.size()];
		Segment* UpperLeft = new Segment;
		Segment* Upper = new Segment;
		UpperLeft->Length = M;
		UpperLeft->ActiveELink = nullptr;
		UpperLeft->PreLink = nullptr;
		UpperLeft->SucLink = Upper;
		Upper->Length = M;
		Upper->ActiveELink = nullptr;
		Upper->PreLink = UpperLeft;
		Upper->SucLink = nullptr;
		Segment* UpperRight = nullptr;
		Segment* PreLowerLeft = nullptr;
		num = variance;
		Segment::regionSegm(UpperLeft, UpperRight, PreLowerLeft, SegmentParamI(0, 0, M, N), all_region, Q, num, vars);
		convergeEnd = clock();
		cverTime = convergeEnd - convergeStart;
		
		Region** pixel_region = new Region * [M * N];
		Mat seg = Mat::zeros(img.size(), img.type());
		for (unsigned int i = 0; i < vars.P.size(); i++)
		{
			int x1 = vars.C[i].dot1.first, x2 = vars.C[i].dot2.first;
			int y1 = vars.C[i].dot1.second, y2 = vars.C[i].dot2.second;
			for (int y = y1; y <= y2; y++)
			{
				uchar* ptrsketch = (uchar*)(seg.data + y * seg.step);
				for (int x = x1; x <= x2; x++)
				{
					ptrsketch[x] = Region::FindParent(all_region[i])->Mean;
					pixel_region[y * N + x] = Region::FindParent(all_region[i]);
				}
			}
		}
		Mat segLine = Mat::zeros(img.size(), img.type());
		for (int y = 0; y < M; y++)
		{
			uchar* ptrsketch = (uchar*)(segLine.data + y * segLine.step);
			for (int x = 0; x < N; x++)
			{
				if (x == N - 1 || y == M - 1)
				{
					ptrsketch[x] = 0;
					break;
				}
				ptrsketch[x] = (pixel_region[y * N + x] != pixel_region[y * N + x + 1] || pixel_region[y * N + x] != pixel_region[(y + 1) * N + x]) ? 0 : 255;
			}
		}
		for (int y = 0; y < M; y++)
		{
			uchar* ptrsketch = (uchar*)(segLine.data + y * segLine.step);
			for (int x = 0; x < N; x++)
			{
				if ((y == 0) || (y == M - 1))
					ptrsketch[x] = 0;
				else if ((x == 0))
					ptrsketch[x] = 0;
			}
		}
		Algo::MakeImggest(imggest, vars.P, vars.C);
		psnr = PSNR(img, imggest);
		//保存图片
		//cvShowImage("区域合并示意图1", seg);
	    //cvShowImage("区域合并示意图2", seg_line);
		//cvSaveImage(grayDir, img, 0);//显示原始灰度图像
		//cvSaveImage(imgDir, imggest, 0); //区域分割后的图像

		//画示意图
		if (N >= 256 || M >= 256)
		{
			//创建素描图像
			Mat sketch = Mat::zeros(img.size(), img.type());
			for (int y = 0; y < M; y++)
			{
				uchar* ptrsketch = (uchar*)(sketch.data + y * sketch.step);

				for (int x = 0; x < N; x++)
				{
					ptrsketch[x] = 255;
				}
			}
			//素描图像初始化完成
			//向原始图像中加矩形时，只需将cvRectangle和cvShowImage("分割示意图",sketch512或sketch);中的sketch或sketch512换为img1即可，共有两处修改！
			/*for (int i = 0; i < C.size(); i++)
			{
				if (C[i].x1 == 0 && C[i].y1 == 0)
					cvRectangle(img1, cvPoint(C[i].x1, C[i].y1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
				else   if (C[i].x1 == 0 && C[i].y1 != 0)
					cvRectangle(img1, cvPoint(C[i].x1, C[i].y1 - 1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
				else   if (C[i].x1 != 0 && C[i].y1 == 0)
					cvRectangle(img1, cvPoint(C[i].x1 - 1, C[i].y1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
				else   if (C[i].x1 != 0 && C[i].y1 != 0)
					cvRectangle(img1, cvPoint(C[i].x1 - 1, C[i].y1 - 1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));

			}*/
		}
		else
		{
			////创建素描图像
			//IplImage* sketch512 = cvCreateImage(cvSize(512, 512), IPL_DEPTH_8U, 1);
			//int xr = 511 / (N - 1);
			//int yr = 511 / (M - 1);
			//for (int y = 0; y < 512; y++)
			//{
			//	uchar* ptrsketch = (uchar*)(sketch512->imageData + y * sketch512->widthStep);

			//	for (int x = 0; x < 512; x++)
			//	{
			//		ptrsketch[x] = 255;
			//	}
			//}
			////素描图像初始化完成
			//for (int i = 0; i < C.size(); i++)
			//{
			//	if (C[i].x1 == 0 && C[i].y1 == 0)
			//		cvRectangle(img1, cvPoint(C[i].x1 * xr, C[i].y1 * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
			//	else   if (C[i].x1 == 0 && C[i].y1 != 0)
			//		cvRectangle(img1, cvPoint(C[i].x1 * xr, (C[i].y1 - 1) * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
			//	else   if (C[i].x1 != 0 && C[i].y1 == 0)
			//		cvRectangle(img1, cvPoint((C[i].x1 - 1) * xr, C[i].y1 * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
			//	else   if (C[i].x1 != 0 && C[i].y1 != 0)
			//		cvRectangle(img1, cvPoint((C[i].x1 - 1) * xr, (C[i].y1 - 1) * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));

			//}
		}

		//保存图像
		//cvSaveImage("二元树分割示意图.bmp", img1, 0);
		//cvSaveImage("二元树区域分割后的图像.bmp", imggest, 0);//重建后的图像
		//cvSaveImage("二元树区域合并示意图1.bmp", seg, 0);//区域合并后用均值填充后的图像
		//cvSaveImage("二元树区域合并示意图2.bmp", seg_line, 0);
		for (int i = 0; i < vars.C.size(); i++)
		{
			if (vars.C[i].dot2.first - vars.C[i].dot1.first == 1)
				nmb++;
		}
		blockNum_2 = nmb ;
		areaNum = vars.reg_num ;
		//cvReleaseImage(&img1);
		//cvReleaseImage(&imggest);
		return true;
	}
	else
	{
		return false;
	}
}
