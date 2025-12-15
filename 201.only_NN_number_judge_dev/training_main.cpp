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
double learning_rate=0.01;
double seed_out=0.05;
double seed_hid=0.01;
int iteration_train=1'000'000'000;
int man=0;
double loss=0;
ofstream Lossfout("Loss.txt");

vector<vector<vector<double>>> weight_data;
vector<vector<vector<double>>> weight_tmp;
vector<vector<double>> coordinate_data;
vector<vector<double>> derivative_data;
void func(int op,int num);
int main(void){
    Lossfout.clear();
    cout<<"\n\n\nlearning rate? : ";cin>>learning_rate;
    Lossfout<<"learning rate : "<<learning_rate<<"\n";
    cout<<"iteration? : ";cin>>iteration_train;
    Lossfout<<"iteration_train : "<<iteration_train<<"\n";
    cout<<"seed_out? : ";cin>>seed_out;
    Lossfout<<"seed_out : "<<seed_out<<"\n";
    cout<<"seed_hid? : ";cin>>seed_hid;
    Lossfout<<"seed_hid : "<<seed_hid<<"\n";
    Lossfout.flush();
    coordinate_data.clear();
    derivative_data.clear();

    
    coordinate_data.resize(layer_number);
    derivative_data.resize(layer_number);

    /*
    convolution
    */
    string image="dataset/"+to_string(0)+"/k ("+to_string(0+1)+").bmp"; //아무거나
    // cout<<image<<"\n";
    
    coordinate_data[0]=conv_function(image);
    for(int i=0;i<layer_number-2;i++){
        coordinate_data[i+1].resize(hidden_node_number[i]);
    }
    coordinate_data[layer_number-1].resize(output_number);

    //read csv -> weight_data
    weight_data.resize(layer_number); // initial(no wight) + hiden *2 + output


    for(int i=1;i<weight_data.size();i++){
        string w_csv ="weight_layer/weight ("+to_string(i)+").csv";
        ifstream fin(w_csv);
        weight_data[i]=read_filter_2D(fin,coordinate_data[i].size(),coordinate_data[i-1].size()+1);
        for(int j=0;j<coordinate_data[i].size();j++){
            if(i==weight_data.size()-1){
                while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)
                    weight_data[i][j].push_back(seed_out*((rand()%2001 - 1000) / 1000.0));
            }
            else{
                while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)
                    weight_data[i][j].push_back(seed_hid*((rand()%2001 - 1000) / 1000.0));
            }
        }
    }



    for(int i=0;i<iteration_train;i++){
        Lossfout<<"iteration : "<<i<<"\n";
        Lossfout.flush();
        vector<int> cnt(10,0);
        vector<int> max_cnt(10,480);
        man=10*480;
        while(man){
            int op=rand()%10;
            if(cnt[op]==max_cnt[op])continue;
            func(op,cnt[op]);
            cnt[op]++;
            
            for(int j=0;j<50;j++)cout<<endl; //for window
            cout<<"\r                                                                                              ";
            cout<<"\riteration : "<<i<<"\n";
            for(int j=0;j<10;j++){
                cout<<"\r"<<j<<" : "<<progress_bar(cnt[j],max_cnt[j])<<"\n";
            }
            // for(int j=0;j<11;j++){ //for rinux like terminal
            //     cout<<"\x1b[1A";
            // }
            man--;
        }
        cout<<"\x1b[1A";
    }
    cout<<loss;
}

void func(int op,int num){
    // weight_data.clear();
    // weight_tmp.clear();
    coordinate_data.clear();
    derivative_data.clear();

    
    coordinate_data.resize(layer_number);
    derivative_data.resize(layer_number);
    vector<double> correct_output(10,0);
    correct_output[op]=1;

    /*
    convolution
    */
    string image="dataset/"+to_string(op)+"/k ("+to_string(num+1)+").bmp";
    // cout<<image<<"\n";
    
    coordinate_data[0]=conv_function(image);
    for(int i=0;i<layer_number-2;i++){
        coordinate_data[i+1].resize(hidden_node_number[i]);
    }
    coordinate_data[layer_number-1].resize(output_number);
    // print_1D(coordinate_data[0]);
    // cout<<"numbers of first layer"<<coordinate_data[0].size()<<"\n";

    // for(int i=0;i<1;i++){
    //     for(int j=0;j<coordinate_data[i].size();j++)
    //         cout<<(int)(coordinate_data[i][j]*10000)<<" ";
    //     cout<<"\n";
    // }
    
    /*
    NN
    */
    
    

    //NN
    for(int i=1;i<weight_data.size();i++){
        coordinate_data[i]=NN_coordinate(coordinate_data[i-1],weight_data[i]);
        if(i==1){ // 히든은 렐루
            for(int j=0;j<coordinate_data[i].size();j++)coordinate_data[i][j]=ReLU(coordinate_data[i][j]);
        }
        else{ // 나머지는 시그모이드
            // for(int j=0;j<coordinate_data[i].size();j++)coordinate_data[i][j]=sigmoid(coordinate_data[i][j]);
            continue;
        }
    }
    
    //softmax
    vector<double> sftmax_vector=sotfmax(coordinate_data.back());
    // print_1D(sftmax_vector);

    /*
    backpropagation
    */
    for(int i=0;i<derivative_data.size();i++){
        derivative_data[i].clear();
        derivative_data[i].resize(coordinate_data[i].size(),0.0);
    }
    //output layer's derivative sum
    for(int i=0;i<correct_output.size();i++){
        derivative_data.back()[i]=correct_output[i]-sftmax_vector[i];
    }
    //derivative sum
    for(int i=derivative_data.size()-1;i>=0;i--){
        // 현재 도착했을 때는 h(1-h) 를 해주고 -> derivative sum 완성!
        for(int j=0;j<derivative_data[i].size();j++){
            double x=coordinate_data[i][j];
            if(i==1){ // 히든은 렐루
                derivative_data[i][j]*=derivative_ReLU(x);
            }
            else{ // 출력은 스킵 continue문은 나중에 해 보자고.
                continue;
                // derivative_data[i][j]*=derivative_sigmoid(x);
            }
        }
        // 그리고 뒤로 쏴주자
        if(i==0)break;
        for(int j=0;j<derivative_data[i].size();j++){
            double delta=derivative_data[i][j];
            for(int k=1;k<weight_data[i][j].size();k++){ //skip bias delta (dont need, but 나중에 update 해야해 ㅠㅠ)
                double w=weight_data[i][j][k];
                derivative_data[i-1][k-1]+=w*delta;
            }
        }
    }
    // print_1D(derivative_data.back());
    // print_2D(derivative_data);
    // weight update
    for(int i=weight_data.size()-1;i>0;i--){
        for(int j=0;j<weight_data[i].size();j++){
            double delta=derivative_data[i][j];
            for(int k=0;k<weight_data[i][j].size();k++){
                if(k==0){//bias
                    weight_data[i][j][k]+=learning_rate*delta;
                }
                else{
                    weight_data[i][j][k]+=learning_rate*delta*coordinate_data[i-1][k-1];
                }
            }
        }
    }
    // print_3D(weight_data);

    //scv<=weight_tmp
    if(man%1000==0){
        for(int i=1;i<weight_data.size();i++){
            string w_csv ="weight_layer/weight ("+to_string(i)+").csv";
            ofstream fout(w_csv);
            for(int j=0;j<weight_data[i].size();j++){
                fout<<data_to_string(weight_data[i][j])<<"\n";
            }
        }
    }
    //loss
    loss=0;
    if(man%20==0){
        for(int i=0;i<10;i++)loss+=0.5*(correct_output[i]-sftmax_vector[i])*(correct_output[i]-sftmax_vector[i]);
        Lossfout<<"Loss : "<<loss<<"\n";
        Lossfout.flush();
    }
}