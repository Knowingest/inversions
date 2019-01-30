//Harrison Hill  -  hmh16c
//cop4531 homework #1
//inversion counter program

//implemented using the recursive sortAndCount() / mergeAndCount() process as found in class notes

//There are a number of lines commented out.  These lines are just cout statements used for testing.
//these printouts are what I used to find infinite loops or crashes as we recurse through the input.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

pair<long, vector<long> > sortAndCount(vector<long>);
pair<long, vector<long> > mergeAndCount(vector<long> a, vector<long> b);


        //was used for testing, to check for infinite loops
//long freezeCounter = 0;

int main(int argc, char* argv[])
{
        ifstream input(argv[1]);
        long token;
        vector<long> listA;

        if (input.is_open())
        {
                while (input >> token)
                {
                        //cout << token << endl;
                        listA.push_back(token);
                }
                input.close();
                /*for (long i = 0; i < listA.size(); i++)
                {
                        cout << listA[i] << endl;
                }*/
        }
        else
        {
                cout << "couldn't open file" << endl;
                return 1;
        }

        //cout << "size of a " << listA.size() << endl;

        long sizeA = listA.size();

        vector<long> listB;

                //cut listA in half, call new half listB
        for (long i = sizeA / 2; i < sizeA; i++)
        {
                listB.push_back(listA[i]);
        }
        for (long i = sizeA / 2; i < sizeA; i++)
        {
                listA.pop_back();
        }

        cout << "Size of input: " << listA.size() + listB.size() << endl;

                //merge them and count the inversions, recursively.
        pair<long, vector<long> > results = mergeAndCount(listA, listB);

        /*
        for (long i = 0; i < results.second.size(); i++)
                {
                        cout << results.second[i] << endl;
                }
        */

        cout << "number of inversions: " << results.first << endl;
        return 0;
}


        //splits one list into two, then merges them.

        //return type is in the format (number_of_inversions, sorted_list)
pair<long, vector<long> > sortAndCount(vector<long> listA)
{
        //cout << ++freezeCounter << endl;
        //cout << "sorting with size: " << listA.size() << endl;
        if (listA.size() == 1) return make_pair(0, listA);

        //cout << "making vector..." << endl;

        long sizeA = listA.size();

        vector<long> listB;
        for (long i = sizeA / 2; i < sizeA; i++)
        {
                listB.push_back(listA[i]);
                //cout << "pushing " << listA[i] << endl;
        }
        for (long i = sizeA / 2; i < sizeA; i++)
        {
                //cout << "popping a..." << endl;
                listA.pop_back();
        }

        return mergeAndCount(listA, listB);
}

        //takes two lists, sorts them recursively, and merges them together.

        //return type is in the format (number_of_inversions, sorted_and_merged_list)
pair<long, vector<long> > mergeAndCount(vector<long> a, vector<long> b)
{
        //cout << ++freezeCounter << endl;
        //cout << "merging..." << endl;

        pair<long, vector<long> > pairA;
        pair<long, vector<long> > pairB;

        pairA = sortAndCount(a);
        pairB = sortAndCount(b);

        //cout << "done sorting..." << endl;

        long numInversionsA = pairA.first;
        long numInversionsB = pairB.first;
        long numInversionsC = 0;
        
        vector<long> c;

                //now to combine the lists

                //while both lists have elements left...
        while(1)
        {
                //cout << "inside while loop..." << endl;
                //cout << "size of A = " << pairA.second.size() << endl;
                //cout << "size of B = " << pairB.second.size() << endl;
                        
                        //if A is empty
                if (pairA.second.empty())
                {
                                //and B is empty, we break
                        if (pairB.second.empty()) break;
                        else
                        {
                                        //if just B has elements, add them to C
                                c.push_back(pairB.second.front());
                                pairB.second.erase(pairB.second.begin());
                                continue;
                        }
                }
                        //if just B is empty, add elements in A to C
                if (pairB.second.empty())
                {
                        c.push_back(pairA.second.front());
                        pairA.second.erase(pairA.second.begin());
                        continue;
                }

                //cout << "both lists aren't empty..." << endl;

                //if A[0] < B[0], add A[0] to C
                if (pairA.second.front() < pairB.second.front())
                {
                        c.push_back(pairA.second.front());
                        pairA.second.erase(pairA.second.begin());
                }
                //if A[0] > B[0], B[0] is inverted with every element in A
                //so we count the inversions, and add B[0] to C
                else if (pairA.second.front() > pairB.second.front())
                {
                        numInversionsC += pairA.second.size();
                        c.push_back(pairB.second.front());
                        pairB.second.erase(pairB.second.begin());
                }
                //if they are equal, we just add A[0] to C  (this choice is irrelevant)
                else
                {
                        c.push_back(pairA.second.front());
                        pairA.second.erase(pairA.second.begin());
                }
        }

                //we now count up the total inversions
        long inversionTotal = numInversionsA + numInversionsB + numInversionsC;
                //and return a pair of the inversion count and the new list
        return make_pair(inversionTotal, c);
}