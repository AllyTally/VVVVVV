#include "LevelDebugger.h"

#include "Constants.h"
#include "Entity.h"
#include "Font.h"
#include "Graphics.h"
#include "KeyPoll.h"
#include "Localization.h"
#include "Map.h"
#include "UtilityClass.h"
#include "VFormat.h"

namespace level_debugger
{
    bool active = false;
    bool should_pause = true;
    bool tab_held = false;
    bool debug_held = false;

    // Moving entities/blocks
    bool mouse_held = false;
    int held_entity = -1;
    int held_block = -1;
    int grabber_offset_x = 0;
    int grabber_offset_y = 0;

    bool is_pausing(void)
    {
        return active && should_pause;
    }

    bool is_active(void)
    {
        return active;
    }

    void toggle_active(void)
    {
        active = !active;
    }

    bool mouse_within(SDL_Rect* rect)
    {
        return key.mx >= rect->x && key.mx < rect->x + rect->w &&
            key.my >= rect->y && key.my < rect->y + rect->h;
    }

    void input(void)
    {
        if (!map.custommode || map.custommodeforreal)
        {
            active = false;
            return;
        }

        if (key.isDown(SDLK_y))
        {
            if (!debug_held)
            {
                debug_held = true;
                active = !active;
            }
        }
        else
        {
            debug_held = false;
        }

        if (!active)
        {
            return;
        }

        if (key.isDown(SDLK_TAB))
        {
            if (!tab_held)
            {
                tab_held = true;
                should_pause = !should_pause;
            }
        }
        else
        {
            tab_held = false;
        }

        for (int i = 0; i < obj.entities.size(); i++)
        {
            SDL_Rect bounding_box = {
                obj.entities[i].xp + obj.entities[i].cx,
                obj.entities[i].yp + obj.entities[i].cy,
                obj.entities[i].w,
                obj.entities[i].h
            };

            if (key.leftbutton)
            {
                if (mouse_within(&bounding_box))
                {
                    if (!mouse_held)
                    {
                        mouse_held = true;
                        held_entity = i;
                        grabber_offset_x = key.mx - obj.entities[i].xp;
                        grabber_offset_y = key.my - obj.entities[i].yp;

                        if (!key.keymap[SDLK_LSHIFT] && !key.keymap[SDLK_RSHIFT])
                        {
                            for (int j = 0; j < obj.blocks.size(); j++)
                            {
                                if (obj.entities[i].xp == obj.blocks[j].rect.x && obj.entities[i].yp == obj.blocks[j].rect.y)
                                {
                                    held_block = j;
                                }
                            }
                        }
                    }
                    break;
                }
            }
            else
            {
                mouse_held = false;
                held_entity = -1;
                held_block = -1;
            }
        }

        if (held_entity == -1)
        {
            for (int i = 0; i < obj.blocks.size(); i++)
            {
                SDL_Rect bounding_box = {
                    obj.blocks[i].rect.x,
                    obj.blocks[i].rect.y,
                    obj.blocks[i].rect.w,
                    obj.blocks[i].rect.h
                };

                if (key.leftbutton)
                {
                    if (mouse_within(&bounding_box))
                    {
                        if (!mouse_held)
                        {
                            mouse_held = true;
                            held_block = i;
                            grabber_offset_x = key.mx - obj.blocks[i].rect.x;
                            grabber_offset_y = key.my - obj.blocks[i].rect.y;
                        }
                        break;
                    }
                }
                else
                {
                    held_entity = -1;
                    mouse_held = false;
                    held_block = -1;
                }
            }
        }

        if (INBOUNDS_VEC(held_entity, obj.entities))
        {
            obj.entities[held_entity].xp = key.mx - grabber_offset_x;
            obj.entities[held_entity].yp = key.my - grabber_offset_y;

            if (key.isDown(SDLK_LSHIFT) || key.isDown(SDLK_RSHIFT))
            {
                obj.entities[held_entity].xp -= obj.entities[held_entity].xp % 8;
                obj.entities[held_entity].yp -= obj.entities[held_entity].yp % 8;
            }
        }

        if (INBOUNDS_VEC(held_block, obj.blocks))
        {
            int new_xp = key.mx - grabber_offset_x;
            int new_yp = key.my - grabber_offset_y;

            if (key.isDown(SDLK_LSHIFT) || key.isDown(SDLK_RSHIFT))
            {
                new_xp -= new_xp % 8;
                new_yp -= new_yp % 8;
            }

            obj.blocks[held_block].xp = new_xp;
            obj.blocks[held_block].yp = new_yp;
            obj.blocks[held_block].rect.x = new_xp;
            obj.blocks[held_block].rect.y = new_yp;
        }
    }

    void render_info(int y, const char* text, const char* value)
    {
        char buffer[SCREEN_WIDTH_CHARS + 1];
        vformat_buf(buffer, sizeof(buffer), text, "value:str", value);
        font::print(PR_BOR | PR_FONT_8X8, 5, 32 + (10 * y), buffer, 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));
    }

    void render(void)
    {
        if (!active)
        {
            return;
        }

        int hovered = -1;
        bool hovered_entity = true;
        SDL_Rect hover_box;

        for (int i = 0; i < obj.entities.size(); i++)
        {
            SDL_Rect bounding_box = {
                obj.entities[i].xp + obj.entities[i].cx,
                obj.entities[i].yp + obj.entities[i].cy,
                obj.entities[i].w,
                obj.entities[i].h
            };

            bool hovering = false;

            if (hovered == -1 && mouse_within(&bounding_box))
            {
                hovering = true;
                hovered = i;
                hovered_entity = true;
                hover_box = bounding_box;
            }

            graphics.draw_rect(bounding_box.x, bounding_box.y, bounding_box.w, bounding_box.h, graphics.getRGB(15, 90, 90));
        }

        for (int i = 0; i < obj.blocks.size(); i++)
        {
            SDL_Rect bounding_box = {
                obj.blocks[i].rect.x,
                obj.blocks[i].rect.y,
                obj.blocks[i].rect.w,
                obj.blocks[i].rect.h
            };

            bool hovering = false;

            if (hovered == -1 && mouse_within(&bounding_box))
            {
                hovering = true;
                hovered = i;
                hovered_entity = false;
                hover_box = bounding_box;
            }

            graphics.draw_rect(bounding_box.x, bounding_box.y, bounding_box.w, bounding_box.h, graphics.getRGB(90, 15, 15));
        }

        font::print(PR_BOR | PR_FONT_8X8, 5, 14, loc::gettext("[Press TAB to toggle movement]"), 220 - (help.glow), 220 - (help.glow), 255 - (help.glow / 2));

        if (hovered != -1)
        {
            int line = 0;
            if (hovered_entity)
            {
                entclass* entity = &obj.entities[hovered];
                render_info(line++, "Index: {value}", help.String(hovered).c_str());
                render_info(line++, "X: {value}", help.String(entity->xp).c_str());
                render_info(line++, "Y: {value}", help.String(entity->yp).c_str());
                render_info(line++, "Width: {value}", help.String(entity->w).c_str());
                render_info(line++, "Height: {value}", help.String(entity->h).c_str());
                line++;
                render_info(line++, "Rule: {value}", help.String(entity->rule).c_str());
                render_info(line++, "Type: {value}", help.String(entity->type).c_str());
                render_info(line++, "Behave: {value}", help.String(entity->behave).c_str());
                render_info(line++, "Para: {value}", help.String(entity->para).c_str());
                line++;
                render_info(line++, "Tile: {value}", help.String(entity->tile).c_str());
                render_info(line++, "Draw Frame: {value}", help.String(entity->drawframe).c_str());
                render_info(line++, "Size: {value}", help.String(entity->size).c_str());
                render_info(line++, "Direction: {value}", help.String(entity->dir).c_str());

                graphics.draw_rect(hover_box.x, hover_box.y, hover_box.w, hover_box.h, graphics.getRGB(32, 255 - help.glow, 255 - help.glow));
            }
            else
            {
                blockclass* block = &obj.blocks[hovered];
                render_info(line++, "Index: {value}", help.String(hovered).c_str());
                render_info(line++, "X: {value}", help.String(block->rect.x).c_str());
                render_info(line++, "Y: {value}", help.String(block->rect.y).c_str());
                render_info(line++, "Width: {value}", help.String(block->rect.w).c_str());
                render_info(line++, "Height: {value}", help.String(block->rect.h).c_str());

                line++;

                if (block->type == TRIGGER || block->type == ACTIVITY)
                {
                    render_info(line++, "Script: {value}", block->script.c_str());
                    render_info(line++, "State: {value}", help.String(block->trigger).c_str());
                }
                else if (block->type == DIRECTIONAL)
                {
                    render_info(line++, "Direction: {value}", help.String(block->trigger).c_str());
                }

                graphics.draw_rect(hover_box.x, hover_box.y, hover_box.w, hover_box.h, graphics.getRGB(255 - help.glow, 32, 32));
            }
        }
    }
};
