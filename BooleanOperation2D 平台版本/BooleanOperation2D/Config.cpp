#include "stdafx.h"
#include "Config.h"

int CConfig::ActiveObjectNumber = -1;
int CConfig::ActiveRegionNumber = -1;
int CConfig::ActiveLoopNumber = -1;
int CConfig::ActivePointNumber = -1;
int CConfig::ActiveEdgeNumber = -1;
float CConfig::EnlargementFactor = 1.0;

int CConfig::RegularPolygonEdgesCount = 3;
bool CConfig::RenderPoint = true;
bool CConfig::RenderFull = false;
bool CConfig::SeleteRegion = false;
bool CConfig::SeletePolygon = false;
bool CConfig::ShowA = true;
bool CConfig::ShowB = true;
bool CConfig::ShowResult = true;
bool CConfig::is_modified = false;
bool CConfig::ShowIndex = false;
