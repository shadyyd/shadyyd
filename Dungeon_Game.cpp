const int MAX = 200 + 1;
int memory[MAX][MAX];
vector<vector<int>> matrix;
const int OO = 1e8;

// This function calculates the minimum health required to traverse from (r, c) to the bottom-right corner
int minHealth(int r, int c) {
	int rows = matrix.size(), cols = matrix[0].size();

	if (r >= rows || c >= cols)	// Check if we are out of the grid
		return OO;	// Return a big value for minimization, indicating an invalid path

	if (r == rows - 1 && c == cols - 1) {	// Check if we are at the last cell
		if (matrix[r][c] < 0)
			return 1 - matrix[r][c]; // Return the health required to survive if this cell has a negative value
		return 1;	// No health loss is needed to reach the last cell
	}

	auto &ret = memory[r][c]; // Using a reference to the memoization table for efficiency
	if (ret != -1)
		return ret; // If we've already calculated and stored the result, return it

	// Calculate the minimum health required for the next move based on the minimum of moving right and moving down
	int mnHealthMove = min(minHealth(r + 1, c), minHealth(r, c + 1));

	if (matrix[r][c] >= mnHealthMove)
		return ret = 1; // If the cell value is greater than or equal to the minimum health required for the next move, return 1

	return ret = mnHealthMove - matrix[r][c]; // Otherwise, return the minimum health required minus the cell's value
}

// This is a class containing the solution
class Solution {
public:
	// This function is called to calculate the minimum initial health required to enter the dungeon
	int calculateMinimumHP(vector<vector<int>> &dungeon) {
		matrix = dungeon; // Copy the dungeon matrix
		memset(memory, -1, sizeof(memory)); // Initialize the memoization table with -1
		return minHealth(0, 0); // Call the minHealth function starting from the top-left corner
	}
};
