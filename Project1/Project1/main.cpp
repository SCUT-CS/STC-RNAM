#include "Headers.h"
#include "Tree.h"
#include "Algo.h"
#include "Calculate.h"
#include "Segment.h"
#include "Region.h"

int reg_num = 0;
int bitnum = 0;
double thresU = 0;
double thresVar = 0;
int cur_block = -1;
vector<doubleCoordinate> C; //建立坐标表
vector<colorListStandard> P; //建立颜色表

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
		C.clear();
		P.clear();
		vector<char> Q; //建立线性树表
		Tree tree;
		treeIterator it(tree);
		thresU = atof(argv[5]);
		thresVar = atof(argv[6]);
		Mat sketch(img.size(), CV_8UC1);  //创建素描图像
		start = clock(); //Start building tree
		Algo::BuildTree(img, it, P, C, num, epsilon, doubleCoordinate(0, 0, M - 1, N - 1));
		Tree::LevelOrder(Q, it); //寻找同类块，构造线性树表，颜色表,坐标表
		end = clock();
		time = end - start;
		cout << "编码所用时间:" << time << "ms" << endl;
		start = clock();
		end = clock();
		time = end - start;
		cout << "解码所用时间:  " << time << "  ms" << endl << endl;
		cout << "epsilon =  " << epsilon << endl << endl;
		cout << "块数:  " << P.size() << endl << endl;
		cout << fixed << setprecision(4) << "BPP:" << Calculate::BPP(P, img.size(), Q) << endl << endl;
		//cout << fixed << setprecision(4) << "CR:  " << 8.0 / BPP(P, img.size(), Q) << endl << endl;
		convergeStart = clock();
		Region** all_region = new Region * [P.size()];
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
		num = atoi(argv[7]);
		Segment::regionSegm(UpperLeft, UpperRight, PreLowerLeft, SegmentParamI( 0, 0, M, N), all_region, Q, num);
		convergeEnd = clock();
		convergeTime = convergeEnd - convergeStart;
		cout << "converge_time of QSC:  " << convergeTime << "  ms" << endl << endl;
		Region** pixel_region = new Region * [M * N];
		Mat seg = Mat::zeros(img.size(), img.type());
		for (unsigned int i = 0; i < P.size(); i++)
		{
			int x1 = C[i].dot1.first, x2 = C[i].dot2.first;
			int y1 = C[i].dot1.second, y2 = C[i].dot2.second;
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

		//cvShowImage("区域合并示意图1", seg);
		//cvShowImage("区域合并示意图2", seg_line);

		Algo::MakeImggest(imggest, P, C);
		cout << "PSNR of recontructured:  " << PSNR(img, imggest) << endl << endl;
		//cvNamedWindow("灰度化图像", CV_WINDOW_AUTOSIZE);
		//cvShowImage("灰度化图像", img1); //显示原始灰度图像
		//cvNamedWindow("QSC区域分割后的图像", CV_WINDOW_AUTOSIZE);     //区域分割后的图像
		//cvShowImage("QSC区域分割后的图像", imggest);//载入转化后的灰度图像   //区域分割后的图像
		//cvSaveImage(argv[2], img1, 0);//把图像写入文件
		//cvSaveImage(argv[3], imggest, 0);//把图像写入文件
		// //画示意图
		//cvNamedWindow("分割示意图", CV_WINDOW_AUTOSIZE);
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
			// 向原始图像中加矩形时，只需将cvRectangle和cvShowImage("分割示意图",sketch512或sketch);中的sketch或sketch512换为img1即可，共有两处修改！
			
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

			}
			cvShowImage("分割示意图", img1);//载入转化后的灰度图像 */
			//画示意图结束
		}
		else //放大图像
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
			//cvShowImage("分割示意图", img1);//载入转化后的灰度图像 
		 //    //画示意图结束
		}
		//cvSaveImage("二元树分割示意图.bmp", img1, 0);//把图像写入文件 , added by zyp
		//cvSaveImage("二元树区域分割后的图像.bmp", imggest, 0);//把图像写入文件 , added by zyp 重建后的图像
		//cvSaveImage("二元树区域合并示意图1.bmp", seg, 0);//把图像写入文件 , added by zyp  区域合并后用均值填充后的图像
		//cvSaveImage("二元树区域合并示意图2.bmp", seg_line, 0);//把图像写入文件 , added by zyp
		//for (int i = 0; i < C.size(); i++)
		//{
		//	if (C[i].x2 - C[i].x1 == 1)
		//		nmb++;
		//}
		////cout << "2*2块数量："<< nmb << endl;
		//cout << "区域数量：  " << reg_num << endl << endl;
		//cvWaitKey(0); //等待按键
		//cvReleaseImage(&img1);
		//cvReleaseImage(&imggest);
		//cvDestroyAllWindows();//关闭
		return 0;

	}
	else
	{
		return -1;
	}
}


	
