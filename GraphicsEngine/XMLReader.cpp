#include "XMLReader.h"
#include <iostream>
#include <fstream>


namespace XML
{
	XMLReader::XMLReader(std::string XMLfile)
	{
		//Load XML FILE
		std::ifstream stream = std::ifstream(XMLfile);
		std::string input;

		Tag ParentTag;
		std::vector<std::string> XMLFile;

		while (std::getline(stream, input))
		{
			XMLFile.push_back(input);
		}
		stream.close();
		int i = 0;
		while (XMLFile.size() != i)
		{
			if (XMLFile.at(i).find('<') != -1)
			{
				baseTags.push_back(LoadTag(XMLFile, i));
			}
			i++;
		}
	}



	XMLReader::~XMLReader()
	{
	}

	Tag XMLReader::GetFirstTag(std::string tagID)
	{
		for (int i = 0; i < baseTags.size(); i++)
		{
			if (baseTags.at(i).tagIdentifier == tagID)
			{
				return baseTags.at(i);
			}
		}
		return Tag();
	}

	std::vector<Tag> XMLReader::GetTags(std::string tagID)
	{
		std::vector<Tag> output;
		for (int i = 0; i < baseTags.size(); i++)
		{
			if (baseTags.at(i).tagIdentifier == tagID)
			{
				output.push_back(baseTags.at(i));
			}
		}
		return output;
	}

	Tag XMLReader::LoadTag(std::vector<std::string> XML, int &currentPosition)
	{
		Tag thisTag;
		int start = XML.at(currentPosition).find('<') + 1;
		int end = XML.at(currentPosition).find('>');
		if (end > XML.at(currentPosition).find(' ', start))
		{
			end = XML.at(currentPosition).find(' ', start);
		}
		thisTag.tagIdentifier = XML.at(currentPosition).substr(start, end - start);

		int space = XML.at(currentPosition).find(' ', start);
		while (space != -1)
		{
			//find '=' space to '=' is paramatername
			int equals = XML.at(currentPosition).find('=', (space + 1));
			Parameters newParam;
			if (equals == -1)
			{
				break;
			}

			newParam.Name = XML.at(currentPosition).substr((space + 1), (equals)-(space + 1));
			space = XML.at(currentPosition).find(' ', (space + 1));
			if (space != -1)
			{
				newParam.Value = XML.at(currentPosition).substr((equals + 2), (space - 2) - (equals + 1));
			}
			else
			{
				newParam.Value = XML.at(currentPosition).substr((equals + 2), (XML.at(currentPosition).find('>') - 2) - (equals + 1));
			}

			//'=' to next space or end is parameter value

			thisTag.parameters.push_back(newParam);
		}

		currentPosition++;

		for (0; currentPosition < XML.size(); ++currentPosition)
		{
			int start = XML.at(currentPosition).find('<') + 1;
			int end = XML.at(currentPosition).find('>');
			int endTag = XML.at(currentPosition).find("</");


			if (start != -1 && end != -1)
			{
				if (endTag + 1 == start) // if the tag doesnt start on this line but ends
				{
					//End this Tag
					return thisTag;
				}
				else if (endTag != -1)
				{
					//Create a child tag
					Tag newTag;

					newTag.tagIdentifier = XML.at(currentPosition).substr(start, end - start);
					newTag.Text = XML.at(currentPosition).substr(end + 1, (endTag)-(end + 1));

					thisTag.childTags.push_back(newTag);
				}
				else // if the tag starts and ends on this line
				{
					thisTag.childTags.push_back(LoadTag(XML, currentPosition));


				}
				//Opening Tag
			}
			else
			{
				thisTag.Text += XML.at(currentPosition);
			}
		}
		return thisTag;
	}

}