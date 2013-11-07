#pragma once

#include "Polygon.h"
#include "BoundingBox.h"
#include "Vector.h"

namespace Algorithms
{
    class CTriangulation
    {
    public:
        // �˴����г�һ������ĺ�������Ҫ�����������Ӻ�������������������Triangulaton.cpp��ʵ��
        // ����: һ��region������һ���⻷�Ͷ��������Ϊ0���ڻ�
        // ���: һ��CEdgeloop������array, ÿ��CEdgeloop�б���������β�����ı�CEdge�����һ��������
        static bool Triangulate(std::vector<CEdgeLoop> &cface, CRegion& region);


    };
}
