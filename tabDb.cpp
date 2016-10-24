#include "DBLite.h"

#include <plugin/sqlite3/lib/sqlite3.h>
#include <plugin/sqlite3/Sqlite3.h>




struct MyDisplay : public Display {
	virtual void Paint(Draw& w, const Rect& r, const Value& q,
	                   Color ink, Color paper, dword style) const {
		Rect r1 = r;
		w.DrawRect(r1, paper);
		r1.SetSize(16, 16);
		if(q == "table")
			w.DrawImage(r1, DBLimg::Table());
		else if(q == "view")
			w.DrawImage(r1, DBLimg::View());
		else if(q == "index")
			w.DrawImage(r1, DBLimg::Index());
	}
};

TabDB::TabDB(Sqlite3Session& _db) : BaseTab(_db)
{
	AddFrame(sfh.Right(gc, 200));
	AddFrame(sfv.Bottom(ce.SetEditable(false), 200));
	Add(db.SizePos());
	db.SetLineCy(20);
	db.SetMinSize(Size(16,16));
	db.AddColumn("Type", 16).SetDisplay(Single<MyDisplay>());
	db.AddColumn("Name", 60);
	db.AddColumn("Table", 60);
	db.AddColumn("SQL", 100);
	db.WhenSel = THISBACK(OnSelTbl);
	db.WhenLeftDouble = THISBACK(OnView);
	gc.AddColumn("Pragma");
	gc.AddColumn("Value");

	ce.SetFont(::StdFont());
}
	
void TabDB::MainBar(Bar& bar) 
{
	bar.Add("AddTbl", DBLimg::AddTbl(), THISBACK(OnAddTbl))
		.Enable(db3.IsOpen())
	   .Help("Add a new table");
	bar.Add("DelTbl", DBLimg::DelTbl(), THISBACK(OnDelTbl))
		.Enable(db3.IsOpen() && db.GetCursor() >= 0)
	   .Help("Delete this table");
}

void TabDB::OnOpen() 
{
	if(db3.IsOpen()) {
		Sql sql(db3);
		sql.Execute("SELECT type, name, tbl_name, sql FROM sqlite_master ORDER BY tbl_name, type DESC;");
		while (sql.Fetch())
			db.Add(sql.GetRow());
	}
}

void TabDB::OnClose() 
{
	db.Clear();
	gc.Clear();
	ce.Clear();
}

void TabDB::OnView() 
{	
}

void TabDB::OnSelTbl() 
{
	if(db.GetCursor() >= 0) {
		StringStream ss(db.Get(db.GetCursor(), 3));
		ce.Load(ss);
	}
}

void TabDB::OnAddTbl() 
{	
}

void TabDB::OnDelTbl() 
{	
}

void TabDB::OnActive() 
{	
}
