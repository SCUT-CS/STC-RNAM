#include "Calculate.h"

/** Calculate the BPP
  * @author CuiYuxin
  * @param vector<colorListStandard>& P
  * @param Size imgSize
  * @param vector<char>& Q
  * @return double BPP */
double Calculate::BPP(vector<colorListStandard>& P, Size imgSize, vector<char>& Q)
{
	return (Q.size() + 32.0 * P.size()) / (imgSize.height * imgSize.width);
}

/** Calculate the BPP
  * @author CuiYuxin
  * @param vector<ColorNode>& cn
  * @param int xn
  * @param int yn
  * @param vector<char>& Q
  * @return double BPP */
double Calculate::BPP(vector<ColorNode>& cn, int xn, int yn, vector<char>& Q)
{
	int a1 = 0, a2 = 0, a3 = 0;
	for (int i = 0; i < cn.size(); i++) {
		if (cn[i].g1 != -1 && cn[i].g4 != -1) a1++;
		else if (cn[i].g2 == -1 && cn[i].g3 == -1) a3++;
		else  a2++;
	}
	double BPPValue = (Q.size() + 16 * a1 + 8 * a2 + 4.0 * a3) / (xn * yn);
	return BPPValue;
}

