#pragma once
#include <iostream>


class domino

{
private:
		int left;
		int right;
public:
    domino() {
        // Initialize with default values, e.g., 0 and 0
        left = 0;
        right = 0;
    }
    domino(int l, int r) : left(l), right(r) {}

    void display() const {
          std::cout << "[" << left << "|" << right << "]";
    }

    bool matches(const domino& other) const {
        return (left == other.left || left == other.right ||
            right == other.left || right == other.right);
    }

    int getLeft() const { return left; }
    int getRight() const { return right; }
    
};

