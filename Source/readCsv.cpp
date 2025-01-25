#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void readCSV(const string& filename, vector<vector<float>>& vet){
    ifstream file(filename);

    if(!file.is_open()){cerr << "Error opening " << filename << " file!" << endl; exit(1);}

    string line;
    getline(file, line); // remove 1º Linha
    while(getline(file, line)){ 
        string cell;
        stringstream ss(line);

        vector<float> row;
        getline(ss, cell, ';'); // remove 1º Elemento (ID)
        while(getline(ss, cell, ';')){
            row.push_back(stof(cell));
        }
        vet.push_back(row);
    }


    file.close(); 
}

// int main(){
//     string filename = "../Data/data.csv";
//     vector<vector<float>> people;
//     readCSV(filename, people);

//     for(size_t i=0; i<=people.size()-1; i++){
//         for(size_t j=0; j<=people[i].size()-1; j++){
//             cout << people[i][j] << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }