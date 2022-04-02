#pragma once
#include<bits/stdc++.h>
#include"map_result.h"
#include"dir_file.h"
#define p1 0.2      //第三代测序错误率
#define p2 0.05     //第二代测序错误率
#define p3 0.2
#define p4 0.8
#define p5 0.5
using namespace std;
double combine_num(int n,int m);

void combine_judge(vector<bool>& judge1,vector<bool>& judge2);

void combine_base_count(vector<vector<pair<char,int>>>& base_count1,vector<vector<pair<char,int>>>& base_count2);

//mode=1 用第三代测序数据进行杂合性判断 mode=2 用第二代测序数据进行杂合性判断
vector<bool> judge(const string &ref,vector<map_result>& map_results,int mode,vector<vector<pair<char,int>>>& base_count);
