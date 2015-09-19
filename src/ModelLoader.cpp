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
 : TotalConnectedTriangles_(0),
   TotalConnectedPoints_(0)
{
}

ModelLoader::~ModelLoader()
{
    delete faces_;
    delete facesNormals_;
    delete vertices_;
}


bool ModelLoader::loadFromFile(const std::string& folder, const std::string& filename)
{
    std::cout << "Loading " << folder << "/" << filename << std::endl;
    float bbox[2][3] =
    {
        {  inf,  inf,  inf },
        { -inf, -inf, -inf }
    };

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

    size_t nbVertices = 0;
    size_t nbFaces = 0;
    for (size_t m=0; m<scene->mNumMeshes; ++m)
    {
        aiMesh* mesh = scene->mMeshes[m];
        nbVertices += mesh->mNumVertices;
        nbFaces += mesh->mNumFaces;
    }
    vertices_ = new float[3*nbVertices];
    faces_ = new float[9*nbFaces];
    facesNormals_ = new float[9*nbFaces];

    for (size_t m=0; m<scene->mNumMeshes; ++m)
    {
        aiMesh* mesh = scene->mMeshes[m];

        nbVertices += mesh->mNumVertices;
        for (size_t i=0; i<mesh->mNumVertices; ++i)
        {
            aiVector3D v = mesh->mVertices[i];
            vertices_[TotalConnectedPoints_] = v.x;
            vertices_[TotalConnectedPoints_+1] = v.y;
            vertices_[TotalConnectedPoints_+2] = v.z;

            bbox[0][0] = min(bbox[0][0], v.x);
            bbox[0][1] = min(bbox[0][1], v.y);
            bbox[0][2] = min(bbox[0][2], v.z);

            bbox[1][0] = max(bbox[1][0], v.x);
            bbox[1][1] = max(bbox[1][1], v.y);
            bbox[1][2] = max(bbox[1][2], v.z);

            TotalConnectedPoints_ += POINTS_PER_VERTEX;
        }

        for (size_t f=0; f<mesh->mNumFaces; ++f)
        {
            for (size_t c=0; c<3; ++c)
            {
                faces_[(TotalConnectedTriangles_ + f)*9 + c    ] =
                        mesh->mVertices[mesh->mFaces[f].mIndices[0]][c];
                faces_[(TotalConnectedTriangles_ + f)*9 + 3 + c] =
                        mesh->mVertices[mesh->mFaces[f].mIndices[1]][c];
                faces_[(TotalConnectedTriangles_ + f)*9 + 6 + c] =
                        mesh->mVertices[mesh->mFaces[f].mIndices[2]][c];

                if( mesh->mNormals )
                {
                    facesNormals_[(TotalConnectedTriangles_ + f)*9 + c    ] =
                            mesh->mNormals[mesh->mFaces[f].mIndices[0]][c];
                    facesNormals_[(TotalConnectedTriangles_ + f)*9 + 3 + c] =
                            mesh->mNormals[mesh->mFaces[f].mIndices[1]][c];
                    facesNormals_[(TotalConnectedTriangles_ + f)*9 + 6 + c] =
                            mesh->mNormals[mesh->mFaces[f].mIndices[2]][c];

                }
            }
        }
        TotalConnectedTriangles_ += mesh->mNumFaces*3;
    }

    std::cout << "Bounding box ("
              << bbox[0][0] << "," << bbox[0][1] << "," << bbox[0][2] << "),("
                                                                      << bbox[1][0] << "," << bbox[1][1] << "," << bbox[1][2] << ")"
                                                                                                                              << std::endl;
    std::cout << "Loaded " << nbVertices << " vertices and "
              << TotalConnectedTriangles_ << " faces" << std::endl;

    return true;
}

void ModelLoader::draw()
{

    glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
    glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
    glVertexPointer(3, GL_FLOAT, 0, faces_);				// Vertex Pointer to triangle array
    glNormalPointer(GL_FLOAT, 0, facesNormals_);						// Normal pointer to normal array
    glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles_);		// Draw the triangles
    glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
    glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
}

