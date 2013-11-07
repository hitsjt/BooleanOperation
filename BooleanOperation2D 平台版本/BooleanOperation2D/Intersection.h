#pragma once
#include "Vector.h"
#include "Polygon.h"
#include "BoundingBox.h"
#include <list>

namespace Algorithms
{
    enum IntersectionResult
    {
        None = 0,   // û�н���
        Regular,    // ��������
        OverlapSameDirection,    // �غ�ͬ��
        OverlapOppositeDirection, // �غϷ���
        BoundaryOfA,    // ����λ���߶���˵�
        BoundaryOfB, // ����λ���߶��Ҷ˵�
        PositiveDirection, // ����λ�������ӳ���
        NegativeDirection // ����λ�ڸ����ӳ���
    };

    class CIntersection
    {
    public:
        static IntersectionResult Intersect(CEdge& coedge_a, CEdge& coedge_b, vec2& point); 
        // ��ȷ�������ֱ�ߵĽ��㣬����������㣬���������б���˸õ���a�߶��е�λ��

        // �˴����г�һ������ĺ����������Ҫ�������������Ӻ������������λ�������ⶨ������Intersection.cpp��ʵ�֡�

    };
}
