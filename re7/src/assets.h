#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"


typedef struct
{

    // backgrounds

    Texture2D bgPresent;

    Texture2D bg2007;

    Texture2D bgRua;


    // botões

    Texture2D newGameNormal;

    Texture2D newGameHover;

    Texture2D newGamePressed;

    Texture2D logo;


    // personagens

    Texture2D liaJovemLado;
    Texture2D liaFrente;

} Assets;


void LoadAssets(Assets *assets);

void UnloadAssets(Assets *assets);


#endif