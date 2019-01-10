/* Include necessary libraries */
#include <iostream>
#include <unistd.h>
#include <cstdint>
#include <vector>
using namespace std;

/* Τaste parameter of each food */
int* foods;
/* Partial sum of the array foods */
int64_t* s;
/* Maximum total taste for i foods */
int64_t* p;
/* A line is represented by a slope 'lamda' and a bias 'b' as y = lamda*x + b */
struct line{
    int64_t lamda;
    int64_t b;
};
/* A vector containg the current lines (will be used in conver hull trick) */
vector<line> lines;
int len;
int ptr;

int64_t query(int64_t x){
    ptr = min(ptr, len-1);
    while(ptr + 1 < len && lines[ptr+1].lamda * x + lines[ptr+1].b >= lines[ptr].lamda * x + lines[ptr].b)
        ++ptr;
    return lines[ptr].lamda * x + lines[ptr].b;
}

bool bad(line l1, line l2, line l3){
    return (l3.b - l1.b) * (l1.lamda - l2.lamda) < (l2.b - l1.b) * (l1.lamda - l3.lamda);
}


void add(line x){
    while(len >= 2 && bad(lines[len-2], lines[len-1], x))
        --len;
    lines[len++] = x;
}

int main(){
    int i;
    int N;
    /* Read number of foods */
    cin >> N;
    /* Initialize the vector with the lines */
    line tmp;
    tmp.lamda = 0;
    tmp.b = 0;
    lines.assign(N, tmp);
    /* Read taste parameters */
    int a, b, c;
    cin >> a >> b >> c;
    /* Read taste parameters for each food */
    foods = new int[N];
    for(i = 0; i < N; i++){
        cin >> foods[i];
    }
    len = 0;
    ptr = 0;
    /* Compute partial sums of array foods */
    s = new int64_t[N+1];
    s[0] = 0;
    for(i = 1; i <= N; i++){
        s[i] = s[i-1] + foods[i-1];
    }
    /* Initialize array p */
    p = new int64_t[N+1];
    p[0] = 0;
    p[1] = a * foods[0] * foods[0] + b * foods[0] + c;
    line cur_line;
    cur_line.lamda = -2 * a * s[1];
    cur_line.b = p[1] + a * s[1] * s[1] - b * s[1];
    add(cur_line);
    int64_t val;
    for(i = 2; i <= N; i++){
        val = a*s[i]*s[i] + b*s[i] + c;
        p[i] = max(val, val + query(s[i]));
        line cur_line;
        cur_line.lamda = -2 * a * s[i];
        cur_line.b = p[i] + a * s[i] * s[i] - b * s[i];
        add(cur_line);
    }
    cout << p[N] << endl;
}
