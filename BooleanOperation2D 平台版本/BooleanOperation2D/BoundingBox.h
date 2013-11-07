#pragma once
#include "Vector.h"

class CBoundingBox
{
public:
	//两个成员变量
    vec2 Min;
    vec2 Max;
public:
	//构造函数和析构函数
    CBoundingBox(void) {}
    CBoundingBox(const vec2& min, const vec2& max): Min(min), Max(max) {}
    ~CBoundingBox(void) {}

public:
	//判断两个包围盒是否有重合
    bool IsIntersectWith(const CBoundingBox& box) const;
	//判断当前包围盒是否包含某个点
    bool Contains(const vec2& point) const;
	//两个包围盒求并
    void Union(const CBoundingBox& box);
};

