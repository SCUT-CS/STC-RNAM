#include "Header.h"

void EnCode(CvMat *R,int height,int width,vector<char> &Q)
{
	int c = 0;
	int offsetValue = 0;
	int count = 0;

	for(int i=0;i<height;i++)
	{
		c=0;
		offsetValue=0;
		count = 0;
		//Q.push_back(' ');
		for(int j=0;j<width;j++)
		{
			int value = (R->data.ptr + R->step * i)[j];
			if(0 == value)
			{
				if(j == width -1)
				{
					Q.push_back('0');
				}
			}
			else
			{
				if(1 == value)
				{
					Q.push_back('1');
					Q.push_back('1');
				}
				else if(2 == value)
				{
					Q.push_back('1');
					Q.push_back('0');
					Q.push_back('1');
				}
				else if(3 == value)
				{
					Q.push_back('1');
					Q.push_back('0');
					Q.push_back('0');
				}

				//位置从1开始 不是从0开始 所以多减去1
				int b = ceil(log((double)(width- c -count)) /log(2.0f));
				if(0 == count)
				{
					offsetValue = j;
				}
				else
				{
					offsetValue = j - c -1;
				}

				b = (b==0)? 1:b;
				count = 1;
				c = j;

				for(int v=b-1;v>=0;v--)
				{
					if((offsetValue & (1<<v)) == 0)
					{
						Q.push_back('0');
					}
					else
					{
						Q.push_back('1');
					}
				}
			}
		}
	}
}

void Decode(CvMat *R,int height,int width,const vector<char> &Q)
{
	int n = 0;
	int count = 0;
	//上个非零元素的位置
	int c = 0;
	int row = 0;
	int num = 0;
	for(int pos = 0;pos < Q.size();pos++)
	{
		if('1' == Q[pos])
		{
			pos++;
			if('1' == Q[pos])
			{
				n = 1;
				
			}
			else
			{
				pos++;
				if('1' == Q[pos])
				{
					n = 2;
				}
				else
				{
					n = 3;
				}
			}
		}
		else
		{
             row++;
			 count = 0;
			 c = 0;
			 num = 0;
			 continue;
			//如果是0
			//if(c == 0)
			//{
			//	row++;
			//	continue;
			//}
			//else
			//{
			//	row++;
			//	count = 0;
			//	c = 0;
			//	num = 0;
			//	continue;

			//}
		}

		int b = ceil(log((double)(width- c -count))/log(2.0f));
		b = b==0? 1:b;
		count = 1;

		int value = 0;
		for(int i = b -1;i >=0;i--)
		{
			pos++;
			if('1' == Q[pos])
			{
				value += 1<<i;
			}
		}

		if(0 == num)
		{
			c = c + value;
		}
		else
		{
			c = c + value +1;
		}

		num++;
		

		(R->data.ptr + row*R->step)[c] = n;

		if( c == (width -1))
		{
			row++;
			count = 0;
			c = 0;
			num = 0;
		}
	}

	/*for(vector<char>::const_iterator it = Q.begin();it != Q.end();it++)
	{
		if('1' == *it)
		{
			it++;
			if('1' == *it)
			{
				n = 1;
				
			}
			else
			{
				it++;
				if('1' == *it)
				{
					n = 2;
				}
				else
				{
					n = 3;
				}
			}
		}
		else
		{
			//如果是0
			if(c == 0)
			{
				row++;
				continue;
			}
			else
			{
				

				row++;
				count = 0;
				c = 0;
				num = 0;
				continue;

			}
		}

		int b = ceil(log((double)(width- c -count))/log(2.0f));
		b = b==0? 1:b;
		count = 1;

		int value = 0;
		for(int i = b -1;i >=0;i--)
		{
			it++;
			if(*it == '1')
			{
				value += 1<<i;
			}
		}

		if(0 == num)
		{
			c = c + value;
		}
		else
		{
			c = c + value +1;
		}

		num++;
		

		(R->data.ptr + row*R->step)[c] = n;

		if( c == (width -1))
		{
			row++;
			count = 0;
			c = 0;
			num = 0;
		}
	}*/

}