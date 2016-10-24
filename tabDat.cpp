#include "DBLite.h"

#include <plugin/sqlite3/lib/sqlite3.h>
#include <plugin/sqlite3/Sqlite3.h>


struct SqlGrid :public GridCtrl {
	Sqlite3Session& db3;
	SqlGrid(Sqlite3Session& _db) : db3(_db) {};
	
	void Query(String& SQL) {};
	void Clear() {};
};

TabDat::TabDat(Sqlite3Session& _db) : BaseTab(_db)
{
	Add(gc.SizePos());

	tables <<= THISBACK(OnActive);
}
	
void TabDat::MainBar(Bar& bar) 
{
	bar.Add(tables, 100);
	bar.Add("Edit", DBLimg::EdtDat(), THISBACK(OnActive))
	   .Help("Edit the data");
}

void TabDat::OnOpen() 
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

void TabDat::OnClose() 
{
	gc.Clear();
	tables.Clear();
}

void TabDat::OnActive() 
{
	table = tables.Get();
}
