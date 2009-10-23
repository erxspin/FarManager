#include <windows.h>
#include <string.h>
#include "plugin.hpp"
#include "CRT/crt.hpp"

#if defined(__GNUC__)

#ifdef __cplusplus
extern "C"{
#endif
  BOOL WINAPI DllMainCRTStartup(HANDLE hDll,DWORD dwReason,LPVOID lpReserved);
#ifdef __cplusplus
};
#endif

BOOL WINAPI DllMainCRTStartup(HANDLE hDll,DWORD dwReason,LPVOID lpReserved)
{
  (void) lpReserved;
  (void) dwReason;
  (void) hDll;
  return TRUE;
}
#endif

enum {
  MTitle,
  MMessage1,
  MMessage2,
  MMessage3,
  MMessage4,
  MButton,
};

static struct PluginStartupInfo Info;

/*
 ������� GetMsg ���������� ������ ��������� �� ��������� �����.
 � ��� ���������� ��� Info.GetMsg ��� ���������� ���� :-)
*/
const TCHAR *GetMsg(int MsgId)
{
  return(Info.GetMsg(Info.ModuleNumber,MsgId));
}

/*
������� SetStartupInfo ���������� ���� ���, ����� �����
������� ���������. ��� ���������� ������� ����������,
����������� ��� ���������� ������.
*/
void WINAPI EXP_NAME(SetStartupInfo)(const struct PluginStartupInfo *psi)
{
  Info=*psi;
}

/*
������� GetPluginInfo ���������� ��� ��������� ��������
  (general) ���������� � �������
*/
void WINAPI EXP_NAME(GetPluginInfo)(struct PluginInfo *pi)
{
  static const TCHAR *PluginMenuStrings[1];

  pi->StructSize=sizeof(struct PluginInfo);
  pi->Flags=PF_EDITOR;

  PluginMenuStrings[0]=(TCHAR*)GetMsg(MTitle);
  pi->PluginMenuStrings=PluginMenuStrings;
  pi->PluginMenuStringsNumber=ArraySize(PluginMenuStrings);
}

/*
  ������� OpenPlugin ���������� ��� �������� ����� ����� �������.
*/
HANDLE WINAPI EXP_NAME(OpenPlugin)(int OpenFrom,INT_PTR item)
{
  const TCHAR *Msg[7];

  Msg[0]=GetMsg(MTitle);
  Msg[1]=GetMsg(MMessage1);
  Msg[2]=GetMsg(MMessage2);
  Msg[3]=GetMsg(MMessage3);
  Msg[4]=GetMsg(MMessage4);
  Msg[5]=_T("\x01");                   /* separator line */
  Msg[6]=GetMsg(MButton);

  Info.Message(Info.ModuleNumber,  /* PluginNumber */
               FMSG_WARNING|FMSG_LEFTALIGN,  /* Flags */
               _T("Contents"),         /* HelpTopic */
               Msg,                /* Items */
               7,                  /* ItemsNumber */
               1);                 /* ButtonsNumber */

  return  INVALID_HANDLE_VALUE;
}
