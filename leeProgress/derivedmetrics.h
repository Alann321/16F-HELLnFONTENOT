#ifndef DERIVEDMETRICS_H
#define DERIVEDMETRICS_H
#include "metric.h"
#include "directoryiterator.h"
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

    //constructor with file iterator -> NEED IMPLEMENTATION IN DIRITR
    cmtRatio(directoryIterator files);

    //score creation implementation -> NEED IMPLEMENTATION IN DIRITR
    void createScore(directoryIterator files);

};

//========================
// Comment Quality Metric
//========================
class commentQuality : public basemetric{
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

    //constructor with iterator -> NEED IMPLEMENTATION IN DIRITR
    commentQuality(directoryIterator files);

    //score creation implementation -> NEED IMPLEMENTATION IN DIRITR
    void createScore(directoryIterator files);

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
