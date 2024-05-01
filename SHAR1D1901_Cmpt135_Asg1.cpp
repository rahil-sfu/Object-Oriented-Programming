#include <iostream>
using namespace std;

class CMPT135_String
{
private:
	char *buffer;	//This will be the dynamic array to hold the characters
public:
	//static member function to compute the length of null terminated char arrays
	static int cstrlen(const char *cStr); 

	//Constructors
	CMPT135_String();
	CMPT135_String(const CMPT135_String &s);
	CMPT135_String(const char &c);
	CMPT135_String(const char *cStr); //*cStr is a null terminated char array

	//Destructor
	~CMPT135_String();

	//Assignment operators
	CMPT135_String& operator = (const CMPT135_String &s);
	CMPT135_String& operator = (const char &c);
	CMPT135_String& operator = (const char *cStr); //*cStr is a null terminated char array

	//Getter member functions
	int getLength() const;
	char& operator[](const int &index) const;

	//Setter member functions
	void append(const CMPT135_String &s);
	void append(const char &c);
	void append(const char *cStr); //*cStr is a null terminated char array
	
	//Other member functions
	int findCharIndex(const char &c) const;
	int reverseFindCharIndex(const char &c) const;
	CMPT135_String getSubString(const int &startIndex, const int &len) const;
	bool isSubString(const CMPT135_String &s) const;
	bool isSubString(const char *cStr) const; //*cStr is a null terminated char array
	void reverse();
	int countChar(const char &c) const;
	void removeChar(const char &c);
	void replaceChar(const char &c1, const char &c2);

	//Operator member functions
	CMPT135_String operator + (const CMPT135_String &s) const;
	CMPT135_String operator + (const char *cStr) const; //*cStr is a null terminated char array
	CMPT135_String operator + (const char &c) const;
	CMPT135_String& operator += (const CMPT135_String &s);
	CMPT135_String& operator += (const char *cStr); //*cStr is a null terminated char array
	CMPT135_String& operator += (const char &c);
	
	bool operator == (const CMPT135_String &s) const;
	bool operator == (const char *cStr) const; //*cStr is a null terminated char array
	bool operator != (const CMPT135_String &s) const;
	bool operator != (const char *cStr) const; //*cStr is a null terminated char array
	bool operator < (const CMPT135_String &s) const;
	bool operator < (const char *cStr) const; //*cStr is a null terminated char array
	bool operator > (const CMPT135_String &s) const;
	bool operator > (const char *cStr) const; //*cStr is a null terminated char array
	bool operator <= (const CMPT135_String &s) const;
	bool operator <= (const char *cStr) const; //*cStr is a null terminated char array
	bool operator >= (const CMPT135_String &s) const;
	bool operator >= (const char *cStr) const; //*cStr is a null terminated char array
	
	//Friend Functions (for operators)
	friend CMPT135_String operator + (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
	friend CMPT135_String operator + (const char &c, const CMPT135_String &s);
	friend bool operator == (const char *cStr, const CMPT135_String &s); //*cStr a null terminated char array
	friend bool operator != (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
	friend bool operator < (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
	friend bool operator > (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
	friend bool operator <= (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
	friend bool operator >= (const char *cStr, const CMPT135_String &s); //*cStr is a null terminated char array
	
	friend ostream& operator << (ostream &outputStream, const CMPT135_String &s);
	friend istream& operator >> (istream &inputStream, CMPT135_String &s);
	
};

int CMPT135_String::cstrlen(const char *cStr)
{
	int i=0;
	if (cStr==nullptr)
		return 0;
	else 
	{
		while(cStr[i]!='\0')
			i++;
		return i;
	}
	
} 

CMPT135_String::CMPT135_String()
{
	buffer=nullptr;
}
CMPT135_String::CMPT135_String(const CMPT135_String &s)
{
	int len= CMPT135_String::cstrlen(s.buffer);
	if (len>0)
	{
		this->buffer=new char[len+1];
		for (int i=0;i<len;i++)
			this->buffer[i]=s.buffer[i];
	}
	this->buffer[len]='\0';
}
CMPT135_String::CMPT135_String(const char &c)
{
	this->buffer= new char[2];
	this->buffer[0]=c;
	this->buffer[1]='\0';
}
CMPT135_String::CMPT135_String(const char *cStr)
{
	int len=CMPT135_String::cstrlen(cStr);
	if (len==0)
		buffer=nullptr;
	else 
	{
		this->buffer=new char [len+1];
		for (int i=0;i<len;i++)
			this->buffer[i]=cStr[i];
		this->buffer[len]='\0';
	}
}

CMPT135_String::~CMPT135_String()
{
	if (buffer != nullptr)
	{
		delete[] buffer;
		buffer = nullptr;
	}
}

CMPT135_String& CMPT135_String::operator = (const CMPT135_String &s) 
{
	int len1 = CMPT135_String::cstrlen(s.buffer);
	char* temp= new char[len1+1];
	for (int i=0;i<len1;i++)
		temp[i]=s.buffer[i];
	temp[len1]='\0';
	this->~CMPT135_String();
	this->buffer=temp;
	return *this;
	
}
CMPT135_String& CMPT135_String::operator = (const char &c)
{
	char* temp= new char[2];
	temp[0]=c;
	temp[1]='\0';
	this->~CMPT135_String();
	this->buffer=temp;
	return *this;

}
CMPT135_String& CMPT135_String::operator = (const char *cStr)
{
	int len=CMPT135_String::cstrlen(cStr);
	char* temp=new char[len+1];
	for (int i=0;i<len;i++)
		temp[i]=cStr[i];
	temp[len]='\0';
	this->~CMPT135_String();
	this->buffer=temp;
	return *this;
}

int CMPT135_String::getLength()const
{
	return CMPT135_String::cstrlen(this->buffer);
}
char& CMPT135_String::operator[](const int &index) const
{
	if (index>=0 && index<this->getLength())
	{
		return this->buffer[index];
	}
	else 
	{
		cout<<"ERROR!!, index out of bound j"<<endl;
		abort();
	}
}

void CMPT135_String::append(const CMPT135_String &s)
{
	int len2=s.getLength();
	int len1=this->getLength();
	char*temp= new char[len1+len2+1];
	for (int i=0;i<len1;i++)
		temp[i]=this->buffer[i];
	for (int i=len1,  j=0;j<len2;i++,j++)
		temp[i]=s.buffer[j];
	temp[len1+len2]='\0';
	this->~CMPT135_String();
	this->buffer=temp;
}
void CMPT135_String::append(const char &c)
{
	CMPT135_String temp=c;
	this->append(temp);
	/*
	int len=this->getLength();
	char*temp= new char[this->getLength()+2];
	for (int i=0;i<len;i++)
		temp[i]=this->buffer[i];
	temp[len]=c;
	temp[len+1]='\0';
	this->~CMPT135_String();
	this->buffer=temp;
	*/
}
void CMPT135_String::append(const char *cStr)
{
	/*
	int len1=this->getLength();
	int len2=CMPT135_String::cstrlen(cStr);
	char*temp= new char[len1+len2+1];
	for (int i=0;i<len1;i++)
		temp[i]=this->buffer[i];
	for (int i=len1,j=0;j<len2;i++,j++)
		temp[i]=cStr[j];
	temp[len1+len2]='\0';
	this->~CMPT135_String();
	this->buffer=temp;
	*/
	CMPT135_String temp=cStr;
	this->append(temp);
}

//other functions 
int CMPT135_String::findCharIndex(const char &c) const
{
	int len= this->getLength();
	for (int i=0;i<len;i++)
	{
		if (this->buffer[i]==c)
			return i;
		else 
			continue;
	}
	return -1;
}
int CMPT135_String::reverseFindCharIndex(const char &c) const
{
	int len=this->getLength();
	for (int i=len-1;i>=0;i--)
	{
		if (this->buffer[i]==c)
			return i;
		else 
			continue;
	}
	return -1;
}
CMPT135_String CMPT135_String::getSubString (const int &startIndex, const int &len) const
{
	char*temp;
	CMPT135_String tempN;
	int newlen= this->getLength();

	if (startIndex>=0 && startIndex<newlen)
	{
		int lenDiff =newlen-startIndex;
		if (len<=lenDiff)
			temp= new char[len+1];
		else 
			temp=new char[lenDiff+1];
		
		int j=0;
		for (int i=startIndex;;i++)
		{
			if(this->buffer[i]!='\0' && j<len)
			{
				temp[j]=this->buffer[i];
				j++;
			}
			else 
				break;
		}
		temp[j]='\0';
		tempN.buffer=temp;
		return tempN;
	}
	else 
		return tempN;
	
}
bool CMPT135_String::isSubString(const CMPT135_String &s) const
{
	int len=this->getLength();
	int lenN=s.getLength();
	for (int i=0;i<lenN;i++)
	{
		if (*this==s.getSubString(i,len))
			return true;
	}
	return false;
}
bool CMPT135_String::isSubString(const char *cStr) const
{
	int len=this->getLength();
	int lenN=CMPT135_String::cstrlen(cStr);
	CMPT135_String temp=cStr;
	for (int i=0;i<lenN;i++)
	{
		if (*this==temp.getSubString(i,len))
			return true;
	}
	return false;
}
void CMPT135_String::reverse()
{
	int len=this->getLength();
	char*temp=new char[len+1];
	for(int i=0,j=len-1;i<len;i++,j--)
		temp[i]=this->buffer[j];
	temp[len]='\0';
	this->~CMPT135_String();
	this->buffer=temp;
}
int CMPT135_String::countChar(const char &c) const
{
	int count=0;
	for (int i=0;i<this->getLength();i++)
	{
		if (this->buffer[i]==c)
			count++;
	}
	return count;
}
void CMPT135_String::removeChar(const char &c)
{
	int len=this->getLength();
	int repeat=this->countChar(c);
	char* temp=new char[len-repeat+1];
	int i=0;
	for (int j=0;j<len;j++)
	{
		if (this->buffer[j]!=c)
			{
				temp[i]=this->buffer[j];
				i++;
			}	
	}
	temp[len-repeat]='\0';
	this->~CMPT135_String();
	this->buffer=temp;
}
void CMPT135_String::replaceChar(const char &c1, const char &c2)
{
	int len= this->getLength();
	for (int i=0;i<len;i++)
	{
		if (this->buffer[i]==c1)
			this->buffer[i]=c2;
	}
}

//operator functions

CMPT135_String CMPT135_String::operator + (const CMPT135_String &s) const
{
	CMPT135_String temp=*this;
	temp.append(s);
	return temp;
}
CMPT135_String CMPT135_String::operator + (const char *cStr) const
{
	CMPT135_String temp=*this;
	temp.append(cStr);
	return temp;
}
CMPT135_String CMPT135_String::operator + (const char &c) const
{
	CMPT135_String temp=*this;
	temp.append(c);
	return temp;
}
CMPT135_String& CMPT135_String::operator += (const CMPT135_String &s)
{
	CMPT135_String temp = *this;
	this->~CMPT135_String();
	*this = temp+s;
	
	return *this;
}
CMPT135_String& CMPT135_String::operator += (const char *cStr)
{
	CMPT135_String temp=cStr;
	*this+=temp;
	return *this;
}
CMPT135_String& CMPT135_String::operator += (const char &c)
{
	CMPT135_String temp=c;
	*this+=temp;
	return *this;
}

bool CMPT135_String::operator == (const CMPT135_String &s) const
{
	int len = this->getLength();
	if (len != s.getLength())
		return false;
	else
	{
		for (int i = 0; i < len; i++)
		{
			if (buffer[i] != s[i])
				return false;
		}
		return true;
	}
}
bool CMPT135_String::operator == (const char *cStr) const
{
	int len = this->getLength();
	if (len != CMPT135_String::cstrlen(cStr))
		return false;
	else
	{
		for (int i = 0; i < len; i++)
		{
			if (buffer[i] != cStr[i])
				return false;
		}
		return true;
	}
}
bool CMPT135_String::operator != (const CMPT135_String &s) const
{
	if (*this==s)
		return false;
	else 
		return true;
}
bool CMPT135_String::operator != (const char *cStr) const
{
	if (*this==cStr)
		return false;
	else 
		return true;
}
bool CMPT135_String::operator < (const CMPT135_String &s) const
{
	int len;
	if (this->getLength()<=s.getLength())
		len=this->getLength();
	else
		len=s.getLength();
	int i=0;
	for (;i<len;)
	{
		if (this->buffer[i]<s.buffer[i])
			break;
		else 
			i++;
	}
	if (i<len)
		return true;
	else 
		return false;
	
}
bool CMPT135_String::operator < (const char *cStr) const
{
	CMPT135_String temp= cStr;
	if (*this<temp)
		return true;
	else 
		return false;
}
bool CMPT135_String::operator > (const CMPT135_String &s) const
{
	if (*this<s)
		return false;
	else
		return true;
}
bool CMPT135_String::operator > (const char *cStr) const
{
	if (*this<cStr)
		return false;
	else
		return true;
}
bool CMPT135_String::operator <= (const CMPT135_String &s) const
{
	if (*this<s || *this==s)
		return true;
	else
		return false;
}
bool CMPT135_String::operator <= (const char *cStr) const
{
	CMPT135_String temp= cStr;
	if (*this<temp || *this==temp)
		return true;
	else
		return false;

}
bool CMPT135_String::operator >= (const CMPT135_String &s) const
{
	if (*this>s || *this==s)
		return true;
	else 
		return false;
}
bool CMPT135_String::operator >= (const char *cStr) const
{
	CMPT135_String temp= cStr;
	if (*this>temp || *this==temp)
		return true;
	else
		return false;
}

//friend operators

CMPT135_String operator + (const char *cStr, const CMPT135_String &s)
{
	CMPT135_String temp=cStr;
	temp.append(s);
	return temp;
}
CMPT135_String operator + (const char &c, const CMPT135_String &s)
{
	CMPT135_String temp=c;
	temp.append(s);
	return temp;
}
bool operator == (const char *cStr, const CMPT135_String &s)
{
	CMPT135_String temp=cStr;
	if (temp==s)
		return true;
	else 
		return false;
}
bool operator != (const char *cStr, const CMPT135_String &s)
{
	CMPT135_String temp=cStr;
	if (temp==s)
		return false;
	else 
		return true;
}
bool operator < (const char *cStr, const CMPT135_String &s)
{
	CMPT135_String temp=cStr;
	if (temp<s)
		return true;
	else 
		return false;
}
bool operator > (const char *cStr, const CMPT135_String &s)
{
	CMPT135_String temp=cStr;
	if (temp>s)
		return true;
	else 
		return false;
}
bool operator <= (const char *cStr, const CMPT135_String &s)
{
	CMPT135_String temp=cStr;
	if (temp<s || temp==s)
		return true;
	else 
		return false;
}
bool operator >= (const char *cStr, const CMPT135_String &s)
{
	CMPT135_String temp=cStr;
	if (temp>s || temp==s)
		return true;
	else 
		return false;
}

//instream and ostream functions
ostream& operator << (ostream &outputStream, const CMPT135_String &s)
{
	for (int i = 0; i < s.getLength(); i++)
	outputStream << s.buffer[i];
	return outputStream;
}
istream& operator >> (istream &inputStream, CMPT135_String &s)
{
	int bufferCurrentLength = 5;
	char *buffer = new char[bufferCurrentLength];
	int length = 0;
	char c;
	while (true)
	{
		inputStream.get(c);
		if (c == '\n')
			break;
		if (length == bufferCurrentLength)

		{
			char *temp = new char[2*bufferCurrentLength];
			for (int i = 0; i < bufferCurrentLength; i++)
				temp[i] = buffer[i];

			delete[] buffer;
			
			buffer = temp;
			
			bufferCurrentLength *= 2;
		}
	
		buffer[length++] = c;
	}
		
		s.~CMPT135_String();
		
	if (length > 0)
	{
		s.buffer = new char[length + 1];
		for (int i = 0; i < length; i++)
		s.buffer[i] = buffer[i];
		s.buffer[length] = '\0';
	}
		
		delete[] buffer;
		return inputStream;
}

int main()
{
	
	//Test the cstrlen static member function'
	cout << "The length of \"Yonas\" is " << CMPT135_String::cstrlen("Yonas") << endl;
	cout << "The length of \"\" is " << CMPT135_String::cstrlen("") << endl;
	cout << "The length of nullptr is " << CMPT135_String::cstrlen(nullptr) << endl;

	//Test default constructor and getLength member functions
	CMPT135_String s1;
	cout << "s1 is \"" << s1 << "\" and its length is " << s1.getLength() << endl;
	
	//Test non-default constructor and getLength member functions
	CMPT135_String s2 = 'Y';
	cout << "s2 is \"" << s2 << "\" and its length is " << s2.getLength() << endl;

	//Test non-default constructor and getLength member functions
	CMPT135_String s3 = "CMPT 135";
	cout << "s3 is \"" << s3 << "\" and its length is " << s3.getLength() << endl;
	
	//Test copy constructor and getLength member functions
	CMPT135_String s4 = s3;
	cout << "s4 is \"" << s4 << "\" and its length is " << s4.getLength() << endl;
	
	//Test destructor and getLength member functions
	s4.~CMPT135_String();
	cout << "s4 is \"" << s4 << "\" and its length is " << s4.getLength() << endl;
	
	//Test assignment operator and getLength member functions
	s4 = s2;
	cout << "s4 is \"" << s4 << "\" and its length is " << s4.getLength() << endl;

	//Test assignment operator and getLength member functions
	s4 = 'A';
	cout << "s4 is \"" << s4 << "\" and its length is " << s4.getLength() << endl;

	//Test assignment operator and getLength member functions
	s4 = "This is cool";
	cout << "s4 is \"" << s4 << "\" and its length is " << s4.getLength() << endl;

	//Test indexing operator
	cout << "s4[2] is " << s4[2] << endl;
	s4[2] = 'u';
	cout << "s4[2] is " << s4[2] << endl;
	cout << "s4 is \"" << s4 << "\" and its length is " << s4.getLength() << endl;

	//Test append function and getLength member functions
	s1.append(s4);
	cout << "s1 is \"" << s1 << "\" and its length is " << s1.getLength() << endl;

	//Test append function and getLength member functions
	s3.append(' ');
	cout << "s3 is \"" << s3 << "\" and its length is " << s3.getLength() << endl;

	//Test append function and getLength member functions
	s3.append("201901");
	cout << "s3 is \"" << s3 << "\" and its length is " << s3.getLength() << endl;

	//Test findCharIndex function
	char ch = '1';
	int k = s3.findCharIndex(ch);
	cout << "The first index of '" << ch << "' in \"" << s3 << "\" is " << k << endl;
	ch = 'm';
	k = s3.findCharIndex('m');
	cout << "The first index of '" << ch << "' in \"" << s3 << "\" is " << k << endl;

	//Test reverseFindCharIndex function
	ch = '1';
	k = s3.reverseFindCharIndex(ch);
	cout << "The last index of '" << ch << "' in \"" << s3 << "\" is " << k << endl;
	ch = 'm';
	k = s3.reverseFindCharIndex('m');
	cout << "The last index of '" << ch << "' in \"" << s3 << "\" is " << k << endl;

	//Test getSubString function
	s1 = s3.getSubString(10, 3);
	cout << "s1 is \"" << s1 << "\" and its length is " << s1.getLength() << endl;
	s1 = s3.getSubString(10, 5);
	cout << "s1 is \"" << s1 << "\" and its length is " << s1.getLength() << endl;
	s1 = s3.getSubString(10, 8);
	cout << "s1 is \"" << s1 << "\" and its length is " << s1.getLength() << endl;
	
	//Test isSubString function
	if (s1.isSubString(s3) == true)
		cout << "\"" << s1 << "\" is a substring of \"" << s3 << "\"" << endl;
	else
		cout << "\"" << s1 << "\" is not a substring of \"" << s3 << "\"" << endl;
	s2 = "01902029010190";
	if (s1.isSubString(s2) == true)
		cout << "\"" << s1 << "\" is a substring of \"" << s2 << "\"" << endl;
	else
		cout << "\"" << s1 << "\" is not a substring of \"" << s2 << "\"" << endl;
	char x[] = "01902019010190";
	if (s1.isSubString(x) == true)
		cout << "\"" << s1 << "\" is a substring of \"" << x << "\"" << endl;
	else
		cout << "\"" << s1 << "\" is not a substring of \"" << x << "\"" << endl;
	
	//Test reverse function
	cout << "s1 is \"" << s1 << "\" and its length is " << s1.getLength() << endl;
	s1.reverse();
	cout << "After reversing it, s1 is \"" << s1 << "\" and its length is " << s1.getLength() << endl;
	
	//Test countChar function
	ch = '1';
	k = s1.countChar(ch);
	cout <<  "'" << ch << "' appears " << k << " times in \"" << s1 << "\"" << endl;

	//Test the removeChar function
	cout << "After removing all the '" << ch << "' characters from \"" << s1 << "\", we get ";
	s1.removeChar(ch);
	cout << "\"" << s1 << "\"" << endl;
	s3 = "11111111111";
	cout << "After removing all the '" << ch << "' characters from \"" << s3 << "\", we get ";
	s3.removeChar(ch);
	cout << "\"" << s3 << "\"" << endl;
	
	//Test replaceChar function
	cout << "After replacing 1 by 5 from \"" << s2 << "\", we get ";
	s2.replaceChar('1', '5');
	cout << s2 << endl;
	
	//Test + operator
	cout << "s1 is \"" << s1 << "\", s3 is \"" << s3 << "\" and s1 + s3 is \"" << s1 + s3 << "\"" << endl;
	cout << "s1 is \"" << s1 << " and s1 + \"yonas\" is \"" << s1 + "yonas" << endl;
	cout << "s1 is \"" << s1 << " and s1 + 'Y' is \"" << s1 + 'Y' << endl;
	
	//Test += operatror
	s2 = "Test";
	cout << "s1 is " << s1 <<", s2 is " << s2 << ", and s3 is " << s3 << endl;
	s3 = s1 += s2;
	cout << "After s3 = s1 += s2, we get s1 is " << s1 <<", s2 is " << s2 << ", and s3 is " << s3 << endl;

	cout << "s2 is \"" << s2 << "\". ";
	s2 += "FIC";
	cout << "After s2 += \"FIC\", we get \"" << s2 << "\"" << endl; 
	cout << "s2 is \"" << s2 << "\". ";
	s2 += '!';
	cout << "After s2 += '!', we get \"" << s2 << "\"" << endl;

	//Test relational operators
	s1 = "Test1";
	s2 = "";
	cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 == s2 is " << (s1 == s2) << endl;
	cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 != s2 is " << (s1 != s2) << endl;
	cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 > s2 is " << (s1 > s2) << endl;
	cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 < s2 is " << (s1 < s2) << endl;
	cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 >= s2 is " << (s1 >= s2) << endl;
	cout << "s1 is \"" << s1 << "\", s2 is \"" << s2 << "\" and s1 <= s2 is " << (s1 <= s2) << endl;

	//Test + friend functions
	cout << "\"Yonas\" + \"" << s1 << "\" is \"" << "Yonas" + s1 << "\"" << endl;
	cout << "'y' + \"" << s1 << "\" is \"" << 'y' + s1 << "\"" << endl;

	//Test friend relational operators
	cout << "s1 is \"" << s1 << "\" and \"Test2\" == s1 is " << ("Test2" == s1) << endl;
	cout << "s1 is \"" << s1 << "\" and \"Test2\" != s1 is " << ("Test2" != s1) << endl;
	cout << "s1 is \"" << s1 << "\" and \"Test2\" < s1 is " << ("Test2" < s1) << endl;
	cout << "s1 is \"" << s1 << "\" and \"Test2\" > s1 is " << ("Test2" > s1) << endl;
	cout << "s1 is \"" << s1 << "\" and \"Test2\" <= s1 is " << ("Test2" <= s1) << endl;
	cout << "s1 is \"" << s1 << "\" and \"Test2\" >= s1 is " << ("Test2" >= s1) << endl;

	//Test input stream operator
	cout << "Enter a string of any length you want (including spaces, punctuation marks, etc if you wish): ";
	cin >> s1;
	cout << "You entered \"" << s1 << "\"" << endl;


	system("pause");
	return 0;
}

