#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

namespace StrUtils
{
    template<class T>
    static char* ToString(T value)
    {
         std::stringstream ss;
        ss << value;
		const std::string& tmp = ss.str();
		char* chara = new char[tmp.length()+1];
		tmp.copy(chara, tmp.length());
		chara[tmp.length()] = '\0';
		ss.str("");
        return chara;
    }
    
    static int GetLength(char* str)
    {
		char* temp = str;
        int length = 0;
        while(*(temp) != '\0' && ++temp)
            ++length;
        
        return length;
    }

    static char* Append(char* left, char* right)
    {
		char *tempL = left, *tempR = right;

        int length = GetLength(tempL) + GetLength(tempR);

        char* newStr = new char[length];
        for(int i = 0; i < length+1; ++i)
        {
            if(*tempL != '\0')
            {
                newStr[i] = (*tempL);
                ++tempL;
            }
            else
            {
                newStr[i] = (*tempR);
                ++tempR;
            }
        }

        return newStr;
    }

	static int Find(char* str, char c, int startIndex = 0)
	{
		int length = GetLength(str);
		_ASSERT_EXPR(length > startIndex, "The start index was greater than the length of the string!");
        for(int i = startIndex; str[i] != '\0'; ++i)
		{
			if(str[i] == c)
				return i;
		}
        
        return -1;
	}

	static int rFind(char* str, char c)
	{
		int length = GetLength(str);
		for(int i = length; i > -1; --i)
		{
			if(str[i] == c)
				return i;
		}
		return -1;
	}

	static char* copy(char* str, int startIndex, int count)
	{
		char* ret = new char[count + 1];
		for (int i = 0; i < count; ++i)
		{
			ret[i] = str[startIndex + i];
		}
		ret[count] = '\0';

		return ret;
	}

	static bool isNumber(char* s)
	{
		char* str = s;
		while (*str)
		{
			int val = (*str) - '0';
			if (!(val > 0 && val < 10) && (*str) != '-')
			{
				return false;
				break;
			}
			++str;
		}
		return true;
	}
    static unsigned long stoul(char* s)
	{
		unsigned long num = 0;
		while (*s) {
			num = ((*s) - '0') + num * 10;
			s++;
		}
		return num;
	}
    
    static long stol(char* s)
	{
		long sign = 1;
		if (*s == '-') {
			sign = -1;
			s++;
		}
		return stoul(s) * sign;
	}

	static unsigned int stoui(char* s)
	{
		unsigned int num = 0;
		while (*s) {
			num = ((*s) - '0') + num * 10;
			s++;
		}
		return num;
	}

	static int stoi(char* s)
	{
		int sign = 1;
		if (*s == '-') {
			sign = -1;
			s++;
		}
		int num = 0;
		while (*s) {
			num = ((*s) - '0') + num * 10;
			s++;
		}
		return num * sign;
	}

	static float stof(char* s)
	{
		int sign = 1;
		if (*s == '-') {
			sign = -1;
			s++;
		}
		float num = 0;
		int decimal = 0;
		while (*s) {
			if (*s == '.')
			{
				decimal = 10;
			}
			if (!decimal)
			{
				num = ((*s) - '0') + num * 10;
			}
			else
			{
				num = (((*s) - '0')/10) + num;
				decimal *= 10;
			}
			s++;
		}
		return num * sign;
	}

	static double stod(char* s)
	{
		int sign = 1;
		if (*s == '-') {
			sign = -1;
			s++;
		}
		double num = 0;
		int decimal = 0;
		while (*s) {
			if (*s == '.')
			{
				decimal = 10;
			}
			if (!decimal)
			{
				num = ((*s) - '0') + num * 10;
			}
			else
			{
				num = (((*s) - '0') / 10) + num;
				decimal *= 10;
			}
			s++;
		}
		return num * sign;
	}

	static bool Compare(char* s1, char* s2)
	{
		if (!s1 || !s2)
		{
			return false;
		}
		char *tmp1 = s1, *tmp2 = s2;
		while (*tmp1)
		{
			if (!(*tmp2 && (*tmp1) == (*tmp2))) // if tmp2 is null or they are not the same return false
				return false;
			++tmp1; ++tmp2;
		}
		if (*tmp2) 
			return false; //tem1 was null before tmp2
		return true;
	}
}

#endif //!_STRING_UTILS_H_