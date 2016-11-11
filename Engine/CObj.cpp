#include "stdafx.h"
#include "CObj.h"

namespace Nully
{
  CObj::CObj()
  {
  }

  CObj::CObj(const char * a_file)
  {
    Load(a_file);
  }

  void CObj::Load(const char * a_file)
  {
    if (a_file == nullptr)
    {
      return;
    }

    // Open File and Read the Size
    CFileManager obj;
    obj.Open(a_file, EFileMode::Read);
    auto size = obj.GetFileSize(a_file);

    // wrong size? return
    if (size == 0)
    {
      return;
    }

    // create unique_ptr so the delete[] will be called on leaving scope
    std::unique_ptr<char[]> buffer(new char[size + 1]);

    // buffer which will be incremented and worked with
    char* workBuffer = buffer.get();

    // read the whole file into buffer
    obj.Read(workBuffer, size);
    *(workBuffer + size) = '\0'; // set zero termination

    bool isWorkDone = false;
    uint32_c lineLength = 0;
    EObjDataType type = EObjDataType::Unused;


    while (isWorkDone == false)
    {
      type = GetObjType(workBuffer); // get object type from the first two characters

      lineLength = GetNewLineLength(workBuffer, isWorkDone); // find the length of the line which is determined by '\n' character
      switch (type)
      {
      case EObjDataType::Vertex:
      case EObjDataType::Normal:
        ToNVector3(workBuffer, type, lineLength);
        break;
      case EObjDataType::Name:
        ToName(workBuffer, lineLength);
        break;
      case EObjDataType::Uv:
        break;
      case EObjDataType::Face:
        ToFace(workBuffer, lineLength);
        break;
      case EObjDataType::Unused:
        break;
      default:
        break;
      }

      // increment the buffer which will then point to the next line
      workBuffer += lineLength;
    }

  }
  NVertex& CObj::GetVertices()
  {
    return m_vertices;
  }
  NVertex& CObj::GetNormals()
  {
    return m_normals;
  }
  NFaces& CObj::GetFaces()
  {
    return m_faces;
  }
  std::string& CObj::GetName()
  {
    return m_objName;
  }
  EObjDataType CObj::GetObjType(char * a_buffer)
  {
    if (a_buffer == nullptr)
    {
      return EObjDataType::Unused;
    }

    char objType[2];
    objType[0] = *a_buffer;
    objType[1] = *(a_buffer + 1);

    if (objType[0] == 'v' && objType[1] == 'n')
    {
      return EObjDataType::Normal;
    }
    if (objType[0] == 'v' && objType[1] == 't')
    {
      return EObjDataType::Uv;
    }
    else if (objType[0] == 'v')
    {
      return EObjDataType::Vertex;
    }
    else if (objType[0] == 'f')
    {
      return EObjDataType::Face;
    }
    else if (objType[0] == 'o')
    {
      return EObjDataType::Name;
    }
    else
    {
      return EObjDataType::Unused;
    }
  }
  void CObj::ToNVector3(char* a_buffer, EObjDataType a_type, uint32_c a_lineLength)
  {
    CVector3 tmp;

    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

    char tmpX;
    if (a_type == EObjDataType::Vertex)
    {
      // this is a vertex
      // v 0.137950 0.980785 -0.137950
      //sscanf(buffer, "%c %f %f %f", &tmpX, &tmp.x, &tmp.y, &tmp.z);
      sscanf_s(a_buffer, "%c %f %f %f", &tmpX, 1, &tmp.x, &tmp.y, &tmp.z);
      m_vertices.push_back(tmp);
    }
    else if (a_type == EObjDataType::Normal)
    {
      // this is a vertex normal
      // vn 0.0464 0.8810 -0.4709
      //sscanf(buffer, "%c%c %f %f %f", &tmpX, &tmpX, &tmp.x, &tmp.y, &tmp.z);
      sscanf_s(a_buffer, "%c%c %f %f %f", &tmpX, 1, &tmpX, 1, &tmp.x, &tmp.y, &tmp.z);
      m_normals.push_back(tmp);
    }
  }

  void CObj::ToName(char* a_buffer, uint32_c a_lineLength)
  {
    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

                                          // incoming buffer looks like:
                                          // o Cube
                                          // so we have to move by two bytes
    m_objName = std::string(a_buffer + 2, a_lineLength - 2);
  }
  void CObj::ToFace(char * a_buffer, uint32_c a_lineLength)
  {
    SFace face = {};

    // remove \n and insert space, so sscanf_s can work with it
    *(a_buffer + a_lineLength - 1) = ' '; // -1 to come to the '\n'

    char tmp;
    sscanf_s(a_buffer, "%c %u//%u %u//%u %u//%u %u//%u", &tmp, 1, &face.v1, &face.normalIndex, &face.v2, &face.normalIndex, &face.v3, &face.normalIndex, &face.v4, &face.normalIndex);

    m_faces.push_back(face);
  }
  uint32_c CObj::GetNewLineLength(const char* buffer, bool& a_isNullterminationFound)
  {
    //nuint32 len = strlen(buffer) + 1; // +1 cause of \0

    for (uint32_c i = 0; i < 1024; i++)
    {
      if (*buffer == '\n')
      {
        // found new line
        return i + 1;
      }
      else if (*buffer == '\0')
      {
        // end is found
        a_isNullterminationFound = true;
        return i + 1;
      }

      buffer++;
    }

    a_isNullterminationFound = true;
    return 0;
  }
}

