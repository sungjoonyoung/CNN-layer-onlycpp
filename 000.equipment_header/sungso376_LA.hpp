/*
Linear Algebra + some math

inner product
coordinate
exponential
*/

#include<iostream>
#include<vector>
using namespace std;

//inner product
template <typename T1, typename T2>
auto inner_product(vector<T1>& a, vector<T2>& b) -> decltype(a[0] * b[0]){
    if(a.size()!=b.size()){
        cout<<"\n%%%%inner product에서 백터 사이드 다름%%%%\n\n";
        return 0;
        // if(a.size()!=b.size())return NULL; 뭐 그냥 귀찮아 나중에 해
    }

    using ResultType = decltype(a[0] * b[0]);
    ResultType norm = 0;

    for(int i=0;i<a.size();i++){
        norm+=a[i]*b[i];
    }
    return norm;
}

//coordinate
template <typename T1, typename T2>
auto coordinate(vector<T1>& a, vector<vector<T2>>& basis)->vector<decltype(a[0]*basis[0][0])>{ // 디클레어 이거 맞나? 몰라

    using ResultType = vector<decltype(a[0]*basis[0][0])>;
    ResultType answer;
    using ElementType = decltype(a[0]*basis[0][0]);
    for(int i=0;i<basis.size();i++){
        ElementType tmp;
        tmp=inner_product(a,basis[i]);
        answer.push_back(tmp);
    }
    return answer;
}

/*
NN-coordinate just vector&basis
dont need to add the 1 <- 이게 그 일부러 넣는 그 1그게 뭐였지 여하튼 그거
여하튼 자동으로 1을 앞에 넣어서 계산해 줍니다.
*/
template <typename T1, typename T2>
auto NN_coordinate(vector<T1>& a, vector<vector<T2>>& basis)->vector<decltype(a[0]*basis[0][0])>{ // 디클레어 이거 맞나? 몰라

    using ResultType = vector<decltype(a[0]*basis[0][0])>;
    ResultType answer;
    using ElementType = decltype(a[0]*basis[0][0]);

    vector<T1> before;
    before.push_back(1);
    before.insert(before.end(),a.begin(),a.end());

    for(int i=0;i<basis.size();i++){
        ElementType tmp;
        tmp=inner_product(before,basis[i]);
        answer.push_back(tmp);
    }
    return answer;
}

//익스뽀낸셜! 근데 10까지만 근사.
template <typename T1>
double exp(T1 e){
    //m/n
    double m=1;
    double n=1;
    double answer=1;
    for(int i=1;i<10;i++){
        m*=e;
        n*=i;
        answer+=m/n;
    }
    return answer;
}

// // 또는 C++11 이후의 트레일링 반환(Trailing return) 구문을 사용하여
// // 반환형을 더 유연하게 지정할 수도 있습니다.
// template <typename T1, typename T2>
// auto add_flexible(T1 a, T2 b) -> decltype(a + b) {
//     return a + b;
// }
