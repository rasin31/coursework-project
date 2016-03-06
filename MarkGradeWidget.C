/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */ 

#include <boost/lexical_cast.hpp>

#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/Dbo/Dbo>

#include "MarkGradeWidget.h"
#include "Session.h"

using namespace Wt;

MarkGradeWidget::MarkGradeWidget(Session *session, WContainerWidget *parent):
  WContainerWidget(parent),
  session_(session)
{
  setContentAlignment(AlignLeft);
  setStyleClass("marksgrades");
}

void MarkGradeWidget::update()
{
  clear();
  
  new WText("<h2>Score grading system</h2>", this);
  

  WText *fineprint = new WText(tr("coursegrade.info"), this);
  fineprint->addStyleClass("fineprint");
}
