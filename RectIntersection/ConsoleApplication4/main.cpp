#include "stdafx.h"

#include "RectDef.h"

void reload() {
	RectDef* rectDef = new  RectDef();
	rectDef->LoadData();
	rectDef->PrintDef();
	rectDef->Resolve();
	rectDef->PrintResolve();

}

int main()
{
	while (true) {
		string mystring;
		cin >> mystring;
		if (mystring == "reload") {
			reload();
		}
	}
    return 0;
}

