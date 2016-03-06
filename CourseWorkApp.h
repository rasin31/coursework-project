/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef COURSEWORKAPP_H_
#define COURSEWORKAPP_H_

#include <Wt/WContainerWidget>

#include "Session.h"

namespace Wt {
  class WStackedWidget;
  class WAnchor;
}

class MarkEntryWidget;
class MarkGradeWidget;
class Session;

class CourseworkApp : public Wt::WContainerWidget
{
public:
  CourseworkApp(Wt::WContainerWidget *parent = 0);

  void handleInternalPath(const std::string &internalPath);

private:
  Wt::WStackedWidget *mainStack_;
  MarkEntryWidget *form_;
  MarkGradeWidget *scores_;
  Wt::WContainerWidget *links_;
  Wt::WAnchor *backToGameAnchor_;
  Wt::WAnchor *scoresAnchor_;

  Session session_;

  void onAuthEvent();
  void showMarkEntry();
  void showMarkGrades();
};

#endif //COURSEWORKAPP_H_
