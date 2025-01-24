#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void readCSV(const string& filename, vector<string>& X, vector<string>& Y){
    ifstream file(filename);

    if(!file.is_open()){
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);
        string cell;

        int flag = 0;
        getline(ss, cell, ';');
        while(getline(ss, cell, ';')){
            if((flag++)==0){X.push_back(cell);}else{
                Y.push_back(cell);
                flag--;
            }
        }
    }

    file.close(); 
}

int main(){
    string filename = "Data/data.csv";
    vector<string> X;
    vector<string> Y;
    readCSV(filename, X, Y);

    for(size_t i = 0; i < X.size(); i++){
        cout << X[i] << "_" << Y[i] << endl;
    }

    return 0;
}