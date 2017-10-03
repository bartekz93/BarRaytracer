#include<fstream>
#include"Shaders.h"

using namespace framework;
using namespace renderer;

void CompiledPixelShader::OnRelease()
{
	if (Data)
	{
		delete[] Data;
		Data = NULL;
	}
}

bool CompiledPixelShader::SaveToFile(const string& file)
{
	std::ofstream File;
	File.open(file.c_str(), std::ios::binary);

	if (!File.good())
	{
		Logger::Error("Nie uda³o otworzyc sie pliku " + file);
		return false;
	}

	File.write((char*)&Size, sizeof(int));
	File.seekp(sizeof(int));
	File.write((char*)Data, Size);
	File.close();

	return true;
}

bool CompiledPixelShader::LoadFromFile(const string& file)
{
	std::ifstream File;
	if (!File.good())
	{
		Logger::Error("Nie uda³o otworzyc sie pliku " + file);
		return false;
	}
	File.open(file.c_str(), std::ios::binary);
	File.read((char*)&Size, 4);
	Data = new char[Size];
	File.seekg(4);
	File.read(Data, Size);
	File.close();

	return true;
}