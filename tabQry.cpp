#include "DBLite.h"

#include <plugin/sqlite3/lib/sqlite3.h>
#include <plugin/sqlite3/Sqlite3.h>


TabQry::TabQry(Sqlite3Session& _db) : BaseTab(_db)
{
	AddFrame(sf.Top(ce, 200));
	Add(gc.SizePos());
	
	ce.SetFont(::StdFont());
}
	
void TabQry::MainBar(Bar& bar) 
{
	bar.Add("Query", DBLimg::DoQry(), THISBACK(DoQry))
	   .Help("Execute the Query");
	bar.Add("Load", DBLimg::RdSQL(), THISBACK(OnLoad))
	   .Help("Load SQL from file");
}

void TabQry::OnOpen() 
{
}

void TabQry::OnClose() 
{
	gc.Clear();
	ce.Clear();
}

void TabQry::OnActive() 
{
}

void TabQry::OnLoad() 
{
}

void TabQry::DoQry() 
{
	gc.Clear();
}
