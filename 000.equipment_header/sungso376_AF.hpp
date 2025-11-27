/*
header for activate function
*/

#include<iostream>
#include<vector>
#include<sungso376_LA.hpp>
using namespace std;

//sigmod
template <typename T1>
auto sigmoid(T1 x){
    double tmp=exp(x);
    tmp/=exp(x)+1;
    return tmp;
}

template <typename T1>
auto ReLU(T1 x)->decltype(x){
    return max(x,(T1)0);
}
// // 또는 C++11 이후의 트레일링 반환(Trailing return) 구문을 사용하여
// // 반환형을 더 유연하게 지정할 수도 있습니다.
// template <typename T1, typename T2>
// auto add_flexible(T1 a, T2 b) -> decltype(a + b) {
//     return a + b;
// }
