#pragma once

#ifndef MAP_H
#define MAP_H

#include "General.h"
#include "Structure_definition.h"




void move_cursor(int row, int col);         //FUNCTION TO MOVE CURSOR ON THE CONSOLE WINDOW

void draw_box(int ulr, int ulc, int scale); //FUNCTION TO DRAW BOX ON CONSOLE WINDOW

void draw_street(int ulr, int ulc);         //FUNCTION TO DRAW A STREET ON CONSOLE WINDOW

void draw_avenue(int ulr, int ulc);         //FUNCTION TO DRAW AN AVENUE ON CONSOLE WINDOW

void draw_map(int street, int avenue);      //FUNCTION TO DRAW THE MAP ON CONSOLE WINDOW



#endif MAP_H