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
                i++;
            }
        }

        fin.close();
    }

    int num_count = arr.size();

    TCanvas *c1 = new TCanvas("c1", "All data with 1000 bins");
    TCanvas *c2 = new TCanvas("c2", "Bckg removed");
    c1->SetGrid();

    int bin_count = 1000;
    TH1F *h1 = new TH1F("h1", "Song duration", bin_count, 0, 14);

    // Make the histogram
    for (int i = 0; i < num_count; i++)
        h1->Fill(arr[i]);

    TF1 *poiss = new TF1("poiss", "[0]*TMath::Poisson(x,[1])", 6, 14);

    poiss->SetParLimits(0, 180, 5000);
    poiss->SetParLimits(1, 1, 7.5);

    // Let's fit the poisson to the data
    h1->Fit("poiss", "WR", "", 0, 14);
    gStyle->SetOptFit(1111);

    c1->cd();
    h1->Draw("h");

    TH1F *h1_copy = (TH1F *)h1->Clone();

    TH1F *h2 = new TH1F("h2", "Song duration cut", bin_count, 0, 14);

    for (int i = 0; i < bin_count; i++)
    {
        float x = h2->GetBinCenter(i);
        float y = poiss->Eval(x);
        h2->SetBinContent(i, y);
    }

    // subtract function from the hist

    h1_copy->Add(h2, -1);

    c2->cd();
    c2->SetGrid();
    h1_copy->Draw("h");

    // Hmmm... After fitted function removal no clear pattern is seen.
    // Lack of prior knowledge is not helping us in here :/

    return 0;
}
