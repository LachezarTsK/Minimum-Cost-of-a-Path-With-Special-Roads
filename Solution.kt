
import kotlin.math.abs
import kotlin.math.min

class Solution {

    private lateinit var minCostPath: IntArray;

    fun minimumCost(start: IntArray, target: IntArray, specialRoads: Array<IntArray>): Int {
        minCostPath = IntArray(specialRoads.size);
        calculateMinCostFromStartToEndOfSpecialRoads(start, specialRoads);
        calculateMinCostFromStartToEndOfSpecialRoadsWithGoingBetweenSpecialRoads(specialRoads);
        return calculateMinCostFromStartToTarget(start, target, specialRoads);
    }

    private fun calculateMinCostFromStartToEndOfSpecialRoads(start: IntArray, specialRoads: Array<IntArray>) {
        for (road in specialRoads.indices) {
            val fromX = specialRoads[road][0];
            val fromY = specialRoads[road][1];

            val toX = specialRoads[road][2];
            val toY = specialRoads[road][3];

            val specialCost = specialRoads[road][4];

            val ordinaryCostFromStart = getOrdinaryCost(start[0], start[1], toX, toY);
            val specialCostFromStart = getOrdinaryCost(start[0], start[1], fromX, fromY) + specialCost;

            minCostPath[road] = min(ordinaryCostFromStart, specialCostFromStart);
        }
    }

    private fun calculateMinCostFromStartToEndOfSpecialRoadsWithGoingBetweenSpecialRoads(specialRoads: Array<IntArray>) {
        for (firstRoad in specialRoads.indices) {
            for (secondRoad in specialRoads.indices) {
                if (firstRoad == secondRoad) {
                    continue;
                }
                connectSpecialRoads(firstRoad, secondRoad, specialRoads);
                connectSpecialRoads(secondRoad, firstRoad, specialRoads);
            }
        }
    }

    private fun connectSpecialRoads(indexFrom: Int, indexTo: Int, specialRoads: Array<IntArray>) {
        val fromX = specialRoads[indexFrom][2];
        val fromY = specialRoads[indexFrom][3];
        val toX = specialRoads[indexTo][0];
        val toSecondRoadY = specialRoads[indexTo][1];

        val specialCostSecondRoad = specialRoads[indexTo][4];
        val ordinaryCostFromFirstToSecond = getOrdinaryCost(fromX, fromY, toX, toSecondRoadY);

        val costFromStart = minCostPath[indexFrom] + ordinaryCostFromFirstToSecond + specialCostSecondRoad

        minCostPath[indexTo] = min(minCostPath[indexTo], costFromStart);
    }

    private fun calculateMinCostFromStartToTarget(
        start: IntArray,
        target: IntArray,
        specialRoads: Array<IntArray>
    ): Int {
        var minCostFromStartToTarget = getOrdinaryCost(start[0], start[1], target[0], target[1]);

        for (road in specialRoads.indices) {
            val endRoadX = specialRoads[road][2];
            val endRoadY = specialRoads[road][3];
            val ordinaryCostFromSpecialRoadEndToTarget = getOrdinaryCost(endRoadX, endRoadY, target[0], target[1]);

            minCostFromStartToTarget = min(
                minCostFromStartToTarget, minCostPath[road] + ordinaryCostFromSpecialRoadEndToTarget
            );
        }
        return minCostFromStartToTarget;
    }

    private fun getOrdinaryCost(fromX: Int, fromY: Int, toX: Int, toY: Int): Int {
        return abs(fromX - toX) + abs(fromY - toY);
    }
}
