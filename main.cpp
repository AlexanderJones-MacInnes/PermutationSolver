#include <iostream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

struct PermutationSolver
{
    struct Member
    {
        static int nextID;
        int ID;
        string text;

        Member(string t)
        : text(t)
        , ID(nextID+1)
        {
            nextID++;
        }
    };

    vector<vector<string>> permutations;

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

    void Solve(list<string> members)
    {

        int perTotal = Factorial(members.size());
        permutations.resize(perTotal);
        list<string> memberQueue;
        //Iterate through row selection of columns in permutation list
        for(int cycle = 0; cycle < members.size(); cycle++)
        {
            /*
            To know how many times to place a member in each row you can treat
            each row as a smaller set read from the current row to the right
            */
            int empTotal = Factorial( (members.size() - cycle) -1 );

            //Reset queue for each row-cycle otherwise ya get problems.
            memberQueue = members;

            //Iterate through each permutation in the list at the row-number equal to value of cycle
            for(int index = 0; index < perTotal; index++)
            {
                //When you have emplaced a single member for it's maximum repeats...
                if(index % empTotal == 0 && index != 0)
                {
                    //...Pop queue to next member
                    memberQueue.pop_front();
                    //If you have emplaced the entire queue...
                    if(memberQueue.empty())
                    {
                        //...refresh the queue
                        memberQueue = members;
                    }
                }

                /*
                If any members are in the currently indexed combination remove them from
                the queue to avoid repeating instances. This should be done after the
                prior IF-statement to avoid emptying the queue before emplacemnt.
                */
                for(string s:permutations.at(index))
                {
                    memberQueue.remove(s);
                }

                //Push data to permutation list.
                permutations.at(index).push_back(memberQueue.front());
            }
        }

    }
};
int PermutationSolver::Member::nextID = 0; //Initialize default value for member struct ID

int main()
{
    PermutationSolver p;
    list<string> test = {"a","b","c"};
    p.Solve(test);
    for(vector<string> v:p.permutations)
    {
        for(string s:v)
        {
            cout << s << ',';
        }
        cout << '\n';
    }




}
