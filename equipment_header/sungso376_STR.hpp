#include<iostream>
#include<vector>
using namespace std;

//파싱
// template <typename T1>
auto string_pasing(string a) {
    vector<string> data;
    string in="";
    for(int i=0;i<a.size();i++){
        if(a[i]==' ')continue;
        if(a[i]==','){
            data.push_back(in);
            in="";
        }
        else in+=a[i];
    }
    if(in!="")data.push_back(in);
    return data;
}

// //파싱
// // template <typename T1>
// auto string_pasing(string a) -> decltype(vector<string>) {
//     vector<string> data;
//     string in="";
//     for(int i=0;i<a.size();i++){
//         // if(a[i]==' ')continue;
//         if(a[i]==','){
//             data.push_back(in);
//             in="";
//         }
//         in+=a[i];
//     }
//     return data;
// }

// // 또는 C++11 이후의 트레일링 반환(Trailing return) 구문을 사용하여
// // 반환형을 더 유연하게 지정할 수도 있습니다.
// template <typename T1, typename T2>
// auto add_flexible(T1 a, T2 b) -> decltype(a + b) {
//     return a + b;
// }
