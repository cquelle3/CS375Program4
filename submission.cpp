#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <tuple>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>

using namespace std;


// *** DYNAMIC PROGRAMMING CODE STARTS HERE *** 
int dynamicProg(vector<tuple<int, int>> v, int capacity){
    
    int x_size = capacity + 1;
    int y_size = 2;
    
    int table[x_size][y_size];
    
    
    for(int i=0; i < x_size; i++){
        table[i][0] = 0;
    }
    
    
    for(int i=0; i < v.size(); i++){
        
        tuple<int, int> current_item = v[i];
        int itemWeight = get<0>(current_item);
        int itemProfit = get<1>(current_item);
        
        table[0][1] = 0;
        
        for(int j=1; j < x_size; j++){
            if(get<0>(current_item) > j){
                table[j][1] = table[j][0];
            }
            else{
                table[j][1] = max(table[j][0], table[j-itemWeight][0] + itemProfit);
            }
        }
        
        for(int j=0; j < x_size; j++){
            table[j][0] = table[j][1];
        }
    }
    
    return table[x_size-1][y_size-1];
}

int main(int argc, char *argv[]) {

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    int mode = stoi(argv[3]);
    
    //cout.rdbuf(outfile.rdbuf());

    string line;
    string s1;
    string s2;

    int count = 0;
    int capacity = 0;
    int input_size = 0;
    
    vector<tuple<int, int>> vals;
    
    while(getline(infile, line)){
        
        stringstream s(line);
        s >> s1 >> s2;
        
        if(count == 0){
            input_size = stoi(s1);
            count = stoi(s1);
            capacity = stoi(s2);
        }
        else{
            
            vals.push_back(make_tuple(stoi(s1), stoi(s2)));
            count--;
            
            if(count == 0){
                if(mode == 3){
                    auto start = chrono::high_resolution_clock::now();
                    int p = dynamicProg(vals, capacity);
                    auto end = chrono::high_resolution_clock::now();
                    auto time_needed = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                    cout << input_size << " " << p << " " << time_needed << endl;   
                }
                vals.clear();
            }
        }
    }
    
    return 0;
}