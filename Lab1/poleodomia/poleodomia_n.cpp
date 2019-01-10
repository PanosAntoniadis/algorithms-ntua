#include <iostream>
#include <cstdint>
#include <stack>
#include <bits/stdc++.h>
using namespace std;

uint64_t* H;

int* prevGreater(uint64_t* arr, int N){
    int* prev;
    prev = new int[N];
    // Create a stack and push index of first element to it
    stack<uint64_t> s;
    stack<int> index;
    s.push(arr[0]);
    index.push(0);
    // Previous greater for first element is always 0 cause there isn't one.
    prev[0] = -1;
    // Traverse remaining elements
    for (int i = 1; i < N; i++) {
        // Pop elements from stack while stack is not empty and top of stack is
        // smaller than arr[i]. We always have elements in decreasing order in a
        // stack.
        while (s.empty() == false && s.top() <= arr[i]){
            s.pop();
            index.pop();
        }
        // If stack becomes empty, then no element is greater
        // on left side. Else top of stack is previous
        // greater.
        if(s.empty()){
            prev[i] = i;
        }
        else{
            prev[i] = index.top();
        }
        s.push(arr[i]);
        index.push(i);
    }
    return prev;
}

int* nextGreater(uint64_t* arr, int N){
    int* next;
    next = new int[N];
    // Create a stack and push index of first element to it
    stack<uint64_t> s;
    stack<int> index;
    s.push(arr[N-1]);
    index.push(N-1);
    // Previous greater for first element is always 0 cause there isn't one.
    next[N-1] = -1;
    // Traverse remaining elements
    for (int i = N-2; i >= 0; i--) {
        // Pop elements from stack while stack is not empty and top of stack is
        // smaller than arr[i]. We always have elements in decreasing order in a
        // stack.
        while (s.empty() == false && s.top() <= arr[i]){
            s.pop();
            index.pop();
        }
        // If stack becomes empty, then no element is greater
        // on left side. Else top of stack is previous
        // greater.
        if (s.empty()){
         next[i] = i;
        }
        else{
            next[i] = index.top();
        }
        s.push(arr[i]);
        index.push(i);
    }
    return next;
}

int main(){
    int N;
    // Read number of skyscrapers
    cin >> N;
    // Read height of each skyscraper
    H = new uint64_t[N];
    for (int i = 0; i < N; i++ ){
        cin >> H[i];
    }

    int* prev;
    int* next;
    prev = prevGreater(H, N);
    next = nextGreater(H, N);

    // Each array will have the (righ or left) cost computed if we choose k = i.
    uint64_t leftMax[N], rightMax[N];
    // We keep a current max
    uint64_t current_max = H[0];
    // If k = 0 left cost is 0 cause there isn't any element left to zero index.
    leftMax[0] = 0;

    for(int i = 1; i < N; i++ ){
        if (H[i] >= current_max){
            leftMax[i] = i * H[i];
            current_max = H[i];
        }
        else if (H[i] <= H[i-1]){
            // Cause H[i] won't change the cost of any other skyscraper.
            leftMax[i] = leftMax[i-1] + H[i-1];
        }
        else{
            leftMax[i] = leftMax[prev[i]+1] + (i-prev[i]-1) * H[i];
        }
    }

    current_max = H[N-1];
    // If k = N-1 right cost is 0 cause there isn't any elmenent right to N-1 index.
    rightMax[N-1] = 0;
    for(int i = N-2; i >= 0; i-- ){
        if (H[i] >= current_max){
            rightMax[i] = (N-i-1) * H[i];
            current_max = H[i];
        }
        else if (H[i] <= H[i+1]){
            // Cause it won't change the cost of any other skyscraper.
            rightMax[i] = rightMax[i+1] + H[i+1];
        }
        else{
            rightMax[i] = rightMax[next[i]-1] + (next[i]-i-1)*H[i];
        }
    }

    uint64_t min_cost;
    uint64_t cost;
    // For each index we compute total cost and keep the min.
    for (int i = 0; i < N; i++ ){
        cost = H[i] + leftMax[i] + rightMax[i];
        if (i == 0){
            min_cost = cost;
        }
        if (cost < min_cost){
            min_cost = cost;
        }
    }
    cout << min_cost << endl;
    return 0;

}
