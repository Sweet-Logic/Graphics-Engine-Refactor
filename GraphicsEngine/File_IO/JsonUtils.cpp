#include "JsonUtils.h"

#include <iostream>
#include <fstream> 
#include <Windows.h>

#include "../Utils/String/StringUtils.h"
#include "../Object/Components/ComponentList.h"
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;   \
   os_<< '\n';				\
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str()  );  \
}

namespace JsonUtils
{
    void Json::Release()
    {
        if(m_document!= nullptr)
        {
            ReleaseElement(m_document);
            delete m_document;
            m_document = nullptr;
        }   
    }

    void Json::ReleaseElement(JsonElement* element)
    {
        if(element != nullptr)
        {
            if(element->tag != nullptr)
            {
                delete element->tag;
            }
            if(element->type == E_Value)
            {
                delete static_cast<ValueElement*>(element)->element;
            }
            else if(element->type == E_Array)
            {
                ArrayElement* array = static_cast<ArrayElement*>(element);
                for(std::vector<JsonElement*>::size_type i = 0; i < array->elements.size(); ++i)
                {
                    ReleaseElement(array->elements[i]);
                    delete array->elements[i];
                    array->elements[i] = nullptr;
                }
                array->elements.clear();
            }
        }
    }


	JsonElement* Json::Find(char* tag)
    {
        if(StrUtils::GetLength(tag) > 0 && m_document)
        {
            return m_document->RecursiveFind(tag);
        }
		return nullptr;
    }

    JsonElement* JsonElement::RecursiveFind(char* tag)
    {
		if (this->tag != nullptr)
		{
			if (StrUtils::Compare(this->tag, tag))
			{
				return this;
			}
		}

        if(this->type == E_Array)
        {
            ArrayElement* array = static_cast<ArrayElement*>(this);
            for(std::vector<JsonElement*>::size_type i = 0; i < array->elements.size(); ++i)
            {
                JsonElement* foundElement = array->elements[i]->RecursiveFind(tag);
                if(foundElement != nullptr)
                {
                    return foundElement;
                }
            }
        }
		return nullptr;
    }

    bool Json::WriteToFile(char* filePath)
    {
        std::ofstream outfile(filePath);
        if (outfile.is_open())
        {
			std::stringstream output(ProcessJsonPair(m_document));
            outfile << output.str().c_str();
			DBOUT(output.str().c_str())
			
            outfile.close();
            return true;

        }
        return false;
    };

    bool Json::ReadFromFile(char* filePath)
    {
        std::ifstream inputfile(filePath);
		if (inputfile.is_open())
		{
			std::stringstream input;
			input << inputfile.rdbuf();

			char* line = new char[255];
			std::vector<char*> lineArr;
			while (input.getline(line, 255, '\n'))
			{
				lineArr.push_back(line);
				line = new char[255];
			}
			unsigned int index = 0;
			std::vector<JsonElement*> temp = ParseStream(lineArr, index);
			JsonElement* result = temp[0];
			if (result)
			{
				m_document = static_cast<ArrayElement*>(result);
				return true;
			}
        }
        return false;
    }

    std::stringstream Json::ProcessJsonPair(JsonElement* jsonPair)
    {
		static std::stringstream tabs;
		static int level = 0;
		std::stringstream ss = std::stringstream();
		bool hasTag = jsonPair->tag != nullptr;
		if(hasTag)
		{
			ss << tabs.str().c_str() << "\"" << jsonPair->tag << "\" : ";
		}
		if (jsonPair->type == E_Value)
		{
			ValueElement* value = static_cast<ValueElement*>(jsonPair);
			char* str = value->element;

			if (StrUtils::isNumber(str))
			{
				ss << str;
			}
			else
			{
				ss << '\"' << str << '\"';
			}
		}
		else if(jsonPair->type == E_Array)
		{
			if (hasTag)
			{
				ss << '\n';
			}
			ss << tabs.str().c_str() << '{';
			tabs << '\t';
			level++;

			ArrayElement* array = static_cast<ArrayElement*>(jsonPair);

			int arrayLength = array->elements.size();
			for (int i = 0; i < arrayLength; ++i)
			{
				ss << '\n';
				ss << ProcessJsonPair(array->elements.at(i)).str().c_str();
				if (i < arrayLength - 1)
				{
					ss << ',';
				}
			}
			level--;
			ss << '\n';
			ss << tabs.str().substr(0, level) << '}';
            if(level == 0)
            {
                tabs.clear();
                tabs.str("");
            }
		}
		else
		{
			//Hmmmmmmmm
		}
        return ss;
    }

    std::vector<JsonElement*> Json::ParseStream(std::vector<char*> stringArr, std::vector<char*>::size_type& index)
    {
		DBOUT("Line: " << index);
		std::stringstream ss;
		
        std::vector<JsonElement*> currentElements;
        JsonElement* element;

		std::vector<JsonElement*>::size_type currentIndex = 0;
        std::vector<char*> lines;
        //split proccess the stream
        char* line = new char[255];
		char* tag = nullptr;
        ss.getline(line, 255); //Read the current line up to 255 chars
		for(index; index < stringArr.size(); ++index)
		{   
			line = stringArr[index];
            for(int i = 0; line[i] != '\0'; ++i)
            {            
                switch(line[i])
                {
                    break;
                    case '"':
                    {
                        ++i;
                        std::vector<char> input;
                        while(line[i] != '"')
                        {
                            input.push_back(line[i]);
							++i;
                        }
						input.push_back('\0');
                        if(currentIndex == currentElements.size())
                        {
                            currentElements.push_back(nullptr);
							tag = new char[input.size()];
							for (std::vector<char>::size_type k = 0; k < input.size(); ++k)
							{
								tag[k] = input[k];
							}
                        }
                        else
                        {
							char* str = new char[input.size()];
							for (std::vector<char>::size_type k = 0; k < input.size(); ++k)
							{
								str[k] = input[k];
							}
                            //Value
							ValueElement* value = new ValueElement();
							value->tag = tag;
							tag = nullptr;
                            value->element = str;
							currentElements[currentIndex] = value;
                            ++currentIndex;
                        }
                        break;
                    }
                    case '[':
                    case '{':
                    {
						if (currentIndex == currentElements.size())
						{
							currentElements.push_back(nullptr);
						}
						ArrayElement* array = new ArrayElement();
						if (tag != nullptr)
						{
							array->tag = tag;
							tag = nullptr;
						}
						DBOUT("Line Before Array: " << index);
						++index;
						array->elements = ParseStream(stringArr, index);
						DBOUT("Line After Array: " << index);
						//j += array->elements.size();

						currentElements[currentIndex] = array;
						++currentIndex;
						break;
                    }
                    case ']':
                    case '}':
                        return currentElements;
                    break;
                    case ' '://skip
                    case '\t':
                    case '\n':
					case ':':
					case ',':
                    break;
                    default:
                    {
						//Value
						ValueElement* value = new ValueElement();
						value->tag = tag;
						currentElements[currentIndex] = value;

                        //check if character
                        //character is either white space, line break, value or something lol.
                        char* val;
                        int commas = 0, periods = 0, spaces = 0;
						std::vector<char> input;
						while (line[i] != '\0')
						{
							if (line[i] == ',' && line[i + 1] == '\0')
								break;
							input.push_back(line[i]);
							++i;
						}
						--i; // to ensure we dont access the character after the null term
						input.push_back('\0');

                        //check the type;
						char* str = new char[input.size()];
						for (std::vector<char>::size_type k = 0; k < input.size(); ++k)
						{
							str[k] = input[k];
						}
						value->element = str;
						currentElements[currentIndex] = value;
						++currentIndex;
                    }
                }
            }
        }

        return currentElements;
    }
}