#include "stdafx.h"
#include "BoundingBox.h"

bool CBoundingBox::IsIntersectWith(const CBoundingBox& box) const
{
    if (box.Max.x < Min.x || box.Min.x > Max.x)
        return false;
    if (box.Max.y < Min.y || box.Min.y > Max.y)
        return false;
    return true;
}

bool CBoundingBox::Contains(const vec2& point) const
{
    return (point.x > Min.x) && (point.x < Max.x) && (point.y > Min.y) && (point.y < Max.y);
}

void CBoundingBox::Union(const CBoundingBox& box)
{
    if (Min.x > box.Min.x)
        Min.x = box.Min.x;
    if (Min.y > box.Min.y)
        Min.y = box.Min.y;
    if (Max.x < box.Max.x)
        Max.x = box.Max.x;
    if (Max.y < box.Max.y)
        Max.y = box.Max.y;
}