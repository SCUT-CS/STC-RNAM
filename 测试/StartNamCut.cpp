#include "Header.h"

void SetMarkMatrix(CvMat *markMatrix,int x1,int y1,int x2,int y2,int value)
{
	for(int y = y1;y<=y2;y++)
	{
		for(int x = x1;x<=x2;x++)
		{
			(markMatrix->data.ptr + markMatrix->step*y)[x] = value;
		}
	}
}

void StartNamCut(const IplImage *img,CvMat *markMatrix,CvMat *R,vector<ColorNode> &ColorList,vector<Location> &LocList,int height,int width,double margin,int &num,double ratio)
{
	for(int row = 0;row < height;row++)
	{
		for(int col = 0;col < width;col++)
		{
			if((markMatrix->data.ptr+row*markMatrix->step)[col] == 0)
			{
				num++;
				Location loc = FindSameBlock(img,markMatrix,R,col,row,margin,ratio);
				LocList.push_back(loc);
				//Mark
				SetMarkMatrix(markMatrix,loc.x1,loc.y1,loc.x2,loc.y2,1);
				//R
				if(loc.x1 == loc.x2 && loc.y1 == loc.y2)
				{
					uchar * g = R->data.ptr + R->step*loc.y1;
					g[loc.x1] = 3;
					ColorNode node(3,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1]);
					ColorList.push_back(node);
				}
				else if(loc.x1 == loc.x2)
				{
					for(int j=loc.y1;j<=loc.y2;j++)
					{
						uchar *g = R->data.ptr + R->step*j;
						g[loc.x1] = 0;
					}
					(R->data.ptr + R->step*loc.y1)[loc.x1] = 1;
					(R->data.ptr + R->step*loc.y2)[loc.x1] = 2;
					ColorNode node(2,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x1]);
					ColorList.push_back(node);
					
				}
				else
				{
					for(int i=loc.y1;i<=loc.y2;i++)
					{
						for(int j = loc.x1;j<=loc.x2;j++)
						{
							(R->data.ptr + R->step*i)[j] = 0;
						}
					}

					if(loc.y1 == loc.y2)
					{
						ColorNode node(1,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x2]);
						ColorList.push_back(node);
					}
					else
					{
						ColorNode node(0,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x2],
							((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x2]);
						ColorList.push_back(node);
					}


					(R->data.ptr + R->step*loc.y1)[loc.x1] = 1;
					(R->data.ptr + R->step*loc.y2)[loc.x2] = 2;
				}
			}
		}
	}
}