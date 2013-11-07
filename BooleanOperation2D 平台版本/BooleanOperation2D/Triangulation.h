#pragma once

#include "Polygon.h"
#include "BoundingBox.h"
#include "Vector.h"

namespace Algorithms
{
    class CTriangulation
    {
    public:
        // 此处仅列出一个建议的函数，需要其他函数或子函数，请自行声明并在Triangulaton.cpp中实现
        // 输入: 一个region，含有一个外环和多个（可能为0）内环
        // 输出: 一个CEdgeloop的数组array, 每个CEdgeloop中保存三条收尾相连的边CEdge，组成一个三角形
        static bool Triangulate(std::vector<CEdgeLoop> &cface, CRegion& region);


    };
}
