/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef SESSION_H_
#define SESSION_H_

#include <vector>

#include <Wt/Auth/Login>

#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/Sqlite3>

#include "User.h"

typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

class Session
{
public:
  static void configureAuth();

  Session();
  ~Session();

  Wt::Auth::AbstractUserDatabase& users();
  Wt::Auth::Login& login() { return login_; }


  /*
   * These methods deal with the currently logged in user
   */
  std::string userName() const;

  static const Wt::Auth::AuthService& auth();
  static const Wt::Auth::AbstractPasswordService& passwordAuth();
  static const std::vector<const Wt::Auth::OAuthService *>& oAuth();

private:
  Wt::Dbo::backend::Sqlite3 sqlite3_;
  mutable Wt::Dbo::Session session_;
  UserDatabase *users_;
  Wt::Auth::Login login_;

  Wt::Dbo::ptr<User> user() const;
};

#endif //SESSION_H_
