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
        // ��������β�������
        static bool BooleanOperate(CPolygon &polygon1, CPolygon &polygon2, BooleanOperationType type, CPolygon  &result);
        // ����κ����򲼶�����
        static bool BooleanOperate(CPolygon &polygon, CRegion &region, BooleanOperationType type, CPolygon  &result);
        //���������֮�䲼������
        static bool BooleanOperate(CRegion &region1, CRegion &region2, BooleanOperationType type, CPolygon  &result);

        // ��������������Ϊ���麯���������ã����Բ��������˼·���Լ�д���ɡ�

        // ������������������ʵ�֣�Ϊ����Ͷ���εĺϷ��жϣ���Ϊ��Ҫ�õ��󽻵��㷨�����Է�������ʵ��
        static bool IsValid(CRegion &loop);
        static bool IsValid(CPolygon &polygon);



        // ���������󽻲�����Ӧ���߶ηָ����ָ��������е����б�
        // ���ǲ�������ĵ�һ��
        static IntersectionResult IntersectAndSplit(CRegion &region1, CRegion &region2, std::list<CEdge> &out1, std::list<CEdge> &out2);


        // �ָ�֮�������region���б��������list�����߽��з���
        // ����֮����ݲ����������ͽ��б�ȡ�ᣬ�˴����մ���ҵ�и����Ĺ�ʽ
        // �����ǲ�������ĵڶ�����ȡ�������Ϊ��������
        static void ClassifyEdges(std::list<CEdge> &list1, std::list<CEdge> &list2);

        // �������ԣ�����һ�����Ƿ���һ�黷��ɵ�������ڲ������������߷�����
        // �ú����Ƿ�����Ӻ���
        static EdgeIncludeType EdgeIncludeTypeTest(std::list<CEdge> &list, CEdge &edge); 

        // ȡ��֮��õ����������һ�ѱߣ�list������������������������Ĳ�
        static bool SearchLoopsInEdges(std::list<CEdge> &list, std::vector<CEdgeLoop> &loops);
        // ������һ����֮���ж������⻷��Ȼ����ӵ����������Ķ������
        static bool AddLoopsIntoPolygon(std::vector<CEdgeLoop> &loops, CPolygon & polygon);
    };
}


