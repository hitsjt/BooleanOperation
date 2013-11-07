#include "stdafx.h"
#include "CF_Draw.h"


void cf_getScreenPoint(CPoint &sp,vec2 &p,CPoint &base,double factor)
{
	sp.x = base.x +(int)(p.x * factor);
	sp.y = base.y+(int)(p.y * factor);
}

void cf_drawBezier(CDC &dc,CPolygon &polygon,int segments,CPoint &base,double factor)
{
	EdgeArray aEdgeArray(polygon.Regions[0].OuterLoops.Edges); 
	Vec2Array controalPoints;
	//获取所有的点
	for(EdgeArray::iterator it= aEdgeArray.begin();it!=aEdgeArray.end();it++)
	{
		vec2 tempPoint;
		tempPoint.Setx((*it).Start.Getx());
		tempPoint.Sety((*it).Start.Gety());
		controalPoints.push_back(tempPoint);
	}

	double t = 0;
	for (unsigned int i = 0; i < segments; i++)
	{
		t += 1.0/segments;
		vec2 p = cf_getBezierPoint(controalPoints,t);
		CPoint sp;
		cf_getScreenPoint(sp,p,base,factor);
		if(i ==0)
			dc.MoveTo(sp.x,sp.y);
		dc.LineTo(sp.x,sp.y);
	}



}

vec2 cf_getBezierPoint(Vec2Array &pa,double t)
{
	Vec2Array tempPoints(pa);
	for (unsigned int i = 1; i <= tempPoints.size(); i++){
		for (unsigned int j = 0; j < tempPoints.size()-i; j++)
			tempPoints[j] = tempPoints[j] * (1-t) + tempPoints[j+1] * t; 
	}
	return tempPoints[0];
}