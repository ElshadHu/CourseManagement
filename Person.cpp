#include "Person.h"
// #include <iostream>
// #include <string>
// #include <string_view>

namespace common
{
Person::Person (std::string_view name, std::string_view id):m_name(name),m_id(id){}

void Person::print(std::ostream& os) const{
    os << m_name << " [" << m_id << "]\n";
}

std::string Person::getId() const { return m_id; }
std::string Person::getName() const { return m_name; }

void Person::setName(std::string_view name) { m_name = name; }
void  Person::setId(std::string_view id) { m_id = id; }

}
