/**
 * @file KitModelFile.h
 * @author Eugeniy Dubasov (dubasov.eugeni@yandex.ru)
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright Eugeniy Dubasov (c) 2022
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once
#include "Interfaces/ISerialization.h"
#include "Interfaces/IDeserialization.h"
#include "KitVertex.h"

#define KMF_VERSION 1

struct KMFHeader
{
    uint8_t version;
};

struct KMFDescription
{
    std::string filepath;
    std::string name;
};

struct KMFMesh final
{
    /* Имя сетки*/
    std::string name;

    /* Путь к материалу сетки */
    std::string material;

    /* Данные индексов сетки */
    std::vector<uint32_t> indices;

    /* Данные вершин сетки */
    std::vector<Render::KitVertex> vertices;
};

struct KMFNode final
{
    std::string name;

    KMFNode* pParent = nullptr;
    
    std::vector<KMFMesh> meshes;
    std::vector<std::shared_ptr<KMFNode>> children;

    KMFNode() = default;
    ~KMFNode() = default;
};

class KitModelFile final : private ISerialization, private IDeserialization
{
public:
    KMFHeader header;
    KMFDescription description;
    std::unique_ptr<KMFNode> root;

    /**
     * @brief Сериализация данных сетки в .kmf файл
     * 
     * @param filepath путь к .kmf файлу на диске
     */
    void Serialize(const std::string& filepath) override final;

    /**
     * @brief Десериализация данных сетки из .kmf файла
     * 
     * @param filepath путь к файлу на диске
     */
    void Deserialize(const std::string& filepath) override final;

    /**
     * @brief Проверяет корректно ли был считан файл
     * * Значение по умолчнию всегда true, если вы создаёте новый экземпляр
     * 
     * @return true Если файл считан корректно
     * @return false Если в процессе чтения произошли ошибки
     */
    inline bool IsValid() const { return mIsValid; }

private:

    /**
     * @brief Запись данных сетки в файл
     * 
     * @param out поток вывода 
     * @param pKmfMesh указатель на сетку, из которой нужно прочитать данные
     */
    void WriteMesh(std::ofstream& out, KMFMesh* pKmfMesh);

    /**
     * @brief Запись узла и всех дочерних сеток в файл 
     * * Функция не записывает дочерние узлы
     * 
     * @param out поток вывода
     * @param pParentKmfNode указатель на узел, который нужно записать
     */
    void WriteNode(std::ofstream& out, KMFNode* pParentKmfNode);

    /**
     * @brief Чтение сеток из файла в узел 
     * 
     * @param input поток ввода
     * @param pParentKmfNode куда считать данные
     */
    void ReadNodeMeshes(std::ifstream& input, KMFNode* pParentKmfNode);

    /**
     * @brief Чтение родительского узла
     * 
     * @param input поток ввода
     */
    void ReadRootNode(std::ifstream& input);

    /**
     * @brief Чтение узла
     * 
     * @param input поток ввода
     * @return std::shared_ptr<KMFNode> считанный узел 
     */
    std::shared_ptr<KMFNode> ReadNode(std::ifstream& input);

private:
    bool mIsValid = true;
};
