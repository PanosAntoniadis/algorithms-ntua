#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/* Contains the social credit of all the people that I can meet */
vector<int> credits;
int *a;
int *b;
// Binary search (note boundaries in the caller)
int CeilIndex(std::vector<int>& v, int l, int r, int key)
{
	while (r - l > 1) {
		int m = l + (r - l) / 2;
		if (v[m] >= key)
			r = m;
		else
			l = m;
	}

	return r;
}



int LongestIncreasingSubsequenceLength(std::vector<int>& v,int start, int N)
{
	if (N == 0)
		return 0;

	std::vector<int> tail(N, 0);
	int length = 1; // always points empty slot in tail

	tail[0] = v[start];
	a[0] = length;
	for (int i = start; i < N; i++) {

		// new smallest value
		if (v[i] < tail[0])
			tail[0] = v[i];

		// v[i] extends largest subsequence
		else if (v[i] > tail[length - 1])
			tail[length++] = v[i];

		// v[i] will become end candidate of an existing
		// subsequence or Throw away larger elements in all
		// LIS, to make room for upcoming grater elements
		// than v[i] (and also, v[i] would have already
		// appeared in one of LIS, identify the location
		// and replace it)
		else
			tail[CeilIndex(tail, -1, length - 1, v[i])] = v[i];
		a[i] = length;
	}

	std::vector<int> tail2(N, 0);
	length = 1; // always points empty slot in tail

	tail2[N-1] = v[N-1];
	b[N-1] = length;
	for (int i = N-2; i >= 0; i--) {

		// new smallest value
		if (v[i] > tail2[N-1])
			tail2[N-1] = v[i];

		// v[i] extends largest subsequence
		else if (v[i] < tail2[N - length]){
			tail2[N - length - 1] = v[i];
			length++;
		}
		// v[i] will become end candidate of an existing
		// subsequence or Throw away larger elements in all
		// LIS, to make room for upcoming grater elements
		// than v[i] (and also, v[i] would have already
		// appeared in one of LIS, identify the location
		// and replace it)
		else{
			tail2[CeilIndex(tail2, N-length, N-1, v[i])-1] = v[i];
			//cout << "change	" << CeilIndex(tail2, N-length, N-1, v[i])-1 << endl;
		}
		//cout << "tail" << endl;

		b[i] = length;
		//cout << "Length	" << b[i] << endl;

	}
	int max_p = a[0] + b[0];
	for(int i = 1; i < N; i++){
        max_p = max(max_p, a[i] + b[i]);
    }
	return max_p;
}


int main(){
    int i;
    /* Read number of people */
    int N;
    cin >> N;
	a = new int [N];
	b = new int [N];
    /* Read social credit of each person */
    int temp;
    for(i = 0; i < N; i++){
        cin >> temp;
        credits.push_back(temp);
    }

    cout << LongestIncreasingSubsequenceLength(credits, 0, N) << endl;


	return 0;



}
