#include "Header.h"
double PSNR(IplImage *img,IplImage *newImg)
{
	int yn = img->height;
	int xn = img->width;
	double sum=0.0;
	for(int i=0;i<yn;i++){
		uchar* imgptr=(uchar*)img->imageData+i*img->widthStep;
		uchar* newImgptr=(uchar*)newImg->imageData+i*newImg->widthStep;
		for(int j=0;j<xn;j++){
			sum+=pow((double)(imgptr[j]-newImgptr[j]),2);
		}
	}
	double temp=255.0*255*xn*yn/sum;
	double PSNRValue=10*log(temp)/log(10.0);
	return PSNRValue;
}