#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

int min3(int a, int b, int c) {
    int m = (a < b) ? a : b;
    return (m < c) ? m : c;
}

vector<double> getNormalizedVector(string str) {
    vector<double> v(26, 0.0);
    for(char c : str) {
        if(isalpha(c)) {
            v[tolower(c) - 'a']++;
        }
    }
    double length = 0.0;
    for(auto val : v) {
        length += val * val;
    }
    length = sqrt(length);
    if(length == 0.0) return v;
    for(double& val : v) {
        val /= length;
    }
    return v;
}

double dot(string s1, string s2) {
    auto v1 = getNormalizedVector(s1);
    auto v2 = getNormalizedVector(s2);
    double dot = 0.0;

    for (int i = 0; i < 26; i++) {
        dot += v1[i] * v2[i];
    }

    return dot;
}

double normalizedLevenshtein(const string& s1, const string& s2) {
    size_t len1 = s1.size(), len2 = s2.size();

    if (len1 == 0 && len2 == 0) return 0.0; 

    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));

    for (size_t i = 0; i <= len1; i++) dp[i][0] = i;
    for (size_t j = 0; j <= len2; j++) dp[0][j] = j;

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (tolower(s1[i - 1] == tolower(s2[j - 1]))) ? 0 : 1;
            dp[i][j] = min3(
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + cost
            );
        }
    }

    int dist = dp[len1][len2];
    return static_cast<double>(dist) / max(len1, len2);
}

double similarity(string s1, string s2, double alpha = 0.4) {
    if(s1.size() == 0 || s2.size() == 0) return 0;
    return alpha * (1 - normalizedLevenshtein(s1, s2)) + (1 - alpha) * dot(s1, s2);
}
