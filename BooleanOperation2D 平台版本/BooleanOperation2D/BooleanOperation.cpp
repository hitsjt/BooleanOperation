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
        // 下面是合法性判断的推荐流程

        // 1检测环的种类、数量以及环本身是否合法

        // 2检测各环之间是否相交

        // 3检测内环是否都在外环之内

        // 4检测内环是否有包含的情况

        return true;
    }
    bool CBooleanOperation::IsValid(CPolygon &polygon)
    {
        // 下面是合法性判断的推荐流程

        // 1区域个数以及各Region均是否合法

        // 2各Region之间是否相交

        // 3各Region之间是否包含
        return true;
    }
}
