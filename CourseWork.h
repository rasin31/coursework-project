/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef COURSEWORK_H_
#define COURSEWORK_H_

#include <Wt/WDate>
#include <Wt/WString>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>

namespace dbo = Wt::Dbo;

class CourseWork
{
public:
  Wt::WString assignment_title;
  Wt::WString module_code;
  Wt::WString presentation;
  Wt::WString criteria;
  Wt::WString algorithm;
  Wt::WString ui;
  Wt::WString codes;
  Wt::WString error_free;
  Wt::WString due_date;
  Wt::WString remarks;
  
  //CourseWork();
  //CourseWork(const Wt::WString& student_name);

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, assignment_title, "assignment_title");
    dbo::field(a, module_code, "module_code");
    dbo::field(a, presentation, "presentation");
    dbo::field(a, criteria, "criteria");
    dbo::field(a, algorithm, "algorithm");
    dbo::field(a, ui, "ui");
    dbo::field(a, codes, "codes");
    dbo::field(a, error_free, "error_free");
    dbo::field(a, due_date, "due_date");
    dbo::field(a, remarks, "remarks");
  }
};

#endif // COURSEWORK_H_
