#pragma once
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;


/*
X matrix, filter matrix, stride (default=1)
-> 2d vector matrix
*/
template <typename T1>
void print_1D(vector<T1> &X){
    cout<<"\n";
    for(int j=0;j<X.size();j++){
        cout<<X[j]<<" ";
    }
    cout<<"\n--------------------\n";
}

template <typename T1>
void print_3D(vector<vector<vector<T1>>> &X){
    for(int i=0;i<X.size();i++){
        cout<<"["<<i<<"]-----------\n";
        for(int j=0;j<X[i].size();j++){
            for(int k=0;k<X[i][j].size();k++){
                // cout<<"0.";
                // cout<<(int)(X[i][j][k]*100)<<" ";
                cout<<X[i][j][k]<<" ";
            }
            cout<<"\n";
        }
    }
    cout<<"--------------------\n";
}

template <typename T1>
void print_2D(vector<vector<T1>> &X){
    cout<<"\n";
    for(int j=0;j<X.size();j++){
        for(int k=0;k<X[j].size();k++){
            // cout<<"0.";
            // cout<<(X[j][k]*100)<<" ";
            cout<<X[j][k]<<" ";
        }
        cout<<"\n";
    }
    cout<<"--------------------\n";
}