#include "game.h"

#include "ui.h"
#include "scenes.h"


// =====================================================
// POSIÇÕES DA INTERFACE
// =====================================================

static Rectangle newGameButton =
{
    490,
    439,
    299,
    59
};

/* +20%
static Rectangle newGameButton = {460, 350, 360, 72};

// +40%
static Rectangle newGameButton = {430, 350, 420, 84};

// +60%
static Rectangle newGameButton = {400, 350, 480, 96};

// +80%
static Rectangle newGameButton = {370, 350, 540, 108};*/

// =====================================================
// INICIALIZAR JOGO
// =====================================================

void InitGame(GameState *game)
{
    game->currentScreen =
        SCREEN_MENU;


    game->currentScene =
        SCENE_PRESENT;


    game->dialogueIndex =
        0;
}


// =====================================================
// TROCAR DE CENA
// =====================================================

void ChangeScene(
    GameState *game,
    SceneID nextScene
)
{
    game->currentScene =
        nextScene;


    game->dialogueIndex =
        0;
}


// =====================================================
// UPDATE
// =====================================================

void UpdateGame(GameState *game)
{

    // -------------------------------------------------
    // MENU
    // -------------------------------------------------

    if (
        game->currentScreen
        ==
        SCREEN_MENU
    )
    {

        if (
            IsButtonClicked(
                newGameButton
            )
        )
        {
            game->currentScreen =
                SCREEN_GAME;


            ChangeScene(
                game,
                SCENE_PRESENT
            );
        }

        return;
    }


    // -------------------------------------------------
    // JOGO
    // -------------------------------------------------

    if (
        game->currentScreen
        ==
        SCREEN_GAME
    )
    {

        Scene scene =
            GetScene(
                game->currentScene
            );


        if (
            IsKeyPressed(KEY_SPACE)
        )
        {

            game->dialogueIndex++;


            if (
                game->dialogueIndex
                >=
                scene.dialogueCount
            )
            {

                ChangeScene(
                    game,
                    scene.nextScene
                );
            }
        }
    }
}


// =====================================================
// DESENHAR JOGO
// =====================================================

void DrawGame(
    GameState *game,
    Assets *assets
)
{

    // -------------------------------------------------
    // MENU
    // -------------------------------------------------

    if (
        game->currentScreen
        ==
        SCREEN_MENU
    )
    {

        ClearBackground(
            (Color)
            {
                220,
                235,
                255,
                255
            }
        );

        Rectangle logoRect = {254, 0, 771, 491};
        

        DrawTexturePro(
            assets->logo,
            (Rectangle){
            0,
            0,
            assets->logo.width,
            assets->logo.height
         },
        logoRect,
        (Vector2){0, 0},
        0.0f,
        WHITE
        );


        DrawImageButton(

            assets->newGameNormal,

            assets->newGameHover,

            assets->newGamePressed,

            newGameButton
        );


        return;
    }
// ---------------------------------------------
// PERSONAGEM
// ---------------------------------------------

Rectangle liaRect =
{
    712,   // X
    38,   // Y
    449,   // largura
    1597    // altura
};

DrawTexturePro(
    assets->liaFrente,

    (Rectangle)
    {
        0,
        0,
        assets->liaFrente.width,
        assets->liaFrente.height
    },

    liaRect,

    (Vector2)
    {
        0,
        0
    },

    0.0f,

    WHITE
);


    // -------------------------------------------------
    // CENAS
    // -------------------------------------------------

    if (
        game->currentScreen
        ==
        SCREEN_GAME
    )
    {

        Texture2D background;


        switch (
            game->currentScene
        )
        {

            case SCENE_PRESENT:

                background =
                    assets->bgPresent;

                break;


            case SCENE_2007:

                background =
                    assets->bg2007;

                break;


            default:

                background =
                    assets->bgPresent;

                break;
        }

        // Background ocupando a tela toda

        DrawTexturePro(

            background,

            (Rectangle)
            {
                0,
                0,
                background.width,
                background.height
            },

            (Rectangle)
            {
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight()
            },

            (Vector2)
            {
                0,
                0
            },

            0,

            WHITE
        );

   DrawTexturePro(
            assets->liaFrente,
            (Rectangle){0, 0, assets->liaFrente.width,
            assets->liaFrente.height},
            liaRect,
            (Vector2){0, 0}, 0.0f, WHITE

            
        );
        // ---------------------------------------------
        // DIÁLOGO
        // ---------------------------------------------

        Scene scene =
            GetScene(
                game->currentScene
            );


        Dialogue dialogue =
            scene.dialogues[
                game->dialogueIndex
            ];


        DrawDialogueBox(
            dialogue.speaker,
            dialogue.text
        );
    }


    // Para desenvolvimento:

    // DrawDebugGrid();

    // DrawMousePosition();
}