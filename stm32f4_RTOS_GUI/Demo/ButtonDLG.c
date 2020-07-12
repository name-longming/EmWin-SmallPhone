/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

#include "ButtonDLG.h"
#include <stdio.h>
#include "main.h"
#include "wkup.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_CHECKBOX_3   (GUI_ID_USER + 0x01)
#define ID_TEXT_0   (GUI_ID_USER + 0x02)
#define ID_TEXT_1   (GUI_ID_USER + 0x0a)
#define ID_TEXT_2   (GUI_ID_USER + 0x0b)
#define ID_TEXT_3   (GUI_ID_USER + 0x0c)
#define ID_TEXT_4   (GUI_ID_USER + 0x0d)
#define ID_MULTIEDIT_0   (GUI_ID_USER + 0x03)
#define ID_ICONVIEW_0 (GUI_ID_USER + 0x04)
#define ID_ICONVIEW_1 (GUI_ID_USER + 0x05)
#define ID_ICONVIEW_2 (GUI_ID_USER + 0x06)
#define ID_FRAMEWIN_1 (GUI_ID_USER + 0x07)
#define ID_FRAMEWIN_2 (GUI_ID_USER + 0x08)
#define ID_FRAMEWIN_3 (GUI_ID_USER + 0x09)
#define ID_LISTWHEEL_0 (GUI_ID_USER + 0x10)
#define ID_LISTWHEEL_1 (GUI_ID_USER + 0x11)
#define ID_LISTWHEEL_2 (GUI_ID_USER + 0x12)
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

extern GUI_CONST_STORAGE GUI_BITMAP bmcheckbox_true;
extern GUI_CONST_STORAGE GUI_BITMAP bmcheckbox_false;

extern GUI_CONST_STORAGE GUI_BITMAP bmsetting;
extern GUI_CONST_STORAGE GUI_BITMAP bmclock;
extern GUI_CONST_STORAGE GUI_BITMAP bmcalender;
extern GUI_CONST_STORAGE GUI_BITMAP bmmusic;
extern GUI_CONST_STORAGE GUI_BITMAP bmmessege;
extern GUI_CONST_STORAGE GUI_BITMAP bmfolder;
extern GUI_CONST_STORAGE GUI_BITMAP bmnotebook;
extern GUI_CONST_STORAGE GUI_BITMAP bmsearch;
extern GUI_CONST_STORAGE GUI_BITMAP bmhome;
extern GUI_CONST_STORAGE GUI_BITMAP bmimage;
extern GUI_CONST_STORAGE GUI_BITMAP bmBUTTON_OFF;
extern GUI_CONST_STORAGE GUI_BITMAP bmBUTTON_ON;
/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 320, 240, 0x64, 0x0, 0 },
	{ CHECKBOX_CreateIndirect, "Checkbox1", ID_CHECKBOX_3, 0, 165, 250, 35, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text0", ID_TEXT_0, 0, 0, 250, 50, 0, 0x64, 0 },
	{ MULTIEDIT_CreateIndirect, "Multiedit0", ID_MULTIEDIT_0, 0, 50, 250, 110, 0, 0x0, 0 },
	{ ICONVIEW_CreateIndirect, "Iconview",ID_ICONVIEW_0, 250, 0, 64, 70, 0, 0x00400046, 0},
	{ ICONVIEW_CreateIndirect, "Iconview",ID_ICONVIEW_1, 250, 70, 64, 75, 0, 0x00400046, 0},
	{ ICONVIEW_CreateIndirect, "Iconview",ID_ICONVIEW_2, 250, 145, 64, 70, 0, 0x00400046, 0},
};

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
	const GUI_BITMAP* pBitmap;
	const char* pText;
} BITMAP_ITEM;

static BITMAP_ITEM _abitmapItem[] = {
	{&bmhome,                "home"},
  {&bmfolder,            "folder"},
	{&bmclock,              "Clock"},
	{&bmmessege,          "messege"},
	{&bmcalender,        "calender"},
	{&bmsearch,            "search"},
	{&bmmusic,              "music"},
	{&bmimage,              "image"},
	{&bmsetting,          "Setting"},
};
static char *_apYear[] = {
	"2001", "2002", "2003",
  "2004", "2005", "2006", "2007", "2008", "2009", "2010",
  "2011", "2012", "2013", "2014", "2015", "2016", "2017",
  "2018", "2019", "2020",
};

static char *_apMonth[] = {
  "01",
  "02",
  "03",
  "04",
  "05",
  "06",
  "07",
  "08",
  "09",
  "10",
  "11",
};

static char *_apDay[] = {
  "01", "02", "03", "04",
  "05", "06", "07", "08",
  "09", "10", "11", "12",
  "13", "14", "15", "16",
  "17", "18", "19", "20",
  "21", "22", "23", "24",
  "25", "26", "27", "28",
  "29", "30", "31",
};
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
WM_HWIN  hWin_FRAME;
WM_HWIN	 Basic_hItem;
WM_HWIN	 Frame0_hChild;
WM_HWIN	 CLOCK_hChild;
static const GUI_COLOR aColor[] = {GUI_WHITE, GUI_RED};
int value = 0;
char WeatherFlag=1;
extern char Temper[];
extern char Temper1[];

extern char Timer[];
char botton=1;
extern RTC_HandleTypeDef hrtc;
/**
  * @brief 应用窗口回调函数
  * @note 无
  * @param 无
  * @retval 无
  */
static int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
  GUI_RECT aRect;

  switch (pDrawItemInfo->Cmd) {
  case WIDGET_ITEM_DRAW_OVERLAY:
    /* 获取控件坐标 */
    aRect.x0 = pDrawItemInfo->x0;
    aRect.x1 = pDrawItemInfo->x1;
    aRect.y1 = pDrawItemInfo->y1;
    /* 画分割线 */
    GUI_SetColor(GUI_GRAY_E7);
    GUI_DrawLine(aRect.x0, (aRect.y1-19-16)/2, aRect.x1, (aRect.y1-19-16)/2);
    GUI_DrawLine(aRect.x0, (aRect.y1+19+16)/2, aRect.x1, (aRect.y1+19+16)/2);
    break;
  default:
    return LISTWHEEL_OwnerDraw(pDrawItemInfo);
  }
  return 0;
}

static void _cbICON0(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
    case WM_PAINT:
      /* 设置客户窗口的背景颜色 */
      GUI_SetBkColor(GUI_WHITE);
      GUI_Clear();
      break;
		default:
			WM_DefaultProc(pMsg);
		  break;
	}
}
static void _cbICON1(WM_MESSAGE *pMsg)
{
  WM_HWIN hItem;
  int     NCode;
  int     Id;
	
	switch(pMsg->MsgId)
	{
    case WM_PAINT:
      /* 设置客户窗口的背景颜色 */
      GUI_SetBkColor(GUI_WHITE);
      GUI_Clear();
      break;
		case WM_NOTIFY_PARENT:
			Id = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch(Id)
      {
        case ID_LISTWHEEL_0: // Notifications sent by 'Button'
        switch(NCode)
        {
          case WM_NOTIFICATION_CLICKED:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);
            LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, 0x191919);
            break;
          case WM_NOTIFICATION_RELEASED:
            break;
          case WM_NOTIFICATION_SEL_CHANGED:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);
            LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, 0x007dfe);
            U8 index = LISTWHEEL_GetPos(hItem);
            LISTWHEEL_SetSel(hItem, index);

            break;
        }
        break;
        case ID_LISTWHEEL_1: // Notifications sent by 'Button'
        switch(NCode)
        {
          case WM_NOTIFICATION_CLICKED:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);
            LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, 0x191919);
            break;
          case WM_NOTIFICATION_RELEASED:
            break;
          case WM_NOTIFICATION_SEL_CHANGED:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);
            LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, 0x007dfe);
            U8 index = LISTWHEEL_GetPos(hItem);
            LISTWHEEL_SetSel(hItem, index);

            break;
        }
        break;
        case ID_LISTWHEEL_2: // Notifications sent by 'Button'
        switch(NCode)
        {
          case WM_NOTIFICATION_CLICKED:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);
            LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, 0x191919);
            break;
          case WM_NOTIFICATION_RELEASED:
            break;
          case WM_NOTIFICATION_SEL_CHANGED:
            hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);
            LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, 0x007dfe);
            U8 index = LISTWHEEL_GetPos(hItem);
            LISTWHEEL_SetSel(hItem, index);

            break;
        }
        break;
				case 0:
					hItem = WM_GetDialogItem(pMsg->hWin, 0);
					switch (NCode) {
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
							botton=~botton;
							break;
					}
					break;
      }
      break;
		default:
			WM_DefaultProc(pMsg);
		  break;
	}
}
static void _cbICON2(WM_MESSAGE *pMsg)
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	static  U8  button_3_flag = 0;
	switch(pMsg->MsgId)
	{
    case WM_PAINT:
      /* 设置客户窗口的背景颜色 */
      GUI_SetBkColor(GUI_WHITE);
      GUI_Clear();
      break;
		case WM_NOTIFY_PARENT:
			Id = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id)
			{
				case 0:
					hItem = WM_GetDialogItem(hWin_FRAME, 0);
					switch (NCode) {
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
							button_3_flag = ~button_3_flag;
							if (button_3_flag != 0)
							{
								BUTTON_SetBitmap(hItem, BUTTON_BI_UNPRESSED, &bmBUTTON_ON);
								HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_RESET);
							}
							else
							{
								BUTTON_SetBitmap(hItem, BUTTON_BI_UNPRESSED, &bmBUTTON_OFF);
								HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_SET);
							}
							break;
					}
					break;
			 case 1:
				 switch (NCode) {
					 case WM_NOTIFICATION_CLICKED:
						 break;
					 case WM_NOTIFICATION_RELEASED:
						 break;
					 case WM_NOTIFICATION_VALUE_CHANGED:
						 hItem = WM_GetDialogItem(hWin_FRAME, 1);
						 value = RADIO_GetValue(hItem);
						 WM_InvalidateWindow(Basic_hItem);
						 break;
				 }
				 break;
			 case 2:
				 switch (NCode) {
					 case WM_NOTIFICATION_CLICKED:
						 break;
					 case WM_NOTIFICATION_RELEASED:
						 Sys_Enter_Standby();
						 break;
				 }
				 break;				 
			}
			break;
		default:
			WM_DefaultProc(pMsg);
		  break;
	}
}

static void FUN_ICON0Clicked(void)
{
	WM_HWIN hWin;
  WM_HWIN hChild;
  WM_HWIN hText;
	
  /* 创建框架窗口 */
	hWin = FRAMEWIN_CreateEx(100,        /* 相对于父窗口坐标的最左像素 */
                         20,           /* 相对于父窗口坐标的最上像素 */
                         300,          /* 水平尺寸 */
                         200,          /* 垂直尺寸 */
                         WM_HBKWIN,    /* 父窗口句柄 */
                         WM_CF_SHOW,   /* 窗口创建标志 */
                         FRAMEWIN_CF_MOVEABLE,/* 额外创建标志 */
                         ID_FRAMEWIN_1,/* 控件ID */
                         "",           /* 标题栏文本 */
                         &_cbICON0);   /* 客户窗口回调函数 */
  FRAMEWIN_SetFont(hWin, GUI_FONT_COMIC24B_ASCII);
  FRAMEWIN_SetText(hWin, "Features");
  FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
  /* 设置为模态窗口 */
  WM_MakeModal(hWin);
  /* 获取客户窗口句柄 */
  hChild = WM_GetClientWindow(hWin);
  /* 在客户窗口中创建子控件 */
	Frame0_hChild=hChild;
  hText = TEXT_CreateEx(0, 0, 300, 34, hChild, WM_CF_SHOW, 0, ID_TEXT_0, "Weather Forecast");
  TEXT_SetFont(hText, GUI_FONT_COMIC24B_ASCII);
  TEXT_SetTextColor(hText, GUI_BLUE);
  hText = TEXT_CreateEx(0, 35, 300, 34, hChild, WM_CF_SHOW, 0, ID_TEXT_1, Temper1);
  TEXT_SetFont(hText, GUI_FONT_COMIC24B_ASCII);
  TEXT_SetTextColor(hText, GUI_BLACK);
	hText = TEXT_CreateEx(0, 70, 300, 34, hChild, WM_CF_SHOW, 0, ID_TEXT_2, Temper);
  TEXT_SetFont(hText, GUI_FONT_COMIC24B_ASCII);
  TEXT_SetTextColor(hText, GUI_BLACK);
	
	WeatherFlag=1;
}

static void FUN_ICON1Clicked(void)
{
	WM_HWIN hWin;
  WM_HWIN hChild;
  WM_HWIN hText;
	WM_HWIN hItem;
	RTC_TimeTypeDef sTime = {0};
  /* 创建框架窗口 */
	hWin = FRAMEWIN_CreateEx(100,        /* 相对于父窗口坐标的最左像素 */
                         20,           /* 相对于父窗口坐标的最上像素 */
                         300,          /* 水平尺寸 */
                         200,          /* 垂直尺寸 */
                         WM_HBKWIN,    /* 父窗口句柄 */
                         WM_CF_SHOW,   /* 窗口创建标志 */
                         FRAMEWIN_CF_MOVEABLE,/* 额外创建标志 */
                         ID_FRAMEWIN_2,/* 控件ID */
                         "",           /* 标题栏文本 */
                         &_cbICON1);   /* 客户窗口回调函数 */
  FRAMEWIN_SetFont(hWin, GUI_FONT_COMIC24B_ASCII);
  FRAMEWIN_SetText(hWin, "CLOCKS");
  FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
  /* 设置为模态窗口 */
  WM_MakeModal(hWin);
  /* 获取客户窗口句柄 */
  hChild = WM_GetClientWindow(hWin);
  /* 在客户窗口中创建子控件 */
  hText = TEXT_CreateEx(0, 0, 300, 30, hChild, WM_CF_SHOW, 0, ID_TEXT_3, "00:00:00");
	hItem = WM_GetDialogItem(hChild, ID_TEXT_3);
	CLOCK_hChild=hItem;
  TEXT_SetFont(hText, GUI_FONT_COMIC24B_ASCII);
  TEXT_SetTextColor(hText, GUI_RED);
	LISTWHEEL_CreateEx(0,30,70,178,hChild,WM_CF_MEMDEV|WM_CF_SHOW,0,ID_LISTWHEEL_0,(GUI_ConstString*)_apYear);
	LISTWHEEL_CreateEx(70,30,70,178,hChild,WM_CF_MEMDEV|WM_CF_SHOW,0,ID_LISTWHEEL_1,(GUI_ConstString*)_apMonth);
	LISTWHEEL_CreateEx(125,30,70,178,hChild,WM_CF_MEMDEV|WM_CF_SHOW,0,ID_LISTWHEEL_2,(GUI_ConstString*)_apDay);
	/* 初始化LISTWHEEL */
	for(int i=0; i < 3; i++)
	{
		hItem = WM_GetDialogItem(hChild, ID_LISTWHEEL_0 + i);
		LISTWHEEL_SetLineHeight(hItem, 34);
		LISTWHEEL_SetSnapPosition(hItem, (178-34)/2);
		LISTWHEEL_SetFont(hItem, GUI_FONT_32B_ASCII);
		LISTWHEEL_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_UNSEL, 0x191919);
		LISTWHEEL_SetTextColor(hItem, LISTWHEEL_CI_SEL, 0x007dfe);
		LISTWHEEL_SetDeceleration(hItem, 35);
		LISTWHEEL_SetOwnerDraw(hItem, _OwnerDraw);
		LISTWHEEL_SetSel(hItem, 0);
	}
	/* 添加LISTWHEEL0文本项 */
	hItem = WM_GetDialogItem(hChild, ID_LISTWHEEL_0);
	for(int i=0;i<GUI_COUNTOF(_apYear);i++)
	{
		LISTWHEEL_AddString(hItem, *(_apYear+i));
	}
	/* 添加LISTWHEEL1文本项 */
	hItem = WM_GetDialogItem(hChild, ID_LISTWHEEL_1);
	for(int i=0;i<GUI_COUNTOF(_apMonth);i++)
	{
		LISTWHEEL_AddString(hItem, *(_apMonth+i));
	}
	/* 添加LISTWHEEL2文本项 */
	hItem = WM_GetDialogItem(hChild, ID_LISTWHEEL_2);
	for(int i=0;i<GUI_COUNTOF(_apDay);i++)
	{
		LISTWHEEL_AddString(hItem, *(_apDay+i));
	}
	BUTTON_CreateEx(190,0,100,30,hChild,WM_CF_SHOW,0,0);
	hItem = WM_GetDialogItem(hChild, 0);
	BUTTON_SetFont(hItem,GUI_FONT_COMIC24B_ASCII);
	BUTTON_SetText(hItem,"TimOut");

  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
	botton=1;
}

static void FUN_ICON2Clicked(void)
{
	WM_HWIN hWin;
  WM_HWIN hChild;
  WM_HWIN hText;
	WM_HWIN	hItem;
  /* 创建框架窗口 */
	hWin = FRAMEWIN_CreateEx(100,        /* 相对于父窗口坐标的最左像素 */
                         20,           /* 相对于父窗口坐标的最上像素 */
                         300,          /* 水平尺寸 */
                         200,          /* 垂直尺寸 */
                         WM_HBKWIN,    /* 父窗口句柄 */
                         WM_CF_SHOW,   /* 窗口创建标志 */
                         FRAMEWIN_CF_MOVEABLE,/* 额外创建标志 */
                         ID_FRAMEWIN_3,/* 控件ID */
                         "",           /* 标题栏文本 */
                         &_cbICON2);   /* 客户窗口回调函数 */
  FRAMEWIN_SetFont(hWin, GUI_FONT_COMIC24B_ASCII);
  FRAMEWIN_SetText(hWin, "Setttings");
  FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
  /* 设置为模态窗口 */
  WM_MakeModal(hWin);
  /* 获取客户窗口句柄 */
  hChild = WM_GetClientWindow(hWin);
	hWin_FRAME = hChild;
  /* 在客户窗口中创建子控件 */
  hText = TEXT_CreateEx(0, 0, 300, 34, hChild, WM_CF_SHOW, 0, ID_TEXT_0, "Main Equipment Control");
  TEXT_SetFont(hText, GUI_FONT_COMIC24B_ASCII);
	TEXT_SetTextColor(hText, GUI_BLUE);
	BUTTON_CreateEx(0,100,165,48,hChild,WM_CF_SHOW,0,0);
	hItem = WM_GetDialogItem(hChild, 0);
	BUTTON_SetBitmap(hItem, BUTTON_BI_UNPRESSED, &bmBUTTON_OFF);
	RADIO_CreateEx(0,30,110,50,hChild,WM_CF_SHOW,0,1,2,25);
	hItem = WM_GetDialogItem(hChild, 1);
	RADIO_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
	RADIO_SetText(hItem, "WHITE", 0);
	RADIO_SetText(hItem, "RED", 1);
	BUTTON_CreateEx(190,30,100,115,hChild,WM_CF_SHOW,0,2);
	hItem = WM_GetDialogItem(hChild, 2);
	BUTTON_SetFont(hItem,GUI_FONT_COMIC24B_ASCII);
	BUTTON_SetText(hItem,"Standby");
	
}

/**
  * @brief 对话框回调函数
  * @note 无
  * @param pMsg：消息指针：消息指针
  * @retval 无
  */
static void _cbDialog(WM_MESSAGE* pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;

	switch (pMsg->MsgId) {
	case WM_PAINT:
		/* 设置客户窗口的背景颜色 */
		GUI_SetBkColor(aColor[value]);
		GUI_Clear();
		break;
	case WM_INIT_DIALOG:
		/* 初始化Framewin控件 */
		hItem = pMsg->hWin;
		Basic_hItem=hItem;
		FRAMEWIN_SetText(hItem, "Small Smartphone");
		FRAMEWIN_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
		FRAMEWIN_SetTitleHeight(hItem, 32);	
    /* 初始化Checkbox3 */
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);
    CHECKBOX_SetText(hItem, "Enable time counting");
    CHECKBOX_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
		CHECKBOX_SetTextColor(hItem, GUI_LIGHTGRAY);
		CHECKBOX_SetSkinClassic(hItem);
    CHECKBOX_SetImage(hItem, &bmcheckbox_true, CHECKBOX_BI_ACTIV_CHECKED);		
		CHECKBOX_SetState(hItem, 1);
		/* 初始化Text1 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
		TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetTextColor(hItem,GUI_BLUE);
		TEXT_SetText(hItem, "YTG Blog->nameytg.top");
		/* 初始化MULTIEDIT控件 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
		MULTIEDIT_SetReadOnly(hItem, 1);
		MULTIEDIT_SetBufferSize(hItem, 500);
		MULTIEDIT_SetAutoScrollH(hItem, 1);
		MULTIEDIT_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
		MULTIEDIT_SetBkColor(hItem, MULTIEDIT_CI_READONLY, GUI_BLACK);
		MULTIEDIT_SetTextColor(hItem, MULTIEDIT_CI_READONLY, GUI_GREEN);
		MULTIEDIT_SetTextAlign(hItem, GUI_TA_LEFT);
		/* 显示内容 */
		MULTIEDIT_AddText(hItem, "Instructions For Use\r\n");
		MULTIEDIT_AddText(hItem, "From https://github.com/name-longming/\r\n");
		MULTIEDIT_AddText(hItem, "With multiple functions, you can check the anything\r\n");
		MULTIEDIT_AddText(hItem, "And even as a remote control for a smart home");
		/* 向控件中添加新图标 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_0);

		ICONVIEW_SetIconAlign(hItem, ICONVIEW_IA_TOP|ICONVIEW_IA_LEFT);

		ICONVIEW_SetFrame(hItem, GUI_COORD_X, 0);//设置图标到IconView边框的间距

		ICONVIEW_SetFrame(hItem, GUI_COORD_Y, 0);

		ICONVIEW_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
		ICONVIEW_SetBkColor(hItem, ICONVIEW_CI_SEL, GUI_MAKE_COLOR(0x40ul << 24 | 0xFFFFFF));
		ICONVIEW_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_BOTTOM);
		ICONVIEW_AddBitmapItem(hItem, _abitmapItem[0].pBitmap, "");
		/* 向控件中添加新图标 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_1);

		ICONVIEW_SetIconAlign(hItem, ICONVIEW_IA_TOP|ICONVIEW_IA_LEFT);

		ICONVIEW_SetFrame(hItem, GUI_COORD_X, 0);//设置图标到IconView边框的间距

		ICONVIEW_SetFrame(hItem, GUI_COORD_Y, 0);

		ICONVIEW_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
		ICONVIEW_SetBkColor(hItem, ICONVIEW_CI_SEL, GUI_MAKE_COLOR(0x40ul << 24 | 0xFFFFFF));
		ICONVIEW_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_BOTTOM);
		ICONVIEW_AddBitmapItem(hItem, _abitmapItem[2].pBitmap, "");
		/* 向控件中添加新图标 */
		hItem = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_2);

		ICONVIEW_SetIconAlign(hItem, ICONVIEW_IA_TOP|ICONVIEW_IA_LEFT);

		ICONVIEW_SetFrame(hItem, GUI_COORD_X, 0);//设置图标到IconView边框的间距

		ICONVIEW_SetFrame(hItem, GUI_COORD_Y, 0);

		ICONVIEW_SetFont(hItem, GUI_FONT_COMIC24B_ASCII);
		ICONVIEW_SetBkColor(hItem, ICONVIEW_CI_SEL, GUI_MAKE_COLOR(0x40ul << 24 | 0xFFFFFF));
		ICONVIEW_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_BOTTOM);
		ICONVIEW_AddBitmapItem(hItem, _abitmapItem[8].pBitmap, "");
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
    switch(Id) {
    case ID_CHECKBOX_3: // Notifications sent by 'Checkbox3'
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        if(CHECKBOX_GetState(hItem))
					CHECKBOX_SetImage(hItem, &bmcheckbox_true, CHECKBOX_BI_ACTIV_CHECKED);
        else
          CHECKBOX_SetImage(hItem, &bmcheckbox_false, CHECKBOX_BI_ACTIV_UNCHECKED);
        break;
      case WM_NOTIFICATION_RELEASED:
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        break;
      }
      break;
			
			case ID_ICONVIEW_0:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_0);
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:
						break;
					case WM_NOTIFICATION_RELEASED:
						switch(ICONVIEW_GetSel(hItem))
						{
							case 0:
								FUN_ICON0Clicked();
								break;
							default:
								break;
						}
						break;
				}
				break;
			case ID_ICONVIEW_1:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_1);
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:
						break;
					case WM_NOTIFICATION_RELEASED:
						switch(ICONVIEW_GetSel(hItem))
						{
							case 0:
								FUN_ICON1Clicked();
								break;
							default:
								break;
						}
						break;
				}
				break;
			case ID_ICONVIEW_2:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_ICONVIEW_2);
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:
						break;
					case WM_NOTIFICATION_RELEASED:
						switch(ICONVIEW_GetSel(hItem))
						{
							case 0:
								FUN_ICON2Clicked();
								break;
							default:
								break;
						}
						break;
				}
				break;
    }
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

 /**
  * @brief 以对话框方式间接创建控件
  * @note 无
  * @param 无
  * @retval hWin：资源表中第一个控件的句柄
  */
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

/**
  * @brief GUI主任务
  * @note 无
  * @param 无
  * @retval 无
  */
void MainTask(void)
{
	/* 创建对话框 */
	CreateFramewin();
//  WM_SetCreateFlags(WM_CF_MEMDEV);
//	WM_EnableMemdev(WM_HBKWIN);
	while (1)
	{
		GUI_Delay(200);
	}
}

/*************************** End of file ****************************/
