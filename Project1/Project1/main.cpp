#include "DPInterface.h"
#include "STCInterface.h"

void demoSTC();
void demoDP();

int main(int argc, char** argv)
{
	//demoSTC();
	//demoDP();
}

/** STC Algorithm demo
  * @author CuiYuxin */
void demoSTC()
{
	STCAlgo demo;
	demo.STC("D:/gray_images/lena512.bmp",  "D:/out/", 10, 30, 225, 1); // TODO 保证输出文件夹存在&输入文件名
	cout << "编码所用时间" << demo.codeTime;
	cout << "块数" << demo.blockNum;
	cout << "BPP" << demo.bpp;
	cout << "CR" << demo.cr;
	cout << "Converage time of QSC" << demo.cverTime;
	cout << "2*2块数量" << demo.blockNum_2;
	cout << "PSNR"; demo.psnr;
	cout << "区域数量" << demo.areaNum;
}

/** DP Algorithm demo
  * @author CuiYuxin */
void demoDP()
{
	DPAlgo demo;
	demo.DP("D:/gray_images/lena512.bmp", "D:/out/", 10, 0);
	cout << "编码所用时间"
		<< demo.encodeTime
		<< "解码所用时间"
		<< demo.decodeTime
		<< "块数"
		<< demo.blockNum
		<< "PSNR"
		<< demo.psnr
		<< "BPP"
		<< demo.bpp
		<< "CR"
		<< demo.cr;
}