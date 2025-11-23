#include<iostream>
#include<vector>
#include"..\equipment_header\sungso376_LA.hpp"
// #include"/equipment/sungso376_LA"
using namespace std;
int main(void){
    
    cout<<"\n\n\nA\n\n\n";

    vector<double> v1(3,2); //(2,2,2)
    vector<vector<double>> v2={
        {1,1,1},
        {1,0,1}
    };
    
    for(auto c:coordinate(v1,v2))cout<<c<<"\n";

    
}