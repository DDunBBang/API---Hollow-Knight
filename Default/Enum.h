#pragma once

enum DIRECTION { DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LT, DIR_RT, DIR_LD, DIR_RD, DIR_END };

enum OBJID { OBJ_PLAYER, OBJ_BLADE, OBJ_DASH, OBJ_BLOCK, OBJ_TRAP, OBJ_MONSTER, OBJ_MOUSE, OBJ_BUTTON, OBJ_END };

enum UIID { UI_SOUL_BASE, UI_SOUL, UI_HP, UI_EFFECT, UI_END };

enum SCENEID { SC_MENU, SC_FIELD, SC_ENDING, SC_EDIT, SC_END };

enum EDIT { EDIT_BOTTOM, EDIT_TOP, EDIT_WALL_L, EDIT_WALL_R, EDIT_TRAP, EDIT_TRAP_L, EDIT_TRAP_R, EDIT_SPEAR, EDIT_BOSS, EDIT_END };