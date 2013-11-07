#ifndef CF_DRAW_H
#define CF_DRAW_H
#include "Polygon.h"

typedef std::vector<vec2> Vec2Array;

extern void cf_drawBezier(CDC &dc,CPolygon &polygon,int segments,CPoint &base,double factor);

extern vec2 cf_getBezierPoint(Vec2Array &pa,double t);

extern void cf_getScreenPoint(CPoint &sp,vec2 &p,CPoint &base,double factor);
#endif