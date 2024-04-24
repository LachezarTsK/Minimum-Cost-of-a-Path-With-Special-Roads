
#include <span>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {

    vector<int> minCostPath;

public:
    int minimumCost(const vector<int>& start, const vector<int>& target, const vector<vector<int>>& specialRoads) {
        minCostPath.resize(specialRoads.size());
        calculateMinCostFromStartToEndOfSpecialRoads(start, specialRoads);
        calculateMinCostFromStartToEndOfSpecialRoadsWithGoingBetweenSpecialRoads(specialRoads);
        return calculateMinCostFromStartToTarget(start, target, specialRoads);
    }

private:
    void calculateMinCostFromStartToEndOfSpecialRoads(span<const int>start, span<const vector<int>> specialRoads) {
        for (size_t road = 0; road < specialRoads.size(); ++road) {
            int fromX = specialRoads[road][0];
            int fromY = specialRoads[road][1];

            int toX = specialRoads[road][2];
            int toY = specialRoads[road][3];

            int specialCost = specialRoads[road][4];

            int ordinaryCostFromStart = getOrdinaryCost(start[0], start[1], toX, toY);
            int specialCostFromStart = getOrdinaryCost(start[0], start[1], fromX, fromY) + specialCost;

            minCostPath[road] = min(ordinaryCostFromStart, specialCostFromStart);
        }
    }

    void calculateMinCostFromStartToEndOfSpecialRoadsWithGoingBetweenSpecialRoads(span<const vector<int>> specialRoads) {
        for (size_t firstRoad = 0; firstRoad < specialRoads.size(); ++firstRoad) {
            for (size_t secondRoad = 0; secondRoad < specialRoads.size(); ++secondRoad) {
                if (firstRoad == secondRoad) {
                    continue;
                }
                connectSpecialRoads(firstRoad, secondRoad, specialRoads);
                connectSpecialRoads(secondRoad, firstRoad, specialRoads);
            }
        }
    }

    void connectSpecialRoads(size_t indexFrom, size_t indexTo, span<const vector<int>> specialRoads) {
            int fromX = specialRoads[indexFrom][2];
            int fromY = specialRoads[indexFrom][3];
            int toX = specialRoads[indexTo][0];
            int toSecondRoadY = specialRoads[indexTo][1];

            int specialCostSecondRoad = specialRoads[indexTo][4];
            int ordinaryCostFromFirstToSecond = getOrdinaryCost(fromX, fromY, toX, toSecondRoadY);

            int costFromStart = minCostPath[indexFrom] + ordinaryCostFromFirstToSecond + specialCostSecondRoad;

            minCostPath[indexTo] = min(minCostPath[indexTo], costFromStart);
    }

    int calculateMinCostFromStartToTarget(span<const int> start, span<const int> target, span<const vector<int>> specialRoads) {
        int minCostFromStartToTarget = getOrdinaryCost(start[0], start[1], target[0], target[1]);

        for (size_t road = 0; road < specialRoads.size(); ++road) {
            int endRoadX = specialRoads[road][2];
            int endRoadY = specialRoads[road][3];
            int ordinaryCostFromSpecialRoadEndToTarget = getOrdinaryCost(endRoadX, endRoadY, target[0], target[1]);

            minCostFromStartToTarget = min(minCostFromStartToTarget, minCostPath[road] + ordinaryCostFromSpecialRoadEndToTarget);
        }
        return minCostFromStartToTarget;
    }

    int getOrdinaryCost(int fromX, int fromY, int toX, int toY)const {
        return abs(fromX - toX) + abs(fromY - toY);
    }
};
