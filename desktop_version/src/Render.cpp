#include "Credits.h"
#include "editor.h"
#include "Entity.h"
#include "FileSystemUtils.h"
#include "Graphics.h"
#include "MakeAndPlay.h"
#include "Map.h"
#include "Maths.h"
#include "Music.h"
#include "Script.h"
#include "UtilityClass.h"

int tr;
int tg;
int tb;

// Macro-like inline function used in maprender()
// Used to keep some text positions the same in Flip Mode
int inline FLIP(int ypos)
{
    if (graphics.flipmode)
    {
        return 220 - ypos;
    }
    return ypos;
}

void menurender()
{
    int temp = 50;

    switch (game.currentmenuname)
    {
    case Menu::mainmenu:
        graphics.setcolreal(graphics.getRGB(tr, tg, tb));
        graphics.drawimagecol(0, -1, 46, tr, tg, tb, true);
		graphics.Print( 10, 230, "Port by Ally", tr/2, tg/2, tb/2);
        graphics.Print( 310 - (16*8), 230, "1.0 (VVVVVV 2.3)", tr/2, tg/2, tb/2);
        break;
    case Menu::playmodes:
    {
        switch (game.currentmenuoption)
        {
        case 0:
            graphics.bigprint( -1, 30, "Normal", tr, tg, tb, true);
            graphics.Print( -1, 65, "The normal Super Gravitron from", tr, tg, tb, true);
            graphics.Print( -1, 75, "the game VVVVVV", tr, tg, tb, true);
            break;
        case 1:
            if (game.swnmodesunlocked[0]) {
                graphics.bigprint( -1, 30, "Free fall", tr, tg, tb, true);
                graphics.Print( -1, 65, "The normal Super Gravitron but", tr, tg, tb, true);
                graphics.Print( -1, 75, "both gravity lines are missing", tr, tg, tb, true);
            } else {
                graphics.bigprint( -1, 30, "Free fall...?", tr, tg, tb, true);
                graphics.Print( -1, 65, "You cheater...", tr, tg, tb, true);
            }
            break;
        case 2:
            if (game.swnmodesunlocked[1]) {
                graphics.bigprint( -1, 30, "Death fall", tr, tg, tb, true);
                graphics.Print( -1, 65, "Free fall mode, but your", tr, tg, tb, true);
                graphics.Print( -1, 75, "vertical space is smaller", tr, tg, tb, true);
            } else {
                graphics.bigprint( -1, 30, "???", tr, tg, tb, true);
                graphics.Print( -1, 65, "TO UNLOCK: Play 20 Free fall games", tr, tg, tb, true);
            }
            break;
        }
        break;
    }
    case Menu::options:
    {
        int flipmode_offset = 0;
        int unlockmode_offset = -1;

        int offset = 0;

        switch (game.currentmenuoption)
        {
        case 0:
            graphics.bigprint( -1, 30, "Accessibility", tr, tg, tb, true);
            graphics.Print( -1, 65, "Disable screen effects, enable", tr, tg, tb, true);
            graphics.Print( -1, 75, "slowdown modes or invincibility", tr, tg, tb, true);
            break;
        case 1:
            graphics.bigprint( -1, 30, "Advanced Options", tr, tg, tb, true);
            graphics.Print( -1, 65, "Hide the mouse cursor, remove", tr, tg, tb, true);
            graphics.Print( -1, 75, "the loading screen, turn on", tr, tg, tb, true);
            graphics.Print( -1, 85, "glitchrunner mode and more", tr, tg, tb, true);
            break;
        case 2:
            graphics.bigprint( -1, 30, "Game Pad Options", tr, tg, tb, true);
            graphics.Print( -1, 65, "Rebind your controller's buttons", tr, tg, tb, true);
            graphics.Print( -1, 75, "and adjust sensitivity", tr, tg, tb, true);
            break;
        case 3:
            graphics.bigprint( -1, 30, "Clear Data", tr, tg, tb, true);
            graphics.Print( -1, 65, "Delete your save data", tr, tg, tb, true);
            graphics.Print( -1, 75, "and unlocked play modes", tr, tg, tb, true);
            break;
        }
        break;
    }
    case Menu::graphicoptions:
        switch (game.currentmenuoption)
        {
        case 0:
            graphics.bigprint( -1, 30, "Toggle Fullscreen", tr, tg, tb, true);
            graphics.Print( -1, 65, "Change to fullscreen/windowed mode.", tr, tg, tb, true);

            if(game.fullscreen){
              graphics.Print( -1, 85, "Current mode: FULLSCREEN", tr, tg, tb, true);
            }else{
              graphics.Print( -1, 85, "Current mode: WINDOWED", tr, tg, tb, true);
            }
            break;

        case 1:
            graphics.bigprint( -1, 30, "Scaling Mode", tr, tg, tb, true);
            graphics.Print( -1, 65, "Choose letterbox/stretch/integer mode.", tr, tg, tb, true);

            if(game.stretchMode == 2){
              graphics.Print( -1, 85, "Current mode: INTEGER", tr, tg, tb, true);
            }else if (game.stretchMode == 1){
              graphics.Print( -1, 85, "Current mode: STRETCH", tr, tg, tb, true);
            }else{
              graphics.Print( -1, 85, "Current mode: LETTERBOX", tr, tg, tb, true);
            }
            break;
        case 2:
            graphics.bigprint(-1, 30, "Resize to Nearest", tr, tg, tb, true);
            graphics.Print(-1, 65, "Resize to the nearest window size", tr, tg, tb, true);
            graphics.Print(-1, 75, "that is of an integer multiple.", tr, tg, tb, true);
            if (!graphics.screenbuffer->isWindowed)
            {
                graphics.Print(-1, 95, "You must be in windowed mode", tr, tg, tb, true);
                graphics.Print(-1, 105, "to use this option.", tr, tg, tb, true);
            }
            break;
        case 3:
            graphics.bigprint( -1, 30, "Toggle Filter", tr, tg, tb, true);
            graphics.Print( -1, 65, "Change to nearest/linear filter.", tr, tg, tb, true);

            if(game.useLinearFilter){
              graphics.Print( -1, 85, "Current mode: LINEAR", tr, tg, tb, true);
            }else{
              graphics.Print( -1, 85, "Current mode: NEAREST", tr, tg, tb, true);
            }
            break;

        case 4:
            graphics.bigprint( -1, 30, "Analogue Mode", tr, tg, tb, true);
            graphics.Print( -1, 65, "There is nothing wrong with your", tr, tg, tb, true);
            graphics.Print( -1, 75, "television set. Do not attempt to", tr, tg, tb, true);
            graphics.Print( -1, 85, "adjust the picture.", tr, tg, tb, true);
            break;
        case 5:
            graphics.bigprint(-1, 30, "Toggle 30+ FPS", tr, tg, tb, true);
            graphics.Print(-1, 65, "Change whether the game", tr, tg, tb, true);
            graphics.Print(-1, 75, "runs at 30 or over 30 FPS.", tr, tg, tb, true);

            if (!game.over30mode)
            {
                graphics.Print(-1, 95, "Current mode: 30 FPS", tr/2, tg/2, tb/2, true);
            }
            else
            {
                graphics.Print(-1, 95, "Current mode: Over 30 FPS", tr, tg, tb, true);
            }
            break;
        case 6:
            graphics.bigprint(-1, 30, "Toggle VSync", tr, tg, tb, true);
#ifdef __HAIKU__ // FIXME: Remove after SDL VSync bug is fixed! -flibit
            graphics.Print(-1, 65, "Edit the config file on Haiku!", tr, tg, tb, true);
#else
            graphics.Print(-1, 65, "Turn VSync on or off.", tr, tg, tb, true);
#endif

            if (!graphics.screenbuffer->vsync)
            {
                graphics.Print(-1, 95, "Current mode: VSYNC OFF", tr/2, tg/2, tb/2, true);
            }
            else
            {
                graphics.Print(-1, 95, "Current mode: VSYNC ON", tr, tg, tb, true);
            }
            break;
        }
        break;
    case Menu::cleardatamenu:
        graphics.Print( -1, 100, "Are you sure you want to", tr, tg, tb, true);
        graphics.Print( -1, 110, "delete all your saved data?", tr, tg, tb, true);
        break;
    case Menu::controller:
        graphics.bigprint( -1, 30, "Game Pad", tr, tg, tb, true);
        graphics.Print( -1, 55, "Change controller options.", tr, tg, tb, true);
        switch (game.currentmenuoption)
        {
        case 0:
            switch(game.controllerSensitivity)
            {
            case 0:
                graphics.Print( -1, 85, " Low     Medium     High", tr, tg, tb, true);
                graphics.Print( -1, 95, "[]..................", tr, tg, tb, true);
                break;
            case 1:
                graphics.Print( -1, 85, " Low     Medium     High", tr, tg, tb, true);
                graphics.Print( -1, 95, ".....[].............", tr, tg, tb, true);
                break;
            case 2:
                graphics.Print( -1, 85, " Low     Medium     High", tr, tg, tb, true);
                graphics.Print( -1, 95, ".........[].........", tr, tg, tb, true);
                break;
            case 3:
                graphics.Print( -1, 85, " Low     Medium     High", tr, tg, tb, true);
                graphics.Print( -1, 95, ".............[].....", tr, tg, tb, true);
                break;
            case 4:
                graphics.Print( -1, 85, " Low     Medium     High", tr, tg, tb, true);
                graphics.Print( -1, 95, "..................[]", tr, tg, tb, true);
                break;
            }
            break;
        case 1:
        case 2:
        case 3:
            graphics.Print( -1, 85, "Flip is bound to: " + std::string(help.GCString(game.controllerButton_flip)) , tr, tg, tb, true);
            graphics.Print( -1, 95, "Enter is bound to: "  + std::string(help.GCString(game.controllerButton_map)), tr, tg, tb, true);
            graphics.Print( -1, 105, "Menu is bound to: " + std::string(help.GCString(game.controllerButton_esc)) , tr, tg, tb, true);
            break;
        }


        break;
    case Menu::advancedoptions:
        switch (game.currentmenuoption)
        {
        case 0:
            graphics.bigprint(-1, 30, "Toggle Mouse Cursor", tr, tg, tb, true);
            graphics.Print(-1, 65, "Show/hide the system mouse cursor.", tr, tg, tb, true);

            if (graphics.showmousecursor) {
                graphics.Print(-1, 95, "Current mode: SHOW", tr, tg, tb, true);
            }
            else {
                graphics.Print(-1, 95, "Current mode: HIDE", tr/2, tg/2, tb/2, true);
            }
            break;
        case 1:
            graphics.bigprint( -1, 30, "Unfocus Pause", tr, tg, tb, true);
            graphics.Print( -1, 65, "Toggle if the game will pause", tr, tg, tb, true);
            graphics.Print( -1, 75, "when the window is unfocused.", tr, tg, tb, true);
            if (game.disablepause)
            {
                graphics.Print(-1, 95, "Unfocus pause is OFF", tr/2, tg/2, tb/2, true);
            }
            else
            {
                graphics.Print(-1, 95, "Unfocus pause is ON", tr, tg, tb, true);
            }
            break;
        }
        break;
    case Menu::accessibility:
        switch (game.currentmenuoption)
        {
        case 0:
            graphics.bigprint( -1, 40, "Backgrounds", tr, tg, tb, true);
            if (!game.colourblindmode)
            {
                graphics.Print( -1, 75, "Backgrounds are ON.", tr, tg, tb, true);
            }
            else
            {
                graphics.Print( -1, 75, "Backgrounds are OFF.", tr/2, tg/2, tb/2, true);
            }
            break;
        case 1:
            graphics.bigprint( -1, 40, "Screen Effects", tr, tg, tb, true);
            graphics.Print( -1, 75, "Disables screen shakes and flashes.", tr, tg, tb, true);
            if (!game.noflashingmode)
            {
                graphics.Print( -1, 85, "Screen Effects are ON.", tr, tg, tb, true);
            }
            else
            {
                graphics.Print( -1, 85, "Screen Effects are OFF.", tr/2, tg/2, tb/2, true);
            }
            break;
        }
        break;
    case Menu::youwannaquit:
        graphics.Print( -1, 75, "Are you sure you want to quit?", tr, tg, tb, true);
        break;
    case Menu::about1:
        graphics.drawimage(1,-1,10,true);
        graphics.Print(-1,150,"Hello! My name's Terry and I made",tr,tg,tb,true);
        graphics.Print(-1,160,"the Super Gravitron!",tr,tg,tb,true);
        graphics.Print(-1,175,"Thank you for playing it!",tr,tg,tb,true);
        break;
    case Menu::about2:
        graphics.drawimage(2,-1,10, true);
        graphics.Print(-1,145,"DID YOU KNOW?",tr,tg,tb,true);
        graphics.Print(-1,160,"Super Gravitron is actually a small",tr,tg,tb,true);
        graphics.Print(-1,170,"part of a different game that I made",tr,tg,tb,true);
        graphics.Print(-1,180,"years ago, called VVVVVV!",tr,tg,tb,true);
        break;
    case Menu::about3:
        graphics.Print(-1,10,"Years before I made",tr,tg,tb,true);
        graphics.Print(-1,20,"Super Hexagon, VVVVVV was my",tr,tg,tb,true);
        graphics.Print(-1,30,"first commercial game.",tr,tg,tb,true);
        graphics.drawimage(3,-1,50, true);
        graphics.Print(-1,135,"It's an 80's inspired platformer,",tr,tg,tb,true);
        graphics.Print(-1,145,"built around exploring a single",tr,tg,tb,true);
        graphics.Print(-1,155,"game mechanic as far as I could:",tr,tg,tb,true);
        graphics.Print(-1,170,"What if, instead of jumping,",tr,tg,tb,true);
        graphics.Print(-1,180,"you flipped gravity?",tr,tg,tb,true);
        break;
    case Menu::about4:
        graphics.Print(-1,20,"I'm very proud of VVVVVV, and I'm",tr,tg,tb,true);
        graphics.Print(40,30,"glad that other people like it too!",tr,tg,tb,true);
        graphics.Print(40,50,"When the original version was released",tr,tg,tb,true);
        graphics.Print(40,60,"in 2010, it won an award at Indiecade",tr,tg,tb,true);
        graphics.Print(40,70,"for most Fun Game, and showed up in",tr,tg,tb,true);
        graphics.Print(40,80,"lots of game of the year lists! Here's",tr,tg,tb,true);
        graphics.Print(40,90,"what some people have said about it:",tr,tg,tb,true);
        graphics.Print(40,130,"\"One of the best platformers",tr * 0.8,tg * 0.8,tb * 0.8,true);
        graphics.Print(40,140,"I\'ve ever played.\"",tr * 0.8,tg * 0.8,tb * 0.8,true);
        graphics.Print(40,155,"                      Anthony Burch",tr * 0.5,tg * 0.5,tb * 0.5,true);
        graphics.Print(40,165,"                  Destructoid 10/10",tr * 0.5,tg * 0.5,tb * 0.5,true);
        break;
    case Menu::about5:
        graphics.Print(40,15,"\"I haven't felt as good with a",tr,tg,tb,true);
        graphics.Print(40,25,"videogame, in that direct\"",tr,tg,tb,true);
        graphics.Print(40,35,"physical way, for quite a while.\"",tr,tg,tb,true);
        graphics.Print(40,50,"                      Kieron Gillen",tr * 0.8,tg * 0.8,tb * 0.8,true);
        graphics.Print(40,60,"               Rock, Paper, Shotgun",tr * 0.8,tg * 0.8,tb * 0.8,true);
        graphics.Print(40,85,"\"This game is incredible.\"",tr,tg,tb,true);
        graphics.Print(40,100,"                      Michael Rose",tr * 0.8,tg * 0.8,tb * 0.8,true);
        graphics.Print(40,110,"                    Indiegames.com",tr * 0.8,tg * 0.8,tb * 0.8,true);
        graphics.Print(40,135,"\"When game design is taught in",tr,tg,tb,true);
        graphics.Print(40,145,"most universities, VVVVVV will",tr,tg,tb,true);
        graphics.Print(40,155,"be on every syllabus.\"",tr,tg,tb,true);
        graphics.Print(40,170,"                    Filipe Salgado",tr * 0.8,tg * 0.8,tb * 0.8,true);
        graphics.Print(40,180,"          Kill Screen Best of 2010",tr * 0.8,tg * 0.8,tb * 0.8,true);
        break;
    case Menu::about6:
        graphics.drawimage(4,-1,10, true);
        graphics.Print(-1,140,"If you'd like to try it, VVVVVV is",tr,tg,tb,true);
        graphics.Print(-1,150,"now available for android!",tr,tg,tb,true);
        break;
    default:
        break;
    }
}

void titlerender()
{

    FillRect(graphics.backBuffer, 0,0,graphics.backBuffer->w, graphics.backBuffer->h, 0x00000000 );

    if (!game.menustart)
    {
        tr = graphics.col_tr;
        tg = graphics.col_tg;
        tb = graphics.col_tb;

        graphics.setcolreal(graphics.getRGB(tr, tg, tb));
        graphics.drawimagecol(0, -1, 46, tr, tg, tb, true);

        graphics.Print(5, 175, "[ Press ACTION to Start ]", tr, tg, tb, true);
        graphics.Print(5, 195, "ACTION = Space, Z, or V", int(tr*0.5f), int(tg*0.5f), int(tb*0.5f), true);
    }
    else
    {
        if(!game.colourblindmode) graphics.drawtowerbackground();

        tr = graphics.col_tr;
        tg = graphics.col_tg;
        tb = graphics.col_tb;

        menurender();

        tr = int(tr * .8f);
        tg = int(tg * .8f);
        tb = int(tb * .8f);
        if (tr < 0) tr = 0;
        if(tr>255) tr=255;
        if (tg < 0) tg = 0;
        if(tg>255) tg=255;
        if (tb < 0) tb = 0;
        if(tb>255) tb=255;
        graphics.drawmenu(tr, tg, tb, false);
        //graphics.drawmenu(tr, tg, tb, game.currentmenuname == Menu::levellist);
    }

    graphics.drawfade();

    graphics.renderwithscreeneffects();
}

void gamecompleterender()
{
    FillRect(graphics.backBuffer, 0x000000);

    if(!game.colourblindmode) graphics.drawtowerbackground();

    tr = graphics.col_tr;
    tg = graphics.col_tg;
    tb = graphics.col_tb;


    //rendering starts... here!

    int position = graphics.lerp(game.oldcreditposition, game.creditposition);
    if (graphics.onscreen(220 + position))
    {
        int temp = 220 + position;
        graphics.drawsprite((160 - 96) + 0 * 32, temp, 23, tr, tg, tb);
        graphics.drawsprite((160 - 96) + 1 * 32, temp, 23, tr, tg, tb);
        graphics.drawsprite((160 - 96) + 2 * 32, temp, 23, tr, tg, tb);
        graphics.drawsprite((160 - 96) + 3 * 32, temp, 23, tr, tg, tb);
        graphics.drawsprite((160 - 96) + 4 * 32, temp, 23, tr, tg, tb);
        graphics.drawsprite((160 - 96) + 5 * 32, temp, 23, tr, tg, tb);
    }

    if (graphics.onscreen(290 + position)) graphics.bigprint( -1, 290 + position, "Starring", tr, tg, tb, true, 2);

    if (graphics.onscreen(320 + position))
    {
        graphics.drawcrewman(70, 320 + position, 0, true);
        graphics.Print(100, 330 + position, "Captain Viridian", tr, tg, tb);
    }
    if (graphics.onscreen(350 + position))
    {
        graphics.drawcrewman(70, 350 + position, 1, true);
        graphics.Print(100, 360 + position, "Doctor Violet", tr, tg, tb);
    }
    if (graphics.onscreen(380 + position))
    {
        graphics.drawcrewman(70, 380 + position, 2, true);
        graphics.Print(100, 390 + position, "Professor Vitellary", tr, tg, tb);
    }
    if (graphics.onscreen(410 + position))
    {
        graphics.drawcrewman(70, 410 + position, 3, true);
        graphics.Print(100, 420 + position, "Officer Vermilion", tr, tg, tb);
    }
    if (graphics.onscreen(440 + position))
    {
        graphics.drawcrewman(70, 440 + position, 4, true);
        graphics.Print(100, 450 + position, "Chief Verdigris", tr, tg, tb);
    }
    if (graphics.onscreen(470 + position))
    {
        graphics.drawcrewman(70, 470 + position, 5, true);
        graphics.Print(100, 480 + position, "Doctor Victoria", tr, tg, tb);
    }

    if (graphics.onscreen(520 + position)) graphics.bigprint( -1, 520 + position, "Credits", tr, tg, tb, true, 3);

    if (graphics.onscreen(560 + position))
    {
        graphics.Print(40, 560 + position, "Created by", tr, tg, tb);
        graphics.bigprint(60, 570 + position, "Terry Cavanagh", tr, tg, tb);
    }

    if (graphics.onscreen(600 + position))
    {
        graphics.Print(40, 600 + position, "With Music by", tr, tg, tb);
        graphics.bigprint(60, 610 + position, "Magnus P~lsson", tr, tg, tb);
    }

    if (graphics.onscreen(640 + position))
    {
        graphics.Print(40, 640 + position, "Rooms Named by", tr, tg, tb);
        graphics.bigprint(60, 650 + position, "Bennett Foddy", tr, tg, tb);
    }

    if (graphics.onscreen(680 + position))
    {
        graphics.Print(40, 680 + position, "C++ Port by", tr, tg, tb);
        graphics.bigprint(60, 690 + position, "Simon Roth", tr, tg, tb);
        graphics.bigprint(60, 710 + position, "Ethan Lee", tr, tg, tb);
    }


    if (graphics.onscreen(740 + position))
    {
        graphics.Print(40, 740 + position, "Beta Testing by", tr, tg, tb);
        graphics.bigprint(60, 750 + position, "Sam Kaplan", tr, tg, tb);
        graphics.bigprint(60, 770 + position, "Pauli Kohberger", tr, tg, tb);
    }

    if (graphics.onscreen(800 + position))
    {
        graphics.Print(40, 800 + position, "Ending Picture by", tr, tg, tb);
        graphics.bigprint(60, 810 + position, "Pauli Kohberger", tr, tg, tb);
    }

    if (graphics.onscreen(890 + position)) graphics.bigprint( -1, 870 + position, "Patrons", tr, tg, tb, true, 3);

    int creditOffset = 930;

    for (size_t i = 0; i < SDL_arraysize(Credits::superpatrons); i += 1)
    {
        if (graphics.onscreen(creditOffset + position))
        {
            graphics.Print(-1, creditOffset + position, Credits::superpatrons[i], tr, tg, tb, true);
        }
        creditOffset += 10;
    }

    creditOffset += 10;
    if (graphics.onscreen(creditOffset + position)) graphics.Print( -1, creditOffset + position, "and", tr, tg, tb, true);
    creditOffset += 20;

    for (size_t i = 0; i < SDL_arraysize(Credits::patrons); i += 1)
    {
        if (graphics.onscreen(creditOffset + position))
        {
            graphics.Print(-1, creditOffset + position, Credits::patrons[i], tr, tg, tb, true);
        }
        creditOffset += 10;
    }

    creditOffset += 20;
    if (graphics.onscreen(creditOffset + position)) graphics.bigprint(40, creditOffset + position, "GitHub Contributors", tr, tg, tb, true);
    creditOffset += 30;

    for (size_t i = 0; i < SDL_arraysize(Credits::githubfriends); i += 1)
    {
        if (graphics.onscreen(creditOffset + position))
        {
            graphics.Print(-1, creditOffset + position, Credits::githubfriends[i], tr, tg, tb, true);
        }
        creditOffset += 10;
    }

    creditOffset += 140;
    if (graphics.onscreen(creditOffset + position)) graphics.bigprint( -1, creditOffset + position, "Thanks for playing!", tr, tg, tb, true, 2);

    graphics.drawfade();

    graphics.render();
}

void gamecompleterender2()
{
    FillRect(graphics.backBuffer, 0x000000);

    //graphics.drawimage(10, 0, 0);

    for (int j = 0; j < 30; j++)
    {
        for (int i = 0; i < 40; i++)
        {
            if (j == game.creditposy)
            {
                if (i > game.creditposx)
                {
                    FillRect(graphics.backBuffer, i * 8, j * 8, 8, 8, 0, 0, 0);
                }
            }

            if (j > game.creditposy)
            {
                FillRect(graphics.backBuffer, i * 8, j * 8, 8, 8, 0, 0, 0);
            }
        }
    }

    FillRect(graphics.backBuffer, graphics.lerp(game.oldcreditposx * 8, game.creditposx * 8) + 8, game.creditposy * 8, 8, 8, 0, 0, 0);

    graphics.drawfade();

    graphics.render();
}

void gamerender()
{



    if(!game.blackout)
    {

        if (map.towermode)
        {
            if (!game.colourblindmode)
            {
                graphics.drawtowerbackground();
            }
            else
            {
                FillRect(graphics.backBuffer,0x00000);
            }
            graphics.drawtowermap();
        }
        else
        {
            if(!game.colourblindmode)
            {
                graphics.drawbackground(map.background);
            }
            else
            {
                FillRect(graphics.backBuffer,0x00000);
            }
            if (map.final_colormode)
            {
                graphics.drawfinalmap();
            }
            else
            {
                graphics.drawmap();
            }
        }


        graphics.drawentities();
        if (map.towermode)
        {
            graphics.drawtowerspikes();
        }
        if (game.swnroommode == 2) {// If deathfall
            SDL_Rect temprect;
			temprect.x = 0;
			temprect.y = 0;
			temprect.w = 320;
			temprect.h = 48;
            FillRect(graphics.backBuffer, temprect, 0);
			temprect.x = 0;
			temprect.y = 184;
			temprect.w = 320;
			temprect.h = 56;
            FillRect(graphics.backBuffer, temprect, 0);
        }
    }

    if(map.extrarow==0 || (map.custommode && map.roomname!=""))
    {
        graphics.footerrect.y = 230;
        if (graphics.translucentroomname)
        {
            SDL_BlitSurface(graphics.footerbuffer, NULL, graphics.backBuffer, &graphics.footerrect);
        }
        else
        {
            FillRect(graphics.backBuffer, graphics.footerrect, 0);
        }

        if (map.finalmode)
        {
            graphics.bprint(5, 231, map.glitchname, 196, 196, 255 - help.glow, true);
        }else{
            graphics.bprint(5, 231, map.roomname, 196, 196, 255 - help.glow, true);
        }
    }

    if (map.roomtexton)
    {
        //Draw room text!
        for (size_t i = 0; i < map.roomtext.size(); i++)
        {
            graphics.Print(map.roomtext[i].x*8, (map.roomtext[i].y*8), map.roomtext[i].text, 196, 196, 255 - help.glow);
        }
    }

#if !defined(NO_CUSTOM_LEVELS)
     if(map.custommode && !map.custommodeforreal && !game.advancetext){
        //Return to level editor
        int alpha = graphics.lerp(ed.oldreturneditoralpha, ed.returneditoralpha);
        graphics.bprintalpha(5, 5, "[Press ENTER to return to editor]", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), alpha, false);
      }
#endif


    graphics.cutscenebars();
    graphics.drawfade();
    BlitSurfaceStandard(graphics.backBuffer, NULL, graphics.tempBuffer, NULL);

    graphics.drawgui();
    if (graphics.flipmode)
    {
        if (game.advancetext) graphics.bprint(5, 228, "- Press ACTION to advance text -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }
    else
    {
        if (game.advancetext) graphics.bprint(5, 5, "- Press ACTION to advance text -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }

    if ((game.readytotele > 100 || game.oldreadytotele > 100) && !game.advancetext && game.hascontrol && !script.running && !game.intimetrial)
    {
        int alpha = graphics.lerp(game.oldreadytotele, game.readytotele);
        if(graphics.flipmode)
        {
            graphics.bprint(5, 20, "- Press ENTER to Teleport -", alpha - 20 - (help.glow / 2), alpha - 20 - (help.glow / 2), alpha, true);
        }
        else
        {
            graphics.bprint(5, 210, "- Press ENTER to Teleport -", alpha - 20 - (help.glow / 2), alpha - 20 - (help.glow / 2), alpha, true);
        }
    }

    if (game.swnmode)
    {
        if (game.swngame == 0)
        {
            std::string tempstring = help.timestring(game.swntimer);
            graphics.bigprint( -1, 20, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
        }
        else if (game.swngame == 1)
        {
            if (game.swnmessage == 0)
            {
                std::string tempstring = help.timestring(game.swntimer);
                graphics.Print( 10, 10, "Current Time", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                graphics.bigprint( 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);
                tempstring = help.timestring(game.swnrecords[game.swnroommode]);
                graphics.Print( 240, 10, "Best Time", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                graphics.bigrprint( 300, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);

                switch(game.swnbestrank)
                {
                case 0:
                    graphics.Print( -1, 204, "Next Trophy at 5 seconds", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 1:
                    graphics.Print( -1, 204, "Next Trophy at 10 seconds", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 2:
                    graphics.Print( -1, 204, "Next Trophy at 15 seconds", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 3:
                    graphics.Print( -1, 204, "Next Trophy at 20 seconds", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 4:
                    graphics.Print( -1, 204, "Next Trophy at 30 seconds", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 5:
                    graphics.Print( -1, 204, "Next Trophy at 1 minute", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                case 6:
                    graphics.Print( -1, 204, "All Trophies collected!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                    break;
                }
            }
            else if (game.swnmessage == 1)
            {
                std::string tempstring = help.timestring(game.swntimer);
                graphics.Print( 10, 10, "Current Time", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                graphics.bigprint( 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);
                tempstring = help.timestring(game.swnrecords[game.swnroommode]);
                if (int(game.deathseq / 5) % 2 == 1)
                {
                    graphics.Print( 240, 10, "Best Time", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                    graphics.bigrprint( 300, 24, tempstring, 128 - (help.glow), 220 - (help.glow), 128 - (help.glow / 2), false, 2);

                    graphics.bigprint( -1, 200, "New Record!", 128 - (help.glow), 220 - (help.glow), 128 - (help.glow / 2), true, 2);
                }
            }
            else if (game.swnmessage >= 2)
            {
                game.swnmessage--;
                if (game.swnmessage == 2) game.swnmessage = 0;
                std::string tempstring = help.timestring(game.swntimer);
                graphics.Print( 10, 10, "Current Time", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                graphics.bigprint( 25, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);
                tempstring = help.timestring(game.swnrecords[game.swnroommode]);
                graphics.Print( 240, 10, "Best Time", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false);
                graphics.bigrprint( 300, 24, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), false, 2);

                if (int(game.swnmessage / 5) % 2 == 1)
                {
                    graphics.bigprint( -1, 200, "New Trophy!", 220 - (help.glow), 128 - (help.glow), 128 - (help.glow / 2), true, 2);
                }
            }

            graphics.Print( 20, 228, "[Press ENTER to stop]", 160 - (help.glow/2), 160 - (help.glow/2), 160 - (help.glow/2), true);
        }
        else if(game.swngame==2)
        {
            if (int(game.swndelay / 15) % 2 == 1 || game.swndelay >= 120)
            {
                if (graphics.flipmode)
                {
                    graphics.bigprint( -1, 30, "Survive for", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                    graphics.bigprint( -1, 10, "60 seconds!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                }
                else
                {
                    graphics.bigprint( -1, 10, "Survive for", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                    graphics.bigprint( -1, 30, "60 seconds!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                }
            }
        }
        else if(game.swngame==7)
        {
            if (game.swndelay >= 60)
            {
                graphics.bigprint( -1, 20, "SUPER GRAVITRON", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);

                std::string tempstring = help.timestring(game.swnrecords[game.swnroommode]);
                graphics.Print( 240, 190, "Best Time", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
                graphics.bigrprint( 300, 205, tempstring, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
            }
            else	if (int(game.swndelay / 10) % 2 == 1)
            {
                graphics.bigprint( -1, 20, "SUPER GRAVITRON", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 2);
                graphics.bigprint( -1, 200, "GO!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 3);
            }
        }
    }

    if (game.intimetrial && graphics.fademode==0)
    {
        //Draw countdown!
        if (game.timetrialcountdown > 0)
        {
            if (game.timetrialcountdown < 30)
            {
                game.resetgameclock();
                if (int(game.timetrialcountdown / 4) % 2 == 0) graphics.bigprint( -1, 100, "Go!", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 60)
            {
                graphics.bigprint( -1, 100, "1", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 90)
            {
                graphics.bigprint( -1, 100, "2", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
            else if (game.timetrialcountdown < 120)
            {
                graphics.bigprint( -1, 100, "3", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true, 4);
            }
        }
        else
        {
            //Draw OSD stuff
            graphics.bprint(6, 18, "TIME :",  255,255,255);
            graphics.bprint(6, 30, "DEATH:",  255, 255, 255);
            graphics.bprint(6, 42, "SHINY:",  255,255,255);

            if(game.timetrialparlost)
            {
                graphics.bprint(56, 18, game.timestring(),  196, 80, 80);
            }
            else
            {
                graphics.bprint(56, 18, game.timestring(),  196, 196, 196);
            }
            if(game.deathcounts>0)
            {
                graphics.bprint(56, 30,help.String(game.deathcounts),  196, 80, 80);
            }
            else
            {
                graphics.bprint(56, 30,help.String(game.deathcounts),  196, 196, 196);
            }
            if(game.trinkets()<game.timetrialshinytarget)
            {
                graphics.bprint(56, 42,help.String(game.trinkets()) + " of " +help.String(game.timetrialshinytarget),  196, 80, 80);
            }
            else
            {
                graphics.bprint(56, 42,help.String(game.trinkets()) + " of " +help.String(game.timetrialshinytarget),  196, 196, 196);
            }

            if(game.timetrialparlost)
            {
                graphics.bprint(195, 214, "PAR TIME:",  80, 80, 80);
                graphics.bprint(275, 214, game.partimestring(),  80, 80, 80);
            }
            else
            {
                graphics.bprint(195, 214, "PAR TIME:",  255, 255, 255);
                graphics.bprint(275, 214, game.partimestring(),  196, 196, 196);
            }
        }
    }

    float act_alpha = graphics.lerp(game.prev_act_fade, game.act_fade) / 10.0f;
    if (game.activeactivity > -1)
    {
        game.activity_lastprompt = obj.blocks[game.activeactivity].prompt;
        game.activity_r = obj.blocks[game.activeactivity].r;
        game.activity_g = obj.blocks[game.activeactivity].g;
        game.activity_b = obj.blocks[game.activeactivity].b;
        graphics.drawtextbox(16, 4, 36, 3, game.activity_r*act_alpha, game.activity_g*act_alpha, game.activity_b*act_alpha);
        graphics.Print(5, 12, game.activity_lastprompt, game.activity_r*act_alpha, game.activity_g*act_alpha, game.activity_b*act_alpha, true);
    }
    else if(game.act_fade>5 || game.prev_act_fade>5)
    {
        graphics.drawtextbox(16, 4, 36, 3, game.activity_r*act_alpha, game.activity_g*act_alpha, game.activity_b*act_alpha);
        graphics.Print(5, 12, game.activity_lastprompt, game.activity_r*act_alpha, game.activity_g*act_alpha, game.activity_b*act_alpha, true);
    }

    if (obj.trophytext > 0 || obj.oldtrophytext > 0)
    {
        graphics.drawtrophytext();
    }


    graphics.renderwithscreeneffects();
}

void maprender()
{
    FillRect(graphics.backBuffer, 0x000000);

    //draw screen alliteration
    //Roomname:
    if (map.hiddenname != "")
    {
        graphics.Print(5, 2, map.hiddenname, 196, 196, 255 - help.glow, true);
    }
    else
    {
      if (map.finalmode){
        graphics.Print(5, 2, map.glitchname, 196, 196, 255 - help.glow, true);
      }else{
        graphics.Print(5, 2, map.roomname, 196, 196, 255 - help.glow, true);
      }
    }

    //Background color
    FillRect(graphics.backBuffer,0, 12, 320, 240, 10, 24, 26 );



    //Menubar:
    graphics.drawtextbox( -10, 212, 42, 3, 65, 185, 207);

    // Draw the selected page name at the bottom
    // menupage 0 - 3 is the pause screen
    if (game.menupage <= 3)
    {
        std::string tab1;
        if (game.insecretlab)
        {
            tab1 = "GRAV";
        }
        else if (obj.flags[67] && !map.custommode)
        {
            tab1 = "SHIP";
        }
        else
        {
            tab1 = "CREW";
        }
#define TAB(opt, text) graphics.map_tab(opt, text, game.menupage == opt)
        TAB(0, "MAP");
        TAB(1, tab1);
        TAB(2, "STATS");
        TAB(3, "SAVE");
#undef TAB
    }

    // Draw menu header
    switch (game.menupage)
    {
    case 30:
    case 31:
    case 32:
    case 33:
        graphics.Print(-1, 220, "[ PAUSE ]", 196, 196, 255 - help.glow, true);
    }

    // Draw menu options
    if (game.menupage >= 30 && game.menupage <= 33)
    {
#define OPTION(opt, text) graphics.map_option(opt, 4, text, game.menupage - 30 == opt)
        OPTION(0, "return to game");
        OPTION(1, "quit to menu");
        OPTION(2, "graphic options");
        OPTION(3, "game options");
#undef OPTION
    }

    // Draw the actual menu
    switch(game.menupage)
    {
    case 0:
        if (map.finalmode || (map.custommode&&!map.customshowmm))
        {
            //draw the map image
            graphics.drawpixeltextbox(35, 16, 250, 190, 32,24, 65, 185, 207,4,0);
            //graphics.drawimage(1, 40, 21, false);
            for (int j = 0; j < 20; j++)
            {
                for (int i = 0; i < 20; i++)
                {
                    //graphics.drawimage(2, 40 + (i * 12), 21 + (j * 9), false);
                }
            }
            graphics.Print(-1, 105, "NO SIGNAL", 245, 245, 245, true);
        }
        else if(map.custommode)
        {
          //draw the map image
          graphics.drawcustompixeltextbox(35+map.custommmxoff, 16+map.custommmyoff, map.custommmxsize+10, map.custommmysize+10, (map.custommmxsize+10)/8, (map.custommmysize+10)/8, 65, 185, 207,4,0);
          graphics.drawpartimage(12, 40+map.custommmxoff, 21+map.custommmyoff, map.custommmxsize,map.custommmysize);

          //Black out here
          if(map.customzoom==4){
            for (int j = 0; j < map.customheight; j++){
              for (int i = 0; i < map.customwidth; i++){
                if(map.explored[i+(j*20)]==0){
                  //Draw the fog of war on the map
                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + (j * 36), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + (j * 36), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + 9 + (j * 36), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + 9+ (j * 36), false);

                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + (j * 36), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + (j * 36), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+ 21 + 9 + (j * 36), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + 9+ (j * 36), false);

                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + (j * 36)+18, false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + (j * 36)+18, false);
                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 48), map.custommmyoff+21 + 9 + (j * 36)+18, false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 48), map.custommmyoff+21 + 9+ (j * 36)+18, false);

                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + (j * 36)+18, false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + (j * 36)+18, false);
                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 48) + 24, map.custommmyoff+21 + 9 + (j * 36)+18, false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 48) + 24, map.custommmyoff+21 + 9+ (j * 36)+18, false);
                }
              }
            }
          }else if(map.customzoom==2){
            for (int j = 0; j < map.customheight; j++){
              for (int i = 0; i < map.customwidth; i++){
                if(map.explored[i+(j*20)]==0){
                  //Draw the fog of war on the map
                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 24), map.custommmyoff+21 + (j * 18), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 24), map.custommmyoff+21 + (j * 18), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 24), map.custommmyoff+21 + 9 + (j * 18), false);
                  //graphics.drawimage(2, map.custommmxoff+40 + 12 + (i * 24), map.custommmyoff+21 + 9+ (j * 18), false);
                }
              }
            }
          }else{
            for (int j = 0; j < map.customheight; j++){
              for (int i = 0; i < map.customwidth; i++){
                if(map.explored[i+(j*20)]==0){
                  //Draw the fog of war on the map
                  //graphics.drawimage(2, map.custommmxoff+40 + (i * 12), map.custommmyoff+21 + (j * 9), false);
                }
              }
            }
          }

          //normal size maps
          if(map.customzoom==4){
            if(map.cursorstate==1){
              if (int(map.cursordelay / 4) % 2 == 0){
                graphics.drawrect(40 + ((game.roomx - 100) * 48) +map.custommmxoff, 21 + ((game.roomy - 100) * 36)+map.custommmyoff , 48 , 36 , 255,255,255);
                graphics.drawrect(40 + ((game.roomx - 100) * 48) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 36) + 2+map.custommmyoff, 48 - 4, 36 - 4, 255,255,255);
              }
            }else if (map.cursorstate == 2){
              if (int(map.cursordelay / 15) % 2 == 0){
                graphics.drawrect(40 + ((game.roomx - 100) * 48) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 36) + 2+map.custommmyoff, 48 - 4, 36 - 4, 16, 245 - (help.glow), 245 - (help.glow));
              }
            }
          }else if(map.customzoom==2){
            if(map.cursorstate==1){
              if (int(map.cursordelay / 4) % 2 == 0){
                graphics.drawrect(40 + ((game.roomx - 100) * 24)+map.custommmxoff , 21 + ((game.roomy - 100) * 18)+map.custommmyoff , 24 , 18 , 255,255,255);
                graphics.drawrect(40 + ((game.roomx - 100) * 24) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 18) + 2+map.custommmyoff, 24 - 4, 18 - 4, 255,255,255);
              }
            }else if (map.cursorstate == 2){
              if (int(map.cursordelay / 15) % 2 == 0){
                graphics.drawrect(40 + ((game.roomx - 100) * 24) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 18) + 2+map.custommmyoff, 24 - 4, 18 - 4, 16, 245 - (help.glow), 245 - (help.glow));
              }
            }
          }else{
            if(map.cursorstate==1){
              if (int(map.cursordelay / 4) % 2 == 0){
                graphics.drawrect(40 + ((game.roomx - 100) * 12)+map.custommmxoff , 21 + ((game.roomy - 100) * 9)+map.custommmyoff , 12 , 9 , 255,255,255);
                graphics.drawrect(40 + ((game.roomx - 100) * 12) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 9) + 2+map.custommmyoff, 12 - 4, 9 - 4, 255,255,255);
              }
            }else if (map.cursorstate == 2){
              if (int(map.cursordelay / 15) % 2 == 0){
                graphics.drawrect(40 + ((game.roomx - 100) * 12) + 2+map.custommmxoff, 21 + ((game.roomy - 100) * 9) + 2+map.custommmyoff, 12 - 4, 9 - 4, 16, 245 - (help.glow), 245 - (help.glow));
              }
            }
          }

          if(map.showtrinkets){
            for(size_t i=0; i<map.shinytrinkets.size(); i++){
              if(!obj.collect[i]){
                int temp = 1086;
                if(graphics.flipmode) temp += 3;
                if(map.customzoom==4){
                  graphics.drawtile(40 + (map.shinytrinkets[i].x * 48) + 20+map.custommmxoff, 21 + (map.shinytrinkets[i].y * 36) + 14+map.custommmyoff, temp);
                }else if(map.customzoom==2){
                  graphics.drawtile(40 + (map.shinytrinkets[i].x * 24) + 8+map.custommmxoff, 21 + (map.shinytrinkets[i].y * 18) + 5+map.custommmyoff, temp);
                }else{
                  graphics.drawtile(40 + 3 + (map.shinytrinkets[i].x * 12) + map.custommmxoff, 22 + (map.shinytrinkets[i].y * 9) + map.custommmyoff, temp);
                }
              }
            }
          }
        }
        else
        {
            //draw the map image
            graphics.drawpixeltextbox(35, 16, 250, 190, 32,24, 65, 185, 207,4,0);
            //graphics.drawimage(1, 40, 21, false);

            //black out areas we can't see yet
            for (int j = 0; j < 20; j++)
            {
                for (int i = 0; i < 20; i++)
                {
                    if(map.explored[i+(j*20)]==0)
                    {
                        //Draw the fog of war on the map
                        //graphics.drawimage(2, 40 + (i * 12), 21 + (j * 9), false);
                    }
                }
            }
            //draw the coordinates
            if (game.roomx == 109)
            {
                //tower!instead of room y, scale map.ypos
                if (map.cursorstate == 1)
                {
                    if (int(map.cursordelay / 4) % 2 == 0)
                    {
                        graphics.drawrect(40 + ((game.roomx - 100) * 12) , 21 , 12, 180, 255,255,255);
                        graphics.drawrect(40 + ((game.roomx - 100) * 12) + 2 , 21  + 2, 12 - 4, 180 - 4, 255,255,255);
                    }
                    if (map.cursordelay > 30) map.cursorstate = 2;
                }
                else if (map.cursorstate == 2)
                {
                    if (int(map.cursordelay / 15) % 2 == 0)
                    {
                        graphics.drawrect(40 + ((game.roomx - 100) * 12) + 2 , 21  + 2, 12 - 4, 180 - 4,16, 245 - (help.glow), 245 - (help.glow));
                    }
                }
            }
            else
            {
                if (map.cursorstate == 1)
                {
                    if (int(map.cursordelay / 4) % 2 == 0)
                    {
                        graphics.drawrect(40 + ((game.roomx - 100) * 12) , 21 + ((game.roomy - 100) * 9) , 12 , 9 , 255,255,255);
                        graphics.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21 + ((game.roomy - 100) * 9) + 2, 12 - 4, 9 - 4, 255,255,255);
                    }
                }
                else if (map.cursorstate == 2)
                {
                    if (int(map.cursordelay / 15) % 2 == 0)
                    {
                        graphics.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21 + ((game.roomy - 100) * 9) + 2, 12 - 4, 9 - 4, 16, 245 - (help.glow), 245 - (help.glow));
                    }
                }
            }

            //draw legend details
            for (size_t i = 0; i < map.teleporters.size(); i++)
            {
                if (map.showteleporters && map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)] > 0)
                {
                    int temp = 1126 + map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)];
                    if (graphics.flipmode) temp += 3;
                    graphics.drawtile(40 + 3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), temp);
                }
                else if(map.showtargets && map.explored[map.teleporters[i].x+(20*map.teleporters[i].y)]==0)
                {
                    int temp = 1126 + map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)];
                    if (graphics.flipmode) temp += 3;
                    graphics.drawtile(40 + 3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), temp);
                }
            }

            if (map.showtrinkets)
            {
                for (size_t i = 0; i < map.shinytrinkets.size(); i++)
                {
                    if (!obj.collect[i])
                    {
                        int temp = 1086;
                        if (graphics.flipmode) temp += 3;
                        graphics.drawtile(40 + 3 + (map.shinytrinkets[i].x * 12), 22 + (map.shinytrinkets[i].y * 9),	temp);
                    }
                }
            }
        }
        break;
    case 1:
        if (game.insecretlab)
        {
            if (graphics.flipmode)
            {
                graphics.Print(0, 174, "SUPER GRAVITRON HIGHSCORE", 196, 196, 255 - help.glow, true);

                std::string tempstring = help.timestring(game.swnrecords[game.swnroommode]);
                graphics.Print( 240, 124, "Best Time", 196, 196, 255 - help.glow, true);
                graphics.bigrprint( 300, 94, tempstring, 196, 196, 255 - help.glow, true, 2);

                switch(game.swnbestrank)
                {
                case 0:
                    graphics.Print( -1, 40, "Next Trophy at 5 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 1:
                    graphics.Print( -1, 40, "Next Trophy at 10 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 2:
                    graphics.Print( -1, 40, "Next Trophy at 15 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 3:
                    graphics.Print( -1, 40, "Next Trophy at 20 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 4:
                    graphics.Print( -1, 40, "Next Trophy at 30 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 5:
                    graphics.Print( -1, 40, "Next Trophy at 1 minute", 196, 196, 255 - help.glow, true);
                    break;
                case 6:
                    graphics.Print( -1, 40, "All Trophies collected!", 196, 196, 255 - help.glow, true);
                    break;
                }
            }
            else
            {
                graphics.Print(0, 40, "SUPER GRAVITRON HIGHSCORE", 196, 196, 255 - help.glow, true);

                std::string tempstring = help.timestring(game.swnrecords[game.swnroommode]);
                graphics.Print( 240, 90, "Best Time", 196, 196, 255 - help.glow, true);
                graphics.bigrprint( 300, 104, tempstring, 196, 196, 255 - help.glow, true, 2);

                switch(game.swnbestrank)
                {
                case 0:
                    graphics.Print( -1, 174, "Next Trophy at 5 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 1:
                    graphics.Print( -1, 174, "Next Trophy at 10 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 2:
                    graphics.Print( -1, 174, "Next Trophy at 15 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 3:
                    graphics.Print( -1, 174, "Next Trophy at 20 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 4:
                    graphics.Print( -1, 174, "Next Trophy at 30 seconds", 196, 196, 255 - help.glow, true);
                    break;
                case 5:
                    graphics.Print( -1, 174, "Next Trophy at 1 minute", 196, 196, 255 - help.glow, true);
                    break;
                case 6:
                    graphics.Print( -1, 174, "All Trophies collected!", 196, 196, 255 - help.glow, true);
                    break;
                }
            }
        }
        else if (obj.flags[67] && !map.custommode)
        {
            graphics.Print(0, 105, "Press ACTION to warp to the ship.", 196, 196, 255 - help.glow, true);
        }
#if !defined(NO_CUSTOM_LEVELS)
        else if(map.custommode){
            LevelMetaData& meta = ed.ListOfMetaData[game.playcustomlevel];

            graphics.bigprint( -1, FLIP(45), meta.title, 196, 196, 255 - help.glow, true);
            graphics.Print( -1, FLIP(70), "by " + meta.creator, 196, 196, 255 - help.glow, true);
            graphics.Print( -1, FLIP(80), meta.website, 196, 196, 255 - help.glow, true);
            graphics.Print( -1, FLIP(100), meta.Desc1, 196, 196, 255 - help.glow, true);
            graphics.Print( -1, FLIP(110), meta.Desc2, 196, 196, 255 - help.glow, true);
            graphics.Print( -1, FLIP(120), meta.Desc3, 196, 196, 255 - help.glow, true);

            int remaining = ed.numcrewmates() - game.crewmates();

            if(remaining==1){
                graphics.Print(1,FLIP(165), help.number(remaining)+ " crewmate remains", 196, 196, 255 - help.glow, true);
            }else if(remaining>0){
                graphics.Print(1,FLIP(165), help.number(remaining)+ " crewmates remain", 196, 196, 255 - help.glow, true);
            }
        }
#endif
        else
        {
            if (graphics.flipmode)
            {
                for (int i = 0; i < 3; i++)
                {
                    graphics.drawcrewman(16, 32 + (i * 64), 2-i, game.crewstats[2-i]);
                    if (game.crewstats[(2-i)])
                    {
                        graphics.printcrewname(44, 32 + (i * 64)+4+10, 2-i);
                        graphics.printcrewnamestatus(44, 32 + (i * 64)+4, 2-i);
                    }
                    else
                    {
                        graphics.printcrewnamedark(44, 32 + (i * 64)+4+10, 2-i);
                        graphics.Print(44, 32 + (i * 64) + 4, "Missing...", 64,64,64);
                    }

                    graphics.drawcrewman(16+160, 32 + (i * 64), (2-i)+3, game.crewstats[(2-i)+3]);
                    if (game.crewstats[(2-i)+3])
                    {
                        graphics.printcrewname(44+160, 32 + (i * 64)+4+10, (2-i)+3);
                        graphics.printcrewnamestatus(44+160, 32 + (i * 64)+4, (2-i)+3);
                    }
                    else
                    {
                        graphics.printcrewnamedark(44+160, 32 + (i * 64)+4+10, (2-i)+3);
                        graphics.Print(44+160, 32 + (i * 64) + 4, "Missing...", 64,64,64);
                    }
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    graphics.drawcrewman(16, 32 + (i * 64), i, game.crewstats[i]);
                    if (game.crewstats[i])
                    {
                        graphics.printcrewname(44, 32 + (i * 64)+4, i);
                        graphics.printcrewnamestatus(44, 32 + (i * 64)+4+10, i);
                    }
                    else
                    {
                        graphics.printcrewnamedark(44, 32 + (i * 64)+4, i);
                        graphics.Print(44, 32 + (i * 64) + 4 + 10, "Missing...", 64,64,64);
                    }

                    graphics.drawcrewman(16+160, 32 + (i * 64), i+3, game.crewstats[i+3]);
                    if (game.crewstats[i+3])
                    {
                        graphics.printcrewname(44+160, 32 + (i * 64)+4, i+3);
                        graphics.printcrewnamestatus(44+160, 32 + (i * 64)+4+10, i+3);
                    }
                    else
                    {
                        graphics.printcrewnamedark(44+160, 32 + (i * 64)+4, i+3);
                        graphics.Print(44+160, 32 + (i * 64) + 4 + 10, "Missing...", 64,64,64);
                    }
                }
            }
        }
        break;
    case 2:
#if !defined(NO_CUSTOM_LEVELS)
        if(map.custommode)
        {
          if (graphics.flipmode)
          {
              graphics.Print(0, 164, "[Trinkets found]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 152, help.number(game.trinkets()) + " out of " + help.number(ed.numtrinkets()), 96,96,96, true);

              graphics.Print(0, 114, "[Number of Deaths]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 102,help.String(game.deathcounts),  96,96,96, true);

              graphics.Print(0, 64, "[Time Taken]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 52, game.timestring(),  96, 96, 96, true);
          }
          else
          {
              graphics.Print(0, 52, "[Trinkets found]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 64, help.number(game.trinkets()) + " out of "+help.number(ed.numtrinkets()), 96,96,96, true);

              graphics.Print(0, 102, "[Number of Deaths]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 114,help.String(game.deathcounts),  96,96,96, true);

              graphics.Print(0, 152, "[Time Taken]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 164, game.timestring(),  96, 96, 96, true);
          }
        }
        else
#endif
        {
          if (graphics.flipmode)
          {
              graphics.Print(0, 164, "[Trinkets found]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 152, help.number(game.trinkets()) + " out of Twenty", 96,96,96, true);

              graphics.Print(0, 114, "[Number of Deaths]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 102,help.String(game.deathcounts),  96,96,96, true);

              graphics.Print(0, 64, "[Time Taken]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 52, game.timestring(),  96, 96, 96, true);
          }
          else
          {
              graphics.Print(0, 52, "[Trinkets found]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 64, help.number(game.trinkets()) + " out of Twenty", 96,96,96, true);

              graphics.Print(0, 102, "[Number of Deaths]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 114,help.String(game.deathcounts),  96,96,96, true);

              graphics.Print(0, 152, "[Time Taken]", 196, 196, 255 - help.glow, true);
              graphics.Print(0, 164, game.timestring(),  96, 96, 96, true);
          }
        }
        break;
    case 3:
        if (game.inintermission)
        {
            graphics.Print(0, 115, "Cannot Save in Level Replay", 146, 146, 180, true);
        }
        else if (game.nodeathmode)
        {
            graphics.Print(0, 115, "Cannot Save in No Death Mode", 146, 146, 180, true);
        }
        else if (game.intimetrial)
        {
            graphics.Print(0, 115, "Cannot Save in Time Trial", 146, 146, 180, true);
        }
        else if (game.insecretlab)
        {
            graphics.Print(0, 115, "Cannot Save in Secret Lab", 146, 146, 180, true);
        }
        else if (map.custommode)
        {
            if (game.gamesaved)
            {
                graphics.Print(0, 36, "Game saved ok!", 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2), true);

                graphics.drawpixeltextbox(25, 65, 270, 90, 34,12, 65, 185, 207,0,4);

                if (graphics.flipmode)
                {
                    graphics.Print(0, 122, game.customleveltitle, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                    graphics.Print(160 - 84, 78, game.savetime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                    graphics.Print(160 + 40, 78, help.number(game.savetrinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                    graphics.drawsprite(50, 74, 50, graphics.col_clock);
                    graphics.drawsprite(175, 74, 22, graphics.col_trinket);
                }
                else
                {
                    graphics.Print(0, 90, game.customleveltitle, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                    graphics.Print(160 - 84, 132, game.savetime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                    graphics.Print(160 + 40, 132, help.number(game.savetrinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                    graphics.drawsprite(50, 126, 50, graphics.col_clock);
                    graphics.drawsprite(175, 126, 22, graphics.col_trinket);
                }
            }
            else
            {
                graphics.Print(0, 80, "[Press ACTION to save your game]", 255 - (help.glow * 2), 255 - (help.glow * 2), 255 - help.glow, true);
            }
        }
        else
        {
            if (graphics.flipmode)
            {
                graphics.Print(0, 186, "(Note: The game is autosaved", 146, 146, 180, true);
                graphics.Print(0, 174, "at every teleporter.)", 146, 146, 180, true);
            }
            else
            {
                graphics.Print(0, 174, "(Note: The game is autosaved", 146, 146, 180, true);
                graphics.Print(0, 186, "at every teleporter.)", 146, 146, 180, true);
            }

            if (game.gamesaved)
            {
                graphics.Print(0, 36, "Game saved ok!", 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2), true);

                graphics.drawpixeltextbox(25, 65, 270, 90, 34,12, 65, 185, 207,0,4);

                if (graphics.flipmode)
                {
                    graphics.Print(0, 132, game.savearea, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                    for (int i = 0; i < 6; i++)
                    {
                        graphics.drawcrewman(169-(3*42)+(i*42), 98, i, game.crewstats[i], true);
                    }
                    graphics.Print(160 - 84, 78, game.savetime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                    graphics.Print(160 + 40, 78, help.number(game.savetrinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                    graphics.drawsprite(50, 74, 50, graphics.col_clock);
                    graphics.drawsprite(175, 74, 22, graphics.col_trinket);
                }
                else
                {
                    graphics.Print(0, 80, game.savearea, 25, 255 - (help.glow / 2), 255 - (help.glow / 2), true);
                    for (int i = 0; i < 6; i++)
                    {
                        graphics.drawcrewman(169-(3*42)+(i*42), 95, i, game.crewstats[i], true);
                    }
                    graphics.Print(160 - 84, 132, game.savetime, 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));
                    graphics.Print(160 + 40, 132, help.number(game.savetrinkets), 255 - (help.glow / 2), 255 - (help.glow / 2), 255 - (help.glow / 2));

                    graphics.drawsprite(50, 126, 50, graphics.col_clock);
                    graphics.drawsprite(175, 126, 22, graphics.col_trinket);
                }
            }
            else
            {
                graphics.Print(0, 80, "[Press ACTION to save your game]", 255 - (help.glow * 2), 255 - (help.glow * 2), 255 - help.glow, true);

                if (game.quicksummary != "")
                {
                    if (graphics.flipmode)
                    {
                        graphics.Print(0, 110, "Last Save:", 164 - (help.glow / 4), 164 - (help.glow / 4), 164, true);
                        graphics.Print(0, 100, game.quicksummary, 164  - (help.glow / 4), 164 - (help.glow / 4), 164, true);
                    }
                    else
                    {
                        graphics.Print(0, 100, "Last Save:", 164 - (help.glow / 4), 164 - (help.glow / 4), 164, true);
                        graphics.Print(0, 110, game.quicksummary, 164  - (help.glow / 4), 164 - (help.glow / 4), 164, true);
                    }
                }
            }
        }
        break;
    case 10:
        graphics.Print(128, 220, "[ QUIT ]", 196, 196, 255 - help.glow);

        if (graphics.flipmode)
        {
            if (game.inspecial())
            {
                graphics.Print(0, 135, "Return to main menu?", 196, 196, 255 - help.glow, true);
            }
            else
            {
                graphics.Print(0, 142, "Do you want to quit? You will", 196, 196, 255 - help.glow, true);
                graphics.Print(0, 130, "lose any unsaved progress.", 196, 196, 255 - help.glow, true);
            }

            graphics.Print(80-16, 88, "[ NO, KEEP PLAYING ]", 196, 196, 255 - help.glow);
            graphics.Print(80 + 32, 76, "yes, quit to menu",  96, 96, 96);
        }
        else
        {

            if (game.inspecial())
            {
                graphics.Print(0, 80, "Return to main menu?", 196, 196, 255 - help.glow, true);
            }
            else
            {
                graphics.Print(0, 76, "Do you want to quit? You will", 196, 196, 255 - help.glow, true);
                graphics.Print(0, 88, "lose any unsaved progress.", 196, 196, 255 - help.glow, true);
            }

            graphics.Print(80-16, 130, "[ NO, KEEP PLAYING ]", 196, 196, 255 - help.glow);
            graphics.Print(80 + 32, 142, "yes, quit to menu",  96, 96, 96);

        }
        break;
    case 11:
        graphics.Print(128, 220, "[ QUIT ]", 196, 196, 255 - help.glow);

        if (graphics.flipmode)
        {
            if (game.inspecial())
            {
                graphics.Print(0, 135, "Return to main menu?", 196, 196, 255 - help.glow, true);
            }
            else
            {
                graphics.Print(0, 142, "Do you want to quit? You will", 196, 196, 255 - help.glow, true);
                graphics.Print(0, 130, "lose any unsaved progress.", 196, 196, 255 - help.glow, true);
            }

            graphics.Print(80, 88, "no, keep playing", 96,96,96);
            graphics.Print(80+32-16, 76, "[ YES, QUIT TO MENU ]",  196, 196, 255 - help.glow);
        }
        else
        {
            if (game.inspecial())
            {
                graphics.Print(0, 80, "Return to main menu?", 196, 196, 255 - help.glow, true);
            }
            else
            {
                graphics.Print(0, 76, "Do you want to quit? You will", 196, 196, 255 - help.glow, true);
                graphics.Print(0, 88, "lose any unsaved progress.", 196, 196, 255 - help.glow, true);
            }

            graphics.Print(80, 130, "no, keep playing", 96,96,96);
            graphics.Print(80+32-16, 142, "[ YES, QUIT TO MENU ]", 196, 196, 255 - help.glow);
        }
        break;
    case 20:
        graphics.Print(128, 220, "[ GRAVITRON ]", 196, 196, 255 - help.glow, true);

        if (graphics.flipmode)
        {
            graphics.Print(0, 76, "the secret laboratory?", 196, 196, 255 - help.glow, true);
            graphics.Print(0, 88, "Do you want to return to", 196, 196, 255 - help.glow, true);
            graphics.Print(80-16, 142, "[ NO, KEEP PLAYING ]", 196, 196, 255 - help.glow);
            graphics.Print(80 + 32, 130, "yes, return",  96, 96, 96);
        }
        else
        {
            graphics.Print(0, 76, "Do you want to return to", 196, 196, 255 - help.glow, true);
            graphics.Print(0, 88, "the secret laboratory?", 196, 196, 255 - help.glow, true);
            graphics.Print(80-16, 130, "[ NO, KEEP PLAYING ]", 196, 196, 255 - help.glow);
            graphics.Print(80 + 32, 142, "yes, return",  96, 96, 96);
        }

        break;
    case 21:
        graphics.Print(128, 220, "[ GRAVITRON ]", 196, 196, 255 - help.glow, true);

        if (graphics.flipmode)
        {
            graphics.Print(0, 76, "the secret laboratory?", 196, 196, 255 - help.glow, true);
            graphics.Print(0, 88, "Do you want to return to", 196, 196, 255 - help.glow, true);
            graphics.Print(80, 142, "no, keep playing", 96, 96, 96);
            graphics.Print(80 + 32-16, 130, "[ YES, RETURN ]",  196, 196, 255 - help.glow);
        }
        else
        {
            graphics.Print(0, 76, "Do you want to return to", 196, 196, 255 - help.glow, true);
            graphics.Print(0, 88, "the secret laboratory?", 196, 196, 255 - help.glow, true);
            graphics.Print(80, 130, "no, keep playing", 96, 96, 96);
            graphics.Print(80 + 32-16, 142, "[ YES, RETURN ]",  196, 196, 255 - help.glow);
        }

    }




    // We need to draw the black screen above the menu in order to disguise it
    // being jankily brought down in glitchrunner mode when exiting to the title
    // Otherwise, there's no reason to obscure the menu
    if (game.glitchrunnermode || graphics.fademode == 3 || graphics.fademode == 5)
    {
        graphics.drawfade();
    }

    if (graphics.resumegamemode || graphics.menuoffset > 0 || graphics.oldmenuoffset > 0)
    {
        graphics.menuoffrender();
    }
    else
    {
        graphics.renderwithscreeneffects();
    }
}

void teleporterrender()
{
    FillRect(graphics.backBuffer, 0x000000);
    int tempx;
    int tempy;
    //draw screen alliteration
    //Roomname:
    int temp = map.area(game.roomx, game.roomy);
    if (temp < 2 && !map.custommode && graphics.fademode==0)
    {
        graphics.Print(5, 2, map.hiddenname, 196, 196, 255 - help.glow, true);
    }
    else
    {
        graphics.Print(5, 2, map.roomname, 196, 196, 255 - help.glow, true);
    }

    //Background color
    FillRect(graphics.backBuffer, 0, 12, 320, 240, 10, 24, 26);

    //draw the map image
    graphics.drawpixeltextbox(35, 16, 250, 190, 32,24, 65, 185, 207,4,0);
    //graphics.drawimage(1, 40, 21, false);
    //black out areas we can't see yet
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            if(map.explored[i+(j*20)]==0)
            {
                //graphics.drawfillrect(10 + (i * 12), 21 + (j * 9), 12, 9, 16, 16, 16);
                //graphics.drawimage(2, 40 + (i * 12), 21 + (j * 9), false);
            }
        }
    }

    //draw the coordinates //current
    if (game.roomx == 109)
    {
        //tower!instead of room y, scale map.ypos
        graphics.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21  + 2, 12 - 4, 180 - 4, 16, 245 - (help.glow * 2), 245 - (help.glow * 2));
    }
    else
    {
        graphics.drawrect(40 + ((game.roomx - 100) * 12) + 2, 21 + ((game.roomy - 100) * 9) + 2, 12 - 4, 9 - 4, 16, 245 - (help.glow * 2), 245 - (help.glow * 2));
    }

    if (game.useteleporter)
    {
        //Draw the chosen destination coordinate!
        //TODO
        //draw the coordinates //destination
        int tempx = map.teleporters[game.teleport_to_teleporter].x;
        int tempy = map.teleporters[game.teleport_to_teleporter].y;
        graphics.drawrect(40 + (tempx * 12) + 1, 21 + (tempy * 9) + 1, 12 - 2, 9 - 2, 245 - (help.glow * 2), 16, 16);
        graphics.drawrect(40 + (tempx * 12) + 3, 21 + (tempy * 9) + 3, 12 - 6, 9 - 6, 245 - (help.glow * 2), 16, 16);
    }

    //draw legend details
    for (size_t i = 0; i < map.teleporters.size(); i++)
    {
        if (map.showteleporters && map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)] > 0)
        {
            temp = 1126 + map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)];
            if (graphics.flipmode) temp += 3;
            graphics.drawtile(40 + 3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), temp);
        }
        else if(map.showtargets && map.explored[map.teleporters[i].x+(20*map.teleporters[i].y)]==0)
        {
            temp = 1126 + map.explored[map.teleporters[i].x + (20 * map.teleporters[i].y)];
            if (graphics.flipmode) temp += 3;
            graphics.drawtile(40 + 3 + (map.teleporters[i].x * 12), 22 + (map.teleporters[i].y * 9), temp);
        }
    }

    if (map.showtrinkets)
    {
        for (size_t i = 0; i < map.shinytrinkets.size(); i++)
        {
            if (!obj.collect[i])
            {
                temp = 1086;
                if (graphics.flipmode) temp += 3;
                graphics.drawtile(40 + 3 + (map.shinytrinkets[i].x * 12), 22 + (map.shinytrinkets[i].y * 9),	temp);
            }
        }
    }

    tempx = map.teleporters[game.teleport_to_teleporter].x;
    tempy = map.teleporters[game.teleport_to_teleporter].y;
    if (game.useteleporter && ((help.slowsine%16)>8))
    {
        //colour in the legend
        temp = 1128;
        if (graphics.flipmode) temp += 3;
        graphics.drawtile(40 + 3 + (tempx * 12), 22 + (tempy * 9), temp);
    }

    graphics.cutscenebars();


    if (game.useteleporter)
    {
        //Instructions!
        graphics.Print(5, 210, "Press Left/Right to choose a Teleporter", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
        graphics.Print(5, 225, "Press ENTER to Teleport", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }

    graphics.drawgui();

    if (graphics.flipmode)
    {
        if (game.advancetext) graphics.bprint(5, 228, "- Press ACTION to advance text -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }
    else
    {
        if (game.advancetext) graphics.bprint(5, 5, "- Press ACTION to advance text -", 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2), true);
    }


    if (graphics.resumegamemode || graphics.menuoffset > 0 || graphics.oldmenuoffset > 0)
    {
        graphics.menuoffrender();
    }
    else
    {
        graphics.render();
    }
}
