#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"sungso376_AF.hpp"
#include"sungso376_STR.hpp"
#include<sungso376_CNN.hpp>
#include"sungso376_LA.hpp"
#include<sungso376_image.hpp>
using namespace std;

auto conv_function(string image){
    vector<vector<vector<double>>> con_data;
    vector<vector<vector<double>>> con_tmp;
    vector<vector<double>>filter_data;
    {
        ifstream fin(image, ios::binary);
        con_data.push_back(image_func(fin));        
    }
    // // print_3D(con_data);
    // /*
    // ## 1 ##
    // */
    // //conv
    // con_tmp.clear();
    // {
    //     ifstream fin("filter_layer/1-1.csv");
    //     filter_data=read_filter_2D(fin,3,3);
    //     con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    // }
    // {
    //     ifstream fin("filter_layer/1-2.csv");
    //     filter_data=read_filter_2D(fin,3,3);
    //     con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    //     // print_2D(filter_data);
    // }
    // {
    //     ifstream fin("filter_layer/1-3.csv");
    //     filter_data=read_filter_2D(fin,3,3);
    //     con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    //     // print_3D(con_tmp);
    // }
    // {
    //     ifstream fin("filter_layer/1-4.csv");
    //     filter_data=read_filter_2D(fin,3,3);
    //     con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    //     // print_3D(con_tmp);
    // }
    // {
    //     ifstream fin("filter_layer/1-5.csv");
    //     filter_data=read_filter_2D(fin,3,3);
    //     con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    //     // print_3D(con_tmp);
    // }
    // //activation function
    // for(int i=0;i<con_tmp.size();i++){
    //     for(int j=0;j<con_tmp[i].size();j++){
    //         for(int k=0;k<con_tmp[i][j].size();k++)
    //             con_tmp[i][j][k]=ReLU(con_tmp[i][j][k]);
    //     }
    // }
    // //paste
    // con_data=con_tmp;
    // // print_3D(con_data);
    

    // // /*
    // // ## 2 ##
    // // */
    // // //conv
    // // con_tmp.clear();
    // // {
    // //     ifstream fin("filter_layer/y=x0.csv");
    // //     filter_data=read_filter_2D(fin,3,3);
    // //     con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    // // }
    // // {
    // //     ifstream fin("filter_layer/y=-x0.csv");
    // //     filter_data=read_filter_2D(fin,3,3);
    // //     con_tmp.push_back(convolution_2D(con_data[1],filter_data));
    // //     // print_2D(filter_data);
    // // }
    // // {
    // //     ifstream fin("filter_layer/x0.csv");
    // //     filter_data=read_filter_2D(fin,3,3);
    // //     con_tmp.push_back(convolution_2D(con_data[2],filter_data));
    // //     // print_3D(con_tmp);
    // // }
    // // {
    // //     ifstream fin("filter_layer/y0.csv");
    // //     filter_data=read_filter_2D(fin,3,3);
    // //     con_tmp.push_back(convolution_2D(con_data[3],filter_data));
    // //     // print_3D(con_tmp);
    // // }
    // // //activation function
    // // for(int i=0;i<con_tmp.size();i++){
    // //     for(int j=0;j<con_tmp[i].size();j++){
    // //         for(int k=0;k<con_tmp[i][j].size();k++)
    // //             con_tmp[i][j][k]=ReLU(con_tmp[i][j][k]);
    // //     }
    // // }
    // // //paste
    // // con_data=con_tmp;
    // // // print_3D(con_data);
    

    // /*
    // ## 2.1 ## pooling
    // */
    // con_tmp.clear();
    // for(int i=0;i<con_data.size();i++){
    //     con_tmp.push_back(maxpulling_2D(con_data[i],2,2,2));
    // }
    // //activation function

    // //paste
    // con_data=con_tmp;

    // // /*
    // // ## 3 ##
    // // */
    // // //conv
    // // con_tmp.clear();
    // // {
    // //     ifstream fin("filter_layer/y=x0.csv");
    // //     filter_data=read_filter_2D(fin,3,3);
    // //     con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    // // }
    // // {
    // //     ifstream fin("filter_layer/y=-x0.csv");
    // //     filter_data=read_filter_2D(fin,3,3);
    // //     con_tmp.push_back(convolution_2D(con_data[1],filter_data));
    // //     // print_2D(filter_data);
    // // }
    // // {
    // //     ifstream fin("filter_layer/x0.csv");
    // //     filter_data=read_filter_2D(fin,3,3);
    // //     con_tmp.push_back(convolution_2D(con_data[2],filter_data));
    // //     // print_3D(con_tmp);
    // // }
    // // {
    // //     ifstream fin("filter_layer/y0.csv");
    // //     filter_data=read_filter_2D(fin,3,3);
    // //     con_tmp.push_back(convolution_2D(con_data[3],filter_data));
    // //     // print_3D(con_tmp);
    // // }
    // // //activation function
    // // for(int i=0;i<con_tmp.size();i++){
    // //     for(int j=0;j<con_tmp[i].size();j++){
    // //         for(int k=0;k<con_tmp[i][j].size();k++)
    // //             con_tmp[i][j][k]=ReLU(con_tmp[i][j][k]);
    // //     }
    // // }
    // // //paste
    // // con_data=con_tmp;


    // // /*
    // // ## 3.1 ## pooling
    // // */
    // // con_tmp.clear();
    // // for(int i=0;i<con_data.size();i++){
    // //     con_tmp.push_back(maxpulling_2D(con_data[i],2,2,2));
    // // }
    // // //activation function

    // // //paste
    // // con_data=con_tmp;

    /*
    Final
    */
    vector<double> out;
    /*
    conv->NN
    */
    for(int i=0;i<con_data.size();i++){
        for(int j=0;j<con_data[i].size();j++){
            for(int k=0;k<con_data[i][j].size();k++)
                out.push_back(con_data[i][j][k]);
        }
    }
    return out;
}