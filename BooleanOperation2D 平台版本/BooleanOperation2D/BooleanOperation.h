#pragma once
#include "Intersection.h"
#include "Polygon.h"
#include <list>

namespace Algorithms
{
    enum BooleanOperationType
    {
        BooleanUnion,
        BooleanIntersection,
        BooleanDifference
    };

    class CBooleanOperation
    {
    public:
        // 两个多边形布尔运算
        static bool BooleanOperate(CPolygon &polygon1, CPolygon &polygon2, BooleanOperationType type, CPolygon  &result);
        // 多边形和区域布尔运算
        static bool BooleanOperate(CPolygon &polygon, CRegion &region, BooleanOperationType type, CPolygon  &result);
        //区域和区域之间布尔运算
        static bool BooleanOperate(CRegion &region1, CRegion &region2, BooleanOperationType type, CPolygon  &result);

        // 以上这三个函数为建议函数，逐层调用，可以不按照这个思路，自己写即可。

        // 以下这两个函数必须实现，为区域和多边形的合法判断，因为需要用到求交等算法，所以放在这里实现
        static bool IsValid(CRegion &loop);
        static bool IsValid(CPolygon &polygon);



        // 两个区域求交并将相应的线段分割，输出分割后的区域中的所有边
        // 这是布尔运算的第一步
        static IntersectionResult IntersectAndSplit(CRegion &region1, CRegion &region2, std::list<CEdge> &out1, std::list<CEdge> &out2);


        // 分割之后的两个region所有边组成两个list，将边进行分类
        // 分类之后根据布尔运算类型进行边取舍，此处参照大作业中给出的公式
        // 分类是布尔运算的第二步（取舍可以视为第三步）
        static void ClassifyEdges(std::list<CEdge> &list1, std::list<CEdge> &list2);

        // 包含测试，测试一个边是否在一组环组成的区域的内部，方法是射线法测试
        // 该函数是分类的子函数
        static EdgeIncludeType EdgeIncludeTypeTest(std::list<CEdge> &list, CEdge &edge); 

        // 取舍之后得到布尔运算的一堆边（list）从中搜索环，布尔运算第四步
        static bool SearchLoopsInEdges(std::list<CEdge> &list, std::vector<CEdgeLoop> &loops);
        // 搜索出一个环之后判断其内外环，然后添加到布尔运算后的多边形中
        static bool AddLoopsIntoPolygon(std::vector<CEdgeLoop> &loops, CPolygon & polygon);
    };
}


