#include "DBLite.h"

#include <plugin/sqlite3/lib/sqlite3.h>
#include <plugin/sqlite3/Sqlite3.h>


TabTbl::TabTbl(Sqlite3Session& _db) : BaseTab(_db)
{
	AddFrame(sf.Bottom(ce, 200));
	Add(ac.SizePos());
	ac.AddColumn("cid");
	ac.AddColumn("Name");
	ac.AddColumn("Type");
	ac.AddColumn("Not null");
	ac.AddColumn("Default");
	ac.AddColumn("Primary key");
}
	
void TabTbl::MainBar(Bar& bar) 
{
	bar.Add(tables, 100);
	bar.Add("Edit", DBLimg::EdtTbl(), THISBACK(OnActive))
	   .Help("Edit the table struct");
	bar.Add("Delete", DBLimg::DelTbl(), THISBACK(OnActive))
	   .Help("Delete the table");
	bar.Separator();
	bar.Add("Add table", DBLimg::AddTbl(), THISBACK(OnActive))
	   .Help("Create a new table");
	bar.Separator();
	bar.Add("Add field", DBLimg::AddFld(), THISBACK(OnActive))
	   .Help("Create a new field");
	bar.Add("Delete field", DBLimg::DelFld(), THISBACK(OnActive))
	   .Help("Delete the field");
}

void TabTbl::OnOpen() 
{
}

void TabTbl::OnClose() 
{
}

void TabTbl::OnActive() 
{
}
