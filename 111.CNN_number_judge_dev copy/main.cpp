#include<iostream>
#include<fstream>
#include<vector>
#include"sungso376_AF.hpp"
#include"sungso376_STR.hpp"
#include<sungso376_CNN.hpp>
#include"sungso376_LA.hpp"
#include<sungso376_image.hpp>
#include"conv.hpp"
using namespace std;
void print_1D(vector<double> &X){
    cout<<"\n";
    for(int j=0;j<X.size();j++){
        cout<<X[j]<<" ";
    }
    cout<<"\n--------------------\n";
}
void print_3D(vector<vector<vector<double>>> &X){
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
void print_2D(vector<vector<double>> &X){
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

int layer_number=3;//레이어가 몇 개? x = 1+hidden+1
int hidden_node_number[]={200};
int output_number=10; //아웃풋의 노드가 몇 개?


vector<vector<vector<double>>> weight_data;
vector<vector<vector<double>>> weight_tmp;
vector<vector<double>> coordinate_data;
vector<vector<double>> derivative_data;
int main(void){
    cout<<"\n";
    for(int i=0;;i++){
        weight_data.clear();
        coordinate_data.clear();

        weight_data.resize(layer_number); // initial(no wight) + hiden *2 + output
        coordinate_data.resize(layer_number);

        /*
        convolution
        */
        string image="table.bmp";
        
        coordinate_data[0]=conv_function(image);
        for(int i=0;i<layer_number-2;i++){
            coordinate_data[i+1].resize(hidden_node_number[i]);
        }
        coordinate_data[layer_number-1].resize(output_number);

        // for(int i=0;i<1;i++){
        //     for(int j=0;j<coordinate_data[i].size();j++)
        //         cout<<(int)(coordinate_data[i][j]*10000)<<" ";
        //     cout<<"\n";
        // }
        
        /*
        NN
        */
        
        //read csv -> weight_data
        for(int i=1;i<weight_data.size();i++){
            string w_csv ="weight_layer/weight ("+to_string(i)+").csv";
            ifstream fin(w_csv);
            weight_data[i]=read_filter_2D(fin,coordinate_data[i].size(),coordinate_data[i-1].size()+1);
            for(int j=0;j<coordinate_data[i].size();j++){
                while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.1*(rand()%6+2));//자동으로 채워주는 건데, 체크는 나중에 해 보자고~!
            }
        }

        //NN
        for(int i=1;i<weight_data.size();i++){
            coordinate_data[i]=NN_coordinate(coordinate_data[i-1],weight_data[i]);
            if(i==1){ // 히든은 렐루
                for(int j=0;j<coordinate_data[i].size();j++)coordinate_data[i][j]=ReLU(coordinate_data[i][j]);
            }
            else{ // 나머지는 시그모이드
                for(int j=0;j<coordinate_data[i].size();j++)coordinate_data[i][j]=sigmoid(coordinate_data[i][j]);
            }
        }


        int n=i%4;
        string roading="\\|/-";
        cout<<roading[n]<<"\n";
        double maxnum=-1;
        double maxind=-1;
        double sumnum=0;
        for(int j=0;j<100;j++)cout<<"\n";
        for(int j=0;j<10;j++){
            if(maxnum<coordinate_data.back()[j]){
                maxnum=coordinate_data.back()[j];
                maxind=j;
            }
            sumnum+=coordinate_data.back()[j];
        }
        cout<<"answer : "<<maxind<<"\n";
        for(int j=0;j<10;j++){
            cout<<j<<" : "<<percentage_bar(coordinate_data.back()[j]/sumnum,1)<<"\n";
        }

        for(int j=0;j<100'000'000;j++);
    }
    
}
