#include <iostream>
#include <unistd.h>
#include <cstdint>
using namespace std;

int* foods;
int64_t* s;
int64_t* p;

int main(){
    int i;
    /* Read number of foods */
    int N;
    cin >> N;
    /* Read taste parameters */
    int a, b, c;
    cin >> a >> b >> c;
    /* Read taste parameters for each food */
    foods = new int[N];
    for(i = 0; i < N; i++){
        cin >> foods[i];
    }

    /* Compute partial sums of array foods */
    s = new int64_t[N+1];
    s[0] = 0;
    for(i = 1; i <= N; i++){
        s[i] = s[i-1] + foods[i-1];
    }


    p = new int64_t[N+1];
    p[0] = 0;
    p[1] = a * foods[0] * foods[0] + b * foods[0] + c;
    int j;
    int64_t val, max_p;
    for(i = 2; i <= N; i++){
        max_p = -922337203685477580-1;
        for(j=0; j<i; j++){
            val = p[j] + a*(s[i] - s[j])*(s[i] - s[j]) + b*(s[i] - s[j]) + c;
            if (val > max_p){
                max_p = val;
            }
        }
        p[i] = max_p;
    }
    cout << p[N] << endl;
}  
