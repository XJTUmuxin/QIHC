#include"map_result.h"
map_result::map_result(const string& s1,const string& s2,const string &s3,const string &s4,const string &s5){
    auto temp = string_split(s1);
    if(temp.first=="S_name"){
        reads_name = temp.second;
    }
    else{
        cout<<"map_result class create error"<<endl;
        exit(1);
    }
    temp = string_split(s2);
    if(temp.first=="ref_name"){
        ref_name = temp.second;
    }
    else{
        cout<<"map_result class create error"<<endl;
        exit(1);
    }
    temp = string_split(s3);
    if(temp.first=="first_map_pos"){
        first_map_pos_of_ref = stoi(temp.second);
    }
    else{
        cout<<"map_result class create error"<<endl;
        exit(1);
    }
    temp = string_split(s4);
    if(temp.first=="seq"){
        seq = temp.second;
    }
    else{
        cout<<"map_result class create error"<<endl;
        exit(1);
    }
    temp = string_split(s5);
    if(temp.first=="reads_len"){
        reads_len = stoi(temp.second);
    }
    else{
        cout<<"map_result class create error"<<endl;
        exit(1);
    }
}
map_result::map_result(int mode,const string& filename){
    ifstream file_stream(filename);
    if(!file_stream){  
        exit(1);
    } 
    if(mode==1){//读取L.sam文件
        string temp;
        string info_line;
        while(info_line.size()==0 || info_line[0]=='@'){
            getline(file_stream,info_line);
        }
        istringstream sstream(info_line);
        sstream>>reads_name;
        int flag;
        sstream>>flag;
        if((flag>>1)&1){
            sstream>>temp;
            sstream>>first_map_pos_of_ref;
            sstream>>map_quality;
            if(map_quality>=10){
                is_map = true;
                for(int i=0;i<4;++i)sstream>>temp;
                sstream>>seq;
                reads_len = seq.size();
            }
            else{
                is_map = false;
            }
        }
        else{
            is_map = false;
        }
    }
    else if(mode==2){//读取S.sam文件
        string temp;
        string info_line;
        while(info_line.size()==0 || info_line[0]=='@'){
            getline(file_stream,info_line);
        }
        istringstream sstream(info_line);
        sstream>>reads_name;
        int flag;
        sstream>>flag;
        if((flag>>1)&1){
            sstream>>ref_name;
            sstream>>first_map_pos_of_ref;
            sstream>>map_quality;
            if(map_quality>=10){
                is_map = true;
                for(int i=0;i<4;++i)sstream>>temp;
                sstream>>seq;
                reads_len = seq.size();
            }
            else{
                is_map = false;
            }
        }
        else{
            is_map = false;
        }
    }
    else if(mode==3){//读取txt文件
        string s1,s2,s3,s4,s5,s6;
        getline(file_stream,s1);
        getline(file_stream,s2);
        getline(file_stream,s3);
        getline(file_stream,s4);
        getline(file_stream,s5);
        getline(file_stream,s6);
        auto temp = string_split(s1);
        if(temp.first=="is_map"){
            is_map = temp.second=="1"?true:false;
        }
        else{
            cout<<"map_result class create error"<<endl;
            exit(1);
        }
        temp = string_split(s2);
        if(temp.first=="reads_name"){
            reads_name = temp.second;
        }
        else{
            cout<<"map_result class create error"<<endl;
            exit(1);
        }
        temp = string_split(s3);
        if(temp.first=="map_quality"){
            map_quality = stoi(temp.second);
        }
        else{
            cout<<"map_result class create error"<<endl;
            exit(1);
        }
        temp = string_split(s4);
        if(temp.first=="first_map_pos_of_ref"){
            first_map_pos_of_ref = stoi(temp.second);
        }
        else{
            cout<<"map_result class create error"<<endl;
            exit(1);
        }
        temp = string_split(s5);
        if(temp.first=="seq"){
            seq = temp.second;
        }
        else{
            cout<<"map_result class create error"<<endl;
            exit(1);
        }
        temp = string_split(s6);
        if(temp.first=="reads_len"){
            reads_len = stoi(temp.second);
        }
        else{
            cout<<"map_result class create error"<<endl;
            exit(1);
        }
    }
    else{
        cout<<"map_result class create error"<<endl;
        exit(1);
    }
    file_stream.close();
    file_stream.clear();
}
void map_result::output(int mode){
    if(mode==1){
        string file_name = Lmap_result_dir+string("/")+reads_name+"_mapping_result.txt";
        ofstream file_stream(file_name);
        if(!file_stream){
            cout<<"output_err"<<endl;
            exit(1);
        }
        file_stream<<"is_map:"<<is_map<<"\n";
        if(is_map){
            file_stream<<"reads_name:"<<reads_name<<"\n";
            file_stream<<"map_quality:"<<map_quality<<"\n";
            file_stream<<"first_map_pos_of_ref:"<<first_map_pos_of_ref<<"\n";
            file_stream<<"seq:"<<seq<<"\n";
            file_stream<<"reads_len:"<<reads_len<<"\n";            
        }
        else{
            file_stream<<"seq:"<<seq<<"\n";
        }
        file_stream.close();
        file_stream.clear();
    }
    else if(mode==2){
        string file_name = SLmap_result_dir+string("/")+("STo"+ref_name+".txt");
        ofstream file_stream(file_name,ofstream::app);
        if(!file_stream){
            cout<<"output_err"<<endl;
            exit(1);
        }
        if(is_map){
            file_stream<<"S_name:"<<reads_name<<"\n";
            file_stream<<"ref_name"<<ref_name<<"\n";
            file_stream<<"first_map_pos:"<<first_map_pos_of_ref<<"\n";
            file_stream<<"seq:"<<seq<<"\n";
            file_stream<<"reads_len:"<<reads_len<<"\n";
        }
        file_stream.close();
        file_stream.clear();
    }
    else if(mode==3){
        string file_name = string(SRmap_result_dir)+"/"+reads_name+"_mapping_result.txt";
        ofstream file_stream(file_name);
        if(!file_stream){
            cout<<"output_err"<<endl;
            exit(1);
        }
        file_stream<<"is_map:"<<is_map<<"\n";
        if(is_map){
            file_stream<<"reads_name:"<<reads_name<<"\n";
            file_stream<<"map_quality:"<<map_quality<<"\n";
            file_stream<<"first_map_pos_of_ref:"<<first_map_pos_of_ref<<"\n";
            file_stream<<"seq:"<<seq<<"\n";
            file_stream<<"reads_len:"<<reads_len<<"\n";            
        }
        else{
            file_stream<<"seq:"<<seq<<"\n";
        }
        file_stream.close();
        file_stream.clear();
    }
    else{
        cout<<"output mode error"<<endl;
        exit(1);
    }
}