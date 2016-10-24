#include "DBLite.h"

#include <plugin/sqlite3/lib/sqlite3.h>
#include <plugin/sqlite3/Sqlite3.h>


TabTbl::TabTbl(Sqlite3Session& _db) : BaseTab(_db)
{
	AddFrame(sf.Bottom(ce, 200));
	Add(ac.SizePos());
	ac.SetLineCy(20);
	ac.AddColumn("cid");
	ac.AddColumn("Name").Ctrls<EditString>();
	ac.AddColumn("Type");//.Ctrls(WithDropChoice<EditString>());
	ac.AddColumn("Not null").Ctrls<Option>();
	ac.AddColumn("Default").Ctrls<EditString>();
	ac.AddColumn("Primary key").Ctrls<Option>();
	ac.SetReadOnly();
	
	tables <<= THISBACK(OnActive);

	ce.SetFont(::StdFont());
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
	tables.Clear();
	if(db3.IsOpen()) {
		Sql sql(db3);
		sql.Execute("SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%';");
		while (sql.Fetch())
			tables.Add(sql[0]);
		if(tables.GetCount() > 0) {
			int i = tables.Find(table);
			if(i < 0) i = 0;
			tables.SetIndex(i);	
			OnActive();	
		}
	}	
}

void TabTbl::OnClose() 
{
	ac.Clear();
	tables.Clear();
	ce.Clear();
}

void TabTbl::OnActive() 
{
	table = tables.Get();
	ac.Clear();
	if(db3.IsOpen()) {
		Sql sql(db3);
		sql.Execute(String("PRAGMA table_info(") + table + ");");
		while (sql.Fetch())
			ac.Add(sql.GetRow());
	}
}
