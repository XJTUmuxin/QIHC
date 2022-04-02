//将L映射到参考序列ref上，根据生成的sam文件得到映射结果
//同时区分出Lm和Lu
#include<bits/stdc++.h>
#include<boost/regex.hpp>
#include"dir_file.h"
#include"map_result.h"
using namespace std;

int main(){
    vector<string> files;
    vector<string> Lm;
    vector<string> Lu;
    getFiles(files,Lmap_dir);
    boost::regex expression("L[0-9]*.sam");
    for(auto &file:files){              //得到L的map结果并且获得Lm和Lu集合
        if(boost::regex_match(file,expression)){
            map_result mr(1,Lmap_dir+string("/")+file);
            if(mr.is_mapped()){
                Lm.push_back(mr.get_readsname());
            }
            else{
                Lu.push_back(mr.get_readsname());
            }
            mr.output(1);
        }
    }
    files.clear();
    ofstream ofs(Lmap_result_dir+string("/set_of_Lm.txt"));
    if(!ofs)return -1;
    for(auto &L:Lm){
        ofs<<L<<"\n";
    }
    ofs.close();
    ofs.clear();
    ofs.open(Lmap_result_dir+string("/set_of_Lu.txt"));
    if(!ofs)return -1;
    for(auto &L:Lu){
        ofs<<L<<"\n";
    }
    ofs.close();
    ofs.clear();
    return 0;
}