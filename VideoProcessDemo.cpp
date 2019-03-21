/*
输入是.ts;	.mp4;视频二进制文件（1）
	  .yuv（YUV420）;
	  .rgb;（RGB24）图片二进制文件（2）
*/
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"RGBPicture.h"

//#include<time.h>
//#include<assert.h>

using namespace std;

static int CalcLine(RGBPicture* pic)
{
	vector<int> vec;
	int multiple = 1;
	for (int j = 0; j < pic->h; j += multiple)//行抽样
	{
		for (int i = pic->w * j; i < pic->w * (j + 1); i++)
		{
			//if (pic->data[i * 3] != pic->data[pic->w * j * 3 + 3] || pic->data[i * 3 + 1] != pic->data[pic->w * j * 3 + 4] || pic->data[i * 3 + 2] != pic->data[pic->w * j * 3 + 5])
			//与该行第一个像素是否相同

			//if (pic->data[i * 3] != pic->data[i * 3 + 3] || pic->data[i * 3 + 1] != pic->data[i * 3 + 4] || pic->data[i * 3 + 2] != pic->data[i * 3 + 5])
			//左右颜色是否相同
			if (pic->data[i * 3] != 0 && pic->data[i * 3 + 1] != 0 && pic->data[i * 3 + 2] != 0)
			//是否为黑色
			{
				vec.push_back(i);
				break;
			}
		}
	}

	ofstream outfile("res.txt");
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		outfile << vec[i];
		/*outfile << (vec[i] - vec[0]) % (pic->w * multiple);*/
		if (i < vec.size() - 1)
		{
			outfile << endl;
		}
	}
	outfile.close();

	int count = 0;	
	for (unsigned i = 0; i < vec.size(); i++)
	{
		if ((vec[i] - vec[0]) % (pic->w * multiple) == 0)
		{
			count++;
		}
	}
	cout << "count: " << count << endl;
	cout << "w: " << pic->w << endl
		<< "h: " << pic->h << endl;

	if (count == vec.size())//&& k == vec.size()
	{
		cout << "if " << endl;
		return vec[0];
	}
	else
	{
		cout << "else " << endl;
		int temp = vec[0];
		for (unsigned int i = 0; i < vec.size(); i++)
		{
			if (temp > vec[i])
			{
				temp = vec[i];
			}
		}
		return temp;
	}
}


int main()
{
	RGBPicture* pic = RGBPicture::makeRGBPicture(1920, 1080, "test.rgb");
	int pos = CalcLine(pic);
	cout << "position: " << pos << endl;

	//if (pos > (1920 - 1080) / 2)//竖屏时的误差
	//{
	//	pos += 9;
	//}
	//else
	//{
	//	;
	//}
	RGBPicture* p = RGBPicture::DividPicture(pic, pos,"result.rgb");

	delete pic;

	delete p;

	return 0;
}

/*横屏处理成功，竖屏有误差*/
/*
横屏：1440x1080
竖屏： 810x1080
*/