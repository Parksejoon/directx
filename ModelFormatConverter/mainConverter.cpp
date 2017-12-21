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


	// �������� �̸��� �ҷ����Դϴ�.
	GetModelFilename(filename);

	// ������ ����ü���� �ʱ�ȭ�ɼ� �ֵ���	����, �ؽ���, �븻����, ǥ����� �о���Դϴ�.
	result = ReadFileCounts(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	// ȭ�鿡 ���Ϸκ��� �ҷ��� �����͵��� ǥ���մϴ�
	cout << endl;
	cout << "Vertices: " << vertexCount << endl;
	cout << "UVs:      " << textureCount << endl;
	cout << "Normals:  " << normalCount << endl;
	cout << "Faces:    " << faceCount << endl;

	// ������ �����͸� �о�鿩 ������ ����ü�� �ְ� Ŀ���� �������� �����Ͽ� ����մϴ�.
	result = LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	// �������� ��ȯ�� �Ϸ�Ǿ����� �˸��ϴ�.
	cout << "\nFile has been converted." << endl;
	cin >> garbage;

	return 0;
}

void GetModelFilename(char* filename)
{
	bool done;
	ifstream fin;


	// ������ �̸��� ���� �� ���� �ݺ��մϴ�.
	done = false;
	while (!done)
	{
		// �������� ������ �̸��� ����ϴ�.
		cout << "Enter model filename: ";

		// ������ �̸��� �н��ϴ�.
		cin >> filename;

		// ������ ����ϴ�.
		fin.open(filename);

		if (fin.good())
		{
			// ���� ���⿡ �������� �����ϸ� �����ϴ�.
			done = true;
		}
		else
		{
			// ���� ���⿡ ������ ������ �˸��� �ݴϴ�.
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


	// count���� �ʱ�ȭ�մϴ�.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// ������ ���ϴ�.
	fin.open(filename);

	// ���� ���⿡ �����ߴ��� Ȯ���մϴ�.
	if (fin.fail() == true)
	{
		return false;
	}

	// ������ ������ �о���Դϴ�.
	fin.get(input);
	while (!fin.eof())
	{
		// ���� ���� v�� �����Ѵٸ� ����, �ؽ���, �븻�����Դϴ�.
		if (input == 'v')
		{
			fin.get(input);

			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// ���� ���� f�� �����Ѵٸ� ǥ���� ������ ������ŵ�ϴ�.
		if (input == 'f')
		{
			fin.get(input);

			if (input == ' ') { faceCount++; }
		}

		// ���� �������κ��� ó���մϴ�.
		while (input != '\n')
		{
			fin.get(input);
		}

		// ���� ���� �н��ϴ�.
		fin.get(input);
	}

	// ������ �ݽ��ϴ�.
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


	// �װ��� ������ ����ü�� �ʱ�ȭ�մϴ�.
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

	// �ε������� �ʱ�ȭ�մϴ�.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// �б� ������ ���ϴ�.
	fin.open(filename);

	// ���� ���⿡ �����ߴ��� üũ�մϴ�.
	if (fin.fail() == true)
	{
		return false;
	}

	// ����, �ؽ���, �븻���͸� �о� ������ ����ü�� �ֽ��ϴ�.
	// ���� ������ �޼� ��ǥ�踦 ������ ��ǥ�� �ý������� ��ȯ�մϴ�.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// �������� �н��ϴ�.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;
				
				// �޼� ��ǥ�踦 ��ȯ�մϴ�.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++; 
			}

			// �ؽ��ĸ� �о���Դϴ�.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;
				
				// �޼� ��ǥ�踦 �����մϴ�.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			// �븻���͸� �н��ϴ�.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;
				
				// �޼� ��ǥ�踦 ��ȯ�մϴ�.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// ǥ���� �н��ϴ�.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// ǥ�� �����͸� �о� ������ �ٲ����ν� ��ǥ�踦 ��ȯ�մϴ�.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
				    >> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
				    >> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// �ش� ���� �����κ��� �н��ϴ�.
		while (input != '\n')
		{
			fin.get(input);
		}

		// �������� �б� �����մϴ�.
		fin.get(input);
	}

	// ������ �ݽ��ϴ�.
	fin.close();

	// ������ ��������� ���ϴ�.
	fout.open("model.txt");

	// Ŀ���� �������� ����� ����մϴ�.
	fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data: " << endl;
	fout << endl;

	// ������ ǥ����� ����մϴ�.
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

	// ������ �ݽ��ϴ�.
	fout.close();

	// ������ ����ü���� �����մϴ�.
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
