#include "Header.h"

void RestoreImage(IplImage *img,CvMat *markMatrix,CvMat *R,vector<ColorNode> cn,int height,int width)
{
	int x1(0),x2(0),y1(0),y2(0);

	for(vector<ColorNode>::iterator it=cn.begin();it != cn.end();it++)
	{
		int i = 0;
		//先查找下一个未计算的分块 起点坐标
		while(x2<width)
		{
			if((markMatrix->data.ptr + markMatrix->step*y2)[x2++] == 1)
				break;
			

			if(x2 == width)
			{
				x1 = x2 = 0;
				y1 = ++y2;
			}

		}

		x1 = --x2;

		//再查找出这个块的 (x1,y1) (x2,y2)
		if(0 == (*it).kind)
		{
			while(x2<width)
			{
				//x2要先走一步
				if((R->data.ptr + R->step*y2)[++x2]!=0 || (markMatrix->data.ptr + markMatrix->step*y2)[x2] == 0)
					break;
			}

			x2--;

			while(y2<height)
			{
				if((R->data.ptr + R->step*y2)[x2] == 2 || (markMatrix->data.ptr + markMatrix->step*y2)[x2] == 0)
					break;
				y2++;
			}

		}
		else if(1 == (*it).kind)
		{
			while(x2<width)
			{
				if((R->data.ptr + R->step*y2)[++x2] ==2)
					break;
			}
		}
		else if(2 == (*it).kind)
		{
			while(y2<height)
			{
				if((R->data.ptr + R->step*y2)[x2] == 2)
					break;
				y2++;
			}
		}
		
		//cout<<"("<<x1<<","<<y1<<")("<<x2<<","<<y2<<")"<<endl;
		RestoreImageValue(img,*it,x1,y1,x2,y2);
		
		//Mark

		SetMarkMatrix(markMatrix,x1,y1,x2,y2,0);


		x1 = x2;
		y2=y1;
		
	}
}

void RestoreImageValue(IplImage *img,ColorNode node,int x1, int y1,int x2,int y2)
{
	uchar *upPtr = (uchar*)(img->imageData + img->widthStep*y1);
	uchar *downPtr = (uchar*)(img->imageData + img->widthStep*y2);

	if(3 == node.kind)
	{
		upPtr[x1] = node.g1;
	}
	else if(1 == node.kind)
	{
		upPtr[x1] = node.g1;
		upPtr[x2] = node.g2;
		for(int x = x1+1;x<x2;x++)
		{
			double i2 = (double)(x - x1) / (double)(x2 - x1);
			upPtr[x] =(int)(node.g1 + (node.g2 - node.g1)*i2);
			
		}
	}
	else if(2 == node.kind)
	{
		upPtr[x1] = node.g1;
		downPtr[x1] = node.g2;
		for(int y=y1+1;y<y2;y++)
		{
			double i1 = (double)(y-y1) / (double)(y2 - y1);
			(img->imageData + img->widthStep*y)[x1] = (int)(node.g1 + (node.g2 - node.g1)*i1);
			
		}
	}
	else
	{
		for(int x = x1; x<=x2;x++)
		{
			for(int y = y1;y<=y2;y++)
			{
				double i1 = (double)(y - y1)/(double)(y2 - y1);
				double i2 = (double)(x - x1)/(double)(x2 - x1);
				double g5 = node.g1 + (node.g2 - node.g1)*i2;
				double g6 = node.g3 + (node.g4 - node.g3)*i2;
				(img->imageData + img->widthStep*y)[x] =(int)(g5 + (g6 - g5) *i1);
				
			}
		}

		upPtr[x1] = node.g1;
		upPtr[x2] = node.g2;
		downPtr[x1] = node.g3;
		downPtr[x2] = node.g4;
	}
}