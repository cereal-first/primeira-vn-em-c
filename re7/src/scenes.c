#include "scenes.h"
#include "story.h"


// =====================================================
// RETORNAR CENA
// =====================================================

Scene GetScene(SceneID id)
{
    switch (id)
    {

        case SCENE_PRESENT:
        {
            Scene scene =
            {
                presentDialogues,
                GetPresentDialogueCount(),
                SCENE_2007
            };

            return scene;
        }


        case SCENE_2007:
        {
            Scene scene =
            {
                room2007Dialogues,
                GetRoom2007DialogueCount(),
                SCENE_PRESENT
            };

            return scene;
        }


        default:
        {
            Scene empty = {0};

            return empty;
        }
    }
}