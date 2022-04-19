#include "pch.h"
#include "../Project1/Tree.cpp"
#include "../Project1/Calculate.cpp"
#include "../Project1/Headers.cpp"
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
		EXPECT_TRUE(it.toNeChild());
		EXPECT_FALSE(it.toParent());
		EXPECT_EQ(*it, nullptr);
		treeIterator p(t);
		EXPECT_NE(*p, nullptr);
		EXPECT_NE(*p, *it);
	}
	
	/** Test tree method
      * @author CuiYuxin */
	TEST(TestTree, Testmethod) {
		Tree t;
		treeIterator it(t);
		t.addchild (it, nw);
		t.addchild (it, ne);
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
		Tree::deleteChildNode(it,ne);
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
	TEST(TestHeaders, Struct)
	{
		colorListStandard c;
		c.setFirstHalf('1', '2');
		c.setLastHalf('3', '4');
		EXPECT_EQ(c.g1, '1');
		EXPECT_EQ(c.g2, '2');
		EXPECT_EQ(c.g3, '3');
		EXPECT_EQ(c.g4, '4');
		doubleCoordinate d1;
		d1.setCoordinate(1, 2, 3, 4);
		EXPECT_EQ(d1.dot1.first, 1);
		EXPECT_EQ(d1.dot1.second, 2);
		EXPECT_EQ(d1.dot2.first, 3);
		EXPECT_EQ(d1.dot2.second, 4);
		doubleCoordinate d2(1,2,3,4);
		EXPECT_EQ(d2.dot1.first, 1);
		EXPECT_EQ(d2.dot1.second, 2);
		EXPECT_EQ(d2.dot2.first, 3);
		EXPECT_EQ(d2.dot2.second, 4);
	}
	
	
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}