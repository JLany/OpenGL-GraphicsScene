#ifndef BRESENHAM_CIRCLE_ALGROITHM_H
#define BRESENHAM_CIRCLE_ALGROITHM_H

#include <Windows.h>
#include <cmath>
#include "Util.hpp"
#include "Vertex.h"
#define FACTOR 1

static class BresenhamCircleAlgorithm
{
public:
	/*static Vertex center;
	static float radius;
	static HDC hdc;
	COLORREF color;*/

public:

public:
	static void Draw8Points(int x, int y, float width, float color[])
	{
		//int dx[]{ v.x, v.x, -v.x, -v.x, v.y, v.y, -v.y, -v.y };
		//int dy[]{ v.y, -v.y, v.y, -v.y, v.x, -v.x, v.x, -v.x };

		//for (int i = 0; i < 8; ++i)
		//	SetPixel(hdc, center.x + dx[i], center.y + dy[i], color);


		int dx[]{ x, x, -x, -x, y, y, -y, -y };
		int dy[]{ y, -y, y, -y, x, -x, x, -x };

		for (int i = 0; i < 8; ++i)
		{
			float fx = (float)dx[i] / FACTOR, fy = (float)dy[i] / FACTOR;



			// we need to map this cube to the viewport 
			std::vector<Vertex> cube{
				{ fx - width, fy + width, -10.0f },
				{ fx + width, fy + width, -10.0f },
				{ fx - width, fy - width, -10.0f },
				{ fx + width, fy - width, -10.0f },
				{ fx - width, fy + width, 10.0f },
				{ fx + width, fy + width, 10.0f },
				{ fx - width, fy - width, 10.0f },
				{ fx + width, fy - width, 10.0f },
			};

			DrawCube(cube, color);
		}
	}

	static void Draw(Vertex center, float radius, float width, float color[])
	{
		int x = 0;
		int y = radius * FACTOR;

		Draw8Points(x, y, width, color);

		int d = 1 - radius * FACTOR;
		int ch1 = 3;
		int ch2 = 5 - 2 * radius;

		while (x < y)
		{
			if (d <= 0)
			{
				d += ch1;
				ch2 += 2;
			}
			else
			{
				d += ch2;
				y--;
				ch2 += 4;
			}

			x++;
			ch1 += 2;

			Draw8Points(x, y, width, color);
		}
	}
};

#endif // BRESENHAM_CIRCLE_ALGROITHM_H