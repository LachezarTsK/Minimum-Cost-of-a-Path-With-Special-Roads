
using System;

public class Solution
{
    int[]? minCostPath;

    public int MinimumCost(int[] start, int[] target, int[][] specialRoads)
    {
        minCostPath = new int[specialRoads.Length];
        CalculateMinCostFromStartToEndOfSpecialRoads(start, specialRoads);
        CalculateMinCostFromStartToEndOfSpecialRoadsWithGoingBetweenSpecialRoads(specialRoads);
        return CalculateMinCostFromStartToTarget(start, target, specialRoads);
    }

    private void CalculateMinCostFromStartToEndOfSpecialRoads(int[] start, int[][] specialRoads)
    {
        for (int road = 0; road < specialRoads.Length; ++road)
        {
            int fromX = specialRoads[road][0];
            int fromY = specialRoads[road][1];

            int toX = specialRoads[road][2];
            int toY = specialRoads[road][3];

            int specialCost = specialRoads[road][4];

            int ordinaryCostFromStart = GetOrdinaryCost(start[0], start[1], toX, toY);
            int specialCostFromStart = GetOrdinaryCost(start[0], start[1], fromX, fromY) + specialCost;

            minCostPath[road] = Math.Min(ordinaryCostFromStart, specialCostFromStart);
        }
    }

    private void CalculateMinCostFromStartToEndOfSpecialRoadsWithGoingBetweenSpecialRoads(int[][] specialRoads)
    {
        for (int firstRoad = 0; firstRoad < specialRoads.Length; ++firstRoad)
        {
            for (int secondRoad = 0; secondRoad < specialRoads.Length; ++secondRoad)
            {
                if (firstRoad == secondRoad)
                {
                    continue;
                }
                ConnectSpecialRoads(firstRoad, secondRoad, specialRoads);
                ConnectSpecialRoads(secondRoad, firstRoad, specialRoads);
            }
        }
    }

    private void ConnectSpecialRoads(int indexFrom, int indexTo, int[][] specialRoads)
    {
        int fromX = specialRoads[indexFrom][2];
        int fromY = specialRoads[indexFrom][3];
        int toX = specialRoads[indexTo][0];
        int toSecondRoadY = specialRoads[indexTo][1];

        int specialCostSecondRoad = specialRoads[indexTo][4];
        int ordinaryCostFromFirstToSecond = GetOrdinaryCost(fromX, fromY, toX, toSecondRoadY);

        int costFromStart = minCostPath[indexFrom] + ordinaryCostFromFirstToSecond + specialCostSecondRoad;

        minCostPath[indexTo] = Math.Min(minCostPath[indexTo], costFromStart);
    }

    private int CalculateMinCostFromStartToTarget(int[] start, int[] target, int[][] specialRoads)
    {
        int minCostFromStartToTarget = GetOrdinaryCost(start[0], start[1], target[0], target[1]);

        for (int road = 0; road < specialRoads.Length; ++road)
        {
            int endRoadX = specialRoads[road][2];
            int endRoadY = specialRoads[road][3];
            int ordinaryCostFromSpecialRoadEndToTarget = GetOrdinaryCost(endRoadX, endRoadY, target[0], target[1]);

            minCostFromStartToTarget = Math.Min(minCostFromStartToTarget, minCostPath[road] + ordinaryCostFromSpecialRoadEndToTarget);
        }
        return minCostFromStartToTarget;
    }

    private int GetOrdinaryCost(int fromX, int fromY, int toX, int toY)
    {
        return Math.Abs(fromX - toX) + Math.Abs(fromY - toY);
    }
}
