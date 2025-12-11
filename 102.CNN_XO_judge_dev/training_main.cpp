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

int layer_number=3;
int hidden_node_number[]={30,30,24};
int output_number=2;
double learning_rate=0.01;


vector<vector<vector<double>>> weight_data;
vector<vector<vector<double>>> weight_tmp;
vector<vector<double>> coordinate_data;
vector<vector<double>> derivative_data;
int Onum,Xnum;
void Ofunc(int op);
void Xfunc(int op);
int main(void){
    cout<<"\n";
    Xnum=720;
    Onum=720;
    for(int i=0;i<1;i++){
        cout<<"iteration : "<<i<<"\n";
        int Xind=1;
        int Oind=1;
        while(Xind<=Xnum and Oind<=Xnum){
            if(Xind==Xnum and Oind==Xnum)break;
            int r=rand()%2;
            if(r){//X
                if(Xind==Xnum)Ofunc(Oind++);
                else Xfunc(Xind++);
            }
            else{//O
                if(Oind==Onum)Xfunc(Xind++);
                else Ofunc(Oind++);
            }
            cout<<"X : "<<progress_bar(Xind,Onum)<<"\n";
            cout<<"O : "<<progress_bar(Oind,Onum)<<"\n";
            cout<<"\x1b[1A";
            cout<<"\x1b[1A";
        }
        cout<<"\x1b[1A";
    }
    
}

void Ofunc(int op){
    /*
    O
    */
    // for(int op=1;op<=Onum;op++){
        weight_data.clear();
        weight_tmp.clear();
        coordinate_data.clear();
        derivative_data.clear();

        weight_data.resize(layer_number); // initial(no wight) + hiden *2 + output
        coordinate_data.resize(layer_number);
        derivative_data.resize(layer_number);
        vector<double> correct_output={0,1};

        /*
        convolution
        */
        string image="dataset/O/O ("+to_string(op)+").bmp";
        
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
                if(i==weight_data.size()-1){
                    while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.0004+0.01*(rand()%10));
                }
                else if(i==weight_data.size()-2){
                    while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.00001*(rand()%10));
                }
                else{
                    while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.00000001*(rand()%10));
                }
            }
        }


        //NN
        for(int i=1;i<weight_data.size();i++){
            coordinate_data[i]=NN_coordinate(coordinate_data[i-1],weight_data[i]);
            for(int j=0;j<coordinate_data[i].size();j++)coordinate_data[i][j]=sigmoid(coordinate_data[i][j]);
        }
        // print_1D(coordinate_data.back());
        

        /*
        backpropagation
        */
        for(int i=0;i<derivative_data.size();i++)derivative_data[i].resize(coordinate_data[i].size());
        //output layer's derivative sum
        for(int i=0;i<correct_output.size();i++){
            derivative_data.back()[i]=correct_output[i]-coordinate_data.back()[i];
        }
        //derivative sum
        for(int i=derivative_data.size()-1;i>=0;i--){
            // 현재 도착했을 때는 h(1-h) 를 해주고 -> derivative sum 완성!
            for(int j=0;j<derivative_data[i].size();j++){
                double x=coordinate_data[i][j];
                derivative_data[i][j]*=x*(1-x);
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
        for(int i=1;i<weight_data.size();i++){
            string w_csv ="weight_layer/weight ("+to_string(i)+").csv";
            ofstream fout(w_csv);
            for(int j=0;j<weight_data[i].size();j++){
                fout<<data_to_string(weight_data[i][j])<<"\n";
            }
        }
        // print_1D(coordinate_data.back());
    // }
}
void Xfunc(int op){
    /*
    X
    */
    // for(int op=1;op<=Xnum;op++){
        weight_data.clear();
        weight_tmp.clear();
        coordinate_data.clear();
        derivative_data.clear();

        weight_data.resize(layer_number); // initial(no wight) + hiden *2 + output
        coordinate_data.resize(layer_number);
        derivative_data.resize(layer_number);
        vector<double> correct_output={1,0};

        /*
        convolution
        */
        string image="dataset/X/X ("+to_string(op)+").bmp";
        
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
                if(i==weight_data.size()-1){
                    while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.0004+0.01*(rand()%10));
                }
                else if(i==weight_data.size()-2){
                    while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.00001*(rand()%10));
                }
                else{
                    while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.00000001*(rand()%10));
                }
            }
        }

        //NN
        for(int i=1;i<weight_data.size();i++){
            coordinate_data[i]=NN_coordinate(coordinate_data[i-1],weight_data[i]);
            for(int j=0;j<coordinate_data[i].size();j++)coordinate_data[i][j]=sigmoid(coordinate_data[i][j]);
        }
        // print_1D(coordinate_data.back());
        

        /*
        backpropagation
        */
        for(int i=0;i<derivative_data.size();i++)derivative_data[i].resize(coordinate_data[i].size());
        //output layer's derivative sum
        for(int i=0;i<correct_output.size();i++){
            derivative_data.back()[i]=correct_output[i]-coordinate_data.back()[i];
        }
        //derivative sum
        for(int i=derivative_data.size()-1;i>=0;i--){
            // 현재 도착했을 때는 h(1-h) 를 해주고 -> derivative sum 완성!
            for(int j=0;j<derivative_data[i].size();j++){
                double x=coordinate_data[i][j];
                derivative_data[i][j]*=x*(1-x);
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
        for(int i=1;i<weight_data.size();i++){
            string w_csv ="weight_layer/weight ("+to_string(i)+").csv";
            ofstream fout(w_csv);
            for(int j=0;j<weight_data[i].size();j++){
                fout<<data_to_string(weight_data[i][j])<<"\n";
            }
        }
        // print_1D(coordinate_data.back());
    // }
}