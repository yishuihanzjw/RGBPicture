#include<string>

class RGBPicture
{
public:
	~RGBPicture();
	int w;
	int h;
	char* data;
	static RGBPicture* makeRGBPicture(int w, int h, const std::string& filename);
	static RGBPicture* DividPicture(RGBPicture* pic, int pos,const std::string& filename);
private:
	RGBPicture(int w, int h);
	RGBPicture(const RGBPicture&);
};