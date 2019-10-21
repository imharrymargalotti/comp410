// Driver Program for Red Black Tree

#include <bits/stdc++.h>
#include "RBTree.h"
#include "SplayTree.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <string>
using namespace std;

int * genRandData(int size){
    int * rtnArray = new int[size];
    srand (time(NULL));
    for (int i = 0; i<size; i++){
        int randnum = rand() % 1000 + 1;
        rtnArray[i] = randnum;
    }
    return rtnArray;
}

int * genAscData(int size){
    int * data = new int[size]; //initializes the array
    int num = 1;
    for(int i = 0; i <= size; i++){ //for loop to create array populated with data of size given
        data[i] = num;
        num ++;
        if(num == 1001){
            num=1;
        }
    }
    return data;
}

int * genDescData(int size){
    int * data = new int[size]; //initializes the array
    int num = 1000;
    for(int i = 0; i <= size; i++){ //for loop to create array populated with data of size given
        data[i] = num;
        num --;
        if(num == 0){
            num=1000;
        }
    }
    return data;
}

int * loadFileToArray( std::string &fileName, int size) {
    std::ifstream data(fileName);
    std::string line;
    int *array = new int[size];
    if (data.is_open()) {
//        std::cout << "file opened" << std::endl;
        int i = 0;
        while (i < size) {
            getline(data, line);

            array[i] = stoi(line);

            i++;

            if (i >= size) {
                break;
            }
        }
        return array;
    }
    std::cout<<"file failed to open"<<std::endl;
    quick_exit(100);
}

int main() {
    std::string filename = "/home/hmargalotti/CLionProjects/comp410Proj/DescData.txt";
    int * count = new int[12];
    count[0] = 10000;
    count[1] = 50000;
    count[2] = 100000;
    for (int x = 2; x<=12; x++){
        count[x] = (x-1) * 100000;
    }

    std::cout<<"desc data test: "<<std::endl;
    for (int x = 0; x < 12; x++) {
        std::cout<<"testing for size: " << count[x] << std::endl;
        int sizeForTest = count[x];
        int *testData = loadFileToArray(filename, sizeForTest);

        RBTree *sTree = new RBTree();
        auto runtime = 0;
        int runs = 6;
        for (int x = 1; x < runs; x++) {
            auto begin = chrono::high_resolution_clock::now();
            for (int i = 0; i < sizeForTest; i++) {
                sTree->insertValue(testData[i]);
            }
            auto end = chrono::high_resolution_clock::now();

            auto dur = end - begin;

            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
            runtime += ms;
            cout << "Duration for run" << x << ": " << ms << "ms" << std::endl;
        }

        cout << "Average time: " << runtime / (runs - 1);
        std::cout<<"\n\n";
    }
    return 0;
}