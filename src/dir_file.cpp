#include"dir_file.h"
void getFiles(vector<string>& files,string dir_name)
{	
    files.clear();
	DIR *dp;
	struct dirent *dirp;
    if ((dp = opendir(dir_name.c_str())) != NULL){
        while((dirp = readdir(dp)) != NULL){
            files.push_back(dirp->d_name);
        }
    }
	closedir(dp);
}