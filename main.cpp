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

    list<string> permutations; //Stores permutation results by their member value. (Converted from idOrder)
    list<Member> members; //Stores set members.

    void resetData()
    {
        members.clear();
        permutations.clear();
    }

    void inputSet(string text) //Input set of members as string
    {
        for(char c:text)
        {
            string s;
            s += c;
            members.push_back({s});
        }
    }

    void inputSet(list<string> text) //Input set of members as list of strings
    {
        for(string s:text)
        {
            members.push_back({s});
        }
    }

    void printResults()
    {
        for(string s:permutations)
        {
            cout << s << '\n';
        }
    }

    //Calculates factorial. (Used during calculation of permutations)
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

    void Solve()
    {
        //Get total amount of members that were input.
        int totalMembers = members.size();

        //Find total amount of possible permutations via the factorial of the total count of members.
        int perTotal = Factorial(totalMembers);

        //Create a vector to handle storing combinations of member ID's for calculation of permutations.
        vector<vector<int>> idOrder;
        //Resize permutation vector to contain total amount of possible permutations.
        idOrder.resize(perTotal);

        //Create a list to act as a queue for handling emplacment of members in each permutation.
        list<int> idQueue;
        //Create a second list of all ID's to act as a template for resetting the idQueue later during calculation.
        list<int> ids;
        for(Member m:members)
        {
            ids.push_back(m.ID);
        }

        //Loop through currently selected row-space for member-emplacement.
        for(int cycle = 0; cycle < totalMembers; cycle++)
        {
            /*
            To know how many times to place a member you can treat
            each row as a smaller set, read from the current column to the
            right, ignoring the already emplaced members on the left.
            */
            int empTotal = Factorial( (totalMembers - cycle) -1); // -1 for vector indexing purposes.

            //Reset queue for each cycle otherwise ya get problems.
            idQueue = ids;

            //Iterate through each column in the permutation vector.
            for(int index = 0; index < perTotal; index++)
            {
                //When you have emplaced a single member for it's maximum repeats...
                if(index % empTotal == 0 && index != 0)
                {
                    //...Pop queue to next member
                    idQueue.pop_front();
                    //If you have emplaced the entire queue...
                    if(idQueue.empty())
                    {
                        //...refresh the queue
                        idQueue = ids;
                    }
                }

                /*
                If any members are in the currently indexed combination remove them from
                the queue to avoid repeating instances. This should be done after the
                prior IF-statement to avoid emptying the queue before emplacemnt.
                */
                for(int id:idOrder.at(index))
                {
                    idQueue.remove(id);
                }

                //Push data to idOrder list.
                idOrder.at(index).push_back(idQueue.front());
            }
        }

        //Convert idOrder list to readable results and store it in permutations list.
        for(vector<int> lineRead:idOrder) //Iterate through each permutation in idOrder
        {
            string temp;
            for(int idRead:lineRead) //Iterate through each member ID in the current permutation
            {
                for(Member m:members) //Iterate through members in list
                {
                    if(m.ID == idRead) //Find the member matching the currently read ID
                    {
                        temp += m.text; //Push that members value to a temp string
                        break; //Found member so stop checking member list and loop to next ID.
                    }
                }
            }
            permutations.push_back(temp); //Once entire permutation has been read push string.
        }
    }
};
int PermutationSolver::Member::nextID = 0; //Initialize default value for member struct ID

int main()
{
    PermutationSolver p;
    p.inputSet("abcdef");
    p.Solve();
    p.printResults();
}
