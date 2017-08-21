//
//  Sorters.cpp
//  TypedTests
//
//  Created by Jonathan Ginsburg on 8/21/17.
//  Copyright © 2017 Jonathan Ginsburg. All rights reserved.
//

#include <stdio.h>
#include <vector>

class Sorter {
public:
    virtual std::vector<int> sort(std::vector<int>) = 0;
};

class Merge : public Sorter {
public:
    std::vector<int> sort(std::vector<int> unsorted) {
        if (unsorted.size() == 1) {
            return unsorted;
        }
        else {
            //Split
            std::vector<int> left;
            std::vector<int> right;
            int half = (int)unsorted.size()/2;
            for (int i = 0; i < unsorted.size(); ++i) {
                if (i < half) {
                    left.push_back(unsorted[i]);
                }
                else {
                    right.push_back(unsorted[i]);
                }
            }
            //Sort splitted vectors
            std::vector<int> sortedLeft = this->sort(left);
            std::vector<int> sortedRight = this->sort(right);
            //Merge
            std::vector<int> retVal;
            int leftIndex = 0;
            int rightIndex = 0;
            while (leftIndex < sortedLeft.size() && rightIndex < sortedRight.size()) {
                if (sortedLeft[leftIndex] < sortedRight[rightIndex]) {
                    retVal.push_back(sortedLeft[leftIndex]);
                    ++leftIndex;
                }
                else {
                    retVal.push_back(sortedRight[rightIndex]);
                    ++rightIndex;
                }
            }
            while (leftIndex < sortedLeft.size()) {
                retVal.push_back(sortedLeft[leftIndex++]);
            }
            while (rightIndex < sortedRight.size()) {
                retVal.push_back(sortedRight[rightIndex++]);
            }
            return retVal;
        }
    };
};

class Insertion : public Sorter {
public:
    std::vector<int> sort(std::vector<int> unsorted) {
        for (int i = 1; i < unsorted.size(); ++i) {
            for (int j = (int)unsorted.size() - 1; i <= j; --j) {
                if (unsorted[j - 1] > unsorted[j]) {
                    int tmp = unsorted[j];
                    unsorted[j] = unsorted[j - 1];
                    unsorted[j - 1] = tmp;
                }
            }
        }
        return unsorted;
    }
};

class Bubble : public Sorter {
public:
    std::vector<int> sort(std::vector<int> unsorted) {
        bool swapped = true;
        while (swapped) {
            swapped = false;
            for (int i = 0; i < unsorted.size() - 1; ++i) {
                if (unsorted[i + 1] < unsorted[i]) {
                    int tmp = unsorted[i + 1];
                    unsorted[i + 1] = unsorted[i];
                    unsorted[i] = tmp;
                    swapped = true;
                }
            }
        }
        return unsorted;
    }
};
