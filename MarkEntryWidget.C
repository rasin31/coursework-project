/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#include "MarkEntryWidget.h"
#include "Session.h"
#include "CourseWork.h"
#include "Student.h"
#include "Lecturer.h"

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WDateEdit>
#include <Wt/WSelectionBox>
#include <Wt/WContainerWidget>
#include <Wt/WImage>
#include <Wt/WIntValidator>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WTableCell>
#include <Wt/WTextArea>
#include <Wt/WText>
#include <Wt/WTable> 

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>
#include <Wt/Wstring>

using namespace Wt;
namespace dbo = Wt::Dbo;

MarkEntryWidget::MarkEntryWidget(const std::string &name, WContainerWidget *parent)
  : WContainerWidget(parent),
    name_(name)
{
  setContentAlignment(AlignLeft);
  title_ = new WText(tr("coursework.enterMarks"), this);
  statusText_ = new WText(this);

  new WBreak(this);

  //submitButton = new WPushButton(tr("coursework.submit"), this);
  //submitButton->clicked().connect(this, &MarkEntryWidget::form);
  
  MarkEntryWidget::form();

}

void MarkEntryWidget::form()
{
  WString title(tr("coursework.markEntry"));
  title_->setText(title.arg(name_));


  studentTable_ = new Wt::WTable(this);
  WLabel *label;
  int row = 0;

  // Student number
  ++row;
  studentNumber_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.student_no"), studentTable_->elementAt(row, 0));
  label->setBuddy(studentNumber_);
  //studentNumber_->setValidator(new WValidator(true));

  // Student name
  ++row;
  studentName_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.student_name"), studentTable_->elementAt(row,0));
  label->setBuddy(studentName_);

  // Intake 
  ++row;
  intake_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.intake"), studentTable_->elementAt(row,0));
  label->setBuddy(intake_);

  // Email 
  ++row;
  email_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.email"), studentTable_->elementAt(row,0));
  label->setBuddy(email_);

  // Assignment title
  ++row;
  assignmentTitle_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.assignment_title"), studentTable_->elementAt(row, 0));
  label->setBuddy(assignmentTitle_);
  //childCountEdit_->setValidator(new WIntValidator(0,30));
  //childCountEdit_->validator()->setMandatory(true);

  // Lecturer name
  ++row;
  lecturerName_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.lecturer_name"), studentTable_->elementAt(row,0));
  label->setBuddy(lecturerName_);

  // Due date
  ++row;
  dueDate_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.due_date"), studentTable_->elementAt(row,0));
  label->setBuddy(dueDate_);
  
  // Module code
  ++row;
  moduleCode_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.module_code"), studentTable_->elementAt(row,0));
  label->setBuddy(moduleCode_);

  // Presentation
  ++row;
  presentation_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.presentation"), studentTable_->elementAt(row,0));
  label->setBuddy(presentation_);

  // Criteria
  ++row;
  criteria_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.criteria"), studentTable_->elementAt(row,0));
  label->setBuddy(criteria_);

  // Algorithm
  ++row;
  algorithm_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.algorithm"), studentTable_->elementAt(row,0));
  label->setBuddy(algorithm_);

  // UI
  ++row;
  ui_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.ui"), studentTable_->elementAt(row,0));
  label->setBuddy(ui_);

  // Codes
  ++row;
  codes_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.codes"), studentTable_->elementAt(row,0));
  label->setBuddy(codes_);

  // Error Free
  ++row;
  errorFree_ = new WLineEdit(studentTable_->elementAt(row, 2));
  label = new WLabel(tr("coursework.error_free"), studentTable_->elementAt(row,0));
  label->setBuddy(errorFree_);

  // remarks
  ++row;
  remarksEdit_ = new WTextArea(studentTable_->elementAt(row, 2));
  remarksEdit_->setColumns(40);
  remarksEdit_->setRows(5);
  label = new WLabel(tr("coursework.remarks"),
		     studentTable_->elementAt(row, 0));
  label->setBuddy(remarksEdit_);

  // Set column widths for label and validation icon
  //table_->elementAt(2, 0)->resize(WLength(30, WLength::FontEx), WLength::Auto);
  //table_->elementAt(2, 1)->resize(20, WLength::Auto);


  // Submit button
  ++row;
  WPushButton *submit = new WPushButton(tr("coursework.submit"), studentTable_->elementAt(row, 0));
  submit->clicked().connect(this, &MarkEntryWidget::submit);
  //submitButton->hide();

  statusText_->setText("");
}

void MarkEntryWidget::submit()
{
  dbo::backend::Sqlite3 sqlite3("Student_Grade.db");
  dbo::Session session;
  session.setConnection(sqlite3);
 
  dbo::Transaction transaction(session);

  CourseWork *cwork = new CourseWork();
  session.mapClass<CourseWork>("CourseWork"); //CourseWork is a table from Student_Grade.db

  Lecturer *lecturer = new Lecturer();
  session.mapClass<Lecturer>("Lecturer"); //Lecturer is a table from Student_Grade.db

  Student *student = new Student();
  session.mapClass<Student>("Student"); //Student is a table from Student_Grade.db

  //Entries for Coursework
  dbo::ptr<CourseWork> cworkPtr = session.add(cwork);
  cworkPtr.modify()->module_code = moduleCode_->text();
  cworkPtr.modify()->assignment_title = assignmentTitle_->text();
  cworkPtr.modify()->presentation = presentation_->text();
  cworkPtr.modify()->criteria = criteria_->text();
  cworkPtr.modify()->algorithm = algorithm_->text();
  cworkPtr.modify()->ui = ui_->text();
  cworkPtr.modify()->codes = codes_->text();
  cworkPtr.modify()->error_free = errorFree_->text();
  cworkPtr.modify()->due_date = dueDate_->text();
  cworkPtr.modify()->remarks = remarksEdit_->text();

  //Entries for Student
  dbo::ptr<Student> studentPtr = session.add(student);
  studentPtr.modify()->student_number = studentNumber_->text();
  studentPtr.modify()->student_name = studentName_->text();
  studentPtr.modify()->email = email_->text();
  studentPtr.modify()->intake = intake_->text();

  //Entries for Lecturer
  dbo::ptr<Lecturer> lecturerPtr = session.add(lecturer);
  lecturerPtr.modify()->lecturer_name = lecturerName_->text();

  moduleCode_->setText("");
  assignmentTitle_->setText("");
  presentation_->setText("");
  criteria_->setText("");
  algorithm_->setText("");
  ui_->setText("");
  codes_->setText("");
  errorFree_->setText("");
  dueDate_->setText("");
  remarksEdit_->setText("");
  //table_->refresh();




}


