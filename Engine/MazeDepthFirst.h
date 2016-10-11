#pragma once
#include "stdafx.h"
#include "EngineIntern.h"
#include "Vec2.h"
#include "MathUtility.h"

namespace Nully
{
	namespace Level
	{
		struct SPos
		{
			int x;
			int y;
		};

		struct SMazeCell
		{
			bool visited;
			SPos pos;
			bool leftWall;
			bool rightWall;
			bool topWall;
			bool bottomWall;

			SMazeCell()
			{
				visited = false;
				leftWall = true;
				rightWall = true;
				topWall = true;
				bottomWall = true;
			}
		};

		struct SMazeParams
		{
			int width;
			int height;
			unsigned int seed;
		};

		class CMazeDepthFirst
		{
		public:
			CMazeDepthFirst();
			virtual ~CMazeDepthFirst();

			void Generate(const SMazeParams& params);
			void ShowDebugMaze(const char* strWall = "o", const char* strField = " ");

			bool* GetBoolArray() { return m_pBoolArray; }
			const SMazeParams& GetParams() { return m_params; }

		private:
			void Init();
			void CleanUp();
			SMazeCell* GetCell(int x, int y);
			void FindUnvisitedNeighbors();
			void VisitCell(SMazeCell* pCell);
			void CalcBoolArray();

		private:
			SMazeParams m_params;
			SMazeCell* m_pCells;

			SMazeCell* m_pCurrentCell;
			int m_visitedCount;
			int m_totalCount;

			std::stack<SMazeCell*> m_backTrack;
			std::vector<SMazeCell*> m_unvisitedNeighbors;

			bool* m_pBoolArray;
		};
	}
}