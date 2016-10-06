#include <Core\Core.h>

#include <string>

struct Y
{
  float x;
  float y;
};

class X
{
public:
  union
  {
    struct
    {
      float x, y, 
        z, w;
    };

    Y row[2];
  };
  
  

  Y& operator[](int index)
  {
    return row[index];
  }
};

void main()
{
  X x;
  x[0] = {1,1};
  x[1] = { 1,1 };

  using Nully::Math::CVector3;
  using Nully::Math::CVector4;
  using Nully::Hacking::CProcess;
  using Nully::Tools::CStringA;
  using Nully::Tools::CStringW;
  using Nully::Tools::CFileManager;
  using Nully::Network::CSocket;

  CVector3 vector1 = CVector3::forward;
  CVector3 vector2 = CVector3::forward;

  if (vector1 != vector2)
  {
    return;
  }

  using Nully::Math::CMatrix4x4;

  CMatrix4x4 mat = 
  {
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f}
  };


  system("Pause");

}

/*
Nully::uint32_c address = 0x55E21D2E;
auto x = process.Read<Nully::uint32_c>(&address);

result = process.Write(&address, 10);
Nully::uint32_c result1 = process.Read<Nully::uint32_c>(&address);
*/
/*
CProcess process;
CProcess::SetDebugPrivilegeState(true);

auto processList = process.GetProcessListByName(nullptr, true);
process.DumpToFile(&processList, "dump.txt");
*/


//Nully::ECoreResult result = process.Open(processList[0].id);

/*
Nully::ECoreResult result;

CSocket socket;
result = socket.Open(Nully::Network::SocketFamily::ipv4, Nully::Network::SocketType::Stream);
result = socket.Connect(Nully::Network::SocketFamily::ipv4, Nully::Network::SocketPort::FTP, "127.0.0.1");

//Nully::char_c bufferSend[] = "GET /index.php HTTP/1.1\n User - Agent: Mozilla / 4.0 (compatible; MSIE5.01; Windows NT)\n Host : www.smechler.com\n Accept - Language : en - us\n Accept - Encoding : gzip, deflate\n Connection : Keep - Alive";
Nully::char_c bufferSend[] = "Hello from Sebastian";

result = socket.Send(bufferSend, strlen(bufferSend) + 1);

Nully::char_c buffer[4096];
socket.Receive(buffer, 4096);
*/