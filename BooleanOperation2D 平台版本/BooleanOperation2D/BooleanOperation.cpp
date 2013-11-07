#include "stdafx.h"
#include "BooleanOperation.h"
#include "MathUtility.h"

namespace Algorithms
{
    bool CBooleanOperation::BooleanOperate(CPolygon &polygon1, CPolygon &polygon2, BooleanOperationType type, CPolygon  &result)
    {
        return true;
    }
    bool CBooleanOperation::BooleanOperate(CPolygon &polygon, CRegion &region, BooleanOperationType type, CPolygon  &result)
    {
        return true;
    }
    bool CBooleanOperation::BooleanOperate(CRegion &region1, CRegion &region2, BooleanOperationType type, CPolygon  &result)
    {
        return false;
    }

    IntersectionResult CBooleanOperation::IntersectAndSplit(CRegion &region1, CRegion &region2, std::list<CEdge> &out1, std::list<CEdge> &out2)
    {
        return IntersectionResult::None;
    }

    void CBooleanOperation::ClassifyEdges(std::list<CEdge> &list1, std::list<CEdge> &list2)
    {
    }
    EdgeIncludeType CBooleanOperation::EdgeIncludeTypeTest(std::list<CEdge> &list, CEdge &edge)
    {
        return EdgeIncludeType::Include;
    }

    bool CBooleanOperation::SearchLoopsInEdges(std::list<CEdge> &list, std::vector<CEdgeLoop> &loops)
    {
        return false;
    }
    bool CBooleanOperation::AddLoopsIntoPolygon(std::vector<CEdgeLoop> &loops, CPolygon & polygon)
    {
        return true;
    }
    bool CBooleanOperation::IsValid(CRegion &region)
    {
        region.Commit();
        // �����ǺϷ����жϵ��Ƽ�����

        // 1��⻷�����ࡢ�����Լ��������Ƿ�Ϸ�

        // 2������֮���Ƿ��ཻ

        // 3����ڻ��Ƿ����⻷֮��

        // 4����ڻ��Ƿ��а��������

        return true;
    }
    bool CBooleanOperation::IsValid(CPolygon &polygon)
    {
        // �����ǺϷ����жϵ��Ƽ�����

        // 1��������Լ���Region���Ƿ�Ϸ�

        // 2��Region֮���Ƿ��ཻ

        // 3��Region֮���Ƿ����
        return true;
    }
}
