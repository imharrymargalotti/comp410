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
    //first, lets pick out a file to read data in from 
    //i.e. ascending data, descending data or random data
    std::string filename = "";
    
    std::string dataType = ""; //this will be used in the output (just a string)
    //should be: ascending, descending or random
    
    //lets allocate an array for the number of number we would like to test with
    //i.e. 10,000 | 50,000 | 100,000 | 200,000 ... 900,000 | 1,000,000
    int * count = new int[12];
    count[0] = 10000;
    count[1] = 50000;
    count[2] = 100000;
    for (int x = 2; x<=12; x++){
        count[x] = (x-1) * 100000;
    }
    //now that the array of sizes is populated, lets print some output to clarify what we're doing
    std::cout<< dataType << " data test: "<<std::endl;
    for (int x = 0; x < 12; x++) { //lets iterate through the number of numbers to insert
        std::cout<<"testing for size: " << count[x] << std::endl;
        int sizeForTest = count[x];
        //lets load 'x' numbers into an array from the file specified above
        int *testData = loadFileToArray(filename, sizeForTest);

        RBTree *sTree = new RBTree();
        auto runtime = 0;
        //lets run the test 5 times (1-6 [exclusive]) to get more data
        int runs = 6;
        for (int x = 1; x < runs; x++) {
            //lets grab the time using chrono
            auto begin = chrono::high_resolution_clock::now();
            for (int i = 0; i < sizeForTest; i++) {
                //do the insertion
                sTree->insertValue(testData[i]);
            }
            //now that insertion is complete lets grab the time again
            auto end = chrono::high_resolution_clock::now();
            
            //lets do a trvial calculation to get the elapsed time of the test
            auto dur = end - begin;
            //lets convert that duration to miliseconds
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
            runtime += ms; //store the total time in miliseconds in runtime
            //lets print the results to stdout
            cout << "Duration for run" << x << ": " << ms << "ms" << std::endl;
        }
        //after a test has run 5 times lets take an average for the most accurate data
        cout << "Average time: " << runtime / (runs - 1);
        std::cout<<"\n\n";
    }
    return 0;
}
