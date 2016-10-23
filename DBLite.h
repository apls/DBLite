#ifndef _DBLite_DBLite_h
#define _DBLite_DBLite_h

#include <CtrlLib/CtrlLib.h>
#include <CodeEditor/CodeEditor.h>
#include <plugin/sqlite3/lib/sqlite3.h>
#include <plugin/sqlite3/Sqlite3.h>

using namespace Upp;

#define LAYOUTFILE <DBLite/DBLite.lay>
#include <CtrlCore/lay.h>

#define IMAGECLASS DBLimg
#define IMAGEFILE <DBLite/DBLite.iml>
#include <Draw/iml_header.h>

//class DBLite1 : public WithDBLiteLayout<TopWindow> {
//	WithDbTabLayout<ParentCtrl> tabdb;
//	WithTblTabLayout<ParentCtrl> tabtbl;
//	WithDatTabLayout<ParentCtrl> tabdat;
//	WithQryTabLayout<ParentCtrl> tabqry;
//
//public:
//	typedef DBLite1 CLASSNAME;
//	DBLite1();
//};


struct BaseTab : public ParentCtrl {
	Sqlite3Session& db3;
	BaseTab(Sqlite3Session& _db) : db3(_db) {};
	virtual void MainBar(Bar& bar) = 0;
	virtual void OnOpen() = 0;
	virtual void OnClose() = 0;
	virtual void OnActive() = 0;
};

struct TabDB : public BaseTab {
	SplitterFrame sfv, sfh;
	ArrayCtrl     db, gc;
	CodeEditor    ce;

	typedef TabDB CLASSNAME;
	TabDB(Sqlite3Session& _db);

	void MainBar(Bar& bar);
	void OnOpen();
	void OnClose();
	void OnActive();

	void OnView();
	void OnAddTbl();
	void OnSelTbl();
	void OnDelTbl();
};

struct TabTbl : public BaseTab {
	SplitterFrame sf;
	ArrayCtrl     ac;
	CodeEditor    ce;
	DropList      tables;
	

	typedef TabTbl CLASSNAME;
	TabTbl(Sqlite3Session& _db);

	void MainBar(Bar& bar);
	void OnOpen();
	void OnClose();
	void OnActive();
};

struct TabDat : public BaseTab {
	ArrayCtrl     ac;
	DropList      tables;

	typedef TabDat CLASSNAME;
	TabDat(Sqlite3Session& _db);

	void MainBar(Bar& bar);
	void OnOpen();
	void OnClose();
	void OnActive();
};

struct TabQry : public BaseTab {
	SplitterFrame sf;
	ArrayCtrl     ac;
	CodeEditor    ce;

	typedef TabQry CLASSNAME;
	TabQry(Sqlite3Session& _db);

	void MainBar(Bar& bar);
	void OnOpen();
	void OnClose();
	void OnActive();
};

class DBLite : public TopWindow {
	FrameTop<StaticBarArea> br;
	ToolBar       tb;
	MenuBar       mb;
	StatusBar     sb;
	SplitterFrame sf;
	TabCtrl       tc;
	CodeEditor    ce;
	TabDB         tDB;
	TabTbl        tTbl;
	TabDat        tDat;
	TabQry        tQry;
	FileSel       fs; 
	Sqlite3Session& db3;

public:
	typedef DBLite CLASSNAME;
	DBLite(Sqlite3Session& _db);

	void OnTab();
	void OnNew();
	void OnOpen();
	void OnClose();
	void OnLogs();
	void SetBar();
	void MainBar(Bar& bar);
	void MainMenu(Bar& bar);
	void MenuFile(Bar& bar);
	void MenuHelp(Bar& bar);
	
	void OpenFile(String& file);
	virtual void DragAndDrop(Point p, PasteClip& d);
	void Serialize(Stream& s);
};

#endif
