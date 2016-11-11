#pragma once

#include "stdafx.h"

#include "SObjFace.h"
#include "EObjDataType.h"
#include "CVector3.h"
#include "CFileManager.h"

namespace Nully
{
  typedef std::vector<CVector3> NVertex;
  typedef std::vector<SFace> NFaces;

  class CObj
  {
  public:
    CObj();
    CObj(const char* a_file);
    void Load(const char* a_file);

    NVertex& GetVertices();
    NVertex& GetNormals();
    NFaces& GetFaces();
    std::string& GetName();

  private:
    EObjDataType GetObjType(char* buffer);
    void ToNVector3(char* a_buffer, EObjDataType a_type, uint32_c a_lineLength);
    void ToName(char* a_buffer, uint32_c a_lineLength);
    void ToFace(char* a_buffer, uint32_c a_lineLength);

    uint32_c GetNewLineLength(const char* buffer, bool& a_isNullterminationFound);

    std::string m_objName;
    NVertex m_vertices;
    NVertex m_normals;
    NFaces m_faces;
  };
}
