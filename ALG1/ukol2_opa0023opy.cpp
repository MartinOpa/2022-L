#include <iostream>
#include <vector>

using namespace std;

struct point {
	float x,y;
	int i;
};

int position(point a, point b, point c)
{
    float y1 = a.y - b.y;
    float y2 = a.y - c.y;
    float x1 = a.x - b.x;
    float x2 = a.x - c.x;
    return y2*x1 - y1*x2;
}

void jarvis(point Points[], int n)
{
    cout << "\nJarvis march\nBody konvexního obalu jsou:\n\n";
	int left = 0;
	int next = 0;

	for (int i = 1; i < n; i++)
	{
		if (Points[i].x < Points[left].x)
		{
			left = i;
		}
	}
	int start = left;
	cout << "Index " << Points[start].i << " {" << Points[start].x << "," << Points[start].y << "}\n";

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			if (position(Points[left], Points[next], Points[j]) > 0)
			{
				next = j;
			}
		}
		left = next;
        if (Points[next].i == Points[start].i)
		{
			return;
		}
		cout << "Index " << Points[left].i << " {" << Points[left].x << "," << Points[left].y << "}\n";
		next = i;
	}

	return;
}

bool fits(int lines[], int n)
{
    for (int i = 0; i < n; i++) {
        if (lines[i] < 0)
            return 0;
    }
    
	return 1;
}


void bruteForce(point points[], int n)
{
    cout << "\nBrute force\nBody konvexního obalu jsou:\n\n";
    int *lines = new int[n];
    int a, b, c;
    bool hull;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == i)
            {
                continue;
            }
            else 
            {
                a = points[j].y - points[i].y;
                b = -(points[j].x - points[i].x);
                c = -((points[i].x * a) + (points[i].y * b));
            }

            for (int k = 0; k < n; k++)
            {
                lines[k] = (a * points[k].x) + (b * points[k].y) + c;
            }

            hull = fits(lines, n);
            if(hull == true)
            {
                cout << "Index " << points[i].i << " {" << points[i].x << ", " << points[i].y << "}\n";
            }
        }
    }
}

int main() {
    
	int n = 23;
    point points[] = {{35.850, 26.850, 0},
                    {52.875, 10.875, 1},
                    {72.750, 70.650, 2},
                    {21.900, 28.650, 3},
                    {53.850, 67.125, 4},
                    {50.025, 22.425, 5},
                    {2.625, 67.050, 6},
                    {41.025, 48.300, 7},
                    {23.700, 2.625, 8},
                    {14.250, 63.150, 9},
                    {16.500, 7.950, 10},
                    {19.800, 48.600, 11},
                    {33.450, 60.375, 12},
                    {66.750, 54.675, 13},
                    {0.450, 7.575, 14},
                    {6.300, 71.550, 15},
                    {69.675, 40.575, 16},
                    {1.575, 55.875, 17},
                    {69.300, 5.400, 18},
                    {7.275, 38.400, 19},
                    {73.950, 21.750, 20},
                    {49.125, 43.050, 21},
                    {2.325, 3.900, 22}};
    
    cout << "Jelikož jsem nepozorný čtenář, nabízím hned dva druhy řešení. \n"
    << "Bylo mi líto smazat Jarvise, ale před odevzdáním jsem si všiml požadavku\n"
    << "na \"bruteforce\". Pro bruteforce vložte input 1, pro Jarvise input 2.\n";
    int method = 1;
    // cin >> method;
    
    if ( method != 1 && method != 2 )
    {
        cout << "špatný input";
        return -1;
    }
    
    method == 1 ? bruteForce(points, n) : jarvis(points, n);

	return 0;
}