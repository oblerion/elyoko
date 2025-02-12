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

struct sproject
{
    char name[50];
    char path[100];
};

struct sbrowser
{
    int project_nb;
    char listname_draw[100*50];
    struct sproject listproject[100];
    char isdraw;
    GuiUIBrowserState state_uibrowser;
};

struct sdata_config
{
  int id_theme;
};

struct sconfig
{
    int tmp_theme;
    struct sdata_config data_config;
    GuiUIConfigState state_uiconfig;
    bool visible;
};

struct seditor
{
    struct sbrowser browser;
    struct sconfig config;
} _Editor;

void Config_Load(struct sconfig* sconf)
{
    const char* cfg_file = ".elyoko.conf";
    FILE* fic = fopen(cfg_file,"rb");
    if(fic != NULL)
    {
        fread(&sconf->data_config,sizeof(struct sdata_config),1,fic);
        fclose(fic);
        StyleLoader(sconf->data_config.id_theme);
        sconf->state_uiconfig.ComboBox001Active = sconf->data_config.id_theme;
    }
}

void Config_Save(struct sconfig* sconf)
{
    const char* cfg_file = ".elyoko.conf";
    sconf->data_config.id_theme = sconf->tmp_theme;
    FILE* fic = fopen(cfg_file,"wb");
    fwrite(&sconf->data_config,sizeof(struct sdata_config),1,fic);
    fclose(fic);
}

struct sconfig Config_Init()
{
    struct sconfig conf = {0};
    conf.state_uiconfig = InitGuiUIConfig();
    conf.visible = false;
    Config_Load(&conf);
    return conf;
}

void Config_Draw(struct sconfig* sconf)
{
    GuiUIConfig(&sconf->state_uiconfig);
    if(sconf->state_uiconfig.WindowBox000Active==false)
    {
        sconf->visible = false;
        sconf->state_uiconfig.WindowBox000Active=true;
    }
    if(sconf->tmp_theme != sconf->state_uiconfig.ComboBox001Active)
    {
        StyleLoader(sconf->state_uiconfig.ComboBox001Active);
        sconf->tmp_theme = sconf->state_uiconfig.ComboBox001Active;
        Config_Save(sconf);
    }
}

struct sbrowser Browser_Init()
{
    struct sbrowser _Browser = {0};
    _Browser.project_nb=0;
    strcpy(_Browser.listname_draw,"");
    _Browser.state_uibrowser = InitGuiUIBrowser();
    _Browser.isdraw=1;
    for(int i=0;i<100;i++)
        _Browser.listproject[i]=(struct sproject){""};
    return _Browser;
}
void Browser_Scan(struct sbrowser* _Browser)
{
	_Browser->project_nb=0;
    strcpy(_Browser->listname_draw,"");

	FilePathList files = LoadDirectoryFiles(".");
	for(int i=0;i<files.count;i++)
	{
        if(DirectoryExists(files.paths[i]) &&
            FileExists(TextFormat("%s/main.lua",files.paths[i]))
        )
        {
            struct sproject lpjt = {{0}};
            strcpy(lpjt.name,files.paths[i]);

            if(_Browser->project_nb==0)
            {
                strcat(_Browser->listname_draw,files.paths[i]);
                //strcpy(_BROWSER.listpath[i],sfile);
                _Browser->listproject[_Browser->project_nb] = lpjt;
                _Browser->project_nb++;
            }
            else
            {
                strcat(_Browser->listname_draw,TextFormat(";%s",files.paths[i]));
                _Browser->listproject[_Browser->project_nb] = lpjt;
                _Browser->project_nb++;
                //strcpy(_BROWSER.listpath[i],sfile);
            }
        }
	}
	UnloadDirectoryFiles(files);
}

void Browser_NewProject(struct sbrowser* sbrowser)
{
    if(sbrowser->state_uibrowser.ButtonNewPressed)
    {
        int i = 0;
        char newfolder[50];
        strcpy(newfolder,"new0");
        while(DirectoryExists(newfolder))
        {
            i++;
            strcpy(newfolder,TextFormat("new%d",i));
        }
        system(TextFormat("mkdir %s",newfolder));
        const char* script = TextFormat("%s/main.lua",newfolder);
        FILE* fic = fopen(script,"w");
        fprintf(fic,"\n\nfunction ELYOKO2D()\n-- 2d loop\ntext(%chello world%c,200,20,25,color(255,255,255))\nend\nfunction ELYOKO3D()\n-- 3d loop\nend",'"','"');
        fclose(fic);
        Browser_Scan(sbrowser);
    }
}

void Browser_DelProject(struct sbrowser* sbrowser)
{
    if(sbrowser->state_uibrowser.ButtonDeletePressed)
    {
       int id = (sbrowser->state_uibrowser.ListViewNameScrollIndex*19)+sbrowser->state_uibrowser.ListViewNameActive;
#if defined(__linux)
        system(TextFormat("rm -r %s && rmdir %s",sbrowser->listproject[id].path,
                          GetDirectoryPath(sbrowser->listproject[id].path)));
#elif defined(_WIN32)
        system(TextFormat("rmdir /q /s %s",GetDirectoryPath(sbrowser->listproject[id].path)));
#endif
        Browser_Scan(sbrowser);
    }
}

#define _launchbin(path) if(FileExists(path)) system(TextFormat("%s .",GetFileName(path)))

void Browser_OpenDir(struct sbrowser sbrowser)//GuiUIBrowserState state_uibrowser)
{
    if(sbrowser.state_uibrowser.ButtonOpenDirPressed)
    {
#if defined(__linux)
        _launchbin("/usr/bin/nautilus");
        _launchbin("/usr/bin/nemo");
        _launchbin("/usr/bin/gnome-open");
#elif defined(_WIN32)
        system(TextFormat("start %windir%\\%s %c.%c",
                          "explorer.exe",'"','"'));
#endif
    }
}

void Browser_Doc(struct sbrowser sbrowser)
{
    if(sbrowser.state_uibrowser.ButtonDocPressed)
    {
        if(!FileExists(TextFormat("./manual_elyoko_%s.pdf",LYO_VERSION)))
        {
            OpenURL("https://oblerion.itch.io/elyoko");
        }
        else
        {
            OpenURL(TextFormat("./manual_elyoko_%s.pdf",LYO_VERSION));
        }
    }
}

char Browser_LoadProject(struct sbrowser sbrowser)
{
    char rc = 1;
    if(sbrowser.state_uibrowser.ButtonLoadPressed)
    {
        int id = (sbrowser.state_uibrowser.ListViewNameScrollIndex*19)+sbrowser.state_uibrowser.ListViewNameActive;
        Runner_DoFolder(sbrowser.listproject[id].name);
        rc= 0;
    }
    return rc;
}

void Browser_Config(struct sbrowser sbrowser)
{
    if(sbrowser.state_uibrowser.ButtonConfigPressed)
    {
        _Editor.config.visible=true;
    }
}

char Editor_Init(int narg)
{
    char rc = 0;
    if(narg==1)
    {
        _Editor.browser = Browser_Init();
        _Editor.config = Config_Init();
        Browser_Scan(&_Editor.browser);
        rc = 1;
    }
    return rc;
}

char Editor_Draw()
{
    char rc = 1;
    if(_Editor.config.visible==false)
    {
        GuiUIBrowser(&_Editor.browser.state_uibrowser,_Editor.browser.listname_draw);
        Browser_OpenDir(_Editor.browser);
        Browser_Doc(_Editor.browser);
        rc = Browser_LoadProject(_Editor.browser);
        Browser_Config(_Editor.browser);
        Browser_NewProject(&_Editor.browser);
        Browser_DelProject(&_Editor.browser);
    }
    else
    {
        Config_Draw(&_Editor.config);
    }
    return rc;
}
void Editor_Free()
{}
