#pragma once
#include<bits/stdc++.h>
#define Lmap_result_dir "./../Lmap_result"
#define SLmap_result_dir "./../SLmap_result"
#define SRmap_result_dir "./../SRmap_result"
#define Lmap_dir "./../Lmap"
#define SLmap_dir "./../SLmap"
#define SRmap_dir "./../SRmap"
#define ref_dir "./../ref"
using namespace std;
class map_result{
private:
    string reads_name;
    string ref_name;
    bool is_map=true;
    int map_quality;
    int first_map_pos_of_ref=-1;
    int reads_len=-1;
    string seq;
public:
    map_result(string rn,bool ismap,int mq,int fmpor,int rl,std::string sq):reads_name(rn),is_map(ismap),map_quality(mq),first_map_pos_of_ref(fmpor),reads_len(rl),seq(sq){

    }
    map_result(const string& s1,const string& s2,const string &s3,const string &s4,const string &s5);
    map_result(int mode,const string& filename);
    pair<string,string> string_split(string s){
        string temp1,temp2;
        for(int i=0;i<s.size();++i){
            if(s[i]==':'){
                temp1 = s.substr(0,i);
                temp2 = s.substr(i+1,s.size()-i-1);
                break;
            }
        }
        return make_pair(temp1,temp2);
    }
    bool is_mapped(){
        return is_map;
    }
    string get_readsname(){
        return reads_name;
    }
    string get_seq(){
        return seq;
    }
    int get_first_pos(){
        return first_map_pos_of_ref;
    }
    int get_reads_len(){
        return reads_len;
    }
    void set_seq(int index,char ch){
        seq[index] = ch;
    }
    string get_ref_name(){
        return ref_name;
    }
    void output(int mode);
};