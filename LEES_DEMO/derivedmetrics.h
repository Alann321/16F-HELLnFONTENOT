#ifndef DERIVEDMETRICS_H
#define DERIVEDMETRICS_H
#include "metric.h"
#include "directoryiterator.h"
#include "avltree.h"
#include <fstream>
#include <string>
#include <regex>

//========================
// Redudent block metric
//========================
class redundBlck : public basemetric{

};

//========================
// Function depth metric
//========================
class fcnDepth : public basemetric{

};

//========================
// Comment Ratio Metric
//========================
class cmtRatio : public basemetric{
public:

    //totals for tracking ratio
    int totalLines;
    int totalComments;

    //constructor with file iterator
    cmtRatio(directoryIterator files);

    //score creation implementation
    void createScore(directoryIterator files);

};

//========================
// Comment Quality Metric
//========================
class commentQuality : public basemetric
{
public:
    
    //Counters for determining the ratio
    int totalWordCount;
    int adjectiveCount;
    int adverbCount;
    int nounAndVerbCount;
    int fillerCount;

    // IF : Need to Use AVL
    // int nounCount;
    // int verbCount;

    //constructor with iterator
    commentQuality(directoryIterator files);

    //score creation implementation
    void createScore(directoryIterator files);

    //boolean functions for type of words
    bool isAdj(DSString);
    bool isAdv(DSString);

};


//========================
// White Space Metric
//========================
class whtSpace : public basemetric{

};

//========================
// Formatting Metric
//========================
class formatting : public basemetric{

};

//Troubleshooting metric
class testMetric : public basemetric
{
public:
    testMetric();
    testMetric(int score, int weight);
    void setWeight();

    void createScore();
};

//comment to line number ratio


#endif // DERIVEDMETRICS_H
