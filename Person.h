#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
#include <string_view>

namespace common
{
class Person
{
    std::string m_name;
    std::string m_id;
public:
    Person(std::string_view name, std::string_view id);
    virtual void print(std::ostream& os = std::cout) const ;
    std::string getId() const;
    std::string getName() const;
    void setName( std::string_view name);
    void setId( std::string_view id);
    virtual ~Person() = default;
};

}





#endif // PERSON_H
