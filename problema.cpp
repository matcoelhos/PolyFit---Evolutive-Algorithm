#include "problema.h"

using namespace std;

PolyFitP::PolyFitP(string file)
{
    ifstream infile(file);
    string line;
    while (getline(infile, line))
    {
        istringstream i(line);

        char control;
        i >> control;
        if (control == 'p')
        {
            vector<double> pair;
            double n1, n2;
            i >> n1 >> n2;
            pair.push_back(n1);
            pair.push_back(n2);
            pairs.push_back(pair);
        }
        else
        {
            cout << "GEN:" << line << endl;
        }
    }
    infile.close();
}

void PolyFitP::disp()
{
    for (int i = 0; i < pairs.size(); i++)
    {
        cout << "[" << pairs[i][0] << "," << pairs[i][1] << "]" << endl;
    }
}
