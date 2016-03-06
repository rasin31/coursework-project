/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WAnchor>
#include <Wt/WText>
#include <Wt/WStackedWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WApplication>
#include <Wt/Auth/AuthWidget>

#include "CourseworkApp.h"
#include "MarkEntryWidget.h"
#include "MarkGradeWidget.h"

using namespace Wt;

CourseworkApp::CourseworkApp(WContainerWidget *parent):
  WContainerWidget(parent),
  form_(0),
  scores_(0)
{
  session_.login().changed().connect(this, &CourseworkApp::onAuthEvent);
  Auth::AuthModel *authModel = new Auth::AuthModel(Session::auth(),
						   session_.users(), this);
  authModel->addPasswordAuth(&Session::passwordAuth());
  authModel->addOAuth(Session::oAuth());

  Auth::AuthWidget *authWidget = new Auth::AuthWidget(session_.login());
  authWidget->setModel(authModel);
  authWidget->setRegistrationEnabled(true);

  new WBreak(this);
  WText *title = new WText("<h1>Student coursework marks entry system</h1>");
  addWidget(title);

  addWidget(authWidget);

  mainStack_ = new WStackedWidget();
  mainStack_->setStyleClass("marksentry");
  addWidget(mainStack_);

  links_ = new WContainerWidget();
  links_->setStyleClass("links");
  links_->hide();
  addWidget(links_);

  backToGameAnchor_ = new WAnchor("/markEntry", "Mark entry page", links_);
  backToGameAnchor_->setLink(WLink(WLink::InternalPath, "/markEntry"));

  scoresAnchor_ = new WAnchor("/markGrades", "Mark grades page", links_);
  scoresAnchor_->setLink(WLink(WLink::InternalPath, "/markGrades"));

  WApplication::instance()->internalPathChanged()
    .connect(this, &CourseworkApp::handleInternalPath);

  authWidget->processEnvironment();
}

void CourseworkApp::onAuthEvent()
{
  if (session_.login().loggedIn()) {  
    links_->show();
    handleInternalPath(WApplication::instance()->internalPath());
  } else {
    mainStack_->clear();
    form_ = 0;
    scores_ = 0;
    links_->hide();
  }
}

void CourseworkApp::handleInternalPath(const std::string &internalPath)
{
  if (session_.login().loggedIn()) {
    if (internalPath == "/markEntry")
      showMarkEntry();
    else if (internalPath == "/markGrades")
      showMarkGrades();
    else
      WApplication::instance()->setInternalPath("/markEntry",  true);
  }
}

void CourseworkApp::showMarkGrades()
{
  if (!scores_)
    scores_ = new MarkGradeWidget(&session_, mainStack_);

  mainStack_->setCurrentWidget(scores_);
  scores_->update();

  backToGameAnchor_->removeStyleClass("selected-link");
  scoresAnchor_->addStyleClass("selected-link");
}

void CourseworkApp::showMarkEntry()
{
  if (!form_) {
    form_ = new MarkEntryWidget(session_.userName(), mainStack_);
  }

  mainStack_->setCurrentWidget(form_);

  backToGameAnchor_->addStyleClass("selected-link");
  scoresAnchor_->removeStyleClass("selected-link");
}
