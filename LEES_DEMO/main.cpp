#include <iostream>
#include <fstream>
\
#include "directoryiterator.h"
#include "hashtable.h"
#include "metric.h"
#include "derivedmetrics.h"

void test();
void printResults(DSVector<basemetric> &tests, bool verbose);
double calculateScore(DSVector<basemetric>& tests);

int main(int argc, char* const argv[]){

    if(argc <= 1){
        std::cout << "Invalid Parameters" <<std::endl;
        return -1;
    }

    directoryIterator dirTree(argv[1]);

    DSVector<basemetric> metricVector;
    metricVector.append(cmtRatio(dirTree));
    printResults(metricVector, true);

    metricVector.append(commentQuality(dirTree));
    printResults(metricVector, true);


    //============================
    // BEGIN TESTS
    //test();
    //  END TESTS
    //=========================

    std::cout << "Done!" << std::endl;
    return 0;
}

void test(){
    DSVector<basemetric> tests;
    hashtable<int, int> testTable;
    hashtable<DSString, DSString> stringTable;

    for(int i = 0 ; i < 1000; i++){
        testTable.put(i, i);
    }

    hashtable<int, int > testTable2 = testTable;

    testTable.put(0, 1111);

    std::cout << testTable2.get(4) << std::endl;

    for(int i = 0; i < 1001; i++){
        std::cout << testTable.get(i) <<std::endl;
    }


    stringTable.put(DSString("Test"), DSString("Words"));
    stringTable.put(DSString("Hello"), DSString("World!"));



    std::cout << stringTable.get(DSString("Test")) << std::endl;
    std::cout << stringTable.get(DSString("Hello")) << std::endl;
    std::cout << stringTable.get(DSString("Foo")) << std::endl;

    for(int i = 0; i < 5; i++){
        tests.append(testMetric(i, i));
    }

    tests.append(testMetric(1, 5));
    tests.append((basemetric()));

    printResults(tests, true);

}

//===========================
//     Test Functionality
//===========================

//calculate total score for all tests run
double calculateScore(DSVector<basemetric>& tests)
{
    int totalWeight = 0;
    double totalScore = 0;

    //find total for percentage breakdown
    for(int i = 0; i < tests.getSize(); i++){
        totalWeight += tests[i].weight;
    }
    for(int i = 0; i < tests.getSize(); i++){
        totalScore += tests[i].score *
                    ((double)tests[i].weight / (double)totalWeight);
    }

    return totalScore;
}

void printResults(DSVector<basemetric>& tests, bool verbose){

    std::cout << "Total Score: " << calculateScore(tests) <<std::endl;
    //iterate over tests
    for(int i =0; i < tests.getSize(); i++){
        //print test and scores
        std::cout << "\t" << tests[i].name << std::endl;
        std::cout << "\t\tScore: " << tests[i].score << " Weight: "
                  << tests[i].weight << std::endl;
    }

    //print out records if verbose mode is on
    if(verbose){
        std::cout << "Details" << std::endl;

        //iterate over tests
        for(int i =0; i < tests.getSize(); i++){

            std::cout << "\t" << tests[i].name << std::endl;

            //print records
            for(int j = 0; j < tests[i].verboseLines.getSize(); j++){
                std::cout << "\t\tRecord " << j << ": "<< tests[i].verboseLines[j] <<std::endl;
            }
        }
    }
}
