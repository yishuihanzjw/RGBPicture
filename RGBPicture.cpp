#include"RGBPicture.h"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

RGBPicture::RGBPicture(int width, int height) :w(width), h(height)
{
	this->data = new char[width * height * 3];
//	cout << "构造函数内: " << strlen(this->data) << endl;
}

RGBPicture::~RGBPicture()
{
	delete[] data;
}

RGBPicture* RGBPicture::makeRGBPicture(int w, int h, const string& filename)//"test.rgb"
{
	RGBPicture* p = new RGBPicture(w, h);
	ifstream infile(filename, ios::binary);
	if (!infile)
	{
		cout << "Cannot open file: " << filename << endl;
		exit(0);
	}
	infile.read(p->data, sizeof(char) * w * h * 3);
	infile.close();
	return p;
}
RGBPicture* RGBPicture::DividPicture(RGBPicture* pic, int pos,const string& filename)
{
	RGBPicture* p = new RGBPicture(pic->w - pos * 2, pic->h);
	int temp = pic->w - pos * 2;//输出图的宽
	//for (int j = 0; j < pic->h; j++)
	//{
	//	for (int i = pos + pic->w * j; i < (j + 1) * pic->w - pos; i++)
	//	{
	//		memcpy(p->data + j * temp * 3, pic->data + i * 3, temp);
	//	}
	//}

	for (int j = 0; j < pic->h; j++)
	{
		memcpy(p->data + j * temp * 3, pic->data + pos * 3 + pic->w * j * 3, temp * 3);
	}


	cout << "w: "<<p->w << "\n" << "h: "<<p->h << endl;


	cout << "data_long: "<< strlen(p->data) << endl;

	ofstream outfile(filename, ios::binary);
	cout << "filename: " << filename << endl;
	if (!outfile)
	{
		cout << "Cannot open file!" << endl;
	}
	outfile.write(p->data, sizeof(char) * p->w * p->h * 3);
	outfile.close();

	return 0;
}