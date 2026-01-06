// VoxelGrid.h - The Memory Block
#ifndef VOXELGRID_H
#define VOXELGRID_H

#include <vector>

class VoxelGrid {
public:
    int size;                
    std::vector<bool> data;  

    // Constructor: Creates the empty box
    VoxelGrid(int s) : size(s) {
        data.resize(size * size * size, false); 
    }

    // The Helper: Converts 3D (x,y,z) into 1D Index
    int getIndex(int x, int y, int z) {
        return x + (y * size) + (z * size * size);
    }

    // The Setter: Turn a voxel ON
    void setVoxel(int x, int y, int z, bool value) {
        if (x >= 0 && x < size && y >= 0 && y < size && z >= 0 && z < size) {
            data[getIndex(x, y, z)] = value;
        }
    }

    // The Getter: Is this spot solid?
    bool isSolid(int x, int y, int z) {
        if (x < 0 || x >= size || y < 0 || y >= size || z < 0 || z >= size) {
            return false;
        }
        return data[getIndex(x, y, z)];
    }

    // THE INTEGER INVERSION (Claim 2)
    bool isValidLatticePoint(int x, int y, int z) {
        return (x + y + z) % 2 == 0;
    }
};

#endif
