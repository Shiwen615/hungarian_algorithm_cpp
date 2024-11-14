#include "hungarian.h"
// namespace HungarianAlgorithm {

void HungarianAlgorithm::init() {
    labelY.assign(n_y, 0);
    labelX.assign(n_x, 0);

    // Initialize Y labels with row minimums
    for (int y = 0; y < n_y; y++){
        labelY[y] = costMatrix[y][0];
        for (int x = 1; x < n_x; x++) {
            labelY[y] = std::min(labelY[y], costMatrix[y][x]);
        }
    }

    matchY.assign(n_y, -1);
    matchX.assign(n_x, -1);
}

bool HungarianAlgorithm::findPath(int y) {
    visitedY[y] = true;

    for (int x = 0; x < n_x; x++) {
        if (visitedX[x]) continue;

        // Check if edge exists in equality subgraph
        if (labelY[y] + labelX[x] == costMatrix[y][x]) {
            visitedX[x] = true;

            // If x is unmatched or we can find an augmenting path through x's match
            if (matchX[x] == -1 || findPath(matchX[x])) {
                matchX[x] = y;
                matchY[y] = x;
                return true;
            }
        }
    }
    return false;
}

void HungarianAlgorithm::updateLabels() {
    int delta = std::numeric_limits<int>::max();

    // Find the minimum delta value
    for (int y = 0; y < n_y; y++) {
        if (!visitedY[y]) continue;

        for (int x = 0; x < n_x; x++) {
            if (visitedX[x]) continue;
            delta = std::min(delta,
                             costMatrix[y][x] - labelY[y] - labelX[x]);
        }
    }

    // Update vertex labels
    for (int y = 0; y < n_y; y++) {
        if (visitedY[y]) labelY[y] += delta;
    }

    for (int x = 0; x < n_x; x++) {
        if (visitedX[x]) labelX[x] -= delta;
    }
}

HungarianAlgorithm::HungarianAlgorithm(const std::vector<std::vector<int>>& costs)
    : n_y(costs.size()), n_x(costs[0].size()) {
    if (n_y > n_x) {
        // transpose
        transpose = true;
        std::swap(n_y, n_x);

        costMatrix.resize(n_y, std::vector<int>(n_x, 0));
        for (size_t y = 0; y < n_y; y++) {
            for (size_t x = 0; x < n_x; x++) {
                costMatrix[y][x] = costs[x][y];
            }
        }
    } else {
        costMatrix = costs;
    }

    init();
}

std::vector<std::pair<int, int>> HungarianAlgorithm::solve() {
    // Find augmenting path for each unmatched Y vertex
    for (int y = 0; y < n_y; y++) {
        while (matchY[y] == -1) {   // Continue until a match is found
            visitedY.assign(n_y, false);
            visitedX.assign(n_x, false);

            if (findPath(y)) break;   // Found augmenting path

            // No augmenting path found, update labels
            updateLabels();
        }
    }

    // Collect all matches
    std::vector<std::pair<int, int>> matches;
    for (int y = 0; y < n_y; y++) {
        if (matchY[y] != -1) {
            if (transpose) {
                matches.emplace_back(matchY[y], y);
            } else {
                matches.emplace_back(y, matchY[y]);
            }
        }
    }
    return matches;
}

// }