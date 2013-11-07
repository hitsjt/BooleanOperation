#include "stdafx.h"
#include "Polygon.h"
#include "Vector.h"
#include <sstream>
#include <string>

#pragma region Implements of CEdge

void CEdge::Commit()
{
    Box.Max.x = max(Start.x, End.x);
    Box.Max.y = max(Start.y, End.y);

    Box.Min.x = min(Start.x, End.x);
    Box.Min.y = min(Start.y, End.y);
}
bool CEdge::IsValid()
{
    Commit();
    if (Tolerance.IsZero(Start - End))
        return false;
    return true;
}
bool CEdge::IsIntersectWith(const CEdge& edge) const
{
    if (!Box.IsIntersectWith(edge.Box))
        return false;

    vec2 v1 = edge.Start - Start;
    vec2 v2 = edge.End - Start;
    vec2 v3 = End - Start;

    vec2 v4 = Start - edge.Start;
    vec2 v5 = End - edge.Start;
    vec2 v6 = edge.End - edge.Start;

    double c1 = v1 ^ v3;
    double c2 = v2 ^ v3;
    double c3 = v4 ^ v6;
    double c4 = v5 ^ v6;

    if (c1 * c2 < 0.0 && c3 * c4 < 0.0)
        return true;
    else if (Tolerance.IsZero(c1) && (End - edge.Start) * (Start - edge.Start) <= 0.0)
        return true;
    else if (Tolerance.IsZero(c2) && (End - edge.End) * (Start - edge.End) <= 0.0)
        return true;
    else if (Tolerance.IsZero(c3) && (Start - edge.Start) * (Start - edge.End) <= 0.0)
        return true;
    else if (Tolerance.IsZero(c4) && (End - edge.Start) * (End - edge.End) <= 0.0)
        return true;
    return false;
}
bool CEdge::IsIntersectWith1(const CEdge& edge) const
{
    if (!Box.IsIntersectWith(edge.Box))
        return false;

    vec2 v1 = edge.Start - Start;
    vec2 v2 = edge.End - Start;
    vec2 v3 = End - Start;

    vec2 v4 = Start - edge.Start;
    vec2 v5 = End - edge.Start;
    vec2 v6 = edge.End - edge.Start;

    double c1 = v1 ^ v3;
    double c2 = v2 ^ v3;
    double c3 = v4 ^ v6;
    double c4 = v5 ^ v6;

    if (c1 * c2 < 0.0 && c3 * c4 < 0.0)
        return true;
    else if (Tolerance.IsZero(c1) && (End - edge.Start) * (Start - edge.Start) < 0.0)
        return true;
    else if (Tolerance.IsZero(c2) && (End - edge.End) * (Start - edge.End) < 0.0)
        return true;
    else if (Tolerance.IsZero(c3) && (Start - edge.Start) * (Start - edge.End) < 0.0)
        return true;
    else if (Tolerance.IsZero(c4) && (End - edge.Start) * (End - edge.End) < 0.0)
        return true;
    else if (Tolerance.IsZero(v1) || Tolerance.IsZero(v2)) // Overlap totally
        return true;
    return false;
}

// a的含义(0: 与起点重合; 1: 与终点重合; -1: 其他)
bool CEdge::IsPointOn(const vec2 point, int &a, const CTolerance &tolerance) const
{
    vec2 direction = End - Start;
    a = -1;
    vec2 v1 = point - Start;
    vec2 v2 = point - End;
    double value2 = v1 * v2;
    double distance = direction.GetLength( );
    if (tolerance.IsZero(distance))
    {
        distance = v1.GetLength( );
        if (tolerance.IsZero(distance))
        {
            a = 0;
            return true;
        }
        distance = v2.GetLength( );
        if (tolerance.IsZero(distance))
        {
            a = 1;
            return true;
        }
        return false;
    }

    vec2 normal_direction = vec2(direction.y, -direction.x).GetUnit();

    distance = v1 * normal_direction;
    if (tolerance.IsZero(distance) && (tolerance.IsZero(value2) || value2 <= 0))
    {
        if (tolerance.IsZero(v1))
            a = 0;
        else if (tolerance.IsZero(v2))
            a = 1;
        return true;
    }
    return false;
}
void CEdge::Move(const vec2 direction) // 平移
{
    Start += direction;
    End += direction;
    Commit();
}

#pragma endregion

#pragma region Implements of CEdgeLoop

//注意改变了对象中的数据之后必须调用
void CEdgeLoop::Commit()
{
    if (Edges.size() == 0)
        return;
    for (unsigned int i = 0; i < Edges.size(); i++)
        Edges[i].Commit();
    // get Box
    Box = Edges.begin()->Box;
    for (unsigned int i = 1; i < Edges.size(); i++)
        Box.Union(Edges[i].Box);

    // get ELoopType
    CEdge topend = Edges[0];
    CEdge topstart;
    int position = 0;
    for (unsigned int i = 1; i < Edges.size(); i++)
    {
        if (Edges[i].End.y > topend.End.y)
        {
            topend = Edges[i];
            position = i;
        }
    }
    if (position == Edges.size() - 1)
        topstart = Edges[0];
    else
        topstart = Edges[position + 1];
    vec2 v1 = topend.End - topend.Start;
    vec2 v2 = topstart.End - topend.Start;
    double val = v1 ^ v2;
    if (val > 0.0)
        Type = InnerLoop;
    else
        Type = OuterLoop;
}

//检测CEdgeLoop是否合法，包括边数>=3，每条边是否合法、边首尾相接、边互不相交
bool CEdgeLoop::IsValid()
{
    // the loop should have more than 3 edges.
    if (Edges.size() < 3)
        return false;

    Commit();

    for (unsigned int i = 0; i < Edges.size(); i++)
        if (!Edges[i].IsValid())
            return false;;
    // the Edges are end to end
    for (unsigned int i = 0; i < Edges.size() - 1; i++)
    {
        vec2 point = Edges[i].End - Edges[i + 1].Start;
        if (!Tolerance.IsZero(point))
            return false;
    }
    vec2 point = Edges[0].Start - Edges[Edges.size() - 1].End;
    if (!Tolerance.IsZero(point))
        return false;

    // the Edges should not intersected with each other
    for (unsigned int i = 0; i < Edges.size() - 2; i++)
    {
        CEdge edge = Edges[i];
        for (unsigned int j = i + 2; j < Edges.size(); j++)
        {
            if (i == 0 && j == Edges.size() - 1)
                break;

            if (edge.IsIntersectWith(Edges[j]))
                return false;
        }
    }
    return true;
}

//判断两个环是否相交，方法是判断两个环的各个边是否相交
bool CEdgeLoop::IsIntersectWith(const CEdgeLoop &edgeloop) const
{
    if (!Box.IsIntersectWith(edgeloop.Box))
        return false;

    for (unsigned int i = 0; i < Edges.size(); i++)
    {
        for (unsigned int j = 0; j < edgeloop.Edges.size(); j++)
        {
            if (Edges[i].IsIntersectWith1(edgeloop.Edges[j]))
                return true;
        }
    }
    return false;
}

//判断点是否在edgeloop1上，用a来标记第几条边上，b标记是否与该边的起点或重点重合。只有a生效，b才有可能生效
bool CEdgeLoop::IsPointOn(const vec2 &point, int& a, int &b, const CTolerance &tolerance) const
{
    a = -1;
    for (unsigned int i = 0; i < Edges.size(); i++)
    {
        if (Edges[i].IsPointOn(point, b, tolerance))
        {
            a = i;
            return true;
        }
    }
    return false;
}

//平移该环，方法是平移该环中的每一条CEdge
void CEdgeLoop::Move(const vec2 direction) // 平移
{
    for (unsigned int i = 0; i < Edges.size(); i++)
    {
        Edges[i].Move(direction);
    }
    Commit();
}

#pragma endregion

#pragma region Implements of CRegion

void CRegion::Commit()
{
    OuterLoops.Commit();
    for (unsigned int i = 0; i < InnerLoops.size(); i++)
        InnerLoops[i].Commit();
    // get Box
    Box = OuterLoops.Box;
    for (unsigned int i = 0; i < InnerLoops.size(); i++)
        Box.Union(InnerLoops[i].Box);
}

bool CRegion::IsIntersectWith(const CRegion &region) const
{
    if (!Box.IsIntersectWith(region.Box))
        return false;

    if (OuterLoops.IsIntersectWith(region.OuterLoops))
        return true;
    for (unsigned int i = 0; i < InnerLoops.size(); i++)
    {
        if (region.OuterLoops.IsIntersectWith(InnerLoops[i]))
            return true;
    }
    for (unsigned int i = 0; i < region.InnerLoops.size(); i++)
    {
        if (OuterLoops.IsIntersectWith(region.InnerLoops[i]))
            return true;
    }
    for (unsigned int i = 0; i < InnerLoops.size(); i++)
    {
        for (unsigned int j = 0; j < region.InnerLoops.size(); j++)
        {
            if (InnerLoops[i].IsIntersectWith(region.InnerLoops[j]))
                return true;
        }
    }
    return false;
}

void CRegion::AddOuterloop(const PointArray &points)
{
    CEdgeLoop out;
    for (unsigned int i = 0; i < points.size() - 1; i++)
    {
        CEdge edge(points[i], points[i+1]);
        out.Edges.push_back(edge);
    }
    CEdge edge(points[points.size() - 1], points[0]);
    out.Edges.push_back(edge);
    out.Commit();

    OuterLoops = out;
    Commit();
}
void CRegion::AddInnerloops(const PointArray &points)
{
    CEdgeLoop inloop;
    for (unsigned int i = 0; i < points.size() - 1; i++)
    {
        CEdge edge(points[i], points[i+1]);
        inloop.Edges.push_back(edge);
    }
    CEdge edge(points[points.size() - 1], points[0]);
    inloop.Edges.push_back(edge);
    inloop.Commit();

    InnerLoops.push_back(inloop);
    Commit();
}

bool CRegion::IsPointOn(const vec2 &point, int &a, int &b, int &c, const CTolerance &tolerance) const
{
    if (OuterLoops.IsPointOn(point, b, c, tolerance))
    {
        a = 0;
        return true;
    }
    for (unsigned int i = 0; i < InnerLoops.size(); i++)
    {
        if (InnerLoops[i].IsPointOn(point, b, c, tolerance))
        {
            a = i+1;
            return true;
        }
    }
    a = -1;
    return false;
}

void CRegion::Move(const vec2 direction) // 平移
{
    OuterLoops.Move(direction);
    for (unsigned int i = 0; i < InnerLoops.size(); i++)
    {
        InnerLoops[i].Move(direction);
    }
    Commit();
}

#pragma endregion

#pragma region Implements of CPolygon
void CPolygon::Commit()
{
    if (Regions.size() == 0)
        return;
    for (unsigned int i = 0; i < Regions.size(); i++)
        Regions[i].Commit();
    // get Box
    Box = Regions[0].Box;
    for (unsigned int i = 1; i < Regions.size(); i++)
        Box.Union(Regions[i].Box);
}

void CPolygon::ParseVector(vec2& vec, const char* line)
{
    std::string temp;
    std::stringstream ss(line);
    ss >> vec.x;
    ss >> vec.y;
}

void CPolygon::ParseNumber(int &num, const char* line)
{
    std::string temp;
    std::stringstream ss(line);
    ss >> temp;
    ss >> num;
}

void CPolygon::Dispose()
{
    Regions.clear();
}

void CPolygon::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {	// storing code
        CString line;
        ar.WriteString("# PolygonBooleanOperation\r\n");
        ar.WriteString("# 创建的文件: ");

        SYSTEMTIME st;
        CString strDate,strTime;
        GetLocalTime(&st);
        strDate.Format("%4d-%2d-%2d ",st.wYear,st.wMonth,st.wDay);
        strTime.Format("%2d:%2d:%2d\r\n\r\n",st.wHour,st.wMinute,st.wSecond);
        ar.WriteString(strDate.GetString());
        ar.WriteString(strTime.GetString());

        line.Format("Regions %d\r\n\r\n", Regions.size());
        ar.WriteString(line.GetString());

        for (unsigned int i = 0; i < Regions.size(); i++)
        {
            line.Format("Loops %d\r\n", Regions[i].InnerLoops.size() + 1);
            ar.WriteString(line.GetString());

            for (unsigned int j = 0; j <= Regions[i].InnerLoops.size(); j++)
            {
                if (j == 0)
                {
                    line.Format("Edges %d\r\n", Regions[i].OuterLoops.Edges.size());
                    ar.WriteString(line.GetString());
                    for (unsigned int k = 0; k < Regions[i].OuterLoops.Edges.size(); k++)
                    {
                        line.Format("%f %f\r\n", Regions[i].OuterLoops.Edges[k].Start, Regions[i].OuterLoops.Edges[k].End);
                        ar.WriteString(line.GetString());
                    }
                }
                else
                {
                    line.Format("Edges %d\r\n", Regions[i].InnerLoops[j - 1].Edges.size());
                    ar.WriteString(line.GetString());
                    for (unsigned int k = 0; k < Regions[i].InnerLoops[j - 1].Edges.size(); k++)
                    {
                        line.Format("%f %f\r\n", Regions[i].InnerLoops[j - 1].Edges[k].Start, Regions[i].InnerLoops[j - 1].Edges[k].End);
                        ar.WriteString(line.GetString());
                    }
                }
            }
            ar.WriteString("\r\n");
        }
    }
    else
    {	// loading code
        Dispose();
        CString line;
        std::vector<vec2> points;
        int region_count = 0;
        int loop_count = 0;
        int edge_count = 0;
        CRegion region;
        try
        {
            while(ar.ReadString(line))
            {
                if (!line.IsEmpty())
                {
                    if (line[0] == 'R')
                    {
                        ParseNumber(region_count, line.GetString());
                        break;
                    }
                }
            }

            for (int i = 0; i < region_count; i++)
            {
                region.InnerLoops.clear();
                while(ar.ReadString(line))
                {
                    if (!line.IsEmpty())
                    {
                        if (line[0] == 'L')
                        {
                            ParseNumber(loop_count, line.GetString());
                            break;
                        }
                    }
                }

                for (int j = 0; j < loop_count; j++)
                {
                    points.clear();
                    while(ar.ReadString(line))
                    {
                        if (!line.IsEmpty())
                        {
                            if (line[0] == 'E')
                            {
                                ParseNumber(edge_count, line.GetString());
                                break;
                            }
                        }
                    }

                    for (int k = 0; k < edge_count; k++)
                    {
                        while(ar.ReadString(line))
                        {
                            if (!line.IsEmpty())
                                break;
                        }
                        vec2 vec;
                        ParseVector(vec, line.GetString());
                        points.push_back(vec);
                    }

                    if (j == 0)
                        region.AddOuterloop(points);
                    else
                        region.AddInnerloops(points);
                }
                // judge whether EdgeLoop is valid
                // #ifdef DEBUG
                //                 if (!region.IsValid())
                //                     throw std::exception("region is Invalid!");
                // #endif
                Regions.push_back(region);
            }
            Commit();  // refresh Box of Polygon
        }
        catch (...)
        {
            throw std::exception("Serialize Failed!");
        }
    }
}

bool CPolygon::IsPointOn(const vec2& point, int &a, int &b, int &c, int &d, const CTolerance &tolerance) const
{
    for (unsigned int i = 0; i < Regions.size(); i++)
    {
        if (Regions[i].IsPointOn(point, b, c, d, tolerance))
        {
            a = i;
            return true;
        }
    }
    a = -1;
    return false;
}

void CPolygon::Move(const vec2 direction) // 平移
{
    for (unsigned int i = 0; i < Regions.size(); i++)
    {
        Regions[i].Move(direction);
    }
    Commit();
}

#pragma endregion
