#include <iostream> // Include the necessary library for input and output

using namespace std; // Using the standard namespace for cout, cin, etc.

const int rows = 20; // Define a constant for the number of rows in the grid

const int cols = 20; // Define a constant for the number of columns in the grid

void initializeGrid(bool grid[rows][cols], int liveCellCoordinates[][2], int numLiveCells) {
	
    // Function to initialize the grid with live cells based on provided coordinates
    for (int i = 0; i < numLiveCells; ++i) {
    	
        grid[liveCellCoordinates[i][0]][liveCellCoordinates[i][1]] = true;
        
    }
}

void printGrid(bool grid[rows][cols]) {
	
    // Function to print the grid, displaying live cells as 'O' and dead cells as '.'
    for (int i = 0; i < rows; ++i) {
    	
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]) {
            	
                cout << "O "; // Print 'O' for live cells
            } else {
            	
                cout << ". "; // Print '.' for dead cells
            }
        }
        cout << endl; // Move to the next line after printing each row
    }
}

bool shouldSurvive(int liveNeighbors) {
	
    // Function to determine if a live cell should survive based on the number of live neighbors
    
    return liveNeighbors == 2 || liveNeighbors == 3;
}

bool shouldBirth(int liveNeighbors) {
	
    // Function to determine if a dead cell should become alive based on the number of live neighbors
    
    return liveNeighbors == 3;
}

void updateGrid(bool grid[rows][cols]) {
	
    // Function to update the grid for the next generation
    
    bool newGrid[rows][cols] = {false}; // Create a new grid to store the updated state
    for (int i = 0; i < rows; ++i) {
    	
        for (int j = 0; j < cols; ++j) {
        	
            int liveNeighbors = 0; // Counter for live neighbors of each cell
            
            int changeInRow[] = {-1, -1, -1,  0, 0,  1, 1, 1}; // Changes in row for neighbor cells
            
            int changeInColumn[] = {-1,  0,  1, -1, 1, -1, 0, 1}; // Changes in column for neighbor cells
            
            // Loop through all neighboring cells
            for (int k = 0; k < 8; ++k) {
            	
                int r = i + changeInRow[k]; // Calculate the row index of the neighbor
                
                int c = j + changeInColumn[k]; // Calculate the column index of the neighbor
                
                // Check if the neighbor cell is within the grid boundaries and alive
                
                if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c]) {
                	
                    liveNeighbors++; // Increment the live neighbor count
                }
            }
            // Update cell state based on the rules of the game
            if (grid[i][j]) {
            	
                if (shouldSurvive(liveNeighbors)) {
                	
                    newGrid[i][j] = true; // Cell survives to the next generation
                    
                } else {
                    newGrid[i][j] = false; // Cell dies due to underpopulation or overpopulation
                }
            } else {
                if (shouldBirth(liveNeighbors)) {
                	
                    newGrid[i][j] = true; // Dead cell becomes alive due to reproduction
                }
            }
        }
    }
    // Update the original grid with the new state
    for (int i = 0; i < rows; ++i) {
    	
        for (int j = 0; j < cols; ++j) {
        	
            grid[i][j] = newGrid[i][j];
        }
    }
}

int countLiveCells(bool grid[rows][cols], int liveCellCoordinates[][2]) {
	
    // Function to count the number of live cells and their coordinates
    int liveCellCount = 0; // Counter for live cells
    
    int index = 0; // Index for liveCellCoordinates array
    
    for (int i = 0; i < rows; ++i) {
    	
        for (int j = 0; j < cols; ++j) {
        	
            if (grid[i][j]) {
                liveCellCount++; // Increment live cell count
                
                // Store coordinates of live cell
                liveCellCoordinates[index][0] = i;
                
                liveCellCoordinates[index][1] = j;
                
                index++; // Move to the next index
            }
        }
    }
    return liveCellCount; // Return the total count of live cells
}

void findDeadNeighbors(bool grid[rows][cols], int deadNei[][2], int& deadNeiSize) {// Function to find dead neighbors of live cells
	
    
    int changeInRow[] = {-1, -1, -1,  0, 0,  1, 1, 1}; // Changes in row for neighbor cells
    
    int changeInColumn[] = {-1,  0,  1, -1, 1, -1, 0, 1}; // Changes in column for neighbor cells
    
    bool visited[rows][cols] = {false}; // Array to mark visited cells
    
    int newDeadNeiSize = 0; // Counter for dead neighbor cells
    
    for (int i = 0; i < rows; ++i) {
    	
        for (int j = 0; j < cols; ++j) {
        	
            if (grid[i][j]) { // Check if the cell is alive
            
                // Check the neighbors of the current cell
                for (int k = 0; k < 8; ++k) {
                	
                    int r = i + changeInRow[k]; // Calculate the row index of the neighbor
                    
                    int c = j + changeInColumn[k]; // Calculate the column index of the neighbor
                    
            if (r >= 0 && r < rows && c >= 0 && c < cols && !grid[r][c] && !visited[r][c]) { // Check if the neighbor cell is within the grid boundaries, dead, and unvisited
                    	
                        deadNei[newDeadNeiSize][0] = r; // Store the row index of the dead neighbor
                        
                        deadNei[newDeadNeiSize][1] = c; // Store the column index of the dead neighbor
                        
                        newDeadNeiSize++; // Increment the counter for dead neighbor cells
                        
                        
                        visited[r][c] = true; // Mark the neighbor cell as visited
                    }
                }
            }
        }
    }
    deadNeiSize = newDeadNeiSize; // Update the total count of dead neighbor cells
}

void countLiveCellNeighborsForDeadNeighbors(bool grid[rows][cols], int deadNei[][2], int deadNeiSize, int liveCounts[]) {
	
    // Function to count live cell neighbors for dead neighbors
    
    int changeInRow[] = {-1, -1, -1,  0, 0,  1, 1, 1}; // Changes in row for neighbor cells
    
    int changeInColumn[] = {-1,  0,  1, -1, 1, -1, 0, 1}; // Changes in column for neighbor cells
    for (int i = 0; i < deadNeiSize; ++i) {
    	
        int count = 0; // Counter for live cell neighbors of a dead neighbor
        
        for (int k = 0; k < 8; ++k) {
        	
            int r = deadNei[i][0] + changeInRow[k]; // Calculate the row index of the neighbor
            
            int c = deadNei[i][1] + changeInColumn[k]; // Calculate the column index of the neighbor
            
            // Check if the neighbor cell is within the grid boundaries and alive
            if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c]) {
            	
                count++; // Increment the counter for live cell neighbors
            }
        }
        liveCounts[i] = count; // Store the count of live cell neighbors for the dead neighbor
    }
}

void printLiveCellCount(bool grid[rows][cols]) {
    // Function to print the count of live cells and their coordinates
    
    int liveCellCoordinates[rows * cols][2]; // Array to store the coordinates of live cells
    
    int liveCellCount = countLiveCells(grid, liveCellCoordinates); // Get the count of live cells
    
    cout << "Live Cell Count: " << liveCellCount << endl; // Print the count of live cells
    
    cout << "Coordinates of Live Cells:" << endl; // Print the coordinates of live cells
    
    for (int i = 0; i < liveCellCount; ++i) {
    	
        cout << "(" << liveCellCoordinates[i][0] << ", " << liveCellCoordinates[i][1] << ")" << endl;
    }
}

void printDeadNeighbors(bool grid[rows][cols]) { // Function to print the coordinates of dead neighbors of live cells
    
    int deadNei[rows * cols][2]; // Array to store the coordinates of dead neighbors
    
    int deadNeiSize = 0; // Variable to store the total count of dead neighbors
    
    findDeadNeighbors(grid, deadNei, deadNeiSize); // Find the dead neighbors of live cells
    
    cout << "Dead Neighbors:" << endl; // Print the heading for dead neighbors
    
    for (int i = 0; i < deadNeiSize; ++i) {
    	
        cout << "Dead Neighbor " << i + 1 << " at (" << deadNei[i][0] << ", " << deadNei[i][1] << ")" << endl;
    }
}

void printLiveCellNeighborsForDead(bool grid[rows][cols]) {
	
    // Function to print the count of live cell neighbors for each dead neighbor
    
    int deadNei[rows * cols][2]; // Array to store the coordinates of dead neighbors
    
    int deadNeiSize = 0; // Variable to store the total count of dead neighbors
    
    findDeadNeighbors(grid, deadNei, deadNeiSize); // Find the dead neighbors of live cells
    
    int liveCountsDeadNei[rows * cols]; // Array to store the count of live cell neighbors for dead neighbors
    
    countLiveCellNeighborsForDeadNeighbors(grid, deadNei, deadNeiSize, liveCountsDeadNei); // Count live cell neighbors for dead neighbors
    
    cout << "Live Cell Neighbors Count for Dead Neighbors:" << endl; // Print the heading for live cell neighbors of dead neighbors
    
    for (int i = 0; i < deadNeiSize; ++i) {
    	
        cout << "Dead Neighbor " << i + 1 << " at (" << deadNei[i][0] << ", " << deadNei[i][1] << "): " << liveCountsDeadNei[i] << endl;
        
    }
}

void updateGridForGenerations(bool grid[rows][cols], int generations) {
	
    // Function to update the grid for a specified number of generations and print each generation's grid
    
    for (int gen = 1; gen <= generations; ++gen) {
    	
        cout << "Generation " << gen << " Grid:" << endl; // Print the current generation number
        
        updateGrid(grid); // Update the grid for the next generation
        
        printGrid(grid); // Print the updated grid
        
        printLiveCellCount(grid); // Print the count and coordinates of live cells
        
        printDeadNeighbors(grid); // Print the coordinates of dead neighbors of live cells
        
        printLiveCellNeighborsForDead(grid); // Print the count of live cell neighbors for dead neighbors
        
    }
}

void getInput(int& numLiveCells, int liveCellCoordinates[][2]) {
	
    // Function to get input from the user: number of live cells and their coordinates
    
    cout << "Enter the number of cells in the object: "; // Prompt for input
    
    cin >> numLiveCells; // Read the number of live cells from the user
    
    cout << "Enter the coordinates for the cells in the object (row column):" << endl; // Prompt for input
    
    for (int i = 0; i < numLiveCells; ++i) {
    	
        cout << "Cell " << i + 1 << ":" << endl; // Prompt for input
        
        cin >> liveCellCoordinates[i][0] >> liveCellCoordinates[i][1]; // Read the coordinates of live cells from the user
    }
}

int main() {
	
    bool grid[rows][cols] = {false}; // Initialize the grid with all cells dead
    
    int numLiveCells; // Variable to store the number of live cells
    
    int liveCellCoordinates[rows * cols][2]; // Array to store the coordinates of live cells
    
    getInput(numLiveCells, liveCellCoordinates); // Get input: number of live cells and their coordinates
    
    initializeGrid(grid, liveCellCoordinates, numLiveCells); // Initialize the grid with live cells
    
    cout << "Initial Grid:" << endl; // Print the heading for the initial grid
    
    printGrid(grid); // Print the initial grid
    
    int generations; // Variable to store the number of generations
    
    cout << "Enter the number of generations: "; // Prompt for input
    
    cin >> generations; // Read the number of generations from the user
    
    updateGridForGenerations(grid, generations); // Update the grid for the specified number of generations
    
    return 0; // Indicate successful program execution
}

