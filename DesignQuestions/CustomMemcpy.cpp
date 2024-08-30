#include<iostream>

using namespace std;

void CustomMemcpy(void* dest, void* src, int n) {
    char *cdest = static_cast<char*>(dest);
    char *csrc = static_cast<char*>(src);
    for(int i=0; i<n; i++) {
        cdest[i] = csrc[i];
    }
}

void CustomMemmove(void* dest, const void* src, int n) {
    char *cdest = static_cast<char*>(dest);
    const char *csrc = static_cast<const char*>(src);
    if(dest>src) {
        // Copy from the back
        for(int i=n-1; i>=0; i--) {
            cdest[i] = csrc[i];
        }
    } else {
        // Copy from the front
        for(int i=0; i<n; i++) {
            cdest[i] = csrc[i];
        }
    }
}

int main() {

    int arr[10];
    arr[0] = 1, arr[1] = 2, arr[2] = 3, arr[3] = 4, arr[4] = 5;
    // CustomMemcpy(arr+1, arr, sizeof(arr));
    // for(int i=0; i<5; i++) {
    //     cout<<arr[i]<<" ";
    // }

    CustomMemmove(arr+3, arr, 5*sizeof(arr[0]));
    for(int i=0; i<5; i++) {
        cout<<arr[i]<<" ";
    }

    return 0;
}