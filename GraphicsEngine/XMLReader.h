#pragma once
#include <string>
#include <vector>

namespace XML
{
	struct Parameters
	{
		std::string Name;
		std::string Value;
	};

	struct Tag
	{
		std::string tagIdentifier = "EMPTY";

		std::vector<Tag> childTags;
		std::vector<Parameters> parameters;
		std::string Text = "";

		Tag GetChildTag(std::string tag)
		{
			
			for (int i = 0; i < childTags.size(); i++)
			{
				if (childTags.at(i).tagIdentifier != tag)
				{
					Tag output = childTags.at(i).GetChildTag(tag);
					if (output.tagIdentifier == tag)
					{
						return output;
					}
				}
				else
				{
					return childTags.at(i);

				}
			}

			return Tag();
		}


	};

	class XMLReader
	{
	public:
		XMLReader(std::string XMLfile);
		~XMLReader();

		Tag GetFirstTag(std::string tagID);

		std::vector<Tag> GetTags(std::string tagID);

	private:

		Tag LoadTag(std::vector<std::string> XML, int &currentPosition);
		std::vector<Tag> baseTags;
	};
}