#include<stdafx.h>
#include<iostream>
#include<fstream>
#include<stack>
#include<vector>


using namespace std;
/*
*0 =  front face
* 1 = top face
* 2 = east face
* 3 = west face
* 4 = bottom face
* 5 = back face
*/

class cubenode {
public:
	cubenode * p;
	int lastmove;
	int depth;
	int*** currentstate;
	vector< cubenode *> childnode;

	cubenode(int*** cube) {
		p = nullptr;
		lastmove = 0;
		depth = 0;
		currentstate = cube;
	}
	void addchild(int*** cube) {
		cubenode * a = new cubenode(cube);
		childnode.push_back(a);
	}
};

void storestate(int*** a, int*** b) {
	int input;
	ifstream fin("input.txt");
	if (!fin.is_open()) {
		cout << "unable to read from file" << endl;
	}
	else
	{
		while (!fin.eof()) {
			for (int i = 0; i < 6; i++) {

				//for each row
				for (int j = 0; j < 3; j++) {

					for (int k = 0; k < 3; k++) {

						fin >> input;
						a[i][j][k] = input;

					}

				}

			}
			for (int i = 0; i < 6; i++) {

				//for each row
				for (int j = 0; j < 3; j++) {

					for (int k = 0; k < 3; k++) {

						fin >> input;
						b[i][j][k] = input;

					}

				}

			}
		}
	}
}

void printcubestate(int*** a) {
	for (int i = 0; i < 6; i++) {

		//for each row
		for (int j = 0; j < 3; j++) {

			for (int k = 0; k < 3; k++) {


				cout << a[i][j][k];

			}
			cout << endl;

		}
		cout << endl;

	}
	cout << endl;
}

int*** rotatepointclockwise(int face, int*** cube1, int*** cube2) {

	//Top Row goes:
	//0,0 -> 0,2
	//1,0 -> 0,1
	//2,0 -> 0,0
	cube1[face][0][2] = cube2[face][0][0];
	cube1[face][0][1] = cube2[face][1][0];
	cube1[face][0][0] = cube2[face][2][0];


	//Middle row goes:
	//0,1 -> 1,2
	//1,1 -> 1,1
	//2,1 -> 1,0
	cube1[face][1][2] = cube2[face][0][1];
	cube1[face][1][1] = cube2[face][1][1];
	cube1[face][1][0] = cube2[face][2][1];


	//Bottom Row goes to:
	//0,2 -> 2,2
	//1,2 -> 2,1
	//2,2 -> 2,0
	cube1[face][2][2] = cube2[face][0][2];
	cube1[face][2][1] = cube2[face][1][2];
	cube1[face][2][0] = cube2[face][2][2];

	return cube1;



}

int*** rotatepointanticlockwise(int face, int*** cube1, int*** cube2) {
	//Top Row goes:
	//0,0 -> 2,0
	//1,0 -> 2,1
	//2,0 -> 2,2

	cube1[face][2][0] = cube2[face][0][0];
	cube1[face][2][1] = cube2[face][1][0];
	cube1[face][2][2] = cube2[face][2][0];
	//Middle row goes:
	//0,1 -> 1,0
	//1,1 -> 1,1
	//2,1 -> 1,2


	cube1[face][1][0] = cube2[face][0][1];
	cube1[face][1][1] = cube2[face][1][1];
	cube1[face][1][2] = cube2[face][2][1];
	//Bottom row goes:
	//0,2 -> 0,0
	//1,2 -> 0,1
	//2,2 -> 0,2


	cube1[face][0][0] = cube2[face][0][2];
	cube1[face][0][1] = cube2[face][1][2];
	cube1[face][0][2] = cube2[face][2][2];

	return cube1;



}

int*** leftclockwise(int*** cube)
{
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}



	//do first swap
	//moves face 0 into the position of face 4
	temp[4][0][0] = cube[0][0][0];
	temp[4][1][0] = cube[0][1][0];
	temp[4][2][0] = cube[0][2][0];


	//do second swap
	//moves face 4 into face 5
	temp[5][0][0] = cube[4][0][0];
	temp[5][1][0] = cube[4][1][0];
	temp[5][2][0] = cube[4][2][0];


	//do third swap
	//moves face 5 into face 1
	temp[1][0][0] = cube[5][0][0];
	temp[1][1][0] = cube[5][1][0];
	temp[1][2][0] = cube[5][2][0];


	//do fourth swap
	//moves face 1 into face 0
	temp[0][0][0] = cube[1][0][0];
	temp[0][1][0] = cube[1][1][0];
	temp[0][2][0] = cube[1][2][0];


	return rotatepointclockwise(3, temp, cube);
}

int*** leftanticlockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}

	//do first swap
	//moves face 0 into the position of face 1
	temp[1][0][0] = cube[0][0][0];
	temp[1][1][0] = cube[0][1][0];
	temp[1][2][0] = cube[0][2][0];


	//do second swap
	//moves face 1 into face 5
	temp[5][0][0] = cube[1][0][0];
	temp[5][1][0] = cube[1][1][0];
	temp[5][2][0] = cube[1][2][0];


	//do third swap
	//moves face 5 into face 4
	temp[4][0][0] = cube[5][0][0];
	temp[4][1][0] = cube[5][1][0];
	temp[4][2][0] = cube[5][2][0];


	//do fourth swap
	//moves face 4 into face 0
	temp[0][0][0] = cube[4][0][0];
	temp[0][1][0] = cube[4][1][0];
	temp[0][2][0] = cube[4][2][0];

	return rotatepointanticlockwise(3, temp, cube);

}

int*** rightclockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}

	//do first swap
	//moves face 0 into the position of face 4
	temp[4][0][2] = cube[0][0][2];
	temp[4][1][2] = cube[0][1][2];
	temp[4][2][2] = cube[0][2][2];


	//do second swap
	//moves face 4 into face 5
	temp[5][0][2] = cube[4][0][2];
	temp[5][1][2] = cube[4][1][2];
	temp[5][2][2] = cube[4][2][2];


	//do third swap
	//moves face 5 into face 1
	temp[1][0][2] = cube[5][0][2];
	temp[1][1][2] = cube[5][1][2];
	temp[1][2][2] = cube[5][2][2];


	//do fourth swap
	//moves face 1 into face 0
	temp[0][0][2] = cube[1][0][2];
	temp[0][1][2] = cube[1][1][2];
	temp[0][2][2] = cube[1][2][2];

	return rotatepointclockwise(2, temp, cube);

}

int*** rightanticlockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}

	//do first swap
	//moves face 0 into the position of face 1
	temp[1][0][2] = cube[0][0][2];
	temp[1][1][2] = cube[0][1][2];
	temp[1][2][2] = cube[0][2][2];


	//do second swap
	//moves face 1 into face 5
	temp[5][0][2] = cube[1][0][2];
	temp[5][1][2] = cube[1][1][2];
	temp[5][2][2] = cube[1][2][2];


	//do third swap
	//moves face 5 into face 4
	temp[4][0][2] = cube[5][0][2];
	temp[4][1][2] = cube[5][1][2];
	temp[4][2][2] = cube[5][2][2];


	//do fourth swap
	//moves face 4 into face 0
	temp[0][0][2] = cube[4][0][2];
	temp[0][1][2] = cube[4][1][2];
	temp[0][2][2] = cube[4][2][2];

	return rotatepointanticlockwise(2, temp, cube);

}

int*** upclockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}
	//do first swap
	//moves face 0 into the position of face 3
	temp[3][0][0] = cube[0][0][0];
	temp[3][0][1] = cube[0][0][1];
	temp[3][0][2] = cube[0][0][2];


	//do second swap
	//moves face 3 into face 5
	temp[5][0][0] = cube[3][0][0];
	temp[5][0][1] = cube[3][0][1];
	temp[5][0][2] = cube[3][0][2];


	//do third swap
	//moves face 5 into face 2
	temp[2][0][0] = cube[5][0][0];
	temp[2][0][1] = cube[5][0][1];
	temp[2][0][2] = cube[5][0][2];


	//do fourth swap
	//moves face 2 into face 0
	temp[0][0][0] = cube[2][0][0];
	temp[0][0][1] = cube[2][0][1];
	temp[0][0][2] = cube[2][0][2];

	return rotatepointclockwise(1, temp, cube);


}

int*** upanticlockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}
	//do first swap
	//moves face 0 into the position of face 2
	temp[2][0][0] = cube[0][0][0];
	temp[2][0][1] = cube[0][0][1];
	temp[2][0][2] = cube[0][0][2];


	//do second swap
	//moves face 2 into face 5
	temp[5][0][0] = cube[2][0][0];
	temp[5][0][1] = cube[2][0][1];
	temp[5][0][2] = cube[2][0][2];


	//do third swap
	//moves face 5 into face 3
	temp[3][0][0] = cube[5][0][0];
	temp[3][0][1] = cube[5][0][1];
	temp[3][0][2] = cube[5][0][2];


	//do fourth swap
	//moves face 3 into face 0
	temp[0][0][0] = cube[3][0][0];
	temp[0][0][1] = cube[3][0][1];
	temp[0][0][2] = cube[3][0][2];

	return rotatepointanticlockwise(1, temp, cube);
}

int*** bottomclockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}
	//do first swap
	//moves face 0 into the position of face 3
	temp[3][2][0] = cube[0][2][0];
	temp[3][2][1] = cube[0][2][1];
	temp[3][2][2] = cube[0][2][2];


	//do second swap
	//moves face 3 into face 5
	temp[5][2][0] = cube[3][2][0];
	temp[5][2][1] = cube[3][2][1];
	temp[5][2][2] = cube[3][2][2];


	//do third swap
	//moves face 5 into face 2
	temp[2][2][0] = cube[5][2][0];
	temp[2][2][1] = cube[5][2][1];
	temp[2][2][2] = cube[5][2][2];


	//do fourth swap
	//moves face 2 into face 0
	temp[0][2][0] = cube[2][2][0];
	temp[0][2][1] = cube[2][2][1];
	temp[0][2][2] = cube[2][2][2];

	return rotatepointclockwise(4, temp, cube);
}

int*** bottomanticlockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}
	//do first swap
	//moves face 0 into the position of face 2
	temp[2][2][0] = cube[0][2][0];
	temp[2][2][1] = cube[0][2][1];
	temp[2][2][2] = cube[0][2][2];


	//do second swap
	//moves face 2 into face 5
	temp[5][2][0] = cube[2][2][0];
	temp[5][2][1] = cube[2][2][1];
	temp[5][2][2] = cube[2][2][2];


	//do third swap
	//moves face 5 into face 3
	temp[3][2][0] = cube[5][2][0];
	temp[3][2][1] = cube[5][2][1];
	temp[3][2][2] = cube[5][2][2];


	//do fourth swap
	//moves face 3 into face 0
	temp[0][2][0] = cube[3][2][0];
	temp[0][2][1] = cube[3][2][1];
	temp[0][2][2] = cube[3][2][2];

	return rotatepointanticlockwise(4, temp, cube);

}

int*** frontclockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}
	//do first swap
	//moves face 1 into the position of face 3
	temp[3][2][0] = cube[1][2][0];
	temp[3][2][1] = cube[1][2][1];
	temp[3][2][2] = cube[1][2][2];


	//do second swap
	//moves face 3 into face 4
	temp[4][2][0] = cube[3][2][0];
	temp[4][2][1] = cube[3][2][1];
	temp[4][2][2] = cube[3][2][2];


	//do third swap
	//moves face 4 into face 2
	temp[2][2][0] = cube[4][2][0];
	temp[2][2][1] = cube[4][2][1];
	temp[2][2][2] = cube[4][2][2];


	//do fourth swap
	//moves face 2 into face 1
	temp[1][2][0] = cube[2][2][0];
	temp[1][2][1] = cube[2][2][1];
	temp[1][2][2] = cube[2][2][2];

	return rotatepointclockwise(0, temp, cube);
}

int*** frontanticlockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}
	//do first swap
	//moves face 1 into the position of face 2
	temp[2][2][0] = cube[1][2][0];
	temp[2][2][1] = cube[1][2][1];
	temp[2][2][2] = cube[1][2][2];


	//do second swap
	//moves face 2 into face 4
	temp[4][2][0] = cube[2][2][0];
	temp[4][2][1] = cube[2][2][1];
	temp[4][2][2] = cube[2][2][2];


	//do third swap
	//moves face 4 into face 3
	temp[3][2][0] = cube[4][2][0];
	temp[3][2][1] = cube[4][2][1];
	temp[3][2][2] = cube[4][2][2];


	//do fourth swap
	//moves face 3 into face 1
	temp[1][2][0] = cube[3][2][0];
	temp[1][2][1] = cube[3][2][1];
	temp[1][2][2] = cube[3][2][2];

	return rotatepointanticlockwise(0, temp, cube);

}

int*** backclockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}
	//do first swap
	//moves face 1 into the position of face 3
	temp[3][0][0] = cube[1][0][0];
	temp[3][0][1] = cube[1][0][1];
	temp[3][0][2] = cube[1][0][2];


	//do second swap
	//moves face 3 into face 4
	temp[4][0][0] = cube[3][0][0];
	temp[4][0][1] = cube[3][0][1];
	temp[4][0][2] = cube[3][0][2];


	//do third swap
	//moves face 4 into face 2
	temp[2][0][0] = cube[4][0][0];
	temp[2][0][1] = cube[4][0][1];
	temp[2][0][2] = cube[4][0][2];


	//do fourth swap
	//moves face 2 into face 1
	temp[1][0][0] = cube[2][0][0];
	temp[1][0][1] = cube[2][0][1];
	temp[1][0][2] = cube[2][0][2];

	return rotatepointclockwise(5, temp, cube);

}

int*** backanticlockwise(int*** cube) {
	int*** temp;
	temp = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = new int[3];
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				temp[i][j][k] = cube[i][j][k];
			}
		}
	}
	//do first swap
	//moves face 1 into the position of face 2
	temp[2][0][0] = cube[1][0][0];
	temp[2][0][1] = cube[1][0][1];
	temp[2][0][2] = cube[1][0][2];


	//do second swap
	//moves face 2 into face 4
	temp[4][0][0] = cube[2][0][0];
	temp[4][0][1] = cube[2][0][1];
	temp[4][0][2] = cube[2][0][2];


	//do third swap
	//moves face 4 into face 3
	temp[3][0][0] = cube[4][0][0];
	temp[3][0][1] = cube[4][0][1];
	temp[3][0][2] = cube[4][0][2];


	//do fourth swap
	//moves face 3 into face 1
	temp[1][0][0] = cube[3][0][0];
	temp[1][0][1] = cube[3][0][1];
	temp[1][0][2] = cube[3][0][2];

	return rotatepointanticlockwise(5, temp, cube);
}

void createchild(cubenode * obj) {
	int*** temp;
	temp = leftclockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(0)->lastmove = 0;
	obj->childnode.at(0)->depth = obj->depth + 1;
	obj->childnode.at(0)->p = obj;
	temp = leftanticlockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(1)->lastmove = 1;
	obj->childnode.at(1)->depth = obj->depth + 1;
	obj->childnode.at(1)->p = obj;
	temp = rightclockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(2)->lastmove = 2;
	obj->childnode.at(2)->depth = obj->depth + 1;
	obj->childnode.at(2)->p = obj;
	temp = rightanticlockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(3)->lastmove = 3;
	obj->childnode.at(3)->depth = obj->depth + 1;
	obj->childnode.at(3)->p = obj;
	temp = upclockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(4)->lastmove = 4;
	obj->childnode.at(4)->depth = obj->depth + 1;
	obj->childnode.at(4)->p = obj;
	temp = upanticlockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(5)->lastmove = 5;
	obj->childnode.at(5)->depth = obj->depth + 1;
	obj->childnode.at(5)->p = obj;
	temp = bottomclockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(6)->lastmove = 6;
	obj->childnode.at(6)->depth = obj->depth + 1;
	obj->childnode.at(6)->p = obj;
	temp = bottomanticlockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(7)->lastmove = 7;
	obj->childnode.at(7)->depth = obj->depth + 1;
	obj->childnode.at(7)->p = obj;
	temp = frontclockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(8)->lastmove = 8;
	obj->childnode.at(8)->depth = obj->depth + 1;
	obj->childnode.at(8)->p = obj;
	temp = frontanticlockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(9)->lastmove = 9;
	obj->childnode.at(9)->depth = obj->depth + 1;
	obj->childnode.at(9)->p = obj;
	temp = backclockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(10)->lastmove = 10;
	obj->childnode.at(10)->depth = obj->depth + 1;
	obj->childnode.at(10)->p = obj;
	temp = backanticlockwise(obj->currentstate);
	obj->addchild(temp);
	obj->childnode.at(11)->lastmove = 11;
	obj->childnode.at(11)->depth = obj->depth + 1;
	obj->childnode.at(11)->p = obj;
}

int*** initializearray() {
	int ***a;
	a = new int**[6];
	for (int i = 0; i < 6; i++)
	{
		a[i] = new int*[3];
		for (int j = 0; j < 3; j++)
		{
			a[i][j] = new int[3];
		}
	}
	return a;

	/*for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{

				a[i][j][k] = 0;
				cout << a[i][j][k];
			}
		}
	}*/

}

bool comparison(int***a,int***b)
{
	int equal = 1;
	for (int i = 0; i < 6; i++) {

		//for each row
		for (int j = 0; j < 3; j++) {

			for (int k = 0; k < 3; k++) {


				if(a[i][j][k]!=b[i][j][k])
				{
					equal = 0;
					return equal;
				}

			}
		

		}
		return equal;

	}
	
}

int main() {
	int ***startcube = nullptr;
	int ***finalcube = nullptr;

	startcube=initializearray();
	finalcube=initializearray();


	storestate(startcube, finalcube);
	
	startcube = backclockwise((finalcube));
	//startcube = rightclockwise((startcube));
	//startcube = backanticlockwise(startcube);
	printcubestate(startcube);
	

	
	stack<cubenode *> s;
	cubenode * obj=new cubenode(startcube);
	s.push(obj);
	cubenode * a;
	while (!s.empty())
	{
		a = s.top();
		s.pop();
		cout << a->depth;
		//printcubestate(a->currentstate);
		if (comparison(a->currentstate, finalcube)) 
		{
			cout << "Rubric Solved" << endl;
			stack<int> r;
			while (a->p != nullptr)
			{
				int path = a->lastmove;
				r.push(path);
				a = a->p;

			}
			while (!r.empty())
			{
				cout << r.top();
				r.pop();
			}
		}

		else if (a->depth < 5)
		{
			createchild(a);
			for (int i = 0; i < 12; i++)
			{
				s.push(a->childnode.at(i));
			}
		}

		else 
		{
			cout << "rubric not solved" << endl;
			s.pop();
		}
	}
	
	system("pause");
	return 0;
}