#include "DBLite.h"

#define IMAGECLASS DBLimg
#define IMAGEFILE <DBLite/DBLite.iml>
#include <Draw/iml_source.h>

//DBLite1::DBLite1()
//{
//	CtrlLayout(*this, "Window title");
//	CtrlLayout(tabdb);
//	CtrlLayout(tabtbl);
//	CtrlLayout(tabdat);
//	CtrlLayout(tabqry);
//	tab.Add(tabdb.SizePos(), "Database");
//	tab.Add(tabtbl.SizePos(), "Struct");
//	tab.Add(tabdat.SizePos(), "Data");
//	tab.Add(tabqry.SizePos(), "Query");
//	Sizeable().Zoomable();
//}

#define TITLE "DBLite"

DBLite::DBLite(Sqlite3Session& _db) : db3(_db), tDB(_db), tTbl(_db), tDat(_db), tQry(_db)
{
	Sizeable().Zoomable().Title(TITLE);
	
	ClearFrames();
	int r = HorzLayoutZoom(100);
	int l = HorzLayoutZoom(100);
	mb.Transparent();
	tb.SetFrame(NullFrame());
	br.Add(mb.LeftPos(0, l).VCenterPos(mb.GetStdHeight()));
	br.Add(tb.HSizePos(l, r).VCenterPos(tb.GetStdHeight()));
	//br.Add(display.RightPos(4, r).VSizePos(2, 3));
	br.Height(max(mb.GetStdHeight(), tb.GetStdHeight()));
	AddFrame(br);
	tb.Transparent();
	
	AddFrame(sb);
	AddFrame(sf.Bottom(ce.SetEditable(false), 200));
	Add(tc.SizePos());
	
	tc.Add(tDB.SizePos(), DBLimg::DB(), "Database");
	tc.Add(tTbl.SizePos(), DBLimg::Table(), "Table");
	tc.Add(tDat.SizePos(), DBLimg::Data(), "Data");
	tc.Add(tQry.SizePos(), DBLimg::Query(), "Query");
	tc.WhenSet = THISBACK(OnTab);
	sf.Hide();
	SetBar();
	mb.Set(THISBACK(MainMenu));
	
	fs.Type("SQLite db file", "*.db *.db3 *.dat")
		.AllFilesType().Multi(false);
		
	ce.SetFont(::StdFont());
}

void DBLite::MainMenu(Bar& bar)
{
	bar.Add("&File", THISBACK(MenuFile));
	bar.Add("&View", THISBACK(MenuView));
	bar.Add("&Help", THISBACK(MenuHelp));
}

void DBLite::MenuFile(Bar& bar)
{
	bar.Add("Open", THISBACK(OnOpen));
	bar.Add("New", THISBACK(OnNew));
	bar.Separator();
	bar.Add("Exit", THISBACK(OnLogs))
		.Key(K_CTRL_E);
}

void DBLite::MenuView(Bar& bar)
{
	bar.Add("Log window", THISBACK(OnLogs))
		.Check(ce.IsVisible());

}

void DBLite::MenuHelp(Bar& bar)
{
	bar.Add("About", THISBACK(OnLogs))
		.Key(K_F1);
}

void DBLite::MainBar(Bar& bar)
{
	bar.Separator();
	bar.Add("New", DBLimg::New(), THISBACK(OnNew))
	   .Key(K_CTRL_N)
	   .Help("Create new database");
	if(db3.IsOpen())
		bar.Add("Close", DBLimg::Close(), THISBACK(OnClose))
			.Enable(db3.IsOpen())
			.Help("Close current database");
	else
		bar.Add("Open..", DBLimg::Open(), THISBACK(OnOpen))
		   .Key(K_CTRL_O)
		   .Help("Open existing database");
	bar.Separator();
	bar.Add("Export", DBLimg::Export(), THISBACK(OnNew))
	   .Help("Export database");
	bar.Separator();
	bar.Add("Logs", DBLimg::Logs(), THISBACK(OnLogs))
		.Check(ce.IsVisible())
		.Help("Query logs");
	bar.Separator();
	switch(tc.Get()) {
		case 0: tDB.MainBar(bar); break;
		case 1: tTbl.MainBar(bar); break;
		case 2: tDat.MainBar(bar); break;
		case 3: tQry.MainBar(bar); break;
	}	
	bar.ToolGap();
}

void DBLite::SetBar()
{
	tb.Set(THISBACK(MainBar));
}

void DBLite::OnTab()
{
	SetBar();
}

void DBLite::OnLogs()
{
	sf.Show(!ce.IsVisible());
	SetBar();
}

void DBLite::OnNew()
{
	if(fs.ExecuteSaveAs("Create db file as")) {
		OnClose();
		OpenFile(fs.Get());
	}
}

void DBLite::OpenFile(String& file)
{
	OnClose();
	if(db3.Open(file)) {
		Title(String(TITLE) << " - " << file);
		
		tDB.OnOpen();
		tTbl.OnOpen();
		tDat.OnOpen();
		tQry.OnOpen();
	} else {
	}
	SetBar();
}

void DBLite::OnOpen()
{
	if(fs.ExecuteOpen())
		OpenFile(fs.Get());
}

void DBLite::OnClose()
{
	tDB.OnClose();
	tTbl.OnClose();
	tDat.OnClose();
	tQry.OnClose();
	
	db3.Close();
	Title(TITLE);
	tc.Set(tDB);
	SetBar();	
}

void DBLite::DragAndDrop(Point p, PasteClip& d)
{
	Vector<String> files;
	if (AcceptFiles(d)) {
		files = GetFiles(d);
		if(files.GetCount() == 1) {
			OpenFile(files[0]);
		} else {
		}
	}
}

void DBLite::Serialize(Stream& s)
{
	int version = 0;
	s / version;
	SerializePlacement(s);
	tDB.Serialize(s);
	tTbl.Serialize(s);
	tDat.Serialize(s);
	tQry.Serialize(s);
}

GUI_APP_MAIN
{
	SetDateFormat("%1:04d-%2:02d-%3:02d");
	SetDateScan("ymd");
#ifdef PLATFORM_WIN32
	SetStdFont(StdFont(12));
#endif
	
	//MiniSplitter();
	Sqlite3Session db3;
	DBLite* dbl = new DBLite(db3);
	LoadFromFile(*dbl);
	SetLanguage(LNGC_('Z','H','C','N', CHARSET_UNICODE));
	dbl->Run();
	StoreToFile(*dbl);
	delete dbl;
}
