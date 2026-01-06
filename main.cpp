// main.cpp - The Tetra Viewer (MRI Animation Version)
#include <iostream>
#include <fstream>
#include "VoxelGrid.h"

int main() {
    std::cout << "--- TETRA ENGINE LOADING ---" << std::endl;

    // 1. OPEN THE FILE
    std::ifstream file("model.tetra");
    if (!file.is_open()) {
        std::cout << "Error: Could not open model.tetra!" << std::endl;
        return 1;
    }

    // 2. READ HEADER
    int resolution;
    file >> resolution;
    std::cout << "Resolution Detected: " << resolution << std::endl;

    // 3. INITIALIZE GRID
    VoxelGrid engine(resolution + 2); 

    // 4. LOAD VOXELS
    int x, y, z;
    int count = 0;
    while (file >> x >> y >> z) {
        engine.setVoxel(x, y, z, true);
        count++;
    }
    std::cout << "Imported " << count << " voxels." << std::endl;

    // 5. MRI SCAN ANIMATION
    std::cout << "--- INITIATING SCAN ---" << std::endl;
    
    // Loop through every vertical layer (Z-axis)
    for (int currentZ = 0; currentZ < resolution; currentZ++) {
        
        // Clear the terminal screen (The "Flash")
        std::cout << "\033[2J\033[1;1H"; 
        
        std::cout << "--- LAYER Z = " << currentZ << " / " << resolution << " ---" << std::endl;

        // Draw the Slice
        for (int y = 0; y < resolution; y++) {
            for (int x = 0; x < resolution; x++) {
                if (engine.isSolid(x, y, currentZ)) {
                    std::cout << "[]"; 
                } else {
                    std::cout << "  "; 
                }
            }
            std::cout << std::endl;
        }

        // Slight Pause (so it doesn't flash too fast)
        for(int i=0; i<15000000; i++) {} 
    }

    return 0;
}
