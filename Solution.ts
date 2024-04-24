
function minimumCost(start: number[], target: number[], specialRoads: number[][]): number {
    this.minCostPath = new Array<number>(specialRoads.length);
    calculateMinCostFromStartToEndOfSpecialRoads(start, specialRoads);
    calculateMinCostFromStartToEndOfSpecialRoadsWithGoingBetweenSpecialRoads(specialRoads);
    return calculateMinCostFromStartToTarget(start, target, specialRoads);
};

function calculateMinCostFromStartToEndOfSpecialRoads(start: number[], specialRoads: number[][]): void {
    for (let road = 0; road < specialRoads.length; ++road) {
        const fromX = specialRoads[road][0];
        const fromY = specialRoads[road][1];

        const toX = specialRoads[road][2];
        const toY = specialRoads[road][3];

        const specialCost = specialRoads[road][4];

        const ordinaryCostFromStart = getOrdinaryCost(start[0], start[1], toX, toY);
        const specialCostFromStart = getOrdinaryCost(start[0], start[1], fromX, fromY) + specialCost;

        this.minCostPath[road] = Math.min(ordinaryCostFromStart, specialCostFromStart);
    }
}

function calculateMinCostFromStartToEndOfSpecialRoadsWithGoingBetweenSpecialRoads(specialRoads): void {
    for (let firstRoad = 0; firstRoad < specialRoads.length; ++firstRoad) {
        for (let secondRoad = 0; secondRoad < specialRoads.length; ++secondRoad) {
            if (firstRoad === secondRoad) {
                continue;
            }
            connectSpecialRoads(firstRoad, secondRoad, specialRoads);
            connectSpecialRoads(secondRoad, firstRoad, specialRoads);
        }
    }
}

function connectSpecialRoads(indexFrom: number, indexTo: number, specialRoads: number[][]) {
    const fromX = specialRoads[indexFrom][2];
    const fromY = specialRoads[indexFrom][3];
    const toX = specialRoads[indexTo][0];
    const toSecondRoadY = specialRoads[indexTo][1];

    const specialCostSecondRoad = specialRoads[indexTo][4];
    const ordinaryCostFromFirstToSecond = getOrdinaryCost(fromX, fromY, toX, toSecondRoadY);

    const costFromStart = this.minCostPath[indexFrom] + ordinaryCostFromFirstToSecond + specialCostSecondRoad;

    this.minCostPath[indexTo] = Math.min(this.minCostPath[indexTo], costFromStart);
}

function calculateMinCostFromStartToTarget(start: number[], target: number[], specialRoads: number[][]): number {
    let minCostFromStartToTarget = getOrdinaryCost(start[0], start[1], target[0], target[1]);

    for (let road = 0; road < specialRoads.length; ++road) {
        const endRoadX = specialRoads[road][2];
        const endRoadY = specialRoads[road][3];
        const ordinaryCostFromSpecialRoadEndToTarget = getOrdinaryCost(endRoadX, endRoadY, target[0], target[1]);

        minCostFromStartToTarget = Math.min(minCostFromStartToTarget, this.minCostPath[road] + ordinaryCostFromSpecialRoadEndToTarget);
    }
    return minCostFromStartToTarget;
}

function getOrdinaryCost(fromX: number, fromY: number, toX: number, toY: number): number {
    return Math.abs(fromX - toX) + Math.abs(fromY - toY);
}
