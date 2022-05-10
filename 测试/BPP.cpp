#include "Header.h"
double BPP (vector<ColorNode> &cn ,int xn , int yn , vector<char> &Q )
{ 
	int a1=0,a2=0,a3=0;
	for (int i=0;i<cn.size();i++){ 
		if(cn[i].g1!=-1&&cn[i].g4!=-1 ) a1++;
		else if(cn[i].g2==-1&&cn[i].g3==-1) a3++;
		else  a2++;
	}
	double BPPValue = (Q.size()+16*a1+8*a2+4.0*a3)/(xn*yn);
	return BPPValue;
}