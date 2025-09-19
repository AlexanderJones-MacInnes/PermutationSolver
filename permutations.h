#pragma once
#include <list>
#include <vector>

namespace permutations
{
    struct Member;
    int Factorial(int);
    std::vector<std::string> SolvePermutations(std::list<Member> members);
    std::vector<std::string> SolvePermutations(std::string str);
    std::vector<std::string> SolvePermutations(std::list<std::string> lstr);
    std::vector<std::string> SolvePermutations(std::vector<std::string> vstr);

    struct Member
    {
        int id;
        std::string data;

        Member(int id, std::string data)
        : id(id)
        , data(data)
        {}
    };

    int Factorial(int n)
    {   int f = n;
        if(f == 0)
        {
            f = 1;
        }
        else
        {
            for(int i = 1; i < n; i++)
            {
                f *= (n - i);
            }
        }
        return f;
    }

    //Main permutation solving function. Overloads to handle input types for this function are below.
    std::vector<std::string> SolvePermutations(std::list<Member> members)
    {
        //Find total number of permutations for the size of the set
        int totalMembers = members.size();
        int totalPermutations = Factorial(totalMembers);

        //Set up a vector of lists to organize member-ID's during the calculation of permutations
        std::vector<std::list<int>> combinationsIdOrder(totalPermutations);
        //Set up a vector of strings to contain human-readable output for all permutations
        std::vector<std::string> combinationValues(totalPermutations);

        //Set up system for queueing the placement of set members into specific permutations

        //This list acts as the aformentioned queue
        std::list<int> emplacementQueue;

        //This list acts as a template for resetting the queue so that the following loop only has to be run once
        std::list<int> queueRefresh;
        for(Member m : members)
        {
            queueRefresh.push_back(m.id);
        }

        /*
        Solve for all permutations of the input set. This loop runs first by column then by row
        It advances down each index of the vector of lists (combinationsIdOrder) and appends the set member
        that currently lies at the front of the emplacementQueue to the list currently indexed in the vector.

        The emplacementQueue list is popped and reset according to a pattern in which a specific member across all permutations
        of a set of N only appears in any given row-space a number of times equal to factorial of (N-1).

        EG: In the 24 permutations of a set of 4 any specific member only appears in row-1, 6 times across all permutations.

        It is possible to use this pattern to create the following loop by treating each subsequent row as a set with
        a smaller size, while also eliminating members that are already placed into that permutation.

        So this process builds all combinations simultaneously rather than sequentially by working down a column before
        advancing to the next row and going down by column again and again.
        */
        for(int row = 0; row < totalMembers; row++)
        {
            //Counter used for knowing when to pop and refresh the queue.
            int emplacementCounter = Factorial( (totalMembers - (row+1))) ;

            //Clear the queue so that empty-check reads true below and resets the queue on iteration 0 of the next loop
            emplacementQueue.clear();
            //This will be popped immediately it just stops the queue system from emptying itself on the first run
            emplacementQueue.push_back(0);

            for(int column = 0; column < totalPermutations; column++)
            {
                if(column % emplacementCounter == 0)
                {
                    emplacementQueue.pop_front();

                    if(emplacementQueue.empty())
                    {
                        /*
                        Reset queue and remove any members already emplaced at the current index as to
                        avoid repeating instances of the same member in a permutation.
                        As one advances towards the right-side rows this process becomes more frequent
                        due to the shrinking size of emplacementCounter.
                        */
                        emplacementQueue = queueRefresh;
                        for(int i : combinationsIdOrder.at(column))
                        {
                            emplacementQueue.remove(i);
                        }
                    }
                }
                //Emplace next queued member into IdOrder list at vector index of current loop iteration
                combinationsIdOrder.at(column).push_back(emplacementQueue.front());

                //Update human-readable output vector with the data associated to that ID
                for(Member m : members)
                {
                    if(m.id == emplacementQueue.front())
                    {
                        combinationValues.at(column) += m.data;
                    }
                }
            }
        }
        return combinationValues;
    }

    std::vector<std::string> SolvePermutations(std::string str)
    {
        //Set up list of structs containing set member data associated to a unique numerical ID.
        int id = 0;
        std::list<Member> members;

        //Parse input string (str) into the members-list
        for(int i = 0; i < (int)str.length(); i++)
        {
            std::string temp = "";
            temp += str[i];
            members.push_back( { id, temp} );
            id++;
        }
        return SolvePermutations(members);
    }

    std::vector<std::string> SolvePermutations(std::list<std::string> lstr)
    {
        int id = 0;
        std::list<Member> members;

        //Parse input string-list (lstr) into members-list
        for(std::string temp : lstr)
        {
            members.push_back( {id, temp} );
            id++;
        }
        return SolvePermutations(members);
    }

    std::vector<std::string> SolvePermutations(std::vector<std::string> vstr)
    {
        int id = 0;
        std::list<Member> members;

        //Parse input string-vector (vstr) into members-list
        for(std::string temp : vstr)
        {
            members.push_back( {id, temp} );
            id++;
        }
        return SolvePermutations(members);
    }





}
