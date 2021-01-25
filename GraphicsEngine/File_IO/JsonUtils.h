#ifndef _JSON_UTILS_H_
#define _JSON_UTILS_H_

#include <ostream>
#include <iostream>
#include <sstream>
#include <vector>

namespace JsonUtils
{

    //  enum Json_Type
    //  {
    //      E_NONE = 0x00,
    //      E_INT,
    //      E_UINT,
    //      E_LINT,
    //      E_LLINT,
    //      E_FLOAT,
    //      E_DOUBLE,
    //      E_PCHAR,
    //      E_VECTOR2,
    //      E_VECTOR3,
    //      E_QUATERNION,
    //      E_BOOL,

    //      E_ARRAY,
    //      E_JSON_ELEMENTS,

    //E_COUNT
    //  };

    enum ElementType
    {
        E_Value,
        E_Array
    };

    struct JsonElement
    {
        JsonElement(ElementType _type) : type(_type) {}
        JsonElement(char *_tag, ElementType _type) : tag(_tag), type(_type) {}
        ElementType type;
        char *tag = nullptr;
        JsonElement *RecursiveFind(char *tag);
    };

    struct ValueElement : public JsonElement
    {
        ValueElement() : JsonElement(E_Value) {}
        ValueElement(char *_tag, char *_value) : JsonElement(_tag, E_Value), element(_value) {}
        char *element;
    };

    struct ArrayElement : public JsonElement
    {
        ArrayElement() : JsonElement(E_Array) {}
        ArrayElement(char *_tag, std::vector<JsonElement *> _value) : JsonElement(_tag, E_Array), elements(_value) {}
        std::vector<JsonElement *> elements;
    };

    //  struct JsonElement // "char*" : value
    //  {
    //      char* tag = nullptr;
    //      Json_Type valueType = Json_Type::E_NONE;
    //int valueCount = 1;
    //      void* value = nullptr;
    //  };

    struct Json
    {
    public:
        Json() {};
        ~Json() { Release(); }
        JsonElement *m_document;
        JsonElement *Find(char *tag);

        bool WriteToFile(char *filePath);
        bool ReadFromFile(char *filePath);

        void Release();
    private:
        void ReleaseElement(JsonElement *element);
        std::stringstream ProcessJsonPair(JsonElement *pair);
        std::vector<JsonElement *> ParseStream(std::vector<char *> stream, std::vector<char*>::size_type& index );
        //void ParseString(char* string, JsonElement* currentElement);
    };
} // namespace JsonUtils

#endif //!_JSON_UTILS_H_