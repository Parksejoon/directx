//
// FileName : mainConverter.cpp
//


//
// INCLUDES
//
#include <iostream>
#include <fstream>

using namespace std;


//
// TYPEDEFS
//
typedef struct
{
	float x, y, z;
} VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
} FaceType;


//
// FUNCTION PROTOTYPES
//
void GetModelFilename(char*);
bool ReadFileCounts(char*, int&, int&, int&, int&);
bool LoadDataStructures(char*, int, int, int, int);


//
// MAIN PROGRAM
//
int main()
{
	bool result;
	char filename[256];
	int vertexCount, textureCount, normalCount, faceCount;
	char garbage;


	// 모델파일의 이름을 불러들입니다.
	GetModelFilename(filename);

	// 데이터 구조체들이 초기화될수 있도록	정점, 텍스쳐, 노말벡터, 표면들을 읽어들입니다.
	result = ReadFileCounts(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	// 화면에 파일로부터 불러온 데이터들을 표시합니다
	cout << endl;
	cout << "Vertices: " << vertexCount << endl;
	cout << "UVs:      " << textureCount << endl;
	cout << "Normals:  " << normalCount << endl;
	cout << "Faces:    " << faceCount << endl;

	// 파일의 데이터를 읽어들여 데이터 구조체에 넣고 커스텀 포맷으로 변경하여 출력합니다.
	result = LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	// 유저에게 변환이 완료되었음을 알립니다.
	cout << "\nFile has been converted." << endl;
	cin >> garbage;

	return 0;
}

void GetModelFilename(char* filename)
{
	bool done;
	ifstream fin;


	// 파일의 이름을 받을 때 까지 반복합니다.
	done = false;
	while (!done)
	{
		// 유저에게 파일의 이름을 물어봅니다.
		cout << "Enter model filename: ";

		// 파일의 이름을 읽습니다.
		cin >> filename;

		// 파일을 열어봅니다.
		fin.open(filename);

		if (fin.good())
		{
			// 파일 열기에 문제없이 성공하면 끝냅니다.
			done = true;
		}
		else
		{
			// 파일 열기에 문제가 있으면 알림을 줍니다.
			fin.clear();
			cout << endl;
			cout << "File " << filename << " could not be opened." << endl << endl;
		}
	}

	return;
}

bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;


	// count들을 초기화합니다.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// 파일을 엽니다.
	fin.open(filename);

	// 파일 열기에 성공했는지 확인합니다.
	if (fin.fail() == true)
	{
		return false;
	}

	// 파일의 끝까지 읽어들입니다.
	fin.get(input);
	while (!fin.eof())
	{
		// 만약 줄이 v로 시작한다면 정점, 텍스쳐, 노말벡터입니다.
		if (input == 'v')
		{
			fin.get(input);

			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// 만약 줄이 f로 시작한다면 표면의 갯수를 증가시킵니다.
		if (input == 'f')
		{
			fin.get(input);

			if (input == ' ') { faceCount++; }
		}

		// 줄의 나머지부분을 처리합니다.
		while (input != '\n')
		{
			fin.get(input);
		}

		// 다음 줄을 읽습니다.
		fin.get(input);
	}

	// 파일을 닫습니다.
	fin.close();

	return true;
}

bool LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount)
{
	VertexType *vertices, *texcoords, *normals;
	FaceType *faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	ofstream fout;


	// 네가지 데이터 구조체를 초기화합니다.
	vertices = new VertexType[vertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new VertexType[textureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new VertexType[normalCount];
	if (!normals)
	{
		return false;
	}

	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}

	// 인덱스들을 초기화합니다.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// 읽기 파일을 엽니다.
	fin.open(filename);

	// 파일 열기에 성공했는지 체크합니다.
	if (fin.fail() == true)
	{
		return false;
	}

	// 정점, 텍스쳐, 노말벡터를 읽어 데이터 구조체에 넣습니다.
	// 또한 마야의 왼손 좌표계를 오른손 좌표계 시스템으로 변환합니다.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// 정점들을 읽습니다.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;
				
				// 왼손 좌표계를 변환합니다.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++; 
			}

			// 텍스쳐를 읽어들입니다.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;
				
				// 왼손 좌표계를 변한합니다.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			// 노말벡터를 읽습니다.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;
				
				// 왼손 좌표계를 변환합니다.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// 표면을 읽습니다.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// 표면 데이터를 읽어 순서를 바꿈으로써 좌표계를 변환합니다.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
				    >> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
				    >> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// 해당 줄의 남은부분을 읽습니다.
		while (input != '\n')
		{
			fin.get(input);
		}

		// 다음줄을 읽기 시작합니다.
		fin.get(input);
	}

	// 파일을 닫습니다.
	fin.close();

	// 파일을 쓰기용으로 엽니다.
	fout.open("model.txt");

	// 커스텀 포맷으로 헤더를 기록합니다.
	fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data: " << endl;
	fout << endl;

	// 각각의 표면들을 기록합니다.
	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			 << texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			 << normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].vIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			 << texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			 << normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].vIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
 			 << texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
	 		 << normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
	}

	// 파일을 닫습니다.
	fout.close();

	// 데이터 구조체들을 해제합니다.
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}

	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}

	if (normals)
	{
		delete[] normals;
		normals = 0;
	}

	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}
