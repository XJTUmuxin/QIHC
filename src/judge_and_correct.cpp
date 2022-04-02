#include<bits/stdc++.h>
#include<boost/regex.hpp>
#include"map_result.h"
#include"dir_file.h"
#include"judgeHeterozygosity.h"
#include"correct.h"
using namespace std;
int main(){
    vector<string> files;
    getFiles(files,SLmap_result_dir);
    ofstream ofs(string(correct_dir)+"/correct_L.txt");
    //纠错Lu
    boost::regex expression("SToL[0-9]*.txt");
    for(auto &file:files){
        if(boost::regex_match(file,expression)){
            string ref;
            vector<map_result> map_results;
            vector<vector<pair<char,int>>> base_count(ref.size(),vector<pair<char,int>>{make_pair('A',0),make_pair('T',0),make_pair('G',0),make_pair('C',0),make_pair('N',0)});   //该位点匹配到的序列对应位点的各碱基数统计
            string temp1,temp2,temp3,temp4,temp5;
            ifstream fstream(file);
            while(getline(fstream,temp1)){
                getline(fstream,temp2);
                getline(fstream,temp3);
                getline(fstream,temp4);
                getline(fstream,temp5);
                map_results.push_back(map_result(temp1,temp2,temp3,temp4,temp5));
            }
            fstream.close();
            fstream.clear();
            fstream.open(string(Lmap_result_dir)+"/"+map_results[0].get_ref_name()+"_mapping_result.txt");
            getline(fstream,ref);
            getline(fstream,ref);
            fstream.close();
            fstream.clear();
            vector<bool>hete = judge(ref,map_results,2,base_count);
            correct_Lu(hete,base_count,ref);
            ofs<<map_results[0].get_ref_name()<<":\n";
            ofs<<ref<<"\n";
        }
    }
    //纠错Lm
    getFiles(files,Lmap_result_dir);
    string ref;
    ifstream fstream(string(ref_dir)+"/ref.txt");
    getline(fstream,ref);
    fstream.close();
    fstream.clear();
    vector<map_result> map_results;
    
    getFiles(files,SRmap_result_dir);
    vector<vector<pair<char,int>>> base_count1(ref.size(),vector<pair<char,int>>{make_pair('A',0),make_pair('T',0),make_pair('G',0),make_pair('C',0),make_pair('N',0)});   //该位点匹配到的序列对应位点的各碱基数统计
    expression.assign("S[0-9]*_mapping_result.txt");
    for(auto &file:files){
        if(boost::regex_match(file,expression)){
            map_result temp = map_result(3,string(SRmap_result_dir)+"/"+file);
            if(temp.is_mapped()){
                map_results.push_back(temp);
            }
        }
    }
    vector<bool> hete1 = judge(ref,map_results,2,base_count1);  //通过S获得的杂合判断结果
    map_results.clear();
    vector<vector<pair<char,int>>> base_count2(ref.size(),vector<pair<char,int>>{make_pair('A',0),make_pair('T',0),make_pair('G',0),make_pair('C',0),make_pair('N',0)});   //该位点匹配到的序列对应位点的各碱基数统计
    expression.assign("L[0-9]*_mapping_result.txt");
    for(auto &file:files){
        if(boost::regex_match(file,expression)){
            map_result temp = map_result(3,string(Lmap_result_dir)+"/"+file);
            if(temp.is_mapped()){
                map_results.push_back(temp);
            }
        }
    }    
    vector<bool> hete2 = judge(ref,map_results,1,base_count2);  //通过Lm获得的杂合判断结果
    combine_judge(hete1,hete2);
    combine_base_count(base_count1,base_count2);
    for(auto &v:base_count1){
        sort(v.begin(),v.end(),[](pair<char,int>& a,pair<char,int>& b){return a.second>b.second;});
    }
    for(auto &map_result:map_results){
        correct_Lm(hete1,base_count1,map_result);
        ofs<<map_result.get_readsname()<<":\n";
        ofs<<map_result.get_seq()<<"\n";
    }
    ofs.close();
    ofs.clear();
}