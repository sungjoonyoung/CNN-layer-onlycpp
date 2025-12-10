#include<iostream>
#include<fstream>
#include<vector>
#include"sungso376_AF.hpp"
#include"sungso376_STR.hpp"
#include<sungso376_CNN.hpp>
#include"sungso376_LA.hpp"
#include<sungso376_image.hpp>
using namespace std;
void print_3D(vector<vector<vector<double>>> X){
    for(int i=0;i<X.size();i++){
        cout<<"["<<i<<"]-----------\n";
        for(int j=0;j<X[i].size();j++){
            for(int k=0;k<X[i][j].size();k++){
                cout<<"0.";
                cout<<(int)(X[i][j][k]*100)<<" ";
            }
            cout<<"\n";
        }
    }
    cout<<"--------------------\n";
}
void print_2D(vector<vector<double>> X){
    cout<<"\n";
    for(int j=0;j<X.size();j++){
        for(int k=0;k<X[j].size();k++){
            cout<<"0.";
            cout<<(X[j][k]*100)<<" ";
        }
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
    // print_3D(con_data);
    /*
    ## 1 ##
    */
    //conv
    con_tmp.clear();
    {
        ifstream fin("filter_layer/y=x0.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    }
    {
        ifstream fin("filter_layer/y=-x0.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
        // print_2D(filter_data);
    }
    {
        ifstream fin("filter_layer/Xshape0.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
        // print_3D(con_tmp);
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
    // print_3D(con_data);
    

    /*
    ## 2 ##
    */
    //conv
    con_tmp.clear();
    {
        ifstream fin("filter_layer/y=x.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    }
    {
        ifstream fin("filter_layer/y=-x.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[1],filter_data));
    }
    {
        ifstream fin("filter_layer/Xshape.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[2],filter_data));
        // print_3D(con_tmp);
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
    // print_3D(con_data);
    

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
        // print_3D(con_tmp);
    }
    //activation function

    //paste
    con_data=con_tmp;
    // print_3D(con_data);

    /*
    ## 3 ##
    */
    //conv
    con_tmp.clear();
    {
        ifstream fin("filter_layer/y=x.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[0],filter_data));
    }
    {
        ifstream fin("filter_layer/y=-x.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[1],filter_data));
    }
    {
        ifstream fin("filter_layer/Xshape.csv");
        filter_data=read_filter_2D(fin,3,3);
        con_tmp.push_back(convolution_2D(con_data[2],filter_data));
        // print_3D(con_tmp);
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
    // print_3D(con_data);


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
        // print_3D(con_tmp);
    }
    //activation function

    //paste
    con_data=con_tmp;
    // print_3D(con_data);

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




vector<vector<vector<double>>> weight_data;
vector<vector<vector<double>>> weight_tmp;
vector<vector<double>> coordinate_data;
int main(void){
    cout<<"\n";
    double learning_rate=0.1;
    /*
    X
    */
    for(int op=1;op<=3;op++){
        weight_data.clear();
        weight_tmp.clear();
        coordinate_data.clear();

        weight_data.resize(4); // initial(no wight) + hiden *2 + output
        coordinate_data.resize(4);

        /*
        convolution
        */
        string image="dataset/X/X ("+to_string(op)+").bmp";
        
        coordinate_data[0]=conv_function(image);
        coordinate_data[1].resize(24); //numbers of nodes
        coordinate_data[2].resize(24);
        coordinate_data[3].resize(2);
        coordinate_data[3]={1,0};

        for(int i=0;i<1;i++){
            for(int j=0;j<coordinate_data[i].size();j++)
                cout<<(int)(coordinate_data[i][j]*10000)<<" ";
            cout<<"\n";
        }
        
        /*
        NN
        */
        
        //read csv -> weight_data
        for(int i=1;i<weight_data.size();i++){
            string w_csv ="weight_layer/weight ("+to_string(op)+").csv";
            ifstream fin(w_csv);
            weight_data[i]=read_filter_2D(fin,coordinate_data[i].size(),coordinate_data[i-1].size()+1);
        }
        weight_tmp=weight_data;
        
        //NN

        
        //backpropagation -> weight_tmp

        //scv<=weight_tmp

    }


    /*
    O
    */
    for(int op=1;op<=3;op++){
        vector<vector<double>> coordinate_data;
        /*
        convolution
        */
        string image="dataset/O/O ("+to_string(op)+").bmp";
        coordinate_data.push_back(conv_function(image));
        
        for(int i=0;i<1;i++){
            for(int j=0;j<coordinate_data[i].size();j++)
                cout<<(int)(coordinate_data[i][j]*10000)<<" ";
            cout<<"\n";
        }
        /*
        NN
        */
        
    }

}