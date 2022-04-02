//将S映射到参考序列ref上，根据生成的sam文件得到映射结果
#include<bits/stdc++.h>
#include<boost/regex.hpp>
#include"dir_file.h"
#include"map_result.h"
using namespace std;

int main(){
    vector<string> files;
    getFiles(files,SRmap_dir);
    boost::regex expression("S[0-9]*.sam");
    for(auto &file:files){            
        if(boost::regex_match(file,expression)){
            map_result mr(1,Lmap_dir+string("/")+file);
            mr.output(1);
        }
    }
    return 0;
}