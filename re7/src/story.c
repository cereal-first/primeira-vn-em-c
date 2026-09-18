#include "story.h"


// =====================================================
// CENA: PRESENTE
// =====================================================

Dialogue presentDialogues[] =
{
    {
        "Lia",
        "Finalmente terminei de trabalhar..."
    },

    {
        "Lia",
        "Por que eu ainda estou olhando para essa tela?"
    },

    {
        "IA",
        "Talvez voce precise descansar."
    },

    {
        "Lia",
        "Desde quando voce se preocupa comigo?"
    }
};


// =====================================================
// CENA: 2007
// =====================================================

Dialogue room2007Dialogues[] =
{
    {
        "Lia",
        "..."
    },

    {
        "Lia",
        "Nao pode ser."
    },

    {
        "Lia",
        "Esse quarto..."
    },

    {
        "Lia",
        "Eu voltei para 2007?"
    }
};


// =====================================================
// CONTAGEM DE DIÁLOGOS
// =====================================================

int GetPresentDialogueCount(void)
{
    return sizeof(presentDialogues) / sizeof(presentDialogues[0]);
}

int GetRoom2007DialogueCount(void)
{
    return sizeof(room2007Dialogues) / sizeof(room2007Dialogues[0]);
}