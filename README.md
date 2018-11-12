# NitroCppTest-LanLiu
Use and Test

	RectDef* rectDef = new  RectDef();
	rectDef->LoadData("test.json");
	
	rectDef->PrintDef();
	rectDef->Resolve();
	rectDef->PrintResolve();


	//Test : result must be loaded after rect definitions;
	rectDef->LoadResult("result.json");
	rectDef->CheckResult();
