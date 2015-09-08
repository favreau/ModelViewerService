/*
 *
 * Demonstrates how to load and display an Wavefront OBJ file.
 * Using triangles and normals as static object. No texture mapping.
 * https://tutorialsplay.com/opengl/
 *
 * OBJ files must be triangulated!!!
 * Non triangulated objects wont work!
 * You can use Blender to triangulate
 *
 */

#ifndef ModelLoader_H
#define ModelLoader_H

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9

class ModelLoader
{
public:
    ModelLoader();
    ~ModelLoader();
    bool loadFromFile(
        const std::string& folder,
        const std::string& filename);
    void draw();

private:
    float* normals_;
    float* faces_;
    float* vertices_;
    long TotalConnectedTriangles_;
    long TotalConnectedPoints_;
};

#endif // ModelLoader_H
