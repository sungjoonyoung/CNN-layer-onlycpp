#include<iostream>
#include<fstream>
#include<vector>
#include"sungso376_STR.hpp"
using namespace std;
int main(void){
    // string file = "_file_chck.csv";
    string file = "contain/tmp.csv";

    ifstream fin(file);
    if (fin) {
        string str;
        // for(int i=0;i<3;i++){
        //     fin>>str;
        //     cout<<str<<"\n";
        //     vector<string> v;
        //     v=string_pasing(str);
        //     for(auto c:v)cout<<stod(c)<<"\n";
        // }
        while(getline(fin,str)){
            cout<<str<<"\n";
            vector<string> v;
            v=string_pasing(str);
            for(auto c:v)cout<<stod(c)<<"\n";
        }
    }
}