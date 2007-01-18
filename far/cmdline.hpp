#ifndef __COMMANDLINE_HPP__
#define __COMMANDLINE_HPP__
/*
cmdline.hpp

��������� ������

*/

#include "scrobj.hpp"
#include "edit.hpp"
#include "farconst.hpp"

enum {
  FCMDOBJ_LOCKUPDATEPANEL   = 0x00010000,
};

class CommandLine:public ScreenObject
{
  private:
    Edit CmdStr;
    SaveScreen *BackgroundScreen;
    char CurDir[NM];
    char *LastCmdStr;
    int  LastCmdLength;
    int  LastCmdPartLength;

  private:
    void DisplayObject();
    int CmdExecute(char *CmdLine,int AlwaysWaitFinish,int SeparateWindow,int DirectRun);
    int ProcessOSCommands(char *CmdLine,int SeparateWindow);
    void GetPrompt(char *DestStr);
    BOOL SetLastCmdStr(const char *Ptr,int LenPtr);

  public:
    CommandLine();
    ~CommandLine();

  public:
    int ProcessKey(int Key);
    int ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent);

    int GetCurDir(char *CurDir);
    void SetCurDir(const char *CurDir);
    void GetString(char *Str,int MaxSize);
    const char *GetStringAddr();
    void SetString(const char *Str,BOOL Redraw=TRUE);
    int GetLength() {return(CmdStr.GetLength());};
    void ExecString(char *Str,int AlwaysWaitFinish,int SeparateWindow=FALSE,int DirectRun=FALSE);
    /* $ 10.05.2001 DJ */
    void ShowViewEditHistory();
    /* DJ $ */
    void InsertString(const char *Str);
    void SetCurPos(int Pos);
    int GetCurPos();
    /* $ 11.05.2001 OT */

    /* $ 09.09.2001 IS
       ����������/�������� ���������� ����� */
    void SetPersistentBlocks(int Mode);
    /* IS $ */

    /*$ 13.08.2001 SKV*/
    void GetSelString(char*,int);
    void Select(int,int);
    /* SKV$*/
    void GetSelection(int &Start,int &End);
    void SaveBackground(int X1,int Y1,int X2,int Y2);
    void SaveBackground();
    void ShowBackground();
    void CorrectRealScreenCoord();
    /* OT $ */
    void ResizeConsole();
    void LockUpdatePanel(int Mode) {Flags.Change(FCMDOBJ_LOCKUPDATEPANEL,Mode);};
};

#endif  // __COMMANDLINE_HPP__
