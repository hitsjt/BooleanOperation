#pragma once
struct CConfig
{
    static int ActiveObjectNumber; // 标记当前活动的多边形
    static int ActiveRegionNumber; // 标记当前活动的区域
    static int ActiveLoopNumber; // 标记当前活动的环
    static int ActiveEdgeNumber; // 标记当前活动的边
    static int ActivePointNumber; // 标记当前活动的点
    static float EnlargementFactor; // 鼠标放大缩小倍数

    static int RegularPolygonEdgesCount; // 记录数字编辑框中的数值
    static bool RenderPoint; // 复选框顶点
    static bool RenderFull; // 复选框填充
    static bool SeleteRegion; // 复选框选择整个区域
    static bool SeletePolygon; // 复选框选择整个多边形
    static bool ShowA; // 复选框显示A
    static bool ShowB; // 复选框显示B
    static bool ShowResult; // 复选框显示结果
    static bool is_modified; // 记录是否改动，需要三角化
    static bool ShowIndex; // 标记是否显示顶点信息
};

