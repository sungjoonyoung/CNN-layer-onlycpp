#include<iostream>
#include<vector>
#include"..\equipment_header\sungso376_LA.hpp"
// #include"/equipment/sungso376_LA"
using namespace std;
int main(void){
    vector<double> v1(3,2);
    vector<double> v2(3,3);
    cout<<"\n\n\nA\n\n\n";
    cout<<inner_product(v1,v2)<<"\n";

    
}