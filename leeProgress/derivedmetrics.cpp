#include "derivedmetrics.h"

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
        string singleLine("\s*\/\/.*");
        string multiLine("\s\/\*.*");

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
            if( std::regex_match(searchString, Match1, expr1) ||
                    std::regex_search(searchString, Match2, expr2)){

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
}

//============================
// Comment Ratio Metric END
//============================

//==============================
// Comment Quality Metric START
//==============================

commentQuality::commentQuality(directoryIterator files)
{
    name = DSString("Comment Quality");
    verboseLines.deleteElement(0);
    //wordCount = contentCount = adjCount = advCount = fillerCount = 0;
    weight = 10;
    createScore(files);
}

void commentQuality::createScore(directoryIterator files)
{
    //String Dump for counting words
    DSVector<string> wordsInComment;

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

            //if either style of comment is found, copy to the vector
            if( std::regex_match(searchString, Match1, expr1) ||
                    std::regex_search(searchString, Match2, expr2))
                    {

                        //after stripping the punctuation, store in char*

//                        DSString dsSearch = searchString.c_str();
                        //strip punctuation
//                        dsSearch.cleanPunct();
                        //store the line into a dump (vector)
                        //wordsInComment.add();
                    }

                    //break at the end of file
                    if(input.eof())
                        break;
            }//end of whileloop

            delete[] buffer;
            //close file
            input.close();

            //get words from vector. at each index, deliminate the string by whitespace
            // for(int j=0; j<wordsInComment.getSize(); j++)
            // {
            //     //read in the words, increment total counter
            //     totalWord ++;
            //
            //     //increment according counters
            //     if(word != article)
            //     {
            //         if(word == adj)
            //             adj++;
            //
            //         else if(word == adv)
            //             adv++;
            //
            //         else if(filler.contains(word) == true)
            //             filler++;
            //         else
            //             content++;
            //     }//end of if
            // }//end of forloop
            //
            // //logic check
            // int adjRatio, advRatio, fillerRatio, contentRatio = 0;
            // adjRatio = (100*adj)/totalWord;
            // advRatio = (100*adv)/totalWord;
            // fillerRatio = (100*filler)/totalWord;
            // contentRatio = (100*content)/totalWord;
            //
            // if(adjRatio<15 || adjRatio>25)
            //     increase score;
            // if(advRatio<15 || adjRatio>25)
            //     increase score;
            // if(contentRatio<40 || contentRatio>60)
            //     increase score;
            // if(fillerRatio>10)
            //     increase score;
            // if(adjRatio>advRatio)
            //     increase score;
            //
            // create record for reference
            //
            // add to verbose output

    }//end of forloop -> files Done

    //score = something;

}//end of function


//==============================
// Comment Quality Metric END
//==============================
