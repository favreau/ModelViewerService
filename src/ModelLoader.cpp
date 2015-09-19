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

#ifdef __APPLE__
#  include "GLUT/glut.h"
#else
#  include "GL/glut.h"
#endif
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/postprocess.h>

#include "ModelLoader.h"

using namespace std;

#define inf 1e38

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

bool ModelLoader::loadFromFile(const std::string& folder, const std::string& filename)
{
    std::cout << "Loading " << folder << "/" << filename << std::endl;
    Assimp::Importer importer;
    const aiScene *scene = NULL;
    std::string fullname = folder + "/" + filename;
    scene = importer.ReadFile( fullname.c_str() , aiProcessPreset_TargetRealtime_MaxQuality);
    if (!scene)
    {
        std::cerr << "Error parsing " << fullname.c_str() << ": " <<
                     importer.GetErrorString() << std::endl;
        return false;
    }

    if (!scene->HasMeshes())
    {
        std::cerr << "Error Finding Model In file. " <<
                     "Did you export an empty scene?" << std::endl;
        return false;
    }

    for (size_t m=0; m<scene->mNumMeshes; ++m)
    {
        aiMesh* mesh = scene->mMeshes[m];
        for (size_t f=0; f<mesh->mNumFaces; ++f)
        {
            for( size_t c=0; c<3; ++c)
            {
                for( size_t v=0; v<3; ++v)
                {
                    faces_.push_back(mesh->mVertices[mesh->mFaces[f].mIndices[c]][v]);
                    if( mesh->mNormals )
                        facesNormals_.push_back(mesh->mNormals[mesh->mFaces[f].mIndices[c]][v]);
                }
            }
        }
    }
    return true;
}

void ModelLoader::draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);		 	 // Enable vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY);			 // Enable normal arrays
    glVertexPointer(3, GL_FLOAT, 0, &faces_[0]);	 // Vertex Pointer to triangle array
    glNormalPointer(GL_FLOAT, 0, &facesNormals_[0]); // Normal pointer to normal array
    glDrawArrays(GL_TRIANGLES, 0, faces_.size()/3);  // Draw the triangles
    glDisableClientState(GL_NORMAL_ARRAY);   		 // Disable normal arrays
    glDisableClientState(GL_VERTEX_ARRAY);			 // Disable vertex arrays
}

