#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <rapidjson/istreamwrapper.h>
#include <list>
#include <fstream>

#include "CustomStruct.h"

using namespace std;
using namespace rapidjson;


class Divider {
public :
	int value;
	list<RectShape*> checkRects;
	list<OverlapPair> overlapPairs;
	Divider( int value) {
		this->value = value;
	};

	void AddPair(OverlapPair pair);
	bool HasPair(OverlapPair pair) const;
	list<OverlapPair> GetSharedPair(const Divider& divider);
};

struct DivideRegion {
public:
	Divider* startDivider;
	Divider* endDivider;
	
	list<OverlapPair>  overlapPairs;
	list<OverlapPair> processedPairs;
	DivideRegion(Divider* startDivider, Divider* endDivider) {
		this->startDivider = startDivider;
		this->endDivider = endDivider;
	}
	DivideRegion() {};
	void CalculateOverlapPairs();
	int GetRangeValue() const;
	bool IncludeOverlapPairs(list<OverlapPair> pairs);

};

class  RectDef {

public:

	void LoadData();
	void PrintDef();
	void PrintResolve();
	list<RectShape*> defineRects;
	list<RectShape*> resolveRects;
	list<RectShape*> resolveRectsExpand;

	void Resolve();
	bool HasExpandRect(const list<RectShape*> &shapes) const;
	

private:
	const char* filePath = "data.json";
	void GetDividersFromEdges(const list<RectEdge> &edges, list<Divider*> &dividers);
	void GenerateOverlapPairs(const list<RectEdge> &edges, list<Divider*> &dividers);
	
};

