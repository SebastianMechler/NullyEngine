#pragma once

// Windows includes
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Psapi.h> // EnumProcessModules
#include <WinSock2.h>
#include <Ws2tcpip.h>

// DirectX includes
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

// C++ includes
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <stack>
#include <cassert>
#include <cmath>
#include <stdlib.h> // required for function: srand + rand
#include <time.h> // required for function: timeGetTime

// Linker
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DCompiler.lib")