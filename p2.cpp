#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void merge(int * ,int , int , int, int);
void merge(string * ,int , int , int, int);

void merge_sort(int *arr, int low, int high, int count)
{
    int mid;
    if (low < high){
        mid=(low+high)/2;
        merge_sort(arr,low,mid,count);
        merge_sort(arr,mid+1,high,count);
        merge(arr,low,high,mid,count);
    }
}

void merge_sort(string *arr, int low, int high, int count)
{
    int mid;
    if (low < high){
        mid=(low+high)/2;
        merge_sort(arr,low,mid,count);
        merge_sort(arr,mid+1,high,count);
        merge(arr,low,high,mid,count);
    }
}

void merge(int *arr, int low, int high, int mid, int count) {
    int l, j, k, c[high];
    l = low;
    k = low;
    j = mid + 1;
    while (l <= mid && j <= high) { //while both have stuff
        if (arr[l] < arr[j]) {
            c[k] = arr[l];
            k++;
            l++;
        }
        else  {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (l <= mid) { //while only left has stuff
        c[k] = arr[l];
        k++;
        l++;
    }
    while (j <= high) { //while only right has stuff
        c[k] = arr[j];
        k++;
        j++;
    }
    for (l = low; l < k; l++)  {
        arr[l] = c[l];
    }
}

void merge(string *arr, int low, int high, int mid, int count) {

    int l, j, k;
    string c[high+1];
    l = low;
    k = low;
    j = mid + 1;
    while (l <= mid && j <= high) {
        if (arr[l] < arr[j]) {
            c[k] = arr[l];
            k++;
            l++;
        }
        else  {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (l <= mid) {
        c[k] = arr[l];
        k++;
        l++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (l = low; l < k; l++)  {
        arr[l] = c[l];
    }
}

int main(int argc, char **argv) {
    ifstream fp1, fp2;
    fp1.open (argv[2]); //open files and make sure they're proper
    fp2.open (argv[3]);
    if (!fp1.is_open()) {
        cout << "Could not open file " << argv[1] << endl;
        return 1;
    }
    if (!fp2.is_open()) {
        cout << "Could not open file " << argv[1] << endl;
        return 1;
    }


    int count1=0, count2=0;
    string str, type = argv[1];
    while(!fp1.eof()) { //count both files lengths to declare proper length arrays
        fp1 >> str;
        if (fp1.eof()) break;
        count1++;
    }
    while(!fp2.eof()) {
        fp2 >> str;
        if (fp2.eof()) break;
        count2++;
    }


    string raw1[count1+1], raw2[count2+1]; //reset files for rereading
    fp1.clear();
    fp1.seekg(0, ios::beg);
    fp2.clear();
    fp2.seekg(0, ios::beg); 


    int i=0;
    while(!fp1.eof()) { //read each file into respective array
        fp1 >> raw1[i];
        i++;
    }
    i=0;
    while(!fp2.eof()) {
        fp2 >> raw2[i];
        i++;
    }


    int count = count1 + count2, c=0;;
    string raw[count];
    for (int a=0; a<count1; a++) { //checks each member of raw1 against each member of raw2 after making sure the object doesnt exist twice in raw1
        bool test=false;
        for (int d=a+1; d<count1; d++) { //ignores an object if a duplicate exists past it in the list
            if (raw1[d]==raw1[a]) {
                // cout << "found-" << raw1[a] << endl;
                test=true;
                break;
            }
        }
        if (test==false) {
            for (int b=0; b<count2; b++) { 
                if (raw1[a]==raw2[b]) {
                    raw[c] = raw1[a];
                    c++;
                    break;
                }
            }
        }
    }
    count = c;


    if (type=="i") {
        int intraw[count];
        for (int r=0; r<count; r++) {
            intraw[r] = stoi(raw[r]);
        }
        merge_sort(intraw, 0, count-1, count);
        for (int k=0; k<count; k++) { //final print for intraw
            cout << intraw[k] << endl;
        }
    }
    else if (type=="s") {
        merge_sort(raw, 0, count, count);
        for (int k=1; k<count+1; k++) { //final print for raw
            cout << raw[k] << endl;
        }
    }
    

    return 0;
}