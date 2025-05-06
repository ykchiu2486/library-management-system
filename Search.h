#pragma once
#include <vector>
#include <string>
#include <functional>
using namespace std;

template<typename T, typename Key>
long long binarySearch(const vector<T>& vec, const Key& target, long long left, long long right,
    function<string(const T&)> getKey, function<string(const Key&)> getTargetKey) {
    if (left >= right) return -1;

    long long mid = left + (right - left) / 2;
    string midKey = getKey(vec[mid]);
    string targetKey = getTargetKey(target);

    if (midKey == targetKey) {
        return mid;
    }
    else if (midKey > targetKey) {
        return binarySearch(vec, target, left, mid, getKey, getTargetKey);
    }
    else {
        return binarySearch(vec, target, mid + 1, right, getKey, getTargetKey);
    }
}