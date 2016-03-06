/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef LECTURER_H_
#define LECTURER_H_

#include <Wt/WDate>
#include <Wt/WString>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>

namespace dbo = Wt::Dbo;

class Lecturer
{
public:
  Wt::WString lecturer_number;
  Wt::WString lecturer_name;
  Wt::WString department;
  Wt::WString phone_number;
  Wt::WString version;
  
  //Lecturer();
  //Lecturer(const Wt::WString& student_name);

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, lecturer_number, "lecturer_number");
    dbo::field(a, lecturer_name, "lecturer_name");
    dbo::field(a, department, "department");
    dbo::field(a, phone_number, "phone_number");
    dbo::field(a, version, "version");
  }
};

#endif // LECTURER_H_
