#include<iostream>
#include<sungso376_STR.hpp>
using namespace std;
int main(void){
    int tmp=0;
    for(int i=0;i<15;i++){
        for(int k=0;k<1'000'000'000;k++)tmp++;
        cout<<progress_bar(15,i)<<"\r";
    }
}