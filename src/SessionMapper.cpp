// ------------------------------------ //
#include "SessionMapper.h"

#include "Task.h"

#include <iostream>
// ------------------------------------ //
namespace bce {
void MapAllClasses(Wt::Dbo::Session& session)
{
    session.mapClass<Task>("tasks");
}

void PrintSQLForTables(Wt::Dbo::Session& session)
{
    std::cout << "Full table SQL: \n";
    std::cout << session.tableCreationSql() << "\nEnd of table SQL\n";
}

} // namespace bce
