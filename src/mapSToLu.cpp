//将S映射到Lu上，根据生成的sam文件得到映射结果
#include<bits/stdc++.h>
#include<boost/regex.hpp>
#include"map_result.h"
#include"dir_file.h"
using namespace std;

int main(){
    vector<string> files;
    getFiles(files,SRmap_dir);
    boost::regex expression("S[0-9]*_L[0-9]*.sam");
    for(auto &file:files){
        int len = file.size();
        if(boost::regex_match(file,expression)){
            map_result mr(2,SRmap_dir+string("/")+file);
            mr.output(2);
        }
    }    
    return 0;
}