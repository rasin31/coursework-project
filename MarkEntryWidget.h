/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef MARKENTRY_WIDGET_H_
#define MARKENTRY_WIDGET_H_

#include <Wt/WContainerWidget>

class Session;

class MarkEntryWidget: public Wt::WContainerWidget
{
public:
  MarkEntryWidget(const std::string &name, Wt::WContainerWidget *parent = 0);
  Wt::Signal<int>& scoreUpdated() { return scoreUpdated_; }
  
private:
  Wt::WText                     *title_;
  Wt::WText                     *statusText_;
  Wt::WPushButton               *submitButton;
  Wt::Signal<int>                scoreUpdated_;
  std::string                    name_; 

  Wt::WLineEdit			*moduleCode_;
  Wt::WLineEdit			*assignmentTitle_;
  Wt::WLineEdit			*presentation_;
  Wt::WLineEdit			*criteria_;
  Wt::WLineEdit			*algorithm_;
  Wt::WLineEdit			*ui_;
  Wt::WLineEdit			*codes_;
  Wt::WLineEdit			*errorFree_;
  Wt::WLineEdit			*dueDate_;
  Wt::WTextArea                 *remarksEdit_;

  Wt::WLineEdit			*studentNumber_;
  Wt::WLineEdit			*studentName_;
  Wt::WLineEdit			*email_;
  Wt::WLineEdit			*intake_;

  Wt::WLineEdit			*lecturerName_;

  Wt::WTable                    *studentTable_;
  //Wt::WTable                    *courseworkTable_;
  void form();
  void submit();
};

#endif //MARKENTRY_WIDGET_H_
