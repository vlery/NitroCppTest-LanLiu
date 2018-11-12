# NitroCppTest-LanLiu
i.Use and Test

	RectDef* rectDef = new  RectDef();
	rectDef->LoadData("test.json");
	
	rectDef->PrintDef();
	rectDef->Resolve();
	rectDef->PrintResolve();


	//Test : result must be loaded after rect definitions;
	rectDef->LoadResult("result.json");
	rectDef->CheckResult();


ii.Input and Output:

Type in "reload" in console to load data, calculate and test. If all the intersections listed in the result.json have been detected, then the output is "pass". Otherwise, it will print the first case cause failure.
	
	reload
	Input:
	1 :  Rectangle at (100, 100),  w=250, h=80.
	2 :  Rectangle at (120, 200),  w=250, h=150.
	3 :  Rectangle at (140, 160),  w=250, h=100.
	4 :  Rectangle at (160, 140),  w=350, h=190.
	Intersections
	Between rectangle 1 and 3 at (140, 160),  w=210, h=20.
	Between rectangle 2 and 3 at (140, 200),  w=230, h=60.
	Between rectangle 1 and 4 at (160, 140),  w=190, h=40.
	Between rectangle 1,3 and 4 at (160, 160),  w=190, h=20.
	Between rectangle 3 and 4 at (160, 160),  w=230, h=100.
	Between rectangle 2,3 and 4 at (160, 200),  w=210, h=60.
	Between rectangle 2 and 4 at (160, 200),  w=210, h=130.
	test
	pass
	

iii. Other

third party lib: rapidjson
project environment: VS2015
