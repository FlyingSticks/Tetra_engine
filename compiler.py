import numpy as np
import trimesh
import struct

def compile_to_tetra(filename, output_name="model.tetra"):
    print(f"Loading {filename}...")
    try:
        mesh = trimesh.load(filename)
    except:
        print("Error: Could not find file!")
        return

    # Normalize
    mesh.vertices -= mesh.center_mass
    mesh.vertices /= np.max(np.linalg.norm(mesh.vertices, axis=1))

    # 1. Generate Lattice (Medium Resolution)
    print("Voxelizing...")
    resolution = 64
    spacing = 2.0 / resolution
    
    # Create the grid
    x = np.arange(-1, 1, spacing)
    y = np.arange(-1, 1, spacing)
    z = np.arange(-1, 1, spacing)
    grid_x, grid_y, grid_z = np.meshgrid(x, y, z)
    points = np.vstack((grid_x.flatten(), grid_y.flatten(), grid_z.flatten())).T
    
    # 2. Filter for FCC Lattice (Integer Inversion check)
    # We map float coordinates back to integer indices to check parity
    # (Simplified: We just check if points are inside mesh)
    
    # Check Inside
    inside_mask = mesh.contains(points)
    voxels = points[inside_mask]
    
    print(f"Found {len(voxels)} solid voxels.")
    
    # 3. Save to .tetra format
    # Format: Simple text file where each line is X Y Z
    # We will map these floats to Integers (0 to 64) for the C++ grid
    print(f"Saving to {output_name}...")
    
    with open(output_name, "w") as f:
        # Write Header (Resolution)
        f.write(f"{resolution}\n")
        
        for v in voxels:
            # Convert float (-1.0 to 1.0) to Integer (0 to 64)
            ix = int((v[0] + 1.0) * (resolution / 2))
            iy = int((v[1] + 1.0) * (resolution / 2))
            iz = int((v[2] + 1.0) * (resolution / 2))
            f.write(f"{ix} {iy} {iz}\n")

    print("Done! Compilation Complete.")

if __name__ == "__main__":
    compile_to_tetra("blocky.obj")
