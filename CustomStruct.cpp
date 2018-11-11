#include "CustomStruct.h"


void RectShape::PrintDef() {
	CustomOutput::PrintRect(index, x, y, w, h);
}

void RectShape::PrintIntersection() {
	std::string s = "";
	int i = overlapRect.size() - 2;
	auto itr = overlapRect.begin();

	while (i > 0) {
		s.append(std::to_string((*itr)->index));
		s.append(",");
		itr++;
		i--;
	}


	s.append(std::to_string((*itr)->index));
	itr++;
	s.append(" and ");
	s.append(std::to_string((*itr)->index));

	CustomOutput::PrintIntersection(s, x, y, w, h);
}
Vector2* RectShape::GetPointsArray() {
	Vector2 points[4] = { Vector2(x,y), Vector2(x, y + h), Vector2(x + w, y + h), Vector2(x + w, y) };
	return points;
}
RectShape::RectShape(int index, int x, int y, int w, int h)
{
	this->index = index;
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
}

void RectShape::AddOverlapRect(RectShape* shape) {
	if (std::find(overlapRect.begin(), overlapRect.end(), shape) == overlapRect.end()) {
		overlapRect.push_back(shape);
		overlapRect.sort(RectShapeComparator());
	}
}

bool OverlapPair::operator==(const OverlapPair& pair) const {
	if (pair.rect1 == rect1 && pair.rect2 == rect2) {
		return true;
	}
	if (pair.rect2 == rect1 && pair.rect1 == rect2) {
		return true;
	}
	return false;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}
Vector2::Vector2() {}


bool RectShape::IfInclude(int x, int y) {
	if (x > this->x && x < this->x + this->w) {
		if (y > this->y && y < this->y + this->h) {
			return true;
		}
	}
	return false;
}