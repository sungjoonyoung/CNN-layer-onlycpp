/*
for data parsing

string "x,xx,x" -> vector{x,xx,x}
or
vector{xx,xxx,x} -> "xx,xxx,x"
*/
#pragma once
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

//파싱
// template <typename T1>
// string "x,xx,x" -> vector{x,xx,x}
auto string_pasing(string &a, int max_size=2'000'000'000) {
    vector<string> data;
    string in="";
    for(int i=0;i<a.size();i++){
        if(a[i]==' ')continue;
        if(a[i]==','){
            if(data.size()==max_size)break;
            data.push_back(in);
            in="";
        }
        else in+=a[i];
    }
    if(in!="" and data.size()!=max_size)data.push_back(in);
    return data;
}

// vector{xx,xxx,x} -> "xx,xxx,x"
template <typename T1>
auto data_to_string(vector<T1> &v){
    string out = "";
    for(auto s:v){
        out+=to_string(s);
        out+=",";
    }
    return out;
}

template <typename T1, typename T2>
auto progress_bar(T1 N, T2 progress){
    string str="[";
    for(int i=1;i<=10;i++){
        if(i*10<(double)progress/N*100)str+='*';
        else str+='.';
    }
    str+=']';
    str+='(';
    str+=to_string(progress);
    str+='/';
    str+=to_string(N);
    str+=")";
    return str;
}

/*
ifsteam 형태로 scv 를 받아서
파싱해서
레이어 노드들을 파싱
*/
auto read_node(ifstream &fin,int N,int demension){
    vector<vector<double>> layer;
    for(int i=0;i<N;i++){
        string str;fin>>str;
        auto tmp=string_pasing(str);
        layer.push_back(vector<double>());
        for(auto s:tmp)layer[i].push_back(stod(s));
    }
    return layer;
}

/*
ifsteam 형태로 scv 를 받아서
파싱해서
필터를 파싱
*/
auto read_filter_2D(ifstream &fin,int N,int M, int D=1){
    vector<vector<double>> filter;
    for(int i=0;i<N;i++){
        string str;fin>>str;
        auto tmp=string_pasing(str,M);
        filter.push_back(vector<double>());
        for(auto s:tmp)if(s!="")filter[i].push_back(stof(s));
    }
    return filter;
}

/*
ifsteam 형태로 scv 를 받아서
파싱해서
필터를 파싱
*/
auto read_filter_3D(ifstream &fin,int N,int M, int D=1){
    vector<vector<vector<double>>> filter;
    for(int d=0;d<D;d++){
        filter.push_back(vector<vector<double>>());
        for(int i=0;i<N;i++){
            string str;fin>>str;
            auto tmp=string_pasing(str);
            filter[d].push_back(vector<double>());
            for(auto s:tmp)filter[d][i].push_back(stod(s));
        }
    }
    return filter;
}

// //파싱
// // template <typename T1>
// auto string_pasing(string a) -> decltype(vector<string>) {
//     vector<string> data;
//     string in="";
//     for(int i=0;i<a.size();i++){
//         // if(a[i]==' ')continue;
//         if(a[i]==','){
//             data.push_back(in);
//             in="";
//         }
//         in+=a[i];
//     }
//     return data;
// }

// // 또는 C++11 이후의 트레일링 반환(Trailing return) 구문을 사용하여
// // 반환형을 더 유연하게 지정할 수도 있습니다.
// template <typename T1, typename T2>
// auto add_flexible(T1 a, T2 b) -> decltype(a + b) {
//     return a + b;
// }
