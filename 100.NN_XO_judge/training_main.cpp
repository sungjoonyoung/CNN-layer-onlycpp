#include<iostream>
#include<fstream>
#include<vector>
#include"sungso376_AF.hpp"
#include"sungso376_STR.hpp"
#include<sungso376_CNN.hpp>
#include"sungso376_LA.hpp"
#include<sungso376_image.hpp>
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
vector<vector<double>> derivative_data;
double learning_rate=0.9;
int main(void){
    cout<<"\n";
    int Onum,Xnum;
    Xnum=3;
    Onum=3;
    /*
    X
    */
    for(int op=1;op<=Xnum;op++){
        weight_data.clear();
        weight_tmp.clear();
        coordinate_data.clear();
        derivative_data.clear();

        weight_data.resize(4); // initial(no wight) + hiden *2 + output
        coordinate_data.resize(4);
        derivative_data.resize(4);
        vector<double> correct_output={1,0};

        /*
        convolution
        */
        string image="dataset/X/X ("+to_string(op)+").bmp";
        
        coordinate_data[0]=conv_function(image);
        coordinate_data[1].resize(24); //numbers of nodes
        coordinate_data[2].resize(24);
        coordinate_data[3].resize(2);

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
            string w_csv ="weight_layer/weight ("+to_string(i)+").csv";
            ifstream fin(w_csv);
            weight_data[i]=read_filter_2D(fin,coordinate_data[i].size(),coordinate_data[i-1].size()+1);
            for(int j=0;j<coordinate_data[i].size();j++){
                while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.1*(rand()%6+2));//자동으로 채워주는 건데, 체크는 나중에 해 보자고~!
            }
        }
        weight_tmp=weight_data;

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
        cout<<"X : "<<progress_bar(op,Xnum)<<"\r";
    }


    /*
    O
    */
    for(int op=1;op<=Onum;op++){
        weight_data.clear();
        weight_tmp.clear();
        coordinate_data.clear();
        derivative_data.clear();

        weight_data.resize(4); // initial(no wight) + hiden *2 + output
        coordinate_data.resize(4);
        derivative_data.resize(4);
        vector<double> correct_output={0,1};

        /*
        convolution
        */
        string image="dataset/O/O ("+to_string(op)+").bmp";
        
        coordinate_data[0]=conv_function(image);
        coordinate_data[1].resize(24); //numbers of nodes
        coordinate_data[2].resize(24);
        coordinate_data[3].resize(2);

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
            string w_csv ="weight_layer/weight ("+to_string(i)+").csv";
            ifstream fin(w_csv);
            weight_data[i]=read_filter_2D(fin,coordinate_data[i].size(),coordinate_data[i-1].size()+1);
            for(int j=0;j<coordinate_data[i].size();j++){
                while(weight_data[i][j].size()!=coordinate_data[i-1].size()+1)weight_data[i][j].push_back(0.1*(rand()%6+2));//자동으로 채워주는 건데, 체크는 나중에 해 보자고~!
            }
        }
        weight_tmp=weight_data;

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
        cout<<"O : "<<progress_bar(i,Onum)<<"\r";
    }
}