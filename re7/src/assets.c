#include "assets.h"


void LoadAssets(Assets *assets)
{

    // BACKGROUNDS

    assets->bgPresent =
        LoadTexture(
            "assets/backgrounds/quarto_presente.png"
        );


    assets->bg2007 =
        LoadTexture(
            "assets/backgrounds/quarto_2007.png"
        );

    assets->bgRua =
        LoadTexture(
            "assets/backgrounds/rua.png"
        );
    // NEW GAME

    assets->newGameNormal =
        LoadTexture(
            "assets/ui/newGameNormal.png"
        );


    assets->newGameHover =
        LoadTexture(
            "assets/ui/newGameHover.png"
        );


    assets->newGamePressed =
        LoadTexture(
            "assets/ui/newGamePressed.png"
        );

    assets->logo =
        LoadTexture(
            "assets/ui/logo.png"
        );



    // PERSONAGEM

    assets->liaFrente =
        LoadTexture(
            "assets/characters/liaFrente.png"
        );


    assets->liaJovemLado =
        LoadTexture(
            "assets/characters/liaJovemLado.png"
        );
}


void UnloadAssets(Assets *assets)
{

    UnloadTexture(assets->bgPresent);

    UnloadTexture(assets->bg2007);
    
    UnloadTexture(assets->bgRua);


    UnloadTexture(
        assets->newGameNormal
    );

    UnloadTexture(
        assets->newGameHover
    );

    UnloadTexture(
        assets->newGamePressed
    );


    UnloadTexture(assets->liaFrente);

    UnloadTexture(assets->liaJovemLado);

    UnloadTexture(assets->logo);
    
}