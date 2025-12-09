#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<sungso376_LA.hpp>
using namespace std;
/*
X matrix, filter matrix, stride (default=1)
-> 3d vector matrix
*/
template <typename T1, typename T2>
auto convolution_3D(vector<vector<vector<T1>>> &X, vector<vector<vector<T2>>> &filter,int stride=1)
->vector<vector<decltype(X[0][0][0]*filter[0][0][0])>>
{
    using ResultType = decltype(X[0][0][0]*filter[0][0][0]);
    vector<vector<ResultType>> answer;
    for(int i=0;i+filter.size()-1<X.size();i+=stride){
        answer.push_back(vector<ResultType>());
        for(int j=0;j+filter[0].size()-1<X[i].size();j+=stride){
            ResultType tmp=0;
            int N=0;
            for(int ii=0;ii<filter.size();ii++)for(int jj=0;jj<filter[ii].size();jj++){
                for(int d=0;d<filter[0][0].size();d++){
                    tmp+=X[i+ii][j+jj][d]*filter[ii][jj][d];
                    N++;
                }
            }
            answer[i/stride].push_back(tmp/N);
        }
    }
    return answer;
}

/*
X matrix, filter matrix, stride (default=1)
-> 2d vector matrix
*/
template <typename T1, typename T2>
auto convolution_2D(vector<vector<T1>> &X, vector<vector<T2>> &filter,int stride=1)
->vector<vector<decltype(X[0][0]*filter[0][0])>>
{
    using ResultType = decltype(X[0][0]*filter[0][0]);
    vector<vector<ResultType>> answer;
    for(int i=0;i+filter.size()-1<X.size();i+=stride){
        answer.push_back(vector<ResultType>());
        for(int j=0;j+filter[0].size()-1<X[i].size();j+=stride){
            ResultType tmp=0;
            int N=0;
            for(int ii=0;ii<filter.size();ii++)for(int jj=0;jj<filter[ii].size();jj++){
                tmp+=X[i+ii][j+jj]*filter[ii][jj];
                N++;
            }
            answer[i/stride].push_back(tmp/N);
        }
    }
    // cout<<X.size()<<"A"<<X[0].size()<<"A";
    return answer;
}
