#pragma once
#include "Vector.h"

class CBoundingBox
{
public:
	//������Ա����
    vec2 Min;
    vec2 Max;
public:
	//���캯������������
    CBoundingBox(void) {}
    CBoundingBox(const vec2& min, const vec2& max): Min(min), Max(max) {}
    ~CBoundingBox(void) {}

public:
	//�ж�������Χ���Ƿ����غ�
    bool IsIntersectWith(const CBoundingBox& box) const;
	//�жϵ�ǰ��Χ���Ƿ����ĳ����
    bool Contains(const vec2& point) const;
	//������Χ����
    void Union(const CBoundingBox& box);
};

