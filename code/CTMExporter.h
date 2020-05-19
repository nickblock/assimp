#ifndef AI_CTMEXPORTER_H_INC
#define AI_CTMEXPORTER_H_INC

struct aiScene;
struct aiNode;

namespace Assimp  
{


class CTMExporter {
public:
  CTMExporter(const char* filename, const aiScene* pScene);
};


}


#endif