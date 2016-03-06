/*
 * Copyright (C) 2016 Raja Singam. This file uses Wt++ libraries courtesy of Emweb.
 *
 * See the LICENSE file for terms of use.
 */

#include "User.h"

#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Dbo/Impl>

DBO_INSTANTIATE_TEMPLATES(User);

using namespace Wt;
using namespace Wt::Dbo;

User::User()
{ }
