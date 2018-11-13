#include <iostream>
#include <cstdint>
using namespace std;

uint64_t *H, *leftMax, *rightMax;

int main(){
    int N;
    // Read number of skyscrapers
    cin >> N;
    // Read height of each skyscraper
    H = new uint64_t[N];
    for (int i = 0; i < N; i++ ){
        cin >> H[i];
    }
    // Each array will have the (righ or left) cost computed if we choose k = i.
    leftMax = new uint64_t[N];
    rightMax = new uint64_t[N];
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
            // H[i] will change the cost of all skyscrapers until we find a taller skyscraper
            int64_t k = i-2;
            leftMax[i] = H[i];
            while ((H[i] > H[k]) and (k >= 0)){
                leftMax[i] = leftMax[i] + H[i];
                k -= 1;
            }
            leftMax[i] += leftMax[k+1];
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
            // H[i] will change the cost of all skyscrapers until we find a taller skyscraper
            int64_t k = i+2;
            rightMax[i] = H[i];
            while ((H[i] > H[k]) and (k < N)){
                rightMax[i] = rightMax[i] + H[i];
                k += 1;
            }
            rightMax[i] += rightMax[k-1];
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
