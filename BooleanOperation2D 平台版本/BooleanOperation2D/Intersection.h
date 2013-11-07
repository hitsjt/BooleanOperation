#pragma once
#include "Vector.h"
#include "Polygon.h"
#include "BoundingBox.h"
#include <list>

namespace Algorithms
{
    enum IntersectionResult
    {
        None = 0,   // 没有交点
        Regular,    // 正常交点
        OverlapSameDirection,    // 重合同向
        OverlapOppositeDirection, // 重合反向
        BoundaryOfA,    // 交点位于线段左端点
        BoundaryOfB, // 交点位于线段右端点
        PositiveDirection, // 交点位于正向延长线
        NegativeDirection // 交点位于负向延长线
    };

    class CIntersection
    {
    public:
        static IntersectionResult Intersect(CEdge& coedge_a, CEdge& coedge_b, vec2& point); 
        // 精确求出两条直线的交点，并返回这个点，返回类型中标记了该点在a线段中的位置

        // 此处仅列出一个建议的函数，如果需要其它函数或者子函数，请在这个位置自行拟定，并在Intersection.cpp中实现。

    };
}
