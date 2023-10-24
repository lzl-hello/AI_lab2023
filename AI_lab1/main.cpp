#include <iostream>
#include<string>
using namespace std;

struct State
{
	int monkey; /*-1:Monkey at A;0: Monkey at B;1:Monkey at C;*/
	int box; /*-1:box at A;0:box at B;1:box at C;*/
	int banana; /*Banana at B,Banana=0*/
	int monbox; /*-1: monkey under the box;1: monkey on the box;*/
};
struct State States[150];

string routesave[150];

/*定义猴子的移动*/
void monkeygoto(int b, int i)
{

	int a;
	a = b;
	if (a == -1)
	{
		routesave[i] = "Monkey go to A";
		States[i + 1] = States[i];
		States[i + 1].monkey = -1;
	}
	else if (a == 0)
	{
		routesave[i] = "Monkey go to B";
		States[i + 1] = States[i];
		States[i + 1].monkey = 0;
	}
	else if (a == 1)
	{
		routesave[i] = "Monkey go to C";
		States[i + 1] = States[i];
		States[i + 1].monkey = 1;
	}
	else
	{
		printf("parameter is wrong");
	}
}

/*猴子推箱子*/
void movebox(int a, int i)
{

	int B;
	B = a;
	if (B == -1)
	{
		routesave[i] = "monkey move box to A";
		States[i + 1] = States[i];
		States[i + 1].monkey = -1;
		States[i + 1].box = -1;
	}
	else if (B == 0)
	{
		routesave[i] = "monkey move box to B";
		States[i + 1] = States[i];
		States[i + 1].monkey = 0;
		States[i + 1].box = 0;
	}
	else if (B == 1)
	{
		routesave[i] = "monkey move box to C";
		States[i + 1] = States[i];
		States[i + 1].monkey = 1;
		States[i + 1].box = 1;
	}
	else
	{
		printf("parameter is wrong");
	}
}

/*猴子爬上箱子*/
void climbonto(int i)
{

	routesave[i] = "Monkey climb onto the box";
	States[i + 1] = States[i];
	States[i + 1].monbox = 1;
}

/* 猴子爬下箱子*/
void climbdown(int i)
{

	routesave[i] = "Monkey climb down from the box";
	States[i + 1] = States[i];
	States[i + 1].monbox = -1;
}

/*判断是否拿到香蕉*/
void reach(int i)
{
	routesave[i] = "Monkey reach the banana";
}

/*输出每一步*/
void showSolution(int i)
{
	int c;
	cout<<"Result to problem:"<<endl;
	for (c = 0; c < i + 1; c++)
	{
		cout<<"Step"<< c + 1<<":" <<routesave[c]<<endl;
	}
	cout<<endl;
}

/*递归*/
void nextStep(int i)
{
	int c;
	int j;
	if (i >= 150)
	{
		cout << "steplength reached 150,have problem " << endl;
		return;
	}
	for (c = 0; c < i; c++) /*if the current state is same to previous,retrospect*/
	{
		if (States[c].monkey == States[i].monkey&&States[c].box == States[i].box&&States[c].banana == States[i].banana&&States[c].monbox == States[i].monbox)
		{
			return;
		}
	}
	if (States[i].monbox == 1 && States[i].monkey == States[0].banana && States[i].banana == States[0].banana && States[i].box == States[0].banana)
	{
		showSolution(i);
		cout << "Press any key to continue " << endl;
		//getchar();/*to save screen for user,press any key to continue*/
		return; 
	}
	j = i + 1;
	if (States[i].box == States[i].monkey&&States[i].box == States[i].banana)
	{
		if (States[i].monbox == -1)
		{
			climbonto(i);
			reach(i + 1);
			nextStep(j);

		}
		else
		{
			reach(i + 1);
			nextStep(j);

		}
	}
	else if (States[i].box == States[i].monkey&&States[i].box != States[i].banana)
	{
		if (States[i].monbox == -1)
		{

			movebox(States[i].banana, i);
			nextStep(j);

		}
		else
		{
			climbdown(i);
			nextStep(j);

		}
	}
	else if (States[i].box != States[i].monkey&&States[i].box == States[i].banana)
	{
		monkeygoto(States[i].box, i);
		nextStep(j);

	}
	else if (States[i].box != States[i].monkey&&States[i].box != States[i].banana)
	{
		monkeygoto(States[i].box, i);
		nextStep(j);

	}
}

int main()
{
	cout << "初始位置：" << endl;
	cout << "monkey(-1 or 0 or 1):";
	cin>>States[0].monkey;
	cout << "box(-1 or 0 or 1):";
	cin >> States[0].box;
	cout << "banana(-1 or 0 or 1):";
	cin>>States[0].banana;
	cout << "monbox(-1 or 1):";
	cin>>States[0].monbox;
	nextStep(0);
}
