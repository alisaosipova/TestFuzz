#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

void computeLPS(const string& pat, int* lps)
{
    if (pat.empty()) {
        return;
    }

    int j = 0;
    int i = 1;
    lps[0] = 0;

    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0) {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(const string& pat, const string& txt)
{
    if (pat.empty() || txt.empty()) {
        return 0;
    }

    int* lps = new int[pat.size()];
    computeLPS(pat, lps);

    int x = 0;
    int i = 0;
    int j = 0;

    while (i < txt.size()) {
        if (j < pat.size() && pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == pat.size()) {
            ++x;
            j = lps[j - 1];
        }
        else if (i < txt.size() && pat[j] != txt[i]) {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }
    delete[] lps;

    return x;
}

bool isKPeriodic(const string& text, unsigned int K)
{
    if (K == 0 || K > text.size()) {
        return false;
    }

    std::vector<string> temp(K);

    for (unsigned int i = 0; i < K; i++)
        temp[i] = text.substr(i, 1);

    int coincidence = KMPSearch(temp[0], text);

    return coincidence % K == 0;

}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t * Data, size_t Size) {
    if (Size < sizeof(unsigned int)) {
        unsigned int K = 0;
        std::string text;

        int result = isKPeriodic(text, K);
        return result;
    }

    unsigned int K = 0;
    memcpy(&K, Data, sizeof(unsigned int));

    K = K % Size;
    std::string text(reinterpret_cast<const char*>(Data), Size);

    int result = isKPeriodic(text, K);

    std::string pattern = "XYZ"; 

    int* lps = new int[pattern.size()];
    computeLPS(pattern, lps);
    delete[] lps;

    return result;
}

