#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "readCsv.cpp"
#include "bestFit.cpp"
//#include "geneticAlgorithm.cpp"

#define PEOPLE_PATH "../Data/people.csv"
#define ACESSP_PATH "../Data/acessPoint.csv"

using namespace std;

int main(){
    vector<vector<float>> people;
    readCSV(PEOPLE_PATH, people);
    vector<vector<float>> acessP;
    readCSV(ACESSP_PATH, acessP);

    vector<int> s(people.size(), -1);
    bestFit(s, people, acessP);
    for(int i=0; i<=s.size()-1; i++){
        cout << s[i] << " ";
    }
    // for(size_t i=0; i<=acessP.size()-1; i++){
    //     for(size_t j=0; j<=acessP[i].size()-1; j++){
    //         cout << acessP[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    // for(size_t i=0; i<=people.size()-1; i++){
    //     for(size_t j=0; j<=people[i].size()-1; j++){
    //         cout << people[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    printf("Fim do Programa.");
    return 0;
}