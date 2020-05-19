

#ifndef ASSIMP_BUILD_NO_EXPORT
#ifndef ASSIMP_BUILD_NO_CTM_EXPORTER

#include "assimp/scene.h"
#include <assimp/IOSystem.hpp>
#include <assimp/Exporter.hpp>
#include "CTMExporter.h"
#include "openctm.h"

#include <vector>

using std::vector;

namespace Assimp {

void ExportSceneCTM(const char* pFile, IOSystem* pIOSystem, const aiScene* pScene, const Assimp::ExportProperties*)
{
  CTMExporter exporter(pFile, pScene);
}

CTMExporter::CTMExporter(const char* filename, const aiScene* pScene)
{
  vector<float> vertices;
  vector<float> normals;
  vector<uint32_t> indices;

  for(size_t m=0; m<pScene->mNumMeshes; m++) {
    
    const aiMesh* mesh = pScene->mMeshes[m];

    vertices.insert(vertices.end(), (float*)mesh->mVertices, (float*)&mesh->mVertices[mesh->mNumVertices]);
    normals.insert(normals.end(), (float*)mesh->mNormals, (float*)&mesh->mNormals[mesh->mNumVertices]);

    size_t curIndex = indices.size();
    for(size_t f=0; f<mesh->mNumFaces; f++) {

      aiFace& face = mesh->mFaces[f];

      indices.insert(indices.end(), (uint32_t*)face.mIndices, (uint32_t*)&face.mIndices[face.mNumIndices]);
    }
  }

  CTMexporter ctm;

  ctm.DefineMesh((CTMfloat *) vertices.data(), vertices.size(),
                 (const CTMuint*) indices.data(), indices.size() / 3,
                 normals.data());

  ctm.CompressionMethod(CTM_METHOD_MG1);
  ctm.CompressionLevel(9);


  ctm.Save(filename);
}

}


#endif
#endif