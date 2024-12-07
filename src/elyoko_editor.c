#include "elyoko_editor.h"
#include "elyoko_runner.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/style_jungle.h"            // raygui style: jungle
#include "styles/style_candy.h"             // raygui style: candy
#include "styles/style_lavanda.h"           // raygui style: lavanda
#include "styles/style_cyber.h"             // raygui style: cyber
#include "styles/style_terminal.h"          // raygui style: terminal
#include "styles/style_ashes.h"             // raygui style: ashes
#include "styles/style_bluish.h"            // raygui style: bluish
#include "styles/style_dark.h"              // raygui style: dark
#include "styles/style_cherry.h"            // raygui style: cherry
#include "styles/style_sunny.h"             // raygui style: sunny
#include "styles/style_enefete.h"           // raygui style: enefete

void StyleLoader(int pid)
{
    switch (pid)
    {
        case 1: GuiLoadStyleJungle(); break;
        case 2: GuiLoadStyleCandy(); break;
        case 3: GuiLoadStyleLavanda(); break;
        case 4: GuiLoadStyleCyber(); break;
        case 5: GuiLoadStyleTerminal(); break;
        case 6: GuiLoadStyleAshes(); break;
        case 7: GuiLoadStyleBluish(); break;
        case 8: GuiLoadStyleDark(); break;
        case 9: GuiLoadStyleCherry(); break;
        case 10: GuiLoadStyleSunny(); break;
        case 11: GuiLoadStyleEnefete(); break;
        default: GuiLoadStyleDefault();break;
    }
}

#define GUI_UIBROWSER_IMPLEMENTATION
#include "gui/gui_UIBrowser.h"
#define GUI_UICONFIG_IMPLEMENTATION
#include "gui/gui_UIConfig.h"

GuiUIBrowserState state_uibrowser;
GuiUIConfigState state_uiconfig;

struct sproject
{
    char path[100];
};

struct sbrowser
{
    int project_nb;
    char listname_draw[100*50];
    struct sproject listproject[100];
    char isdraw;
}_BROWSER={0};

void BROWSER_Init()
{
    _BROWSER.project_nb=0;
    _BROWSER.isdraw=0;
    strcpy(_BROWSER.listname_draw,"");
    for(int i=0;i<100;i++)
        _BROWSER.listproject[i]=(struct sproject){""};
}
void BROWSER_Scan()
{
	_BROWSER.project_nb=0;
    strcpy(_BROWSER.listname_draw,"");

	FilePathList files = LoadDirectoryFiles(".");
	for(int i=0;i<files.count;i++)
	{
		if(!DirectoryExists(files.paths[i]))
		{
			const char* file_noext = GetFileName(files.paths[i]);
			// if(!BROWSER_IfProjectLoaded(file_noext))
			// 	BROWSER_LoadProject(file_noext);
            const char* sext = GetFileExtension(files.paths[i]);
            const char* sfile = GetFileName(files.paths[i]);
            if(TextIsEqual(sext,".lua") && !TextIsEqual(files.paths[i],"."))
            {
                printf("\n|%s|\n",sfile);
                struct sproject lpjt = {{0}};
                strcpy(lpjt.path,sfile);
                if(_BROWSER.project_nb==0)
                {
                    strcat(_BROWSER.listname_draw,file_noext);
                    //strcpy(_BROWSER.listpath[i],sfile);
                    _BROWSER.listproject[_BROWSER.project_nb] = lpjt;
                    _BROWSER.project_nb++;
                }
                else
                {
                    strcat(_BROWSER.listname_draw,TextFormat(";%s",file_noext));
                    _BROWSER.listproject[_BROWSER.project_nb] = lpjt;
                    _BROWSER.project_nb++;
                    //strcpy(_BROWSER.listpath[i],sfile);
                }

            }
        }
	}
	UnloadDirectoryFiles(files);
}

char Editor_Init(int narg,char** sarg)
{
    if(narg==1)
    {
        BROWSER_Init();
        state_uibrowser = InitGuiUIBrowser();
        _BROWSER.isdraw=1;
        BROWSER_Scan();
        return 1;
    }
    return 0;
}
char Editor_Draw()
{
    GuiUIBrowser(&state_uibrowser,_BROWSER.listname_draw);
    if(state_uibrowser.ButtonLoadPressed)
    {
        int id = (state_uibrowser.ListViewNameScrollIndex*19)+state_uibrowser.ListViewNameActive;
        Runner_DoFile(_BROWSER.listproject[id].path);
        return 0;
    }
    return 1;
}
void Editor_Free()
{}
