#include<iostream>
#include<fstream>
#include<vector>
#include"sungso376_AF.hpp"
#include"sungso376_STR.hpp"
#include<sungso376_CNN.hpp>
#include"sungso376_LA.hpp"
#include<sungso376_image.hpp>
using namespace std;
void print_con(vector<vector<vector<double>>> X){
    for(int i=0;i<X.size();i++){
        for(int j=0;j<X[i].size();j++){
            for(int k=0;k<X[i][j].size();k++)
                cout<<(int)(X[i][j][k]*100)<<" ";
            cout<<"\n";
        }
        cout<<"--------------------\n";
    }
    cout<<"--------------------\n";
}
void print_2D(vector<vector<double>> X){
    cout<<"\n";
    for(int j=0;j<X.size();j++){
        for(int k=0;k<X[j].size();k++)
            cout<<(X[j][k]*100)<<" ";
        cout<<"\n";
    }
    cout<<"--------------------\n";
}
auto conv_function(string image){
    vector<vector<vector<double>>> con_data;
    vector<vector<vector<double>>> con_tmp;
    vector<vector<double>>filter_data;
    {
        ifstream fin(image, ios::binary);
        con_data.push_back(image_func(fin));        
    }
    print_con(con_data);
    /*
    ## 1 ##
    */
    //conv
    con_tmp.clear();
    {
        ifstream fin("layer/y=x0.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    }
    {
        ifstream fin("layer/y=-x0.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
        // print_2D(filter_data);
    }
    {
        ifstream fin("layer/Xshape0.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
        // print_con(con_tmp);
    }
    //activation function
    for(int i=0;i<con_tmp.size();i++){
        for(int j=0;j<con_tmp[i].size();j++){
            for(int k=0;k<con_tmp[i][j].size();k++)
                con_tmp[i][j][k]=ReLU(con_tmp[i][j][k]);
        }
    }
    //paste
    con_data=con_tmp;
    print_con(con_data);
    

    /*
    ## 2 ##
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
        con_tmp.push_back(convolution_2D(con_data[1],filter_data));
    }
    {
        ifstream fin("layer/Xshape.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[2],filter_data));
        // print_con(con_tmp);
    }
    //activation function
    for(int i=0;i<con_tmp.size();i++){
        for(int j=0;j<con_tmp[i].size();j++){
            for(int k=0;k<con_tmp[i][j].size();k++)
                con_tmp[i][j][k]=ReLU(con_tmp[i][j][k]);
        }
    }
    //paste
    con_data=con_tmp;
    print_con(con_data);
    

    /*
    ## 2.1 ## pooling
    */
    con_tmp.clear();
    {
        con_tmp.push_back(maxpulling_2D(con_data[0],3,3,3));
    }
    {
        con_tmp.push_back(maxpulling_2D(con_data[1],3,3,3));
    }
    {
        con_tmp.push_back(maxpulling_2D(con_data[2],3,3,3));
        // print_con(con_tmp);
    }
    //activation function

    //paste
    con_data=con_tmp;
    print_con(con_data);

    /*
    ## 3 ##
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
        con_tmp.push_back(convolution_2D(con_data[1],filter_data));
    }
    {
        ifstream fin("layer/Xshape.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[2],filter_data));
        // print_con(con_tmp);
    }
    //activation function
    for(int i=0;i<con_tmp.size();i++){
        for(int j=0;j<con_tmp[i].size();j++){
            for(int k=0;k<con_tmp[i][j].size();k++)
                con_tmp[i][j][k]=ReLU(con_tmp[i][j][k]);
        }
    }
    //paste
    con_data=con_tmp;
    print_con(con_data);


    /*
    ## 3.1 ## pooling
    */
    con_tmp.clear();
    {
        con_tmp.push_back(maxpulling_2D(con_data[0],2,2,2));
    }
    {
        con_tmp.push_back(maxpulling_2D(con_data[1],2,2,2));
    }
    {
        con_tmp.push_back(maxpulling_2D(con_data[2],2,2,2));
        // print_con(con_tmp);
    }
    //activation function

    //paste
    con_data=con_tmp;
    print_con(con_data);

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







int main(void){
    for(int op=1;op<2;op++){
        vector<vector<double>> coordinate_data;
        /*
        convolution
        */
        {
            string image="dataset/X/X ("+to_string(op)+").bmp";
            coordinate_data.push_back(conv_function(image));            
        }
        {
            string image="dataset/O/O ("+to_string(op)+").bmp";
            coordinate_data.push_back(conv_function(image));
        }
        
        for(int i=0;i<coordinate_data.size();i++){
            for(int j=0;j<coordinate_data[i].size();j++)
                cout<<(int)(coordinate_data[i][j]*10000)<<" ";
            cout<<"\n";
        }
        /*
        NN
        */
        
    }

}