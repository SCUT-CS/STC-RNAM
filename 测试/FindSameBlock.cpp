#include "Header.h"

bool IsSameBlock(const IplImage *img,int x1,int y1,int x2,int y2,int margin)
{
	uchar *gy1 = (uchar*)img->imageData + y1*img->widthStep;
	uchar *g1 = gy1 + x1;
	uchar *g2 = gy1 + x2;
	uchar *gy2 = (uchar*)img->imageData + y2*img->widthStep;
	uchar *g3 = gy2 + x1;
	uchar *g4 = gy2 + x2;
	bool returnValue = true;

	if(x1 == x2  && y1 == y2)
	{
		returnValue = true;
	}
	else if(y1 == y2)
	{
		for(int x = x1+1;x<x2;x++)
		{
			double i2 = (double)(x - x1) / (double)(x2 - x1);
			double g = *g1 + (*g4 - *g1)*i2;
			uchar *gValue = gy1 + x;
			if(abs(*gValue - g) > margin)
			{
				returnValue = false;
				break;
			}

		}
	}
	else if(x1 == x2)
	{
		for(int y=y1+1;y<y2;y++)
		{
			double i1 = (double)(y-y1) / (double)(y2 - y1);
			double g = *g1 + (*g4 - *g1)*i1;
			uchar *gy = (uchar*)img->imageData + y*img->widthStep;
			uchar *gValue = gy + x1;
			if(abs(*gValue - g) >margin)
			{
				returnValue = false;
				break;
			}
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
				double g5 = *g1 + (*g2 - *g1)*i2;
				double g6 = *g3 + (*g4 - *g3)*i2;
				double g = g5 + (g6 - g5) *i1;
				uchar *gy = (uchar*)img->imageData + y*img->widthStep;
			    uchar *gValue = gy + x;
				if(abs(*gValue - g) >margin)
				{
					returnValue = false;
					break;
				}
			}
		}
	}

	return returnValue;
}

Location FindSameBlock(const IplImage *img,CvMat *markMatrix,CvMat *R,int x1,int y1,double margin,double ratio)
{
	int x2(x1),y2(y1);

	while (x2<img->width && y2<img->height && (markMatrix->data.ptr+y1*markMatrix->step)[x2]== 0 && (markMatrix->data.ptr+y2*markMatrix->step)[x1] == 0)
	{
		if(!IsSameBlock(img,x1,y1,x2,y2,margin))
			break;

		x2++;
		y2++;

	}

	x2--;
    y2--;

	int endX = x2;

	int maxX = ratio == 0?INT_MAX:(y2-y1+1)*ratio;

	while (x2 < img->width && (x2-x1 < maxX)&& (markMatrix->data.ptr+y1*markMatrix->step)[x2]== 0)
	{
		if(!IsSameBlock(img,x1,y1,x2,y2,margin))
		{
			break;
		}
		x2++;
    }
	x2--;

	int tempX = x2;
	int tempY = y2;
	
	x2 = endX;
	int maxY = ratio == 0?INT_MAX:(x2-x1+1)*ratio;
	while (y2 < img->height && (y2-y1<maxY))
	{
		if(!IsSameBlock(img,x1,y1,x2,y2,margin))
		{
			break;
		}

		y2 = y2+1;
	}

	y2--;

	if(/*ratio !=0 &&*/((tempX-x1+1)*(tempY-y1+1) >= (x2-x1+1)*(y2-y1+1)) )
	{
		x2 = tempX;
		y2 = tempY;
	}
	
	Location loc(x1,y1,x2,y2);

	return loc;
}