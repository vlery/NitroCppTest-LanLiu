
#include <list>
#include "Output.h"
using namespace std;

struct Vector2 {
public:
	float x, y;
	Vector2(float x, float y);
	Vector2();
};


class RectShape {
public:
	Vector2 points[4];

	RectShape(int index, int x, int y, int w, int h);
	Vector2* GetPointsArray();

	list<RectShape*> overlapRect;


	int index;
	int w;
	int h;
	int x;
	int y;

	void AddOverlapRect(RectShape* shape);
	void PrintDef();
	void PrintIntersection();
	bool IfInclude(int x, int y);

};
struct RectShapeComparator
{

	bool operator ()(const RectShape* shape1, const RectShape* shape2)
	{
		return shape1->index < shape2->index;

	}
};

struct RectEdge {
public:
	int value;
	bool direction;
	RectShape* rect;
	RectEdge(int value, RectShape* rect, bool direction) {
		this->value = value;
		this->direction = direction;
		this->rect = rect;
	};

	bool operator ()(const RectEdge & edge1, const RectEdge & edge2) const
	{
		return edge1.value < edge2.value;

	}
};


struct RectEdgeComparator
{

	bool operator ()(const RectEdge & edge1, const RectEdge & edge2)
	{
		return edge1.value < edge2.value;

	}
};


struct OverlapPair {
public:
	RectShape* rect1;
	RectShape* rect2;
	OverlapPair(RectShape* rect1, RectShape* rect2) {
		this->rect1 = rect1;
		this->rect2 = rect2;
	}
	bool operator==(const OverlapPair& pair) const;
};


