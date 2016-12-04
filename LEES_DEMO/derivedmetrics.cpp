#include "derivedmetrics.h"
#include <math.h>
#include <sstream>

testMetric::testMetric()
{
    this->name = DSString("TEST METRIC");
    this->verboseLines.deleteElement(0);
    createScore();
    setWeight();
}
testMetric::testMetric(int score, int weight)
{
    this->name = DSString ("TEST METRIC ++");
    this->verboseLines.deleteElement(0);
    this->score = score;
    this->weight = weight;
    for(int i = 0; i < score * weight; i++){
        this->verboseLines.append(DSString("This is a Test!"));
    }

}

void testMetric::createScore()
{
    this->score = 1;
}

void testMetric::setWeight()
{
    this->weight = 1;
}


//============================
// Comment Ratio Metric START
//============================


cmtRatio::cmtRatio(directoryIterator files){
    //std::cout << "Creating Comment Ratio Metric" <<std::endl;
    name = DSString("Comment to Line of File Ratio");
    verboseLines.deleteElement(0);
    totalComments = 0;
    totalLines = 0;
    weight = 10;
    createScore(files);
}


void cmtRatio::createScore(directoryIterator files){

    //iterate over files in directory and all sub dirs
    for(int i = 0; i < files.fileNames.getSize(); i++){

        //open file for evaluation
        fstream input;
        input.open(files.fileNames[i].c_str());



        if(!input){
            std::cout << "Could not open File!" <<std::endl;
            break;
        }

        int lineCount = 0;
        int commentCount = 0;

        //dummy buffer for line count
        char* buffer = new char[200];

        //define expressions for search
        string singleLine("\/\/.*");
        string multiLine("\/\*");

        regex expr1(singleLine);
        regex expr2(multiLine);

        smatch Match1;
        smatch Match2;

        string searchString;

        //read lines untill end of file is hit
        while(true && lineCount < 1000){
            input.getline(buffer, 200);

            searchString = buffer;

            //if either style of comment is found, incrament
            if( std::regex_match(searchString, Match1, expr1)/* ||
                    std::regex_search(searchString, Match2, expr2)*/){
                std::cout<<searchString<<std::endl;
                commentCount ++;
            }

            //update total line count
            lineCount ++;
            if(input.eof()){
                break;
            }

        }

        delete[] buffer;
        //close file
        input.close();

        totalComments += commentCount;
        totalLines += lineCount;

        //create record for reference
        DSString tmpRecord("File: ");
        tmpRecord = tmpRecord + files.fileNames[i] +
                DSString("\n \t\t\tLines Sampled: ") +
                lineCount + DSString(" Comments found: ") +
                commentCount;

        //add to verbose output
        verboseLines.append(tmpRecord);

    }

    double ratio = totalComments / totalLines;
    score = abs(ratio - .33);
}

//============================
// Comment Ratio Metric END
//============================

//==============================
// Comment Quality Metric START
//==============================

//Problem

//AVL Tree is working -> Added Template to utility methods
//Stringstream and Vector seems to have problems. Memory Leak.

commentQuality::commentQuality(directoryIterator files)
{
    name = DSString("Comment Quality");
    verboseLines.deleteElement(0);
    totalWordCount = nounAndVerbCount = adjectiveCount = adverbCount = fillerCount = 0;
    weight = 10;
    createScore(files);
}

bool commentQuality::isAdj(DSString ending)
{
    if(ending.substring(ending.size()-3, ending.size()) == "ble")
        return true;
    else if(ending.substring(ending.size()-2, ending.size()) == "al")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ful")
        return true;
    else if(ending.substring(ending.size()-2, ending.size()) == "ic")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ive")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ous")
        return true;
    else if(ending.substring(ending.size()-3, ending.size()) == "ish")
        return true;
    else
        return false;
}

bool commentQuality::isAdv(DSString ending)
{
    if(ending.substring(ending.size()-2, ending.size()) == "ly")
        return true;
    else if(ending.substring(ending.size()-4, ending.size()) == "ward")
        return true;
    else
        return false;
}

void commentQuality::createScore(directoryIterator files)
{
    //String Dump for counting words
    DSVector<DSString> wordsInComment;

    //read in files for checking
    fstream filler;
    filler.open("filler.txt");

    //AVL Tree of filler word list
    AVLTree<DSString> fillerTree;
    char* fillerBuffer = new char[15];

    //store the string to the avl tree
    while(filler>>fillerBuffer)
    {
        DSString fillerStr(fillerBuffer);
        fillerTree.addNode(fillerStr);
    }

    //close the filler list
    filler.close();

    //iterate over files in directory & subdirectories
    for(int i=0; i<files.fileNames.getSize(); i++)
    {
        //open files
        fstream input;
        input.open(files.fileNames[i].c_str());

        //break condition if the file cannot be openned
        if(!input)
        {
            std::cout<<"File can't be openned"<<std::endl;
            break;
        }

        //Counter to prevent segfaults at large files
        int lineCount = 0;

        //buffer for reading in lines
        char* buffer = new char[200];

        //define regex for search
        string singleLine("\s*\/\/.*");
        string multiLine("\s\/\*.*");

        regex expr1(singleLine);
        regex expr2(multiLine);

        smatch Match1;
        smatch Match2;

        string searchString;

        //read lines untill end of file is hit
        while(true && lineCount < 1000)
        {
            input.getline(buffer, 200);
            searchString = buffer;

            //NEED to only read in words & numbers
            //NEED to write a method for splitting strings

            //WHAT IF
            //instead of regex, have conditionals.

//            if(first two chars of a line == '//', then read each word until it hits newline char)
//            else if(first two chars of a line =='/*', then read each word until it hits a word with last two chars =='*/')
//            -> have flag for non alphabets. If the first or last char of a string is nonalpha, recursively remove this


            //if either style of comment is found, copy to the vector
            if( std::regex_match(searchString, Match1, expr1)/* ||
                    std::regex_search(searchString, Match2, expr2)*/)
                    {
                        //std::cout<<searchString<<std::endl;
                        //create stringstream object for deliminating words from line of string
                        istringstream ssObj(searchString);
                        //temp string used for stringstream operation
                        string tempStr;
                        //store the individual words into vector.
//                        while(ssObj >> tempStr)
//                        {
//                            //create Custom string object with searchString
//                            DSString bufferStr(tempStr.c_str());

//                            //strip punctuation
//                            bufferStr.cleanPunct();

////                            std::cout<<tempStr<<std::endl;

////                            //after stripping the punctuation, store the line into dump
////                            wordsInComment.add(bufferStr);
//                        }
                    }

                    //break at the end of file
                    if(input.eof())
                        break;
            }//end of whileloop

            delete[] buffer;
            //close file
            input.close();

////            get words from vector. at each index, deliminate the string by whitespace
//             for(int j=0; j<wordsInComment.getSize(); j++)
//             {
//                 if(wordsInComment[i] != "a" && wordsInComment[i] != "an" && wordsInComment[i] != "the")
//                 {
//                     //read in the words, increment total counter
//                     totalWordCount ++;

//                         //increment according counters
//                         if(isAdj(wordsInComment[i]) == true)
//                             adjectiveCount++;

//                         else if(isAdv(wordsInComment[i]) == true)
//                             adverbCount++;

//                         //if the word is found in the fillerTree, increment filler counter
////                         else if(fillerTree.findValue(wordsInComment[i]) != nullptr)
////                             fillerCount++;
//                         //if none of the above are applicable, increment noun and verb counter
//                         else
//                             nounAndVerbCount++;
//                 }//end of if (!artile)
//             }//end of forloop (counters)

//            // //logic check
//             double adjRatio, advRatio/*, fillerRatio*/, nounAndVerbRatio = 0.0;

//             //create ratio using the counts
//             adjRatio = adjectiveCount/totalWordCount;
//             advRatio = adverbCount/totalWordCount;
////             fillerRatio = fillerCount/totalWordCount;
//             nounAndVerbRatio = nounAndVerbCount/totalWordCount;

//             //set scoring rubic -> need more robust mechanism -> scale
//             if(adjRatio<15.0 || adjRatio>25.0)
//                 score += 10.0;
//             if(advRatio<15.0 || adjRatio>25.0)
//                 score += 10.0;
//             if(nounAndVerbRatio<40.0 || nounAndVerbRatio>60.0)
//                 score +- 10.0;
////             if(fillerRatio>10.0)
////                 score += 10.0;
//             if(adjRatio>advRatio)
//                 score += 10.0;

//         //create record for reference
//         DSString tmpRecord("File: ");
//         tmpRecord = tmpRecord + files.fileNames[i] +
//                 DSString("\n \t\t\tWords In Comment: "); /*+
//                 totalWordCount + DSString(" Content Ratio: ") +
//                 nounAndVerbCount + DSString(" Filler Ratio: ") +
////                 fillerCount + DSString(" Modifier Ratio: ") +
//                 adjectiveCount + adverbCount;*/

//         //add to verbose output
//         verboseLines.append(tmpRecord);

    }//end of forloop -> files Done

    //score

}//end of function


//==============================
// Comment Quality Metric END
//==============================
