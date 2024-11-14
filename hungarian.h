#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

class HungarianAlgorithm {
    private:
        std::vector<std::vector<int>> costMatrix;
        int n_y;
        int n_x;
        std::vector<int> labelY;
        std::vector<int> labelX;
        std::vector<int> matchY;    // Matching from Y to X
        std::vector<int> matchX;    // Matching from X to Y
        std::vector<bool> visitedY; // DFS visited marks
        std::vector<bool> visitedX;
        bool transpose = false;

        void init();
        bool findPath(int y);
        void updateLabels();

    public:
     HungarianAlgorithm(const std::vector<std::vector<int>>& costs);
        std::vector<std::pair<int, int>> solve();
};