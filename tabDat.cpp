#include "DBLite.h"

#include <plugin/sqlite3/lib/sqlite3.h>
#include <plugin/sqlite3/Sqlite3.h>


TabDat::TabDat(Sqlite3Session& _db) : BaseTab(_db)
{
	Add(ac.SizePos());
}
	
void TabDat::MainBar(Bar& bar) 
{
	bar.Add(tables, 100);
	bar.Add("Edit", DBLimg::EdtDat(), THISBACK(OnActive))
	   .Help("Edit the data");
}

void TabDat::OnOpen() 
{
}

void TabDat::OnClose() 
{
}

void TabDat::OnActive() 
{
}
