#include "game.h"

#include "ui.h"
#include "scenes.h"
#include <math.h>
#include <stdio.h>


// =====================================================
// FUNDO COSMICO DO MENU
// =====================================================

static void BrilhoSuave(float cx, float cy, float raio, Color cor, float alfa)
{
    DrawCircleGradient((Vector2){cx, cy}, raio, Fade(cor, alfa), Fade(cor, 0.0f));
}

static void DesenharFundo(void)
{
    int w = GetScreenWidth();
    int h = GetScreenHeight();
    float t = (float)GetTime();

    // base: violeta-noite para azul-marinho
    DrawRectangleGradientV(0, 0, w, h, (Color){24, 14, 52, 255}, (Color){12, 34, 66, 255});

    // manchas de luz nas cores do logo, flutuando devagar
    BrilhoSuave(w * 0.20f + sinf(t * 0.30f) * 30, h * 0.30f, 340, (Color){255, 105, 200, 255}, 0.35f);
    BrilhoSuave(w * 0.80f + cosf(t * 0.25f) * 30, h * 0.70f, 380, (Color){ 80, 200, 255, 255}, 0.30f);
    BrilhoSuave(w * 0.50f,                        h * 0.40f, 300, (Color){190, 150, 255, 255}, 0.25f);

    // estrelinhas piscando
    for (int i = 0; i < 45; i++)
    {
        unsigned int s = (unsigned int)(i + 1) * 2654435761u;
        float x = (float)(s % (unsigned)w);
        float y = (float)((s >> 8) % (unsigned)h);
        float tam = 3.0f + (float)((s >> 16) % 5);
        float brilho = 0.35f + 0.65f * (0.5f + 0.5f * sinf(t * 2.0f + i));
        Color c = Fade(WHITE, brilho);

        DrawLineEx((Vector2){x - tam, y}, (Vector2){x + tam, y}, 1.5f, c);
        DrawLineEx((Vector2){x, y - tam}, (Vector2){x, y + tam}, 1.5f, c);
        DrawCircleV((Vector2){x, y}, 1.5f, c);
    }
}


// =====================================================
// SAVE / LOAD (arquivo de texto: "cena fala")
// =====================================================

#define SAVE_FILE "save.dat"

static void SaveGame(GameState *game)
{
    SaveFileText(
        SAVE_FILE,
        (char *)TextFormat("%d %d", (int)game->currentScene, game->dialogueIndex)
    );
}

// Retorna true se conseguiu carregar um save valido
static bool LoadGame(GameState *game)
{
    if (!FileExists(SAVE_FILE)) return false;

    char *text = LoadFileText(SAVE_FILE);

    if (text == NULL) return false;

    int scene = 0;
    int index = 0;

    int lidos = sscanf(text, "%d %d", &scene, &index);

    UnloadFileText(text);

    if (lidos != 2) return false;

    if (scene < 0 || scene >= SCENE_COUNT) return false;

    Scene s = GetScene((SceneID)scene);

    if (index < 0 || index >= s.dialogueCount) index = 0;

    game->currentScene = (SceneID)scene;
    game->dialogueIndex = index;

    return true;
}


// =====================================================
// POSIÇÕES DOS BOTÕES DO MENU
// =====================================================

#define MENU_BUTTONS 4

static Rectangle menuRects[MENU_BUTTONS] =
{
    {490, 439, 299, 59},   // 0 - Novo Jogo
    {515, 505, 250, 50},   // 1 - Continuar
    {515, 565, 250, 50},   // 2 - Creditos
    {515, 625, 250, 50}    // 3 - Sair
};


// =====================================================
// INICIALIZAR JOGO
// =====================================================

void InitGame(GameState *game)
{
    game->currentScreen = SCREEN_MENU;

    game->currentScene = SCENE_PRESENT;

    game->dialogueIndex = 0;

    game->shouldExit = false;
}


// =====================================================
// TROCAR DE CENA
// =====================================================

void ChangeScene(
    GameState *game,
    SceneID nextScene
)
{
    game->currentScene = nextScene;

    game->dialogueIndex = 0;
}


// =====================================================
// UPDATE
// =====================================================

void UpdateGame(GameState *game)
{

    // -------------------------------------------------
    // MENU
    // -------------------------------------------------

    if (game->currentScreen == SCREEN_MENU)
    {
        if (IsButtonClicked(menuRects[0]))          // Novo Jogo
        {
            game->currentScreen = SCREEN_GAME;

            ChangeScene(game, SCENE_PRESENT);

            SaveGame(game);                         // zera o save
        }

        if (IsButtonClicked(menuRects[1]))          // Continuar
        {
            // carrega o save; se nao houver, comeca do inicio
            if (!LoadGame(game))
            {
                ChangeScene(game, SCENE_PRESENT);
            }

            game->currentScreen = SCREEN_GAME;
        }

        if (IsButtonClicked(menuRects[2]))          // Creditos
        {
            game->currentScreen = SCREEN_CREDITS;
        }

        if (IsButtonClicked(menuRects[3]))          // Sair
        {
            game->shouldExit = true;
        }

        return;
    }


    // -------------------------------------------------
    // CREDITOS
    // -------------------------------------------------

    if (game->currentScreen == SCREEN_CREDITS)
    {
        if (
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
            ||
            IsKeyPressed(KEY_ENTER)
            ||
            IsKeyPressed(KEY_BACKSPACE)
            ||
            IsKeyPressed(KEY_ESCAPE)
        )
        {
            game->currentScreen = SCREEN_MENU;
        }

        return;
    }


    // -------------------------------------------------
    // JOGO
    // -------------------------------------------------

    if (game->currentScreen == SCREEN_GAME)
    {
        // ESC: salva e volta ao menu
        if (IsKeyPressed(KEY_ESCAPE))
        {
            SaveGame(game);

            game->currentScreen = SCREEN_MENU;

            return;
        }

        Scene scene = GetScene(game->currentScene);

        if (IsKeyPressed(KEY_SPACE))
        {
            game->dialogueIndex++;

            if (game->dialogueIndex >= scene.dialogueCount)
            {
                ChangeScene(game, scene.nextScene);
            }

            SaveGame(game);                         // salva a cada fala
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

    if (game->currentScreen == SCREEN_MENU)
    {
        DesenharFundo();

        // X, Y, largura, altura
        // (aumentar o Y desce o logo, diminuir sobe)
        Rectangle logoRect = {280, 100, 719, 319};

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

        for (int i = 0; i < MENU_BUTTONS; i++)
        {
            DrawImageButton(
                assets->menuButtons[i][0],
                assets->menuButtons[i][1],
                assets->menuButtons[i][2],
                menuRects[i]
            );
        }

        return;
    }


    // -------------------------------------------------
    // CREDITOS
    // -------------------------------------------------

    if (game->currentScreen == SCREEN_CREDITS)
    {
        DesenharFundo();

        DrawCenteredText("CREDITOS", 120, 48, WHITE);
        DrawCenteredText("Re:7 - Projeto Integrador", 220, 28, WHITE);
        DrawCenteredText("(coloque aqui os nomes da equipe)", 280, 24, SKYBLUE);
        DrawCenteredText("Clique, ENTER ou ESC para voltar", 600, 20, Fade(WHITE, 0.7f));

        return;
    }


    // ---------------------------------------------
    // PERSONAGEM
    // ---------------------------------------------

    Rectangle liaRect =
    {
        712,   // X
        38,    // Y
        449,   // largura
        1597   // altura
    };

    DrawTexturePro(
        assets->liaFrente,
        (Rectangle){
            0,
            0,
            assets->liaFrente.width,
            assets->liaFrente.height
        },
        liaRect,
        (Vector2){0, 0},
        0.0f,
        WHITE
    );


    // -------------------------------------------------
    // CENAS
    // -------------------------------------------------

    if (game->currentScreen == SCREEN_GAME)
    {
        Texture2D background;

        switch (game->currentScene)
        {
            case SCENE_PRESENT:
                background = assets->bgPresent;
                break;

            case SCENE_2007:
                background = assets->bg2007;
                break;

            default:
                background = assets->bgPresent;
                break;
        }

        // Background ocupando a tela toda

        DrawTexturePro(
            background,
            (Rectangle){
                0,
                0,
                background.width,
                background.height
            },
            (Rectangle){
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight()
            },
            (Vector2){0, 0},
            0,
            WHITE
        );

        DrawTexturePro(
            assets->liaFrente,
            (Rectangle){
                0,
                0,
                assets->liaFrente.width,
                assets->liaFrente.height
            },
            liaRect,
            (Vector2){0, 0},
            0.0f,
            WHITE
        );

        // ---------------------------------------------
        // DIÁLOGO
        // ---------------------------------------------

        Scene scene = GetScene(game->currentScene);

        Dialogue dialogue = scene.dialogues[game->dialogueIndex];

        DrawDialogueBox(
            dialogue.speaker,
            dialogue.text
        );

        // ---------------------------------------------
        // AVISO: ESC VOLTA AO MENU
        // ---------------------------------------------

        DrawRectangleRounded(
            (Rectangle){20, 20, 170, 36},
            0.4f,
            8,
            Fade(BLACK, 0.55f)
        );

        DrawText("ESC  MENU", 38, 29, 20, WHITE);
    }


    // Para desenvolvimento:

    // DrawDebugGrid();

    // DrawMousePosition();
}