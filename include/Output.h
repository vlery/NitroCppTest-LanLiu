#include "cocos2d.h"

USING_NS_CC;


class CustomOutput {

public:
	static void PrintRect(int index, int x, int y, int w, int h) {
		CCLOG("%i :  Rectangle at (%i, %i),  w=%i, h=%i.", index, x, y, w, h);
	}
	static void PrintIntersection(std::string rectList, int x, int y, int w, int h) {
		CCLOG("Between rectangle %s at (%i, %i),  w=%i, h=%i.", rectList.c_str(), x, y, w, h);
	}
	static void PrintTitle(char* s) {
		CCLOG(s);
	}

	
};