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
    // for(int i=0;i<20;i++){
    //     for(int j=0;j<20;j++){
    //         cout<<con_data[i][j].front()<<" ";
    //     }
    //     cout<<"\n";
    // }

    
    /*
    ## 1 ##
    */
    //conv
    con_tmp.clear();
    {
        ifstream fin("layer/y=x.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    }
    {
        ifstream fin("layer/y=-x.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    }
    {
        ifstream fin("layer/Xshape.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    }
    //activation function
    //paste
    con_data=con_tmp;
    

    for(int i=0;i<con_data[0].size();i++){
        for(int j=0;j<con_data[0].size();j++){
            cout<<(con_data[0][i][j]<con_data[1][i][j])<<" ";
        }
        cout<<"\n";
    }

    /*
    ## 2 ##
    */



    /*
    ## 2 ## pooling
    */



    vector<vector<double>> out;
    /*
    conv->NN
    */
    return out;
}
int main(void){
    for(int i=0;i<1;i++){
        /*
        convolution
        */
        string image="dataset/X/X("+to_string(i)+").bmp";
        vector<vector<double>> con_data=conv_function(image);
        
        cout<<image<<"\n";
        /*
        NN
        */

    }

}