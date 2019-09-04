#ifndef POKEMON_H_INCLUDED
#define POKEMON_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Pokemon
{
private:
	string ID;         // UNIQUE ID
	string name;
	double weight;
	string type;
	string gender;
	double height;


public:
	// constructors
	Pokemon(){}
	Pokemon(const string  id, const string  NAME, const double WEIGHT, const string TYPE, const string GENDER, const double HEIGHT)
            {ID = id; name = NAME; weight = WEIGHT; type = TYPE; gender = GENDER; height = HEIGHT;}

	// accessors
	void setID(const string  id) {ID = id;}
	void setName(const string  aName) {name = aName;}
	void setWeight (const double  aWeight){weight = aWeight;}
	void setType (const string aType){type = aType;}
	void setGender (const string aGender){gender = aGender;}
	void setHeight (const double  aHeight){height = aHeight;}

	// mutators
    string getID() const {return ID;}
	string getName() const {return name;}
	double getWeight() const {return weight;}
	string getType() const {return type;}
	string getGender() const {return gender;}
	double getHeight() const {return height;}
    bool operator != (const Pokemon&obj)
    {
        return (ID != obj.ID);
    }
	friend ostream& operator << (ostream &out, const Pokemon& obj)
	{
		out << obj.ID << " "  <<  obj.name << " " << obj.weight << " " << obj.type << " " << obj.gender;
		return out;
	}
};

#endif // POKEMON_H_INCLUDED

