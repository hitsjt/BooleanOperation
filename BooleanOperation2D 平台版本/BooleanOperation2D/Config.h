#pragma once
struct CConfig
{
    static int ActiveObjectNumber; // ��ǵ�ǰ��Ķ����
    static int ActiveRegionNumber; // ��ǵ�ǰ�������
    static int ActiveLoopNumber; // ��ǵ�ǰ��Ļ�
    static int ActiveEdgeNumber; // ��ǵ�ǰ��ı�
    static int ActivePointNumber; // ��ǵ�ǰ��ĵ�
    static float EnlargementFactor; // ���Ŵ���С����

    static int RegularPolygonEdgesCount; // ��¼���ֱ༭���е���ֵ
    static bool RenderPoint; // ��ѡ�򶥵�
    static bool RenderFull; // ��ѡ�����
    static bool SeleteRegion; // ��ѡ��ѡ����������
    static bool SeletePolygon; // ��ѡ��ѡ�����������
    static bool ShowA; // ��ѡ����ʾA
    static bool ShowB; // ��ѡ����ʾB
    static bool ShowResult; // ��ѡ����ʾ���
    static bool is_modified; // ��¼�Ƿ�Ķ�����Ҫ���ǻ�
    static bool ShowIndex; // ����Ƿ���ʾ������Ϣ
};

