#include "Header.h"

//../gray_images/barbarazyp512.bmp ../gray_images/barbarazyp512XXXgray.bmp ../gray_images/barbarazyp512XXXrnamc.bmp 20 0

//../gray_images/cameraman512.bmp  ../gray_images/barbarazyp512XXXgray.bmp ../gray_images/barbarazyp512XXXrnamc.bmp 10 0
//../gray_images/boatzyp512.bmp  ../gray_images/barbarazyp512XXXgray.bmp ../gray_images/barbarazyp512XXXrnamc.bmp 10 0
//../gray_images/lenazyp512.bmp  ../gray_images/barbarazyp512XXXgray.bmp ../gray_images/barbarazyp512XXXrnamc.bmp 10 0
//../gray_images/flightzyp512.bmp  ../gray_images/barbarazyp512XXXgray.bmp ../gray_images/barbarazyp512XXXrnamc.bmp 10 0


//"大作业test.exe" C:\\Users\\Admin\\Desktop\\gray_images\\barbarazyp512.bmp C:\\Users\\Admin\\Desktop\\gray_images\barbarazyp512XXXgray.bmp C:\\Users\\Admin\\Desktop\gray_images\barbarazyp512XXXrnamc.bmp 20 0

  //  cameraman512.bmp gray.jpg rnamc.jpg 10 0 30 225 
  //  boatzyp512.bmp gray.jpg rnamc.jpg 10 0 30 225
  //  lenazyp512.bmp gray.jpg rnamc.jpg 10 0 30 225
  //  flightzyp512.bmp gray.jpg rnamc.jpg 10 0 30 225
int main(int argc,char **argv)
{
	IplImage *img = NULL;

	if(argc == 6 && (img = cvLoadImage(argv[1],0)) != 0)
	{

		cvNamedWindow("原图灰度图像",1);
		cvShowImage("原图灰度图像",img);
		/*一，分割同类块及编码*/
		int height = img->height;
		int width = img->width;

		CvMat *markMatrix = cvCreateMat(height,width,CV_8UC1);
		cvSetZero(markMatrix);
		CvMat *R = cvCreateMat(height,width,CV_8UC1);
		cvSetZero(R);

		int num = 0;
		vector<ColorNode> colorList;
		vector<Location> locList;
		double margin = atof(argv[4]);
		double ratio  = atof(argv[5]);
		time_t begin,end;
		begin = clock();
		/*分块*/
		StartNamCut(img,markMatrix,R,colorList,locList,height,width,margin,num,ratio);

		/*矩阵编码*/
		vector<char> Q;
		EnCode(R,height,width,Q);
		end = clock();

		cout<<"编码压缩花费:"<<end-begin<<"ms"<<endl;
		/*cout<<num<<endl;

		

		for(int i =0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				cout<<(int)(R->data.ptr+i*R->step)[j]<<" ";
			}
			cout<<endl;
		}*/

		
		//cout<<"编码共："<<Q.size()<<"位"<<endl;
		/*for (vector<char>::iterator it = Q.begin();it != Q.end();it++)
		{
			cout<<*it;
		}*/

		/*for (vector<ColorNode>::iterator it = colorList.begin();it != colorList.end();it++)
		{
			cout<<(*it).g1<<" "<<(*it).g2<<" "<<(*it).g3<<" "<<(*it).g4<<endl;
		}*/

		/*for(int i = 0;i<10;i++)
		{
			cout<<"("<<locList[i].x1<<","<<locList[i].y1<<")("<<locList[i].x2<<","<<locList[i].y2<<")"<<endl;
		}*/

		/*二，还原图像矩阵及图像*/
		CvMat *T = cvCreateMat(height,width,CV_8UC1);
		cvSetZero(T);
		begin = clock();
        Decode(T,height,width,Q);
	

		/*cout<<endl;
		for(int i =0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				cout<<(int)(T->data.ptr+i*T->step)[j]<<" ";
			}
			cout<<endl;
		}*/

		
		IplImage *newImg = cvCreateImage(cvSize(width,height), 8, 1);
		RestoreImage(newImg,markMatrix,T,colorList,height,width);
		end = clock();

		
		cout<<"还原图像耗时:"<<end-begin<<"ms"<<endl;

		//
		cout<<"块数:"<<num<<endl;
	    cout<<"PSNR值:"<<PSNR(img,newImg)<<endl;
		double BPPValue=BPP(colorList,width,height,Q);
	    cout<<"BPP值:"<<BPPValue<<endl;
	    cout<<"CR值:"<<8.0/BPPValue<<endl;

		cvNamedWindow("压缩图灰度图像",1);
		cvShowImage("压缩图灰度图像",newImg);
		cvSaveImage(argv[2],img,0);
	    cvSaveImage(argv[3],newImg,0);

		//画分割图
		IplImage* sketch;
	    int xr,yr;
	    int sketchXn,sketchYn;
	    if (height>=256||width>=256) 
		{
			xr=1,yr=1,sketchXn=height,sketchYn=width;
		    sketch = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U,1);
	    }
		else
		{
		xr=511/(height-1);
		yr=511/(width-1);
		sketchXn=512,sketchYn=512;
		sketch = cvCreateImage(cvSize(512,512), IPL_DEPTH_8U,1);
	    }

	    for(int i = 0;i<sketchYn;i++)
		{
		   uchar* ptrsketch = (uchar*) (sketch->imageData+i*sketch->widthStep);
		   for (int j = 0;j<sketchXn;j++)
		   {
			   ptrsketch[j]=255;
		   }
	     }
	     for (int i=0 ; i<locList.size();i++)
	     {
			   if (locList[i].x1==0&&locList[i].y1==0)
			   cvRectangle(sketch,cvPoint(locList[i].x1,locList[i].y1),cvPoint(locList[i].x2,locList[i].y2),cvScalar(0x00,0x00,0x00));
			   else   if (locList[i].x1==0&&locList[i].y1!=0)
			   cvRectangle(sketch,cvPoint(locList[i].x1,locList[i].y1-1),cvPoint(locList[i].x2,locList[i].y2),cvScalar(0x00,0x00,0x00));
			   else   if (locList[i].x1!=0&&locList[i].y1==0)
			   cvRectangle(sketch,cvPoint(locList[i].x1-1,locList[i].y1),cvPoint(locList[i].x2,locList[i].y2),cvScalar(0x00,0x00,0x00));
			   else   if (locList[i].x1!=0&&locList[i].y1!=0)
			   cvRectangle(sketch,cvPoint(locList[i].x1-1,locList[i].y1-1),cvPoint(locList[i].x2,locList[i].y2),cvScalar(0x00,0x00,0x00));
	     }
	    cvShowImage("分割示意图",sketch);

		cvWaitKey();
		cvDestroyAllWindows();
	}

	return 0;
}