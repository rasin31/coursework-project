/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MARKS_GRADE_WIDGET_H_
#define MARKS_GRADE_WIDGET_H_

#include <Wt/WContainerWidget>

class Session;

class MarkGradeWidget: public Wt::WContainerWidget
{
public:
  MarkGradeWidget(Session *session, Wt::WContainerWidget *parent = 0);
  void update();

private:
  Session *session_;
};

#endif //MARKS_GRADE_WIDGET_H_
