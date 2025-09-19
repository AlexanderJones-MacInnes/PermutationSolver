#include <iostream>
#include "E:\\documents\\codestuff\\c++\\headers\\Permutations.h"
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[])
{
    string helpText =
"\nThis program finds all permutations for a set of N strings.\n\
Additionally the following arguments can be entered...\n\n\
'<string/text>' Any generic text that is not one of the commands below will be treated as part of the set.\n\
'/help' will display this text.\n\
'/d <char>' will use <char> as a delimiter to seperate a single-string input into multiple items.\n\
'/t <path>' will write output to a text file at the location of <path>\n\n\
Arguments can be entered in any order...";

    char delimiter = false;
    string filePath = "";
    bool silentRun = false;

    list<string> inputSet;

    //Args are read here.
    //If no args were entered displays user help text.
    if(argc == 1)
    {
        cout << helpText;
    }
    //Loop through all entered arguments.
    for(int i = 1; i < argc; i++)
    {
        string temp = argv[i];

        //Check if argument is a command.
        if(temp[0] == '/')
        {
            //Displays user help text
            if(temp == "/help")
            {
                cout << helpText;
            }

            //Flags the program to not print output to stdout.
            else if(temp == "/s")
            {
                silentRun = true;
            }

            //Flags the program to print output to a text file, a filepath needs to be entered after this.
            else if(temp == "/t")
            {
                //Check value of next argument entered to get file path.
                i++;
                filePath = argv[i];
                if(filePath.find(".txt") == string::npos)
                {
                    filePath += ".txt";
                }
            }

            //Flag that input string should be seperated by some delimiter char
            else if(temp == "/d")
            {
                //Check next argument entered to get value of delimiter
                i++;
                if(argv[i])
                {
                    temp = argv[i];
                }
                //If none was entered default to commas
                else
                {
                    temp = ',';
                }
                delimiter = temp[0];
            }
        }

        //If argument was not a command treat it as a set member.
        else
        {
            inputSet.push_back(temp);
        }
    }


    //If delimiter flag was set in arguments split the strings here
    if(delimiter)
    {
        list<string> tempList = inputSet;
        inputSet.clear();

        for(string tempStr : tempList)
        {
            int lastDelimiter = 0;
            for(int i = 0; i <= (int)tempStr.length(); i++)
            {
                if(tempStr[i] == delimiter || tempStr[i] == '\0')
                {
                    inputSet.push_back( tempStr.substr(lastDelimiter, i-lastDelimiter) );
                    lastDelimiter = i+1;
                }
            }
        }
    }

    //Calculate permutations for the given set
    vector<string> output = permutations::SolvePermutations(inputSet);

    //If file path was set in arguments write output to a text file at location of filePath.
    if(filePath != "")
    {
        FILE* pFile = fopen(filePath.c_str(),"w");
        for(string s : output)
        {
            s += '\n';
            fputs(s.c_str(),pFile);
        }
        fclose(pFile);
    }

    //If silentRun flag was set do not print results to stdout.
    if(!silentRun)
    {
        for(string s : output)
        {
            cout << s << '\n';
        }
    }

    return 0;
}
