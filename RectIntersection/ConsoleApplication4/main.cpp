#include "stdafx.h"

#include "RectDef.h"

void reload() {
	RectDef* rectDef = new  RectDef();
	rectDef->LoadData("test.json");
	
	rectDef->PrintDef();
	rectDef->Resolve();
	rectDef->PrintResolve();


	//Test : result must be loaded after rect definitions;
	rectDef->LoadResult("result.json");
	rectDef->CheckResult();

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

