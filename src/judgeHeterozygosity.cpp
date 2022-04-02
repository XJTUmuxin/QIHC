#include"judgeHeterozygosity.h"
double combine_num(int n,int m){
    if (n == m || m == 0) return 1;

    vector<double> dp(m+1);
    for (int i = 0; i <= n; i++){
        for (int j = min(i, m); j >= 0; j--){
            if (i == j || j == 0) dp[j] = 1;
            else dp[j] = dp[j] + dp[j-1];
        }
    }
    return dp[m];
}
void combine_base_count(vector<vector<pair<char,int>>>& base_count1,vector<vector<pair<char,int>>>& base_count2){
    if(base_count1.size()!=base_count2.size()){
        cout<<"combine_base_count_err"<<endl;
        exit(1);
    }
    for(int i=0;i<base_count1.size();++i){
        for(int j=0;j<5;++j){
            base_count1[i][j].second+=base_count2[i][j].second;
        }
    }
}

void combine_judge(vector<bool>& judge1,vector<bool>& judge2){
    int len1 = judge1.size();
    int len2 = judge2.size();
    if(len1!=len2){
        exit(1);
    }
    for(int i=0;i<len1;++i){
        if(!judge1[i] || !judge2[i]){
            judge1[i] = false;
        }
    }
}
//mode=1 对应Lm的杂合性判断 mode=2 对应Lu的杂合性判断
vector<bool> judge(const string &ref,vector<map_result>& map_results,int mode,vector<vector<pair<char,int>>>& base_count){
    if(mode!=1 && mode!=2){
        cout<<"模式错误"<<endl;
        exit(1);
    }
    static int A=0,T=1,G=2,C=3,N=4;
    int ref_len = ref.size();
    vector<bool> judge_result(ref_len);
    vector<int> rd(ref_len,0);              //该位点匹配到的序列数
    vector<int> dl(ref_len,0);              //该位点匹配到的序列对应位点出现的碱基种类
    for(auto &mapresult:map_results){
        int start_index = mapresult.get_first_pos()-1;
        int len = mapresult.get_reads_len();
        string seq = mapresult.get_seq();
        for(int i=0;i<len;++i){
            if(seq[i]=='A'){
                if(base_count[start_index+i][0].second==0)dl[start_index+i]++;
                base_count[start_index+i][0].second++;
            }
            else if(seq[i]=='T'){
                if(base_count[start_index+i][1].second==0)dl[start_index+i]++;
                base_count[start_index+i][1].second++;
            }
            else if(seq[i]=='G'){
                if(base_count[start_index+i][2].second==0)dl[start_index+i]++;
                base_count[start_index+i][2].second++;
            }
            else if(seq[i]=='C'){
                if(base_count[start_index+i][3].second==0)dl[start_index+i]++;
                base_count[start_index+i][3].second++;
            }
            else{
                if(base_count[start_index+i][4].second==0)dl[start_index+i]++;
                base_count[start_index+i][4].second++;
            }
            rd[start_index+i]++;
        }
    }
    vector<vector<pair<char,int>>> base_count_copy = base_count;
    for(auto &v:base_count_copy){
        sort(v.begin(),v.end(),[](pair<char,int>& a,pair<char,int>& b){return a.second>b.second;});
    }
    for(int i=0;i<ref_len;++i){
        double p_err; 
        double p_hete;
        double p_homo;
        int Rd=rd[i];
        if(mode==1){    //Lm
            p_err = p1;
        }
        else{           //Lu
            p_err = p2;
        }
        if(dl[i]<=1){
            judge_result[i] = false;
        }
        else if(dl[i]==2){
            int r1 = base_count_copy[i][0].second;
            int r2 = base_count_copy[i][1].second;
            p_homo = combine_num(Rd,r1)*pow(1-p_err,r1)*pow(p_err,Rd-r1)*combine_num(Rd-r1,r2)*pow(p_err,r2)*pow(1-p_err,Rd-r1-r2)*p3;
            p_hete = combine_num(Rd,r1)*pow(p5,r1)*pow(1-p5,Rd-r1)*combine_num(Rd-r1,r2)*pow(p5,r2)*pow(1-p5,Rd-r1-r2)*p4;

            if(p_homo>p_hete){
                judge_result[i] = false;
            }
            else{
                judge_result[i] = true;
            }
        }
        else if(dl[i]==3){
            int r1 = base_count_copy[i][0].second;
            int r2 = base_count_copy[i][1].second;
            int r3 = base_count_copy[i][2].second;
            p_homo = combine_num(Rd,r1)*pow(1-p_err,r1)*pow(p_err,Rd-r1)*combine_num(Rd-r1,r2)*pow(p_err/2,r2)*pow(1-p_err/2,Rd-r1-r2)*
            combine_num(Rd-r1-r2,r3)*pow(p_err/2,r3)*pow(1-p_err/2,Rd-r1-r2-r3)*p3;

            p_hete = combine_num(Rd,r1)*pow((1-p_err)/2,r1)*pow(1-(1-p_err)/2,Rd-r1)*combine_num(Rd-r1,r2)*pow((1-p_err)/2,r2)*
            pow(1-(1-p_err)/2,Rd-r1-r2)*combine_num(Rd-r1-r2,r3)*pow(p_err,r3)*pow(1-p_err,Rd-r1-r2-r3)*p4;

            if(p_homo>p_hete){
                judge_result[i] = false;
            }
            else{
                judge_result[i] = true;
            }

        }
        else if(dl[i]==4){
            int r1 = base_count_copy[i][0].second;
            int r2 = base_count_copy[i][1].second;
            int r3 = base_count_copy[i][2].second;
            int r4 = base_count_copy[i][3].second;
            p_homo = combine_num(Rd,r1)*pow(1-p_err,r1)*pow(p_err,Rd-r1)*combine_num(Rd-r1,r2)*pow(p_err/3,r2)*pow(1-p_err/3,Rd-r1-r2)*
            combine_num(Rd-r1-r2,r3)*pow(p_err/3,r3)*pow(1-p_err/3,Rd-r1-r2-r3)*combine_num(Rd-r1-r2-r3,r4)*pow(p_err/3,r4)*
            pow(1-p_err/3,Rd-r1-r2-r3-r4)*p3;
            
            p_hete = combine_num(Rd,r1)*pow((1-p_err)/2,r1)*pow(1-(1-p_err)/2,Rd-r1)*combine_num(Rd-r1,r2)*pow((1-p_err)/2,r2)*
            pow(1-(1-p_err)/2,Rd-r1-r2)*combine_num(Rd-r1-r2,r3)*pow(p_err/2,r3)*pow(1-p_err/2,Rd-r1-r2-r3)*combine_num(Rd-r1-r2-r3,r4)*
            pow(p_err/2,r4)*pow(1-p_err/2,Rd-r1-r2-r3-r4)*p4;

            if(p_homo>p_hete){
                judge_result[i] = false;
            }
            else{
                judge_result[i] = true;
            }
        }
        else if(dl[i]==5){
            int r1 = base_count_copy[i][0].second;
            int r2 = base_count_copy[i][1].second;
            int r3 = base_count_copy[i][2].second;
            int r4 = base_count_copy[i][3].second;
            int r5 = base_count_copy[i][4].second;
            p_homo = combine_num(Rd,r1)*pow(1-p_err,r1)*pow(p_err,Rd-r1)*combine_num(Rd-r1,r2)*pow(p_err/4,r2)*pow(1-p_err/4,Rd-r1-r2)*
            combine_num(Rd-r1-r2,r3)*pow(p_err/4,r3)*pow(1-p_err/4,Rd-r1-r2-r3)*combine_num(Rd-r1-r2-r3,r4)*pow(p_err/4,r4)*
            pow(1-p_err/4,Rd-r1-r2-r3-r4)*combine_num(Rd-r1-r2-r3-r4,r5)*pow(p_err/4,r5)*pow(1-p_err/4,Rd-r1-r2-r3-r4-r5)*p3;

            p_hete = combine_num(Rd,r1)*pow((1-p_err)/2,r1)*pow(1-(1-p_err)/2,Rd-r1)*combine_num(Rd-r1,r2)*pow((1-p_err)/2,r2)*
            pow(1-(1-p_err)/2,Rd-r1-r2)*combine_num(Rd-r1-r2,r3)*pow(p_err/3,r3)*pow(1-p_err/3,Rd-r1-r2-r3)*combine_num(Rd-r1-r2-r3,r4)*
            pow(p_err/3,r4)*pow(1-p_err/3,Rd-r1-r2-r3-r4)*combine_num(Rd-r1-r2-r3-r4,r5)*pow(p_err/3,r5)*pow(1-p_err/3,Rd-r1-r2-r3-r4-r5)*p4;

            if(p_homo>p_hete){
                judge_result[i] = false;
            }
            else{
                judge_result[i] = true;
            }
        }
    }
    return judge_result;
}