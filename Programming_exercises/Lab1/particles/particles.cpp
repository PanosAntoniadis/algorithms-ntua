#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

vector<int> tA, uA, tB, uB;

double distance(int u, double start_time, double curr_time){
    return u * (curr_time - start_time);
}

int nextCrash(double l, double r, int L){
    //cout << "Left:" << l << "Right:" << r << endl;
    if (l <= r){
        int N = tA.size();
        double mid, maxA, minB;
        int idxA, idxB;
        int i;
        mid = l + (double)(r-l)/2.0;
        //cout << "Mid" << mid << endl;

        maxA = -1;
        minB = L + 1;
        for(i = 0; i < N; i++){
            //cout << "cur_el " << i << " with " << distance(uA[i], tA[i], mid) << endl;
            if (distance(uA[i], tA[i], mid) > maxA){
                maxA = distance(uA[i], tA[i], mid);
                idxA = i;
                //cout << "cur_max " << maxA << " idx " << i << endl;
            }
            if (maxA > L)   break;
        }
        for(i = 0; i < N; i++){
            if (L - distance(uB[i], tB[i], mid) < minB){
                minB = L - distance(uB[i], tB[i], mid);
                idxB = i;
            }
            if (minB < 0)   break;
        }
        //cout << "maxA" << maxA << "minB" << minB << endl;
        if (maxA < minB)    return nextCrash(mid, r, L);
        else{
            double secA, secB;
            secA = -1;
            secB = L+1;
            for(i = 0; i < N; i++){
                if (distance(uA[i], tA[i], mid) != maxA){
                    if (distance(uA[i], tA[i], mid) > secA) secA = distance(uA[i], tA[i], mid);
                }
                if (secA > L+1)     break;
            }
            for(i = 0; i < N; i++){
                if (L - distance(uB[i], tB[i], mid) != minB){
                    if (L - distance(uB[i], tB[i], mid) < secB) secB = L - distance(uB[i], tB[i], mid);
                }
                if (secB < 0)      break;
            }
            //cout << "secA" << secA << "secB" << secB << endl;
            if (secA < secB and secA < minB and secB > maxA){
                cout << idxA+1 << " " << idxB+1 << endl;
                uA[idxA] = 0;
                uB[idxB] = 0;
                //swap (uA[idxA], uA[N-1]);
                //swap (tA[idxA], tA[N-1]);
                //swap (uB[idxB], uB[N-1]);
                //swap (tB[idxB], tB[N-1]);
                return mid;
            }
            else{
                return nextCrash(l, mid, L);
            }
            //usleep(10000000);

        }
    }
    else{
        cout << "Problem";
        return 0;
    }
}

int main(){
    // Read N, L, K
    int N, L, K, i;
    cin >> N >> L >> K;
    // Read starting time and velocity of each particle
    int temp1, temp2;
    for(i = 0; i < N; i++){
        cin >> temp1 >> temp2;
        tA.push_back(temp1);
        uA.push_back(temp2);
    }
    for(i = 0; i < N; i++){
        cin >> temp1 >> temp2;
        tB.push_back(temp1);
        uB.push_back(temp2);
    }

    float m = 0;
    for(i = 0; i < K; i++){
        //cout << m << endl;
        m = nextCrash(m, L, L);
    }

    return 0;
}  
