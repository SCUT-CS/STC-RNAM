#include "pch.h"
#include "../Project1/Tree.h"
#include "../Project1/Tree.cpp"
//#include "../Project1/Calculate.h"
//#include "../Project1/Calculate.cpp"
namespace test 
{
	/** Test tree create and add node
	  * @author CuiYuxin */
	TEST(TestTree, TestCase1) {
		Tree t;
		EXPECT_NE(t.getRoot(), nullptr);
		treeIterator it(t.getRoot());
		Tree::addchild(it, nw);
		Tree::addchild(it, ne);
	}
	/** Test treeIterator create and move
      * @author CuiYuxin */
	TEST(TestTree, TestCase2) {
		Tree t;
		EXPECT_NE(t.getRoot(), nullptr);
		treeIterator it(t.getRoot());
		EXPECT_NE(*it, nullptr);
		Tree::addchild(it, nw);
		Tree::addchild(it, ne);		
		EXPECT_TRUE(it.toNwChild());
		EXPECT_TRUE(it.toNeChild());
		EXPECT_FALSE(it.toParent());
		EXPECT_EQ(*it, nullptr);
		treeIterator p(t);
		EXPECT_NE(*p, nullptr);
		EXPECT_NE(*p, *it);
	}
	/** Test Calaulate::PSNR1
      * @author CuiYuxin */
	TEST(TestCalculate, TestPSNR1)
	{
		//include <windows.h>
		//Óë namespace cv ³åÍ»
		//int bufferSize = GetCurrentDirectory(0, NULL);
		//TCHAR* dir = new TCHAR[bufferSize];
		//GetCurrentDirectory(bufferSize, dir);
		//CurrentDirectory:"C:\Users\L-kanshan\OneDrive - arocyx\ÎÄµµ\GitHub\Project-1\Project1\Project1\x64\Debug"
		
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
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}