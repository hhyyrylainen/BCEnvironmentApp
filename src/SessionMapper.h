#pragma once
//! \file Helpers for the mappings in sessions

#include <Wt/Dbo/Session.h>

namespace bce {

void MapAllClasses(Wt::Dbo::Session& session);

void PrintSQLForTables(Wt::Dbo::Session& session);

} // namespace bce
