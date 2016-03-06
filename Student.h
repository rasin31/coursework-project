/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <Wt/WDate>
#include <Wt/WString>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>

namespace dbo = Wt::Dbo;

class Student
{
public:
  Wt::WString student_number;
  Wt::WString student_name;
  Wt::WString department;
  Wt::WString year;
  Wt::WString email;
  Wt::WString phone_number;
  Wt::WString level;
  Wt::WString intake;
  Wt::WString version;
  
  //Student();
  //Student(const Wt::WString& student_name);

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, student_number, "student_number");
    dbo::field(a, student_name, "student_name");
    dbo::field(a, department, "department");
    dbo::field(a, year, "year");
    dbo::field(a, email, "email");
    dbo::field(a, phone_number, "phone_number");
    dbo::field(a, level, "level");
    dbo::field(a, intake, "intake");
    dbo::field(a, version, "version");
  }
};

#endif // STUDENT_H_
