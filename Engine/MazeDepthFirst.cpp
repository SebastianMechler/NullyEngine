#include "MazeDepthFirst.h"

using namespace Nully::Level;
using namespace Nully::Math;

CMazeDepthFirst::CMazeDepthFirst()
{
	m_pCells = nullptr;
	m_pBoolArray = nullptr;
}

CMazeDepthFirst::~CMazeDepthFirst()
{
	CleanUp();
}

void CMazeDepthFirst::Generate(const SMazeParams& params)
{
	CleanUp();
	m_params = params;
	Init();

	assert(m_backTrack.empty());

	m_totalCount = m_params.width * m_params.height;
	m_visitedCount = 0;
	srand(m_params.seed);

	m_pCurrentCell = nullptr;

	SMazeCell* pStartCell = GetCell(rand() % m_params.width, rand() % m_params.height);
	VisitCell(pStartCell);

	while (m_visitedCount < m_totalCount)
	{
		FindUnvisitedNeighbors();
		
		if (m_unvisitedNeighbors.size() > 0)
		{
			int randomIndex = rand() % m_unvisitedNeighbors.size();
			SMazeCell* pNextCell = m_unvisitedNeighbors[randomIndex];

			VisitCell(pNextCell);
		}
		else if (m_backTrack.size() > 0)
		{
			m_pCurrentCell = m_backTrack.top();
			m_backTrack.pop();
		}
	}

	CalcBoolArray();
}

void CMazeDepthFirst::ShowDebugMaze(const char* strWall, const char* strField)
{
	using namespace std;

	for (int y = 0; y < m_params.height * 3; y++)
	{
		for (int x = 0; x < m_params.width * 3; x++)
		{
			cout << (m_pBoolArray[x + m_params.width * 3 * y] ? strWall : strField) << " ";
		}
		cout << endl;
	}
}

void CMazeDepthFirst::CalcBoolArray()
{
	for (int y = 0; y < m_params.height * 3; y++)
	{
		for (int x = 0; x < m_params.width * 3; x++)
		{
			// Default Value => Wall (for the corners)
			m_pBoolArray[x + m_params.width * 3 * y] = true;
		}
	}

	for (int y = 0; y < m_params.height; y++)
	{
		for (int x = 0; x < m_params.width; x++)
		{
			SMazeCell* pCell = GetCell(x, y);

			// Center
			int centerX = x * 3 + 1;
			int centerY = y * 3 + 1;
			m_pBoolArray[centerX + m_params.width * 3 * centerY] = false;
			// Top
			m_pBoolArray[centerX + m_params.width * 3 * (centerY - 1)] = pCell->topWall;
			// Bottom
			m_pBoolArray[centerX + m_params.width * 3 * (centerY + 1)] = pCell->bottomWall;
			// Left
			m_pBoolArray[centerX - 1 + m_params.width * 3 * centerY] = pCell->leftWall;
			// Right
			m_pBoolArray[centerX + 1 + m_params.width * 3 * centerY] = pCell->rightWall;
		}
	}
}

void CMazeDepthFirst::Init()
{
	int width = m_params.width;
	int height = m_params.height;

	m_pCells = new SMazeCell[width * height];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			m_pCells[x + width * y].pos = { x, y };
		}
	}

	int boolArraySize = m_params.width * m_params.height * 9;
	m_pBoolArray = new bool[boolArraySize];
}

void CMazeDepthFirst::CleanUp()
{
	if (m_pCells != nullptr)
	{
		delete[] m_pCells;
		m_pCells = nullptr;
	}

	if (m_pBoolArray != nullptr)
	{
		delete[] m_pBoolArray;
		m_pBoolArray = nullptr;
	}

	while (m_backTrack.size() != 0)
		m_backTrack.pop();
}

SMazeCell* CMazeDepthFirst::GetCell(int x, int y)
{
	assert(x >= 0 && x < m_params.width);
	assert(y >= 0 && y < m_params.height);

	return &m_pCells[x + m_params.width * y];
}

void CMazeDepthFirst::FindUnvisitedNeighbors()
{
	m_unvisitedNeighbors.clear();
	
	SPos pos = m_pCurrentCell->pos;

	SMazeCell* pCell = nullptr;

	pCell = GetCell(clamp<int>(pos.x - 1, 0, m_params.width - 1), clamp<int>(pos.y, 0, m_params.height - 1));
	if (!pCell->visited)
		m_unvisitedNeighbors.push_back(pCell);

	pCell = GetCell(clamp<int>(pos.x + 1, 0, m_params.width - 1), clamp<int>(pos.y, 0, m_params.height - 1));
	if (!pCell->visited)
		m_unvisitedNeighbors.push_back(pCell);

	pCell = GetCell(clamp<int>(pos.x, 0, m_params.width - 1), clamp<int>(pos.y - 1, 0, m_params.height - 1));
	if (!pCell->visited)
		m_unvisitedNeighbors.push_back(pCell);

	pCell = GetCell(clamp<int>(pos.x, 0, m_params.width - 1), clamp<int>(pos.y + 1, 0, m_params.height - 1));
	if (!pCell->visited)
		m_unvisitedNeighbors.push_back(pCell);
}

void CMazeDepthFirst::VisitCell(SMazeCell* pCell)
{
	assert(!pCell->visited);
	assert(pCell != nullptr);

	if (m_pCurrentCell != nullptr)
	{
		// Remove Walls between current and next cell
		Vec2 vCurrent = Vec2((float)m_pCurrentCell->pos.x, (float)m_pCurrentCell->pos.y);
		Vec2 vNext = Vec2((float)pCell->pos.x, (float)pCell->pos.y);
		Vec2 vDelta = vNext - vCurrent;

		if (vDelta.x == -1)
		{
			m_pCurrentCell->leftWall = false;
			pCell->rightWall = false;
		}
		else if (vDelta.x == 1)
		{
			m_pCurrentCell->rightWall = false;
			pCell->leftWall = false;
		}
		else if (vDelta.y == -1)
		{
			m_pCurrentCell->topWall = false;
			pCell->bottomWall = false;
		}
		else if (vDelta.y == 1)
		{
			m_pCurrentCell->bottomWall = false;
			pCell->topWall = false;
		}
	}

	pCell->visited = true;
	m_backTrack.push(pCell);
	m_visitedCount++;
	m_pCurrentCell = pCell;
}

