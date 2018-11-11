#include <iostream>

class CustomOutput {

public:
	static void PrintRect(int index, int x, int y, int w, int h) {
		printf ("%d :  Rectangle at (%d, %d),  w=%d, h=%d.\n", index, x, y, w, h);
		//CCLOG("%i :  Rectangle at (%i, %i),  w=%i, h=%i.", index, x, y, w, h);
	}
	static void PrintIntersection(std::string rectList, int x, int y, int w, int h) {
		printf("Between rectangle %s at (%d, %d),  w=%d, h=%d.\n", rectList.c_str() , x, y, w, h);
		//CCLOG("Between rectangle %s at (%i, %i),  w=%i, h=%i.", rectList.c_str(), x, y, w, h);
	}
	static void PrintTitle(char* s) {
		printf("%s\n",s);
		//CCLOG(s);
	}

	
};