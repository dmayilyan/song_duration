#include "TF1.h"
#include "TCanvas.h"
#include <vector>

int main()
{
    string details;
    fstream fin;

    fin.open("duration.csv", ios::in);

    // int data_count = 10e6;
    // float *arr = new float(data_count);
    vector<double> arr;

    if (fin.is_open())
    {
        while (fin.good())
        {
            getline(fin, details, ',');
            stringstream ss(details);
            string token;

            int i = 0;
            while (getline(ss, token, '\n'))
            {
                if (i % 2 == 0)
                    arr.push_back(stod(token));
                // cout << stod(token) << "\n";
                i++;
            }
        }

        fin.close();
    }

    TCanvas canvas = TCanvas("canvas");
    int num_count = arr.size();

    TCanvas *c1 = new TCanvas("c1", "Example");

    TH1F *h1 = new TH1F("h1", "Song duration", num_count, 0, 14);

    for (int i = 0; i < num_count; i++)
        h1->Fill(arr[i]);
    TF1 *poiss = new TF1("poiss", "[0]*TMath::Poisson(x,[1]) + gaus(2)", 0, 14);

    poiss->SetParLimits(0, 180, 350);
    poiss->SetParLimits(1, 3, 7.5);
    poiss->SetParLimits(2, 150, 200);
    poiss->SetParLimits(3, 2, 7);
    poiss->SetParLimits(4, 0.5, 2.);


    h1->Fit("poiss", "WR", "", 0, 14);
    gStyle->SetOptFit(1111);


    // canvas.Draw();
    h1->Draw("h");

    return 0;
}
