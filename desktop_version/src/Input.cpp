#include <tinyxml2.h>

#include "Credits.h"
#include "editor.h"
#include "Entity.h"
#include "Enums.h"
#include "FileSystemUtils.h"
#include "Game.h"
#include "Graphics.h"
#include "KeyPoll.h"
#include "Logic.h"
#include "MakeAndPlay.h"
#include "Map.h"
#include "Music.h"
#include "Script.h"

void updatebuttonmappings(int bind)
{
    for (
        SDL_GameControllerButton i = SDL_CONTROLLER_BUTTON_A;
        i < SDL_CONTROLLER_BUTTON_DPAD_UP;
        i = (SDL_GameControllerButton) (i + 1)
    ) {
        if (key.isDown(i))
        {
            bool dupe = false;
            if (bind == 1)
            {
                for (size_t j = 0; j < game.controllerButton_flip.size(); j += 1)
                {
                    if (i == game.controllerButton_flip[j])
                    {
                        dupe = true;
                    }
                }
                if (!dupe)
                {
                    game.controllerButton_flip.push_back(i);
                    music.playef(11);
                }
                for (size_t j = 0; j < game.controllerButton_map.size(); j += 1)
                {
                    if (i == game.controllerButton_map[j])
                    {
                        game.controllerButton_map.erase(game.controllerButton_map.begin() + j);
                    }
                }
                for (size_t j = 0; j < game.controllerButton_esc.size(); j += 1)
                {
                    if (i == game.controllerButton_esc[j])
                    {
                        game.controllerButton_esc.erase(game.controllerButton_esc.begin() + j);
                    }
                }
            }
            if (bind == 2)
            {
                for (size_t j = 0; j < game.controllerButton_map.size(); j += 1)
                {
                    if (i == game.controllerButton_map[j])
                    {
                        dupe = true;
                    }
                }
                if (!dupe)
                {
                    game.controllerButton_map.push_back(i);
                    music.playef(11);
                }
                for (size_t j = 0; j < game.controllerButton_flip.size(); j += 1)
                {
                    if (i == game.controllerButton_flip[j])
                    {
                        game.controllerButton_flip.erase(game.controllerButton_flip.begin() + j);
                    }
                }
                for (size_t j = 0; j < game.controllerButton_esc.size(); j += 1)
                {
                    if (i == game.controllerButton_esc[j])
                    {
                        game.controllerButton_esc.erase(game.controllerButton_esc.begin() + j);
                    }
                }
            }
            if (bind == 3)
            {
                for (size_t j = 0; j < game.controllerButton_esc.size(); j += 1)
                {
                    if (i == game.controllerButton_esc[j])
                    {
                        dupe = true;
                    }
                }
                if (!dupe)
                {
                    game.controllerButton_esc.push_back(i);
                    music.playef(11);
                }
                for (size_t j = 0; j < game.controllerButton_flip.size(); j += 1)
                {
                    if (i == game.controllerButton_flip[j])
                    {
                        game.controllerButton_flip.erase(game.controllerButton_flip.begin() + j);
                    }
                }
                for (size_t j = 0; j < game.controllerButton_map.size(); j += 1)
                {
                    if (i == game.controllerButton_map[j])
                    {
                        game.controllerButton_map.erase(game.controllerButton_map.begin() + j);
                    }
                }
            }
        }
    }
}

void menuactionpress()
{
    switch (game.currentmenuname)
    {
    case Menu::mainmenu:
        switch (game.currentmenuoption)
        {
        case 0:
            //Play
            {
                bool unlocked = false;
                // MODE COUNT = 3. search for "MODE COUNT" in files
                for (int i = 0; i < 3; i++) {
                    if (game.swnmodesunlocked[i]) { // If something's unlocked...
                        unlocked = true; // Set unlocked to true and stop the loop.
                        break;
                    }
                }
                music.playef(11);
                if (unlocked) { // If something is unlocked, go to the mode menu.
                    game.createmenu(Menu::playmodes);
                    map.nexttowercolour();
                } else { // If nothing's unlocked, just start the game.
                    game.swnroommode = 0;
                    game.mainmenu = 11;
                    graphics.fademode = 2;
                }
            }
            break;
        case 1:
            //About VVVVVV
            music.playef(11);
            game.createmenu(Menu::about1);
            //game.createmenu(Menu::credits);
            map.settowercolour(0);
            //map.nexttowercolour();
            break;
        case 2:
            //Options
            music.playef(11);
            game.createmenu(Menu::graphicoptions);
            map.nexttowercolour();
            break;
        case 3:
            //Options
            music.playef(11);
            game.createmenu(Menu::options);
            map.nexttowercolour();
            break;
        case 4:
            //bye!
            music.playef(2);
            game.mainmenu = 100;
            graphics.fademode = 2;
            break;
        }
        break;
    case Menu::playmodes:
        if (game.currentmenuoption == (int)game.menuoptions.size() - 1) {
            game.returnmenu();
            map.nexttowercolour();
        } else {
            if (game.currentmenuoption == 0) {
                game.swnroommode = 0;
                game.mainmenu = 11;
                graphics.fademode = 2;
            }
            else if (game.swnmodesunlocked[game.currentmenuoption - 1]) {
                game.swnroommode = game.currentmenuoption;
                game.mainmenu = 11;
                graphics.fademode = 2;
            } else {
                music.playef(2);
            }
        }
        break;
    case Menu::about1:
        if (game.currentmenuoption == 0) {
            music.playef(11);
            game.createmenu(Menu::about2);
            map.settowercolour(5);
            //map.nexttowercolour();
        } else {
            music.playef(11);
            game.createmenu(Menu::mainmenu);
            map.nexttowercolour();
        }
        break;
    case Menu::about2:
        if (game.currentmenuoption == 0) {
            music.playef(11);
            game.createmenu(Menu::about3);
            map.settowercolour(3);
            //map.nexttowercolour();
        } else {
            music.playef(11);
            game.createmenu(Menu::mainmenu);
            map.nexttowercolour();
        }
        break;
    case Menu::about3:
        if (game.currentmenuoption == 0) {
            music.playef(11);
            game.createmenu(Menu::about4);
            map.settowercolour(1);
            //map.nexttowercolour();
        } else {
            music.playef(11);
            game.createmenu(Menu::mainmenu);
            map.nexttowercolour();
        }
        break;
    case Menu::about4:
        if (game.currentmenuoption == 0) {
            music.playef(11);
            game.createmenu(Menu::about5);
            map.settowercolour(2);
            //map.nexttowercolour();
        } else {
            music.playef(11);
            game.createmenu(Menu::mainmenu);
            map.nexttowercolour();
        }
        break;
    case Menu::about5:
        if (game.currentmenuoption == 0) {
            music.playef(11);
            game.createmenu(Menu::about6);
            map.settowercolour(3);
            //map.nexttowercolour();
        } else {
            music.playef(11);
            game.createmenu(Menu::mainmenu);
            map.nexttowercolour();
        }
        break;
    case Menu::about6:
        music.playef(11);
        game.createmenu(Menu::mainmenu);
        map.nexttowercolour();
        break;
    case Menu::graphicoptions:
        switch (game.currentmenuoption)
        {
        case 0:
            music.playef(11);
            graphics.screenbuffer->toggleFullScreen();
            game.fullscreen = !game.fullscreen;
            game.savestats();

            // Recreate menu to update "resize to nearest"
            game.createmenu(game.currentmenuname, true);
            game.currentmenuoption = 0;
            break;
        case 1:
            music.playef(11);
            graphics.screenbuffer->toggleStretchMode();
            game.stretchMode = (game.stretchMode + 1) % 3;
            game.savestats();
            break;
        case 2:
            // resize to nearest multiple
            if (graphics.screenbuffer->isWindowed)
            {
                music.playef(11);
                graphics.screenbuffer->ResizeToNearestMultiple();
                game.savestats();
            }
            else
            {
                music.playef(2);
            }
            break;
        case 3:
            music.playef(11);
            graphics.screenbuffer->toggleLinearFilter();
            game.useLinearFilter = !game.useLinearFilter;
            game.savestats();
            break;
        case 4:
            //change smoothing
            music.playef(11);
            game.fullScreenEffect_badSignal = !game.fullScreenEffect_badSignal;
            graphics.screenbuffer->badSignalEffect= !graphics.screenbuffer->badSignalEffect;
            game.savestats();
            break;
        case 5:
            //toggle 30+ fps
            music.playef(11);
            game.over30mode = !game.over30mode;
            game.savestats();
            break;
        case 6:
            //toggle vsync
            music.playef(11);
#ifndef __HAIKU__ // FIXME: Remove after SDL VSync bug is fixed! -flibit
            graphics.screenbuffer->vsync = !graphics.screenbuffer->vsync;
            graphics.screenbuffer->resetRendererWorkaround();
            game.savestats();
#endif
            break;
        default:
            //back
            music.playef(11);
            if (game.ingame_titlemode)
            {
                game.returntopausemenu();
            }
            else
            {
                game.returnmenu();
                map.nexttowercolour();
            }
            break;
        }
        break;
    case Menu::youwannaquit:
        switch (game.currentmenuoption)
        {
        case 0:
            //bye!
            music.playef(2);
            game.mainmenu = 100;
            graphics.fademode = 2;
            break;
        default:
            music.playef(11);
            map.nexttowercolour(); //This goes first, otherwise mismatching continuemenu color is possible
            game.returnmenu();
        }
        break;
    case Menu::advancedoptions:
        switch (game.currentmenuoption)
        {
        case 0:
            //toggle mouse cursor
            music.playef(11);
            if (graphics.showmousecursor == true) {
                SDL_ShowCursor(SDL_DISABLE);
                graphics.showmousecursor = false;
            }
            else {
                SDL_ShowCursor(SDL_ENABLE);
                graphics.showmousecursor = true;
            }
            break;
        case 1:
            // toggle unfocus pause
            game.disablepause = !game.disablepause;
            music.playef(11);
            break;
        case 2:
            //back
            music.playef(11);
            game.returnmenu();
            map.nexttowercolour();
            break;
        }
        break;
    case Menu::accessibility:
        switch (game.currentmenuoption)
        {
        case 0:
            //disable animated backgrounds
            game.colourblindmode = !game.colourblindmode;
            game.savestats();
            map.tdrawback = true;
            music.playef(11);
            break;
        case 1:
            //disable screeneffects
            game.noflashingmode = !game.noflashingmode;
            game.savestats();
            if (!game.noflashingmode)
            {
                music.playef(18);
                game.screenshake = 10;
                game.flashlight = 5;
            }else{
                music.playef(11);
            }
            break;
        case 2:
            //back
            music.playef(11);
            game.returnmenu();
            map.nexttowercolour();
            break;
        default:
            //Can't do yet! play sad sound
            music.playef(2);
            break;
        }
        break;
    case Menu::options:
    {
        switch (game.currentmenuoption)
        {
        case 0:
            //accessibility options
            music.playef(11);
            game.createmenu(Menu::accessibility);
            map.nexttowercolour();
            break;
        case 1:
            //advanced options
            music.playef(11);
            game.createmenu(Menu::advancedoptions);
            map.nexttowercolour();
            break;
        case 2:
            //gamepad menu
            music.playef(11);
            game.createmenu(Menu::controller);
            map.nexttowercolour();
            break;
        case 3:
            //clear data menu
            music.playef(11);
            game.createmenu(Menu::cleardatamenu);
            map.nexttowercolour();
            break;
        case 4:
            music.playef(11);
            if (game.ingame_titlemode)
            {
                game.returntopausemenu();
            } else {
                game.returnmenu();
                map.nexttowercolour();
            }
            break;
        }
        break;
    }
    case Menu::play:
    {
        music.playef(11);
        game.mainmenu = 0;
        graphics.fademode = 2;
        break;
    }
    /*case Menu::newgamewarning:
        switch (game.currentmenuoption)
        {
        case 0:
            //yep
            music.playef(11);
            game.mainmenu = 0;
            graphics.fademode = 2;
            game.deletequick();
            game.deletetele();
            break;
        default:
            //back
            music.playef(11);
            game.returnmenu();
            map.nexttowercolour();
            break;
        }
        break;*/

    case Menu::controller:
        switch (game.currentmenuoption)
        {
        case 0:
            game.controllerSensitivity++;
            music.playef(11);
            if(game.controllerSensitivity > 4)
            {
                game.controllerSensitivity = 0;
            }
            break;

        case 4:
            music.playef(11);
            game.returnmenu();
            break;
        }
        break;
    case Menu::cleardatamenu:
        switch (game.currentmenuoption)
        {
        case 0:
            //back
            music.playef(11);
            game.returnmenu();
            map.nexttowercolour();
            break;
        default:
            //yep
            music.playef(23);
            game.deletequick();
            game.deletetele();
            game.deletestats();
            game.flashlight = 5;
            game.screenshake = 15;
            game.createmenu(Menu::mainmenu);
            map.nexttowercolour();
            break;
        }
        break;
    default:
        break;
    }
}

void titleinput()
{
    //game.mx = (mouseX / 4);
    //game.my = (mouseY / 4);

    //TODO bit wasteful doing this every poll
    key.setSensitivity(game.controllerSensitivity);

    game.press_left = false;
    game.press_right = false;
    game.press_action = false;
    game.press_map = false;

    if (graphics.flipmode)
    {
        if (key.isDown(KEYBOARD_LEFT) || key.isDown(KEYBOARD_DOWN) || key.isDown(KEYBOARD_a) ||  key.isDown(KEYBOARD_s) || key.controllerWantsRight(true)) game.press_left = true;
        if (key.isDown(KEYBOARD_RIGHT) || key.isDown(KEYBOARD_UP)  || key.isDown(KEYBOARD_d) ||  key.isDown(KEYBOARD_w) || key.controllerWantsLeft(true)) game.press_right = true;
    }
    else
    {
        if (key.isDown(KEYBOARD_LEFT) || key.isDown(KEYBOARD_UP) || key.isDown(KEYBOARD_a) ||  key.isDown(KEYBOARD_w) || key.controllerWantsLeft(true))
        {
            game.press_left = true;
        }
        if (key.isDown(KEYBOARD_RIGHT) || key.isDown(KEYBOARD_DOWN)  || key.isDown(KEYBOARD_d) ||  key.isDown(KEYBOARD_s) || key.controllerWantsRight(true))
        {
            game.press_right = true;
        }
    }
    if (key.isDown(KEYBOARD_z) || key.isDown(KEYBOARD_SPACE) || key.isDown(KEYBOARD_v) || key.isDown(game.controllerButton_flip)) game.press_action = true;
    //|| key.isDown(KEYBOARD_UP) || key.isDown(KEYBOARD_DOWN)) game.press_action = true; //on menus, up and down don't work as action
    if (key.isDown(KEYBOARD_ENTER)) game.press_map = true;

    //In the menu system, all keypresses are single taps rather than holds. Therefore this test has to be done for all presses
    if (!game.press_action && !game.press_left && !game.press_right) game.jumpheld = false;
    if (!game.press_map) game.mapheld = false;

    if (!game.jumpheld && graphics.fademode==0)
    {
        if (game.press_action || game.press_left || game.press_right || game.press_map)
        {
            game.jumpheld = true;
        }

        if (key.isDown(27) && game.currentmenuname != Menu::youwannaquit && game.menustart)
        {
            music.playef(11);
            if (game.ingame_titlemode)
            {
                game.returntopausemenu();
            }
            else
            {
                game.createmenu(Menu::youwannaquit);
                map.nexttowercolour();
            }
        }

        if(game.menustart)
        {
            if (game.press_left)
            {
                game.currentmenuoption--;
            }
            else if (game.press_right)
            {
                game.currentmenuoption++;
            }
        }

        if (game.currentmenuoption < 0) game.currentmenuoption = game.menuoptions.size()-1;
        if (game.currentmenuoption >= (int) game.menuoptions.size() ) game.currentmenuoption = 0;

        if (game.press_action)
        {
            if (!game.menustart)
            {
                game.menustart = true;
                music.play(6);
                music.playef(18);
                game.screenshake = 10;
                game.flashlight = 5;
                map.colstate = 10;
                map.nexttowercolour();
            }
            else
            {
                menuactionpress();
            }
        }
        if (    game.currentmenuname == Menu::controller &&
                game.currentmenuoption > 0 &&
                game.currentmenuoption < 4 &&
                key.controllerButtonDown()      )
        {
            updatebuttonmappings(game.currentmenuoption);
        }

    }

    if (graphics.fademode == 1)
        script.startgamemode(game.mainmenu);
}

void gameinput()
{
    //TODO mouse input
    //game.mx = (mouseX / 2);
    //game.my = (mouseY / 2);

    if(!script.running)
    {
        game.press_left = false;
        game.press_right = false;
        game.press_action = false;
        game.press_map = false;

        if (key.isDown(KEYBOARD_LEFT) || key.isDown(KEYBOARD_a) || key.controllerWantsLeft(false))
        {
            game.press_left = true;
        }
        if (key.isDown(KEYBOARD_RIGHT) || key.isDown(KEYBOARD_d) || key.controllerWantsRight(false))
        {
            game.press_right = true;
        }
        if (key.isDown(KEYBOARD_z) || key.isDown(KEYBOARD_SPACE) || key.isDown(KEYBOARD_v)
                || key.isDown(KEYBOARD_UP) || key.isDown(KEYBOARD_DOWN) || key.isDown(KEYBOARD_w) || key.isDown(KEYBOARD_s)|| key.isDown(game.controllerButton_flip))
        {
            game.press_action = true;
        };
        if (key.isDown(KEYBOARD_ENTER) || key.isDown(SDLK_KP_ENTER) || key.isDown(game.controllerButton_map)  )
        {
            game.press_map = true;
        }
    }

    if (game.advancetext)
    {
        if (game.pausescript)
        {
            game.press_action = false;
            if (key.isDown(KEYBOARD_z) || key.isDown(KEYBOARD_SPACE) || key.isDown(KEYBOARD_v)
                    || key.isDown(KEYBOARD_UP) || key.isDown(KEYBOARD_DOWN) || key.isDown(KEYBOARD_w) || key.isDown(KEYBOARD_s) || key.isDown(game.controllerButton_flip)) game.press_action = true;
        }

        if (game.press_action && !game.jumpheld)
        {
            if (game.pausescript)
            {
                game.pausescript = false;
                game.hascontrol = true;
                game.jumpheld = true;
            }
            else
            {
                if(game.glitchrunnermode || !game.glitchrunkludge) game.state++;
                    game.jumpheld = true;
                    game.glitchrunkludge=true;
                    //Bug fix! You should only be able to do this ONCE.
                    //...Unless you're in glitchrunner mode
            }
        }
    }

    if (!game.press_map) game.mapheld = false;

    if (game.intimetrial && graphics.fademode == 1 && game.quickrestartkludge)
    {
        //restart the time trial
        game.quickrestartkludge = false;
        script.startgamemode(game.timetriallevel + 3);
        game.deathseq = -1;
        game.completestop = false;
    }

    //Returning to editor mode must always be possible
#if !defined(NO_CUSTOM_LEVELS)
    if(map.custommode && !map.custommodeforreal){
        if ((game.press_map || key.isDown(27)) && !game.mapheld){
            //Return to level editor
            if (game.activeactivity > -1 && game.press_map){
                //pass, let code block below handle it
            }else if(game.activetele && game.readytotele > 20 && game.press_map){
                //pass, let code block below handle it
            }else{
                game.shouldreturntoeditor = true;
                game.mapheld = true;
            }
        }
    }
#endif

    //Entity type 0 is player controled
    for (size_t ie = 0; ie < obj.entities.size(); ++ie)
    {
        if (obj.entities[ie].rule == 0)
        {
            if (game.hascontrol && game.deathseq == -1 && game.lifeseq <= 5)
            {
                if (game.press_map && !game.mapheld)
                {
                    game.mapheld = true;

                    if (game.activetele && game.readytotele > 20 && !game.intimetrial)
                    {
                        if(int(std::abs(obj.entities[ie].vx))<=1 && int(obj.entities[ie].vy)==0)
                        {
                            //wait! space station 2 debug thingy
                            if (game.teleportscript != "")
                            {

                                //trace(game.recordstring);
                                //We're teleporting! Yey!
                                game.activetele = false;
                                game.hascontrol = false;
                                music.fadeout();

                                int player = obj.getplayer();
                                if (player > -1)
                                {
                                    obj.entities[player].colour = 102;
                                }

                                int teleporter = obj.getteleporter();
                                if (teleporter > -1)
                                {
                                    obj.entities[teleporter].tile = 6;
                                    obj.entities[teleporter].colour = 102;
                                }
                                //which teleporter script do we use? it depends on the companion!
                                game.state = 4000;
                                game.statedelay = 0;
                            }
                            else if (game.companion == 0)
                            {
                                //Alright, normal teleporting
                                game.gamestate = TELEPORTERMODE;
                                graphics.menuoffset = 240; //actually this should count the roomname
                                graphics.oldmenuoffset = 240;
                                if (map.extrarow)
                                {
                                    graphics.menuoffset -= 10;
                                    graphics.oldmenuoffset -= 10;
                                }

                                BlitSurfaceStandard(graphics.menubuffer,NULL,graphics.backBuffer, NULL);

                                graphics.resumegamemode = false;

                                game.useteleporter = true;
                                game.initteleportermode();
                            }
                            else
                            {
                                //We're teleporting! Yey!
                                game.activetele = false;
                                game.hascontrol = false;
                                music.fadeout();

                                int player = obj.getplayer();
                                if (player > -1)
                                {
                                    obj.entities[player].colour = 102;
                                }
                                int companion = obj.getcompanion();
                                if(companion>-1) obj.entities[companion].colour = 102;

                                int teleporter = obj.getteleporter();
                                if (teleporter > -1)
                                {
                                    obj.entities[teleporter].tile = 6;
                                    obj.entities[teleporter].colour = 102;
                                }
                                //which teleporter script do we use? it depends on the companion!
                                game.state = 3000;
                                game.statedelay = 0;
                            }
                        }
                    }
                    else if (game.activeactivity > -1)
                    {
                        if((int(std::abs(obj.entities[ie].vx))<=1) && (int(obj.entities[ie].vy) == 0) )
                        {
                            script.load(obj.blocks[game.activeactivity].script);
                            obj.removeblock(game.activeactivity);
                            game.activeactivity = -1;
                        }
                    }
                    else //if (game.swnmode == 1 && game.swngame == 1)
                    {
                        //quitting the super gravitron
                        game.mapheld = true;
                        //Quit menu, same conditions as in game menu

                        //game.mainmenu = 101;
                        if (graphics.fademode == 0) {
                            game.swnmode = false;
                            graphics.fademode = 2;
                            music.fadeout();
                            game.fadetolab = true;
                            game.fadetolabdelay = 16;
                            game.state = 80;
                            break;
                        }
        
                        //game.gamestate = MAPMODE;
                        //game.gamesaved = false;
                        //graphics.resumegamemode = false;
                        //game.menupage = 20; // The Map Page
                        //BlitSurfaceStandard(graphics.menubuffer,NULL,graphics.backBuffer, NULL);
                        //graphics.menuoffset = 240; //actually this should count the roomname
                        //graphics.oldmenuoffset = 240;
                        //if (map.extrarow)
                        //{
                        //    graphics.menuoffset -= 10;
                        //    graphics.oldmenuoffset -= 10;
                        //}
                    }
                }

                if ((key.isDown(27) || key.isDown(game.controllerButton_esc)) && (!map.custommode || map.custommodeforreal))
                {
                    game.mapheld = true;
                    //Quit menu, same conditions as in game menu
                    if (graphics.fademode == 0) {
                        game.swnmode = false;
                        graphics.fademode = 2;
                        music.fadeout();
                        game.fadetolab = true;
                        game.fadetolabdelay = 16;
                        game.state = 80;
                    }
                    //game.gamestate = MAPMODE;
                    //game.gamesaved = false;
                    //graphics.resumegamemode = false;
                    //game.menupage = 30; // Pause screen

                    //BlitSurfaceStandard(graphics.menubuffer,NULL,graphics.backBuffer, NULL);
                    //graphics.menuoffset = 240; //actually this should count the roomname
                    //graphics.oldmenuoffset = 240;
                    //if (map.extrarow)
                    //{
                    //    graphics.menuoffset -= 10;
                    //    graphics.oldmenuoffset -= 10;
                    //}
                }

                if (key.keymap[SDLK_r] && game.deathseq<=0)// && map.custommode) //Have fun glitchrunners!
                {
                    game.deathseq = 30;
                }

                if (game.press_left)
                {
                    game.tapleft++;
                }
                else
                {
                    if (game.tapleft <= 4 && game.tapleft > 0)
                    {
                        if (obj.entities[ie].vx < 0.0f)
                        {
                            obj.entities[ie].vx = 0.0f;
                        }
                    }
                    game.tapleft = 0;
                }
                if (game.press_right)
                {
                    game.tapright++;
                }
                else
                {
                    if (game.tapright <= 4 && game.tapright > 0)
                    {
                        if (obj.entities[ie].vx > 0.0f)
                        {
                            obj.entities[ie].vx = 0.0f;
                        }
                    }
                    game.tapright = 0;
                }


                if(game.press_left)
                {
                    obj.entities[ie].ax = -3;
                    obj.entities[ie].dir = 0;
                }
                else if (game.press_right)
                {
                    obj.entities[ie].ax = 3;
                    obj.entities[ie].dir = 1;
                }

                if (!game.press_action)
                {
                    game.jumppressed = 0;
                    game.jumpheld = false;
                }

                if (game.press_action && !game.jumpheld)
                {
                    game.jumppressed = 5;
                    game.jumpheld = true;
                }

                if (game.jumppressed > 0)
                {
                    game.jumppressed--;
                    if (obj.entities[ie].onground>0 && game.gravitycontrol == 0)
                    {
                        game.gravitycontrol = 1;
                        obj.entities[ie].vy = -4;
                        obj.entities[ie].ay = -3;
                        music.playef(0);
                        game.jumppressed = 0;
                        game.totalflips++;
                    }
                    if (obj.entities[ie].onroof>0 && game.gravitycontrol == 1)
                    {
                        game.gravitycontrol = 0;
                        obj.entities[ie].vy = 4;
                        obj.entities[ie].ay = 3;
                        music.playef(1);
                        game.jumppressed = 0;
                        game.totalflips++;
                    }
                }
            }
            else
            {
                //Simple detection of keypresses outside player control, will probably scrap this (expand on
                //advance text function)
                if (!game.press_action)
                {
                    game.jumppressed = 0;
                    game.jumpheld = false;
                }

                if (game.press_action && !game.jumpheld)
                {
                    game.jumppressed = 5;
                    game.jumpheld = true;
                }
            }
        }
    }
}

void mapmenuactionpress();

void mapinput()
{
    //TODO Mouse Input!
    //game.mx = (mouseX / 2);
    //game.my = (mouseY / 2);

    game.press_left = false;
    game.press_right = false;
    game.press_action = false;
    game.press_map = false;

    if (game.glitchrunnermode && graphics.fademode == 1 && graphics.menuoffset == 0)
    {
        // Deliberate re-addition of the glitchy gamestate-based fadeout!

        // First of all, detecting a black screen means if the glitchy fadeout
        // gets interrupted but you're still on a black screen, opening a menu
        // immediately quits you to the title. This has the side effect that if
        // you accidentally press Esc during a cutscene when it's black, you'll
        // immediately be quit and lose all your progress, but that's fair in
        // glitchrunner mode.
        // Also have to check graphics.menuoffset so this doesn't run every frame

        // Have to close the menu in order to run gamestates. This adds
        // about an extra half second of completely black screen.
        graphics.resumegamemode = true;

        // Technically this was in <=2.2 as well
        obj.removeallblocks();

        if (game.menupage >= 20 && game.menupage <= 21)
        {
            game.state = 96;
            game.statedelay = 0;
        }
        else
        {
            // Produces more glitchiness! Necessary for credits warp to work.
            script.hardreset();

            game.state = 80;
            game.statedelay = 0;
        }
    }

    if (game.fadetomenu && !game.glitchrunnermode)
    {
        if (game.fadetomenudelay > 0)
        {
            game.fadetomenudelay--;
        }
        else
        {
            game.quittomenu();
            game.fadetomenu = false;
        }
    }

    if (game.fadetolab && !game.glitchrunnermode)
    {
        if (game.fadetolabdelay > 0)
        {
            game.fadetolabdelay--;
        }
        else
        {
            game.returntolab();
            game.fadetolab = false;
        }
    }

    if(graphics.menuoffset==0
    && ((!game.glitchrunnermode && game.fadetomenudelay <= 0 && game.fadetolabdelay <= 0)
    || graphics.fademode == 0))
    {
        if (graphics.flipmode)
        {
            if (key.isDown(KEYBOARD_LEFT) || key.isDown(KEYBOARD_DOWN) || key.isDown(KEYBOARD_a) ||  key.isDown(KEYBOARD_s) || key.controllerWantsLeft(false) ) game.press_left = true;
            if (key.isDown(KEYBOARD_RIGHT) || key.isDown(KEYBOARD_UP) || key.isDown(KEYBOARD_d) ||  key.isDown(KEYBOARD_w) || key.controllerWantsRight(false)) game.press_right = true;
        }
        else
        {
            if (key.isDown(KEYBOARD_LEFT) || key.isDown(KEYBOARD_UP) || key.isDown(KEYBOARD_a) ||  key.isDown(KEYBOARD_w)|| key.controllerWantsLeft(false))
            {
                game.press_left = true;
            }
            if (key.isDown(KEYBOARD_RIGHT) || key.isDown(KEYBOARD_DOWN) || key.isDown(KEYBOARD_d) ||  key.isDown(KEYBOARD_s)|| key.controllerWantsRight(false))
            {
                game.press_right = true;
            }
        }
        if (key.isDown(KEYBOARD_z) || key.isDown(KEYBOARD_SPACE) || key.isDown(KEYBOARD_v) || key.isDown(game.controllerButton_flip))
        {
            game.press_action = true;
        }
        if (game.menupage < 12 || (game.menupage >= 30 && game.menupage <= 33))
        {
            if (key.isDown(KEYBOARD_ENTER) || key.isDown(game.controllerButton_map) ) game.press_map = true;
            if (key.isDown(27) && !game.mapheld)
            {
                game.mapheld = true;
                if (game.menupage < 9)
                {
                    game.menupage = 30;
                }
                else if (game.menupage < 12)
                {
                    game.menupage = 31;
                }
                else
                {
                    graphics.resumegamemode = true;
                }
            }
        }
        else
        {
            if (key.isDown(KEYBOARD_ENTER) || key.isDown(27)|| key.isDown(game.controllerButton_map) ) game.press_map = true;
        }

        //In the menu system, all keypresses are single taps rather than holds. Therefore this test has to be done for all presses
        if (!game.press_action && !game.press_left && !game.press_right)
        {
            game.jumpheld = false;
        }
        if (!game.press_map && !key.isDown(27))
        {
            game.mapheld = false;
        }
    }
    else
    {
        game.mapheld = true;
        game.jumpheld = true;
    }

    if (!game.mapheld)
    {
        if(game.press_map && game.menupage < 10)
        {
            //Normal map screen, do transition later
            graphics.resumegamemode = true;
        }
    }

    if (!game.jumpheld)
    {
        if (game.press_action || game.press_left || game.press_right || game.press_map)
        {
            game.jumpheld = true;
        }

        if (game.press_left)
        {
            game.menupage--;
        }
        else if (game.press_right)
        {
            game.menupage++;
        }

        if (game.press_action)
        {
            mapmenuactionpress();
        }

        if (game.menupage < 0) game.menupage = 3;
        if (game.menupage > 3 && game.menupage < 9) game.menupage = 0;

        if (game.menupage == 9) game.menupage = 11;
        if (game.menupage == 12) game.menupage = 10;

        if (game.menupage == 19) game.menupage = 21;
        if (game.menupage == 22) game.menupage = 20;

        if (game.menupage == 29) game.menupage = 33;
        if (game.menupage == 34) game.menupage = 30;
    }
}

void mapmenuactionpress()
{
    switch (game.menupage)
    {
    case 1:
    if (obj.flags[67] && !game.inspecial() && !map.custommode)
    {
        //Warp back to the ship
        graphics.resumegamemode = true;

        game.teleport_to_x = 2;
        game.teleport_to_y = 11;

        //trace(game.recordstring);
        //We're teleporting! Yey!
        game.activetele = false;
        game.hascontrol = false;

        int i = obj.getplayer();
        if (i > -1)
        {
            obj.entities[i].colour = 102;
        }

        //which teleporter script do we use? it depends on the companion!
        game.state = 4000;
        game.statedelay = 0;
    }
        break;
    case 3:
    if (!game.gamesaved && !game.inspecial())
    {
        game.flashlight = 5;
        game.screenshake = 10;
        music.playef(18);
        game.gamesaved = true;

        game.savetime = game.timestring();
        game.savearea = map.currentarea(map.area(game.roomx, game.roomy));
        game.savetrinkets = game.trinkets();

        if (game.roomx >= 102 && game.roomx <= 104 && game.roomy >= 110 && game.roomy <= 111) game.savearea = "The Ship";

#if !defined(NO_CUSTOM_LEVELS)
        if(map.custommodeforreal)
        {
            game.customsavequick(ed.ListOfMetaData[game.playcustomlevel].filename);
        }
        else
#endif
        {
            game.savequick();
        }
    }
        break;

    case 10:
        //return to pause menu
        music.playef(11);
        game.menupage = 31;
        break;
    case 11:
        //quit to menu

        //Kill contents of offset render buffer, since we do that for some reason.
        //This fixes an apparent frame flicker.
        FillRect(graphics.tempBuffer, 0x000000);
        graphics.fademode = 2;
        music.fadeout();
        map.nexttowercolour();
        if (!game.glitchrunnermode)
        {
            game.fadetomenu = true;
            game.fadetomenudelay = 16;
        }
        break;

    case 20:
        //return to game
        graphics.resumegamemode = true;
        break;
    case 21:
        //quit to menu
        game.swnmode = false;
        graphics.fademode = 2;
        music.fadeout();
        if (!game.glitchrunnermode)
        {
            game.fadetolab = true;
            game.fadetolabdelay = 16;
        }
        break;
    case 30:
        // Return to game
        graphics.resumegamemode = true;
        break;
    case 31:
        // Go to quit prompt
        music.playef(11);
        game.menupage = 10;
        break;
    case 32:
    case 33:
        // Graphic options and game options
        music.playef(11);
        game.gamestate = TITLEMODE;
        graphics.flipmode = false;
        game.ingame_titlemode = true;
        if (game.menupage == 32)
        {
            game.createmenu(Menu::graphicoptions);
        }
        else
        {
            game.createmenu(Menu::options);
        }
        map.bg_to_kludge();
        game.kludge_ingametemp = game.currentmenuname;

        map.scrolldir = 0;
        map.colstate = ((int) (map.colstate / 5)) * 5;
        map.bypos = 0;
        map.nexttowercolour();

        // Fix delta rendering glitch
        graphics.updatetowerbackground();
        titleupdatetextcol();
        break;
    }
}

void teleporterinput()
{
    //Todo Mouseinput!
    //game.mx = (mouseX / 2);
    //game.my = (mouseY / 2);

    int tempx, tempy;

    game.press_left = false;
    game.press_right = false;
    game.press_action = false;
    game.press_map = false;

    if(graphics.menuoffset==0)
    {
        if (key.isDown(KEYBOARD_LEFT)|| key.isDown(KEYBOARD_a) || key.controllerWantsLeft(false) ) game.press_left = true;
        if (key.isDown(KEYBOARD_RIGHT) || key.isDown(KEYBOARD_d)|| key.controllerWantsRight(false) ) game.press_right = true;
        if (key.isDown(KEYBOARD_z) || key.isDown(KEYBOARD_SPACE) || key.isDown(KEYBOARD_v)
                || key.isDown(KEYBOARD_UP) || key.isDown(KEYBOARD_DOWN)||  key.isDown(KEYBOARD_w)||  key.isDown(KEYBOARD_s) || key.isDown(game.controllerButton_flip)) game.press_action = true;
        if (key.isDown(KEYBOARD_ENTER) || key.isDown(game.controllerButton_map)) game.press_map = true;

        //In the menu system, all keypresses are single taps rather than holds. Therefore this test has to be done for all presses
        if (!game.press_action && !game.press_left && !game.press_right) game.jumpheld = false;
        if (!game.press_map) game.mapheld = false;

        if (key.isDown(27))
        {
            if (!map.custommode || map.custommodeforreal)
            {
                // Go to pause menu
                game.mapheld = true;
                game.menupage = 30;
                game.gamestate = MAPMODE;
            }
            else
            {
                // Close teleporter menu
                graphics.resumegamemode = true;
            }
        }
    }
    else
    {
        game.mapheld = true;
        game.jumpheld = true;
    }

    if (!game.jumpheld)
    {
        if (game.press_action || game.press_left || game.press_right || game.press_map)
        {
            game.jumpheld = true;
        }

        bool any_tele_unlocked = false;
        if (game.press_left || game.press_right)
        {
            for (size_t i = 0; i < map.teleporters.size(); i++)
            {
                point& tele = map.teleporters[i];

                if (map.explored[tele.x + tele.y*20])
                {
                    any_tele_unlocked = true;
                    break;
                }
            }
        }

        if (game.press_left && any_tele_unlocked)
        {
            do
            {
                game.teleport_to_teleporter--;
                if (game.teleport_to_teleporter < 0) game.teleport_to_teleporter = map.teleporters.size() - 1;
                tempx = map.teleporters[game.teleport_to_teleporter].x;
                tempy = map.teleporters[game.teleport_to_teleporter].y;
            }
            while (map.explored[tempx + (20 * tempy)] == 0);
        }
        else if (game.press_right && any_tele_unlocked)
        {
            do
            {
                game.teleport_to_teleporter++;
                if (game.teleport_to_teleporter >= (int) map.teleporters.size()) game.teleport_to_teleporter = 0;
                tempx = map.teleporters[game.teleport_to_teleporter].x;
                tempy = map.teleporters[game.teleport_to_teleporter].y;
            }
            while (map.explored[tempx + (20 * tempy)] == 0);
        }

        if (game.press_map)
        {
            tempx = map.teleporters[game.teleport_to_teleporter].x;
            tempy = map.teleporters[game.teleport_to_teleporter].y;
            if (game.roomx == tempx + 100 && game.roomy == tempy + 100)
            {
                //cancel!
                graphics.resumegamemode = true;
            }
            else
            {
                //teleport
                graphics.resumegamemode = true;
                game.teleport_to_x = tempx;
                game.teleport_to_y = tempy;

                //trace(game.recordstring);
                //We're teleporting! Yey!
                game.activetele = false;
                game.hascontrol = false;

                int i = obj.getplayer();
                if (i > -1)
                {
                    obj.entities[i].colour = 102;
                }

                i = obj.getteleporter();
                if (i > -1)
                {
                    obj.entities[i].tile = 6;
                    obj.entities[i].colour = 102;
                }
                //which teleporter script do we use? it depends on the companion!
                game.state = 4000;
                game.statedelay = 0;
            }
        }
    }
}

void gamecompleteinput()
{
    game.press_left = false;
    game.press_right = false;
    game.press_action = false;
    game.press_map = false;

    //Do this before we update map.bypos
    if (!game.colourblindmode)
    {
        graphics.updatetowerbackground();
    }

    //Do these here because input comes first
    map.bypos += map.bscroll;
    game.oldcreditposition = game.creditposition;

    if (key.isDown(KEYBOARD_z) || key.isDown(KEYBOARD_SPACE) || key.isDown(KEYBOARD_v) || key.isDown(game.controllerButton_flip))
    {
        game.creditposition -= 6;
        if (game.creditposition <= -Credits::creditmaxposition)
        {
            if(graphics.fademode==0)
            {
                graphics.fademode = 2;
            }
            game.creditposition = -Credits::creditmaxposition;
        }
        else
        {
            map.bscroll = +7;
        }
        game.press_action = true;
    }
    if (key.isDown(KEYBOARD_ENTER)|| key.isDown(game.controllerButton_map)) game.press_map = true;

    if (!game.mapheld)
    {
        if(game.press_map)
        {
            //Return to game
            if(graphics.fademode==0)
            {
                graphics.fademode = 2;
            }
        }
    }
}

void gamecompleteinput2()
{
    game.press_left = false;
    game.press_right = false;
    game.press_action = false;
    game.press_map = false;

    //Do this here because input comes first
    game.oldcreditposx = game.creditposx;

    if (key.isDown(KEYBOARD_z) || key.isDown(KEYBOARD_SPACE) || key.isDown(KEYBOARD_v) || key.isDown(game.controllerButton_flip))
    {
        game.creditposx++;
        game.oldcreditposx++;
        if (game.creditposy >= 30)
        {
            if(graphics.fademode==0)
            {
                graphics.fademode = 2;
                music.fadeout();
            }
        }
        game.press_action = true;
    }
    if (key.isDown(KEYBOARD_ENTER) || key.isDown(game.controllerButton_map)) game.press_map = true;

    if (!game.mapheld)
    {
        if(game.press_map)
        {
            //Return to game
            if(graphics.fademode==0)
            {
                graphics.fademode = 2;
                music.fadeout();
            }
        }
    }
}
