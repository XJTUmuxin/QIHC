#include"correct.h"
void correct_Lu(vector<bool>& hete,vector<vector<pair<char,int>>>& base_count,string& seq){
    if(hete.size()!=base_count.size() || base_count.size()!=seq.size()){
        cout<<"correct_Lu error"<<endl;
        exit(1);
    }
    srand((unsigned)time(NULL));
    int length = hete.size();
    for(int i=0;i<length;++i){
        if(hete[i]){
            if(seq[i]==base_count[i][0].first || seq[i]==base_count[i][1].first){
                continue;
            }
            else{
                int index = rand()%2;
                seq[i]=base_count[i][index].first;
            }
        }
        else{
            seq[i] = base_count[i][0].first;
        }
    }
}
void correct_Lm(vector<bool>& hete,vector<vector<pair<char,int>>>& base_count,map_result& mr){
    if(hete.size()!=base_count.size()){
        cout<<"correct_Lm error"<<endl;
        exit(1);
    }
    string seq = mr.get_seq();
    int length = seq.size();
    int index = mr.get_first_pos()-1;
    srand((unsigned)time(NULL));
    for(int i=0;i<length;++i){
        if(hete[index]){
            if(seq[i]!=base_count[index][0].first || seq[i]!=base_count[index][1].first){
                continue;
            }
            else{
                int j = rand()%2;
                mr.set_seq(i,base_count[index][j].first);
            }
        }
        else{
            mr.set_seq(i,base_count[index][0].first);
        }
        ++index;
    }
}