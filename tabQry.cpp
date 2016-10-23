#include "DBLite.h"

#include <plugin/sqlite3/lib/sqlite3.h>
#include <plugin/sqlite3/Sqlite3.h>


TabQry::TabQry(Sqlite3Session& _db) : BaseTab(_db)
{
	AddFrame(sf.Top(ce, 200));
	Add(ac.SizePos());
}
	
void TabQry::MainBar(Bar& bar) 
{
	bar.Add("Query", DBLimg::DoQry(), THISBACK(OnActive))
	   .Help("Execute the Query");
	bar.Add("Load", DBLimg::RdSQL(), THISBACK(OnActive))
	   .Help("Load SQL from file");
}

void TabQry::OnOpen() 
{
}

void TabQry::OnClose() 
{
}

void TabQry::OnActive() 
{
}
