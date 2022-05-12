#include "pch.h"
#include "../Project1/Tree.cpp"
#include "../Project1/Calculate.cpp"
#include "../Project1/Headers.cpp"
#include "../Project1/Algo.cpp"
#include "../Project1/Segment.cpp"
#include "../Project1/Region.cpp"
#include "../Project1/Variables.h"

namespace test
{
	/** Test tree create and add node
	  * @author CuiYuxin */
	TEST(TestTree, TestCreate) {
		Tree t;
		EXPECT_NE(t.getRoot(), nullptr);
		treeIterator it(t.getRoot());
		Tree::addchild(it, nw);
		Tree::addchild(it, ne);
	}

	/** Test treeIterator create and move
	  * @author CuiYuxin */
	TEST(TestTree, TestIterator) {
		Tree t;
		EXPECT_NE(t.getRoot(), nullptr);
		treeIterator it(t.getRoot());
		EXPECT_NE(*it, nullptr);
		Tree::addchild(it, nw);
		Tree::addchild(it, ne);
		EXPECT_TRUE(it.toNwChild());
		EXPECT_FALSE(it.toNeChild());
		EXPECT_TRUE(it.toParent());
		EXPECT_NE(*it, nullptr);
		treeIterator p(t);
		EXPECT_NE(*p, nullptr);
		EXPECT_EQ(*p, *it);
	}

	/** Test tree method
	  * @author CuiYuxin */
	TEST(TestTree, Testmethod) {
		Tree t;
		treeIterator it(t);
		t.addchild(it, nw);
		t.addchild(it, ne);
		Tree::setConfirm(it, '1');
		EXPECT_EQ(Tree::getConfirm(it), '1');
		Tree::setChildConfirm(it, 'e', ne);
		Tree::setChildConfirm(it, 'w', nw);
		treeIterator pNE, pNW;
		pNE = it.getNeChild();
		pNW = it.getNwChild();
		EXPECT_EQ(Tree::getConfirm(pNE), 'e');
		EXPECT_EQ(Tree::getConfirm(pNW), 'w');
		EXPECT_EQ(*(pNE.getParent()), *it);
		Tree::deleteChildNode(it, ne);
		EXPECT_EQ(*(it.getNeChild()), nullptr);
	}

	/** Test Calaulate::PSNR1
	  * @author CuiYuxin */
	TEST(TestCalculate, TestPSNR1)
	{
		//include <windows.h>
		//与 namespace cv 冲突
		//int bufferSize = GetCurrentDirectory(0, NULL);
		//TCHAR* dir = new TCHAR[bufferSize];
		//GetCurrentDirectory(bufferSize, dir);
		//CurrentDirectory:"C:\Users\L-kanshan\OneDrive - arocyx\文档\GitHub\Project-1\Project1\Project1\x64\Debug"

		string image_path1 = samples::findFile("../../gray_images/1_gray256.bmp");
		Mat img1 = imread(image_path1, 0);
		Mat imggest1 = Mat::zeros(img1.size(), img1.type());
		double res1 = PSNR(img1, imggest1);
		EXPECT_EQ(res1, 2.2584888242135288);
	}

	/** Test Calaulate::PSNR1
	  * @author CuiYuxin */
	TEST(TestCalculate, TestPSNR2)
	{
		string image_path2 = samples::findFile("../../gray_images/bigbuildingzyp256.bmp");
		Mat img2 = imread(image_path2, 0);
		Mat imggest2 = Mat::zeros(img2.size(), img2.type());
		double res2 = PSNR(img2, imggest2);
		EXPECT_EQ(res2, 2.0676017009525007);
	}

	/** Test Calaulate::BPP1
	  * @author CuiYuxin */
	TEST(TestCalculate, TestBPP1)
	{
		string image_path1 = samples::findFile("../../gray_images/flightzyp512.bmp");
		Mat img1 = imread(image_path1, 0);
		vector<colorListStandard> P;//建立颜色表
		vector<char> Q;//建立线性树表
		P.resize(5010);
		Q.resize(3990);
		double res1 = Calculate::BPP(P, img1.size(), Q);
		//EXPECT_EQ(res1, 0.62679290771484375 , 0.0000001); //第三个参数是允许误差
		EXPECT_EQ(res1, 0.62679290771484375);
	}

	/** Test Calaulate::BPP2
	  * @author CuiYuxin */
	TEST(TestCalculate, TestBPP2)
	{
		string image_path2 = samples::findFile("../../gray_images/bigbuildingzyp256.bmp");
		Mat img2 = imread(image_path2, 0);
		vector<colorListStandard> P;//建立颜色表
		vector<char> Q;//建立线性树表
		P.resize(23);
		Q.resize(16);
		double res2 = Calculate::BPP(P, img2.size(), Q);
		EXPECT_EQ(res2, 0.011474609375000000);
	}

	/** Test Headers::Struct
	  * @author CuiYuxin */
	TEST(TestHeaders, TestStruct)
	{
		colorListStandard c;
		c.setFirstHalf('1', '2');
		c.setLastHalf('3', '4');
		EXPECT_EQ(c.g1, '1');
		EXPECT_EQ(c.g2, '2');
		EXPECT_EQ(c.g3, '3');
		EXPECT_EQ(c.g4, '4');
		DoubleDots d1;
		d1.setCoordinate(1, 2, 3, 4);
		EXPECT_EQ(d1.dot1.first, 1);
		EXPECT_EQ(d1.dot1.second, 2);
		EXPECT_EQ(d1.dot2.first, 3);
		EXPECT_EQ(d1.dot2.second, 4);
		DoubleDots d2(1, 2, 3, 4);
		EXPECT_EQ(d2.dot1.first, 1);
		EXPECT_EQ(d2.dot1.second, 2);
		EXPECT_EQ(d2.dot2.first, 3);
		EXPECT_EQ(d2.dot2.second, 4);
	}

	/** Test Algo::judgeSameBlock
	  * @author CuiYuxin */
	TEST(TestAlgo, TestJudgeSameBlock)
	{
		Mat img;
		string imagePath = samples::findFile("../../gray_images/1_gray256.bmp");
		img = imread(imagePath, 0); //将源彩色图像img转化成目标灰色图像读入
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(168, 172, 175, 175)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(180, 162, 183, 163)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(184, 164, 187, 165)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(188, 168, 191, 171)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(160, 180, 167, 183)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(160, 188, 167, 191)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(168, 188, 175, 191)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(188, 178, 191, 179)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(184, 180, 187, 181)));
		EXPECT_FALSE(Algo::JudgeSameBlock(10, img, DoubleDots(212, 136, 215, 137)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(220, 136, 221, 137)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(196, 146, 199, 147)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(206, 144, 207, 145)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(202, 150, 203, 151)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(198, 152, 199, 153)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(204, 156, 207, 159)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(216, 156, 217, 157)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(244, 140, 245, 141)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(192, 164, 193, 165)));
		EXPECT_TRUE(Algo::JudgeSameBlock(10, img, DoubleDots(194, 168, 195, 169)));
	}

	/** Test Algo::bulidTree
	  * @author CuiYuxin */
	TEST(TestAlgo, TestBuildTree1)
	{
		Mat img;
		string imagePath = samples::findFile("../../gray_images/flightzyp512.bmp");
		img = imread(imagePath, 0); //将源彩色图像img转化成目标灰色图像读入
		int num = 3; //test
		int M = img.rows; //图像高度
		int N = img.cols; //图像宽度
		double epsilon = 10; //test
		vector<DoubleDots> C; //建立坐标表
		vector<colorListStandard> P; //建立颜色表
		Tree tree;
		treeIterator it(tree);
		Algo::BuildTree(img, it, P, C, num, epsilon, DoubleDots(0, 0, M - 1, N - 1));
		ASSERT_EQ(P.size(), 19718);
		ASSERT_EQ(C.size(), 19718);
		ASSERT_EQ((int)P[9866].g1, 116);
		ASSERT_EQ((int)P[9866].g2, 102);
		ASSERT_EQ((int)P[9866].g3, 126);
		ASSERT_EQ((int)P[9866].g4, 105);
		ASSERT_EQ(C[1025].dot1.first, 220);
		ASSERT_EQ(C[1025].dot1.second, 70);
		ASSERT_EQ(C[1025].dot2.first, 223);
		ASSERT_EQ(C[1025].dot2.second, 71);
		ASSERT_EQ(Tree::getConfirm(it), '0');
		ASSERT_EQ(Tree::getConfirm(it.getNeChild().getNeChild()), '0');
		ASSERT_EQ(Tree::getConfirm(it.getNwChild()), '0');
	}

	/** Test Algo::bulidTree
	  * @author CuiYuxin */
	TEST(TestAlgo, TestBuildTree2)
	{
		Mat img;
		string imagePath = samples::findFile("../../gray_images/1_gray256.bmp");
		img = imread(imagePath, 0); //将源彩色图像img转化成目标灰色图像读入
		int num = 3; //test
		int M = img.rows; //图像高度
		int N = img.cols; //图像宽度
		double epsilon = 10; //test
		vector<DoubleDots> C; //建立坐标表
		vector<colorListStandard> P; //建立颜色表
		Tree tree;
		treeIterator it(tree);
		Algo::BuildTree(img, it, P, C, num, epsilon, DoubleDots(0, 0, M - 1, N - 1));
		ASSERT_EQ(P.size(), 6986);
		ASSERT_EQ(C.size(), 6986);
		ASSERT_EQ((int)P[2578].g1, 75);
		ASSERT_EQ((int)P[2578].g2, 102);
		ASSERT_EQ((int)P[2578].g3, 90);
		ASSERT_EQ((int)P[2578].g4, 175);
		ASSERT_EQ(C[5612].dot1.first, 252);
		ASSERT_EQ(C[5612].dot1.second, 190);
		ASSERT_EQ(C[5612].dot2.first, 255);
		ASSERT_EQ(C[5612].dot2.second, 191);
		ASSERT_EQ(Tree::getConfirm(it), '0');
		ASSERT_EQ(Tree::getConfirm(it.getNeChild().getNeChild()), '0');
		ASSERT_EQ(Tree::getConfirm(it.getNwChild()), '0');
	}

	/** Test Tree::LevelOrder
	  * @author CuiYuxin */
	TEST(TestTree, TestLevelOrder1)
	{
		Mat img;
		string imagePath = samples::findFile("../../gray_images/flightzyp512.bmp");
		img = imread(imagePath, 0); //将源彩色图像img转化成目标灰色图像读入
		int num = 3; //test
		int M = img.rows; //图像高度
		int N = img.cols; //图像宽度
		double epsilon = 10; //test
		vector<DoubleDots> C; //建立坐标表
		vector<colorListStandard> P; //建立颜色表
		Tree tree;
		treeIterator it(tree);
		Algo::BuildTree(img, it, P, C, num, epsilon, DoubleDots(0, 0, M - 1, N - 1));
		vector<char> Q; //建立线性树表
		Tree::LevelOrder(Q, it); //寻找同类块，构造线性树表，颜色表,坐标表
		ASSERT_EQ(Q.size(), 39435);
		ASSERT_EQ(Q[0], '0');
		ASSERT_EQ(Q[102], '1');
		ASSERT_EQ(Q[1023], '1');
		ASSERT_EQ(Q[10666], '0');
		ASSERT_EQ(Q[31239], '1');
	}

	/** Test Tree::LevelOrder
	  * @author CuiYuxin */
	TEST(TestTree, TestLevelOrder2)
	{
		Mat img;
		string imagePath = samples::findFile("../../gray_images/1_gray256.bmp");
		img = imread(imagePath, 0); //将源彩色图像img转化成目标灰色图像读入
		int num = 3; //test
		int M = img.rows; //图像高度
		int N = img.cols; //图像宽度
		double epsilon = 10; //test
		vector<DoubleDots> C; //建立坐标表
		vector<colorListStandard> P; //建立颜色表
		Tree tree;
		treeIterator it(tree);
		Algo::BuildTree(img, it, P, C, num, epsilon, DoubleDots(0, 0, M - 1, N - 1));
		vector<char> Q; //建立线性树表
		Tree::LevelOrder(Q, it); //寻找同类块，构造线性树表，颜色表,坐标表
		ASSERT_EQ(Q.size(), 13971);
		ASSERT_EQ(Q[0], '0');
		ASSERT_EQ(Q[102], '0');
		ASSERT_EQ(Q[1023], '0');
		ASSERT_EQ(Q[10666], '1');
	}

	/** Test Segment::regionSegm
	  * @author CuiYuxin */
	TEST(TestSegment, TestRegionSegm)
	{
		Varialbes vars;
		Mat img;
		string imagePath = samples::findFile("../../gray_images/flightzyp512.bmp");
		img = imread(imagePath, 0); //将源彩色图像img转化成目标灰色图像读入
		int num = 3; //test
		int M = img.rows; //图像高度
		int N = img.cols; //图像宽度
		double epsilon = 10; //test
		Tree tree;
		treeIterator it(tree);
		Algo::BuildTree(img, it, vars.P, vars.C, num, epsilon, DoubleDots(0, 0, M - 1, N - 1));
		Tree::LevelOrder(vars.Q, it); //寻找同类块，构造线性树表，颜色表,坐标表
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
		num = 1; //test
		Segment::regionSegm(UpperLeft, UpperRight, PreLowerLeft, SegmentParamI(0, 0, M, N), all_region, vars.Q, num, vars);
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

		ASSERT_EQ(vars.C.size(), 19718);
		ASSERT_EQ(vars.P.size(), 19718);
		ASSERT_EQ(vars.Q.size(), 39435);

		ASSERT_EQ(vars.C[10023].dot1.first, 184);
		ASSERT_EQ(vars.C[10023].dot2.first, 187);
		ASSERT_EQ((int)vars.P[3669].g3, 195);
		ASSERT_EQ(vars.Q[12287], '1');

		ASSERT_EQ((int)seg.at<uchar>(256, 256), 106);
		ASSERT_EQ((int)seg.at<uchar>(84, 413), 256 - 53);
		ASSERT_EQ((int)seg.at<uchar>(467, 89), 256 - 47);
		ASSERT_EQ((int)seg.at<uchar>(425, 426), 256 - 43);
		ASSERT_EQ((int)seg.at<uchar>(81, 86), 256 - 51);

		ASSERT_EQ((int)segLine.at<uchar>(256, 256), 256 - 1);
		ASSERT_EQ((int)segLine.at<uchar>(84, 84), 256 - 1);
		ASSERT_EQ((int)segLine.at<uchar>(84, 413), 256 - 1);
		ASSERT_EQ((int)segLine.at<uchar>(467, 89), 256 - 1);
		ASSERT_EQ((int)segLine.at<uchar>(425, 426), 256 - 1);
		ASSERT_EQ((int)segLine.at<uchar>(0, 0), 0);
	}

	/** Test Algo::MakeImggest
	  * @author CuiYuxin */
	TEST(TestAlgo, TestMakeImggest)
	{
		Varialbes vars;
		Mat img;
		string imagePath = samples::findFile("../../gray_images/flightzyp512.bmp");
		img = imread(imagePath, 0); //将源彩色图像img转化成目标灰色图像读入
		int num = 3; //test
		int M = img.rows; //图像高度
		int N = img.cols; //图像宽度
		double epsilon = 10; //test
		Tree tree;
		treeIterator it(tree);
		Algo::BuildTree(img, it, vars.P, vars.C, num, epsilon, DoubleDots(0, 0, M - 1, N - 1));
		Tree::LevelOrder(vars.Q, it); //寻找同类块，构造线性树表，颜色表,坐标表
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
		num = 1; //test
		Segment::regionSegm(UpperLeft, UpperRight, PreLowerLeft, SegmentParamI(0, 0, M, N), all_region, vars.Q, num, vars);
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
		Mat imggest = Mat::zeros(img.size(), img.type());
		Algo::MakeImggest(imggest, vars.P, vars.C);
		ASSERT_EQ((int)imggest.at<uchar>(55, 258), 256 - 60);
	}

	/** Test Algo::Encode
	  * @author CuiYuxin */
	TEST(TestAlgo, TestEncode)
	{
		// TODO
	}

	/** Test Algo::Decode
	  * @author CuiYuxin */
	TEST(TestAlgo, TestDecode)
	{
		// TODO
	}

	/** Test Algo::IsSameBlock
	  * @author CuiYuxin */
	TEST(TestAlgo, TestIsSameBlock)
	{
		// TODO
	}

	/** Test Algo::FindSameBlockk
	  * @author CuiYuxin */
	TEST(TestAlgo, TestFindSameBlock)
	{
		// TODO
	}

	/** Test Algo::RestoreImage
	  * @author CuiYuxin */
	TEST(TestAlgo, TestRestoreImage)
	{
		// TODO
	}

	/** Test Algo::RestoreImageValue
	  * @author CuiYuxin */
	TEST(TestAlgo, TestRestoreImageValue)
	{
		// TODO
	}

	/** Test Algo::StartNamCut
	  * @author CuiYuxin */
	TEST(TestAlgo, TestStartNamCut)
	{
		// TODO
	}

}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}