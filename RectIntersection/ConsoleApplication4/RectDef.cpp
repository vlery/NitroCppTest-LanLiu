#include "stdafx.h"
#include "RectDef.h"


void RectDef::LoadData() {
	defineRects.clear();
	
	ifstream ifs("test.json");
	IStreamWrapper isw(ifs);

	Document d;

	d.ParseStream(isw);

	auto rectList = d["rects"].GetArray();

	int index = 0;
	defineRects.clear();
	for (auto& rect : rectList) {
		index++;
		auto x = rect["x"].GetInt();
		auto y = rect["y"].GetInt();
		auto w = rect["w"].GetInt();
		auto h = rect["h"].GetInt();
		
		RectShape*  r = new  RectShape(index,x,y,w,h);
		if (r->Validate()) {
			defineRects.push_back(r);
		}
	}
	
	resolveRects.clear();
	resolveRectsExpand.clear();

}

void RectDef::PrintDef() {

	CustomOutput::PrintTitle("Input:");
	for each(auto r in defineRects) {
		r->PrintDef();
	}
}

void RectDef::PrintResolve() {
	CustomOutput::PrintTitle("Intersections");
	for each(auto r in resolveRectsExpand) {
		r->PrintIntersection();
	}
}


void RectDef::GetDividersFromEdges(const list<RectEdge> &edges, list<Divider*> &dividers){
	list<RectShape*>  savedShape;
	for each(auto edge in edges) {
		if (edge.direction) {
			savedShape.push_back(edge.rect);
		}
		auto divider = new Divider(edge.value);
		divider->checkRects.clear();
		divider->checkRects.insert(divider->checkRects.end(), savedShape.begin(), savedShape.end());
		dividers.push_back(divider);

		if (!edge.direction) {
			savedShape.remove(edge.rect);
		}
	}
}
void RectDef::GenerateOverlapPairs(const list<RectEdge> &edges, list<Divider*> &dividers) {

	for each(auto divide in dividers) {
		auto checkEdges = divide->checkRects;
		list<RectShape*> filterSortList;
		for each(auto edge in edges) {
			auto itr = std::find(checkEdges.begin(), checkEdges.end(), edge.rect);
			if (itr != checkEdges.end()) {
				filterSortList.push_back(edge.rect);
			}
		}
		list<RectShape*> pairRecord;
		for each(auto rect in filterSortList) {
			auto searchResult = std::find(pairRecord.begin(), pairRecord.end(), rect);
			if (searchResult == pairRecord.end()) {
				for each(auto pairRect in pairRecord) {
					auto existPairs = divide->overlapPairs;
					auto newPair = OverlapPair(pairRect, rect);
					bool ifExist = false;
					for each(auto pair in existPairs) {
						if (pair.rect1 == newPair.rect1 && pair.rect2 == newPair.rect2) {
							ifExist = true;
							break;
						}
						if (pair.rect1 == newPair.rect2 && pair.rect2 == newPair.rect1) {
							ifExist = true;
							break;
						}
					}

					if (!ifExist) {
						divide->overlapPairs.push_back(newPair);
					}
				}
				pairRecord.push_back(rect);
			}
			else {
				pairRecord.remove(rect);
			}
		}
	}
}

void  RectDef::Resolve() {
	if (defineRects.size() <= 0) {
		return;
	}
	list<RectEdge>  verticalEdges;
	list<RectEdge> horizontalEdges;

	for each(auto r in defineRects) {
		verticalEdges.push_back(RectEdge(r->x,r,true));
		verticalEdges.push_back(RectEdge(r->x + r->w, r, false));

		horizontalEdges.push_back(RectEdge(r->y, r, true));
		horizontalEdges.push_back(RectEdge(r->y + r->h, r, false));
	}
	auto comparator = RectEdgeComparator();
	verticalEdges.sort(comparator);
	horizontalEdges.sort(comparator);

	list<Divider*> verticalDividers;
	list<Divider*> horizontalDividers;

	GetDividersFromEdges(verticalEdges, verticalDividers);
	GetDividersFromEdges(horizontalEdges, horizontalDividers);

	GenerateOverlapPairs(horizontalEdges, verticalDividers);
	GenerateOverlapPairs(verticalEdges, horizontalDividers);


	auto region_w = verticalDividers.size() - 1;
	auto region_h = horizontalDividers.size() - 1;
	
	DivideRegion* verticalRegions  = new DivideRegion[region_w];
	DivideRegion* horizontalRegions = new DivideRegion[region_h];
	
	auto itr_v = verticalDividers.begin();
	int index = 0;
	while (itr_v != verticalDividers.end()) {
		verticalRegions[index].startDivider = *itr_v;
		
		itr_v++;
		if (itr_v == verticalDividers.end()) {
			break;
		}
		verticalRegions[index].endDivider = *itr_v;

		verticalRegions[index].CalculateOverlapPairs();
		index++;
	}

	itr_v = horizontalDividers.begin();
	index = 0;
	while (itr_v != horizontalDividers.end()) {
		horizontalRegions[index].startDivider = *itr_v;

		itr_v++;
		if (itr_v == horizontalDividers.end()) {
			break;
		}
		horizontalRegions[index].endDivider = *itr_v;
		horizontalRegions[index].CalculateOverlapPairs();
		index++;
	}

	for (int w = 0; w < region_w; w++) {
		for (int h = 0; h < region_h; h++) {
			
			list<OverlapPair> overlapResult;

			auto  hPairs = horizontalRegions[h].overlapPairs;
			auto vPairs = verticalRegions[w].overlapPairs;
			
			for each(auto p in hPairs) {
				auto searchInHori = std::find(vPairs.begin(), vPairs.end(), p);
				if (searchInHori != vPairs.end()) {
					overlapResult.push_back(p);
				}
			}
				
			if (!overlapResult.empty()) {
				RectShape* shape = new RectShape(0, verticalRegions[w].startDivider->value, horizontalRegions[h].startDivider->value,
					verticalRegions[w].GetRangeValue(), horizontalRegions[h].GetRangeValue());
				
				for each(auto p in overlapResult) {
					shape->AddOverlapRect(p.rect1);
					shape->AddOverlapRect(p.rect2);
				}
				resolveRects.push_back(shape);


				if (!HasExpandRect(shape->overlapRect)) {
					RectShape* expandShape = new RectShape(0, verticalRegions[w].startDivider->value, horizontalRegions[h].startDivider->value,
						verticalRegions[w].GetRangeValue(), horizontalRegions[h].GetRangeValue());
					expandShape->overlapRect = shape->overlapRect;
					auto w_expand = w - 1;
					while (w_expand >= 0) {
						if (verticalRegions[w_expand].IncludeOverlapPairs(overlapResult)) {
							expandShape->x = verticalRegions[w_expand].startDivider->value;
							expandShape->w += verticalRegions[w_expand].GetRangeValue();
						}
						else {
							break;
						}
						w_expand -= 1;
					}
					w_expand = w + 1;
					while (w_expand < region_w) {
						if (verticalRegions[w_expand].IncludeOverlapPairs(overlapResult)) {
							expandShape->w += verticalRegions[w_expand].GetRangeValue();
						}
						else {
							break;
						}
						w_expand += 1;
					}
					auto h_expand = h- 1;
					while (h_expand >= 0) {
						if (horizontalRegions[h_expand].IncludeOverlapPairs(overlapResult)) {
							expandShape->y= horizontalRegions[h_expand].startDivider->value;
							expandShape->h += horizontalRegions[h_expand].GetRangeValue();
						}
						else {
							break;
						}
						h_expand -= 1;
					}
					h_expand = h + 1;
					while (h_expand< region_h) {
						if (horizontalRegions[h_expand].IncludeOverlapPairs(overlapResult)) {
							expandShape->h += horizontalRegions[h_expand].GetRangeValue();
						}
						else {
							break;
						}
						h_expand += 1;
					}

					AddExpandRect(expandShape);
				}
			}
		}
	}

}

void RectDef::AddExpandRect(RectShape* expand) {
	for each(auto rect in resolveRectsExpand) {
		if (rect->x == expand->x && rect->y == expand->y 
				&& rect->w == expand->w && rect->h == expand->h) {
			for each(auto intersec in expand->overlapRect) {
				rect->AddOverlapRect(intersec);
			}
			return;
		}
	}
	resolveRectsExpand.push_back(expand);

}

bool RectDef::HasExpandRect(const list<RectShape*> &shapes) const {
	for each(auto rect in resolveRectsExpand) {
		auto overlapRects = rect->overlapRect;
		if (shapes.size() == overlapRects.size()) {
			auto itr1 = overlapRects.begin();
			auto itr2 = shapes.begin();
			while (itr1 != overlapRects.end()) {
				if (*itr1 != *itr2) {
					break;
				}
				itr1++;
				itr2++;
			}
			if (itr1 == overlapRects.end()) {
				return true;
			}
		}
	}
	return false;
}

void Divider::AddPair(OverlapPair pair) {
	if (!HasPair(pair)) {
		overlapPairs.push_back(pair);
	}
}

bool  Divider::HasPair(OverlapPair pair) const{ 
	return std::find(overlapPairs.begin(), overlapPairs.end(), pair) != overlapPairs.end();
}

list<OverlapPair> Divider::GetSharedPair(const Divider& divider) {
	list<OverlapPair> pairs;

	for each(auto p in overlapPairs) {
		if (divider.HasPair(p)) {
			pairs.push_back(p);
		}
	}
	return pairs;
}

void DivideRegion::CalculateOverlapPairs(){
	overlapPairs = startDivider->GetSharedPair(*endDivider);
}

int DivideRegion::GetRangeValue() const  {
	return endDivider->value - startDivider->value;
}


bool DivideRegion::IncludeOverlapPairs(list<OverlapPair> pairs) {
	for each(auto p in pairs) {
		if (std::find(overlapPairs.begin(), overlapPairs.end(), p)== overlapPairs.end()) {
			return false;
		}
	}
	return true;
}

 
