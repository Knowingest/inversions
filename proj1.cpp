#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

pair<long, vector<long> > sortAndCount(vector<long>);
pair<long, vector<long> > mergeAndCount(vector<long> a, vector<long> b);

long freezeCounter = 0;

int main(int argc, char* argv[])
{
        ifstream input(argv[1]);
        long token;

        long arraySize = 0;
        long numInversions = 0;
        vector<long> listA;

        if (input.is_open())
        {
                while (input >> token)
                {
                        //cout << token << endl;
                        listA.push_back(token);
                }
                input.close();
                for (long i = 0; i < listA.size(); i++)
                {
                        cout << listA[i] << endl;
                }
        }
        else cout << "couldn't open file" << endl;

        cout << "size of a " << listA.size() << endl;

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

        cout << "size of A " << listA.size() << "\nsize of B " << listB.size() << endl;

        pair<long, vector<long> > results = mergeAndCount(listA, listB);

        for (long i = 0; i < results.second.size(); i++)
                {
                        cout << results.second[i] << endl;
                }
        cout << "number of inversions: " << results.first << endl;

        //now the input has been split into two arrays




        return 0;
}

pair<long, vector<long> > sortAndCount(vector<long> listA)
{
        cout << ++freezeCounter << endl;
        if (listA.size() == 1) return make_pair(0, listA);

        vector<long> AsubB;

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
pair<long, vector<long> > mergeAndCount(vector<long> a, vector<long> b)
{
        cout << ++freezeCounter << endl;
        pair<long, vector<long> > pairA;
        pair<long, vector<long> > pairB;

        pairA = sortAndCount(a);
        pairB = sortAndCount(b);

        long numInversionsA = pairA.first;
        long numInversionsB = pairB.first;
        long numInversionsC = 0;
        
        vector<long> c;

                //now to combine the lists

                //while both lists have elements left...
        while(1)
        {
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

                //if both lists still have elements...

                if (pairA.second.front() < pairB.second.front())
                {
                        c.push_back(pairA.second.front());
                        pairA.second.erase(pairA.second.begin());
                }
                else if (pairA.second.front() > pairB.second.front())
                {
                        numInversionsC += pairA.second.size();
                        c.push_back(pairB.second.front());
                        pairB.second.erase(pairB.second.begin());
                }
        }

        long inversionTotal = numInversionsA + numInversionsB + numInversionsC;
        return make_pair(inversionTotal, c);
}