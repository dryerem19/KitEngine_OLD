#include "pch.h"
#include "KitModelFile.h"


void KitModelFile::Serialize()
{
    std::ofstream out(description.filepath, std::ios::binary);
    out.write((char*)&header, sizeof(header));

    size_t size_filepath = description.filepath.size();
    out.write((char*)&size_filepath, sizeof(size_filepath));
    out.write((char*)&description.filepath[0], size_filepath);

    size_t size_name = description.name.size();
    out.write((char*)&size_name, sizeof(size_name));
    out.write((char*)&description.name[0], size_name);

    out.close();
}

void KitModelFile::Deserialize(const std::string& filepath)
{
    std::ifstream input(filepath, std::ios::binary);
    input.read((char*)&header, sizeof(header));
    mIsValid = header.version == KMF_VERSION;
    if(!mIsValid)
    {
        return;
    }

    size_t size_filepath = 0;
    input.read((char*)&size_filepath, sizeof(size_t));
    description.filepath.resize(size_filepath);
    input.read((char*)&description.filepath[0], size_filepath);

    size_t size_name = 0;
    input.read((char*)&size_name, sizeof(size_t));
    description.name.resize(size_name);
    input.read((char*)&description.name[0], size_name);

    input.close();
}