## 🕹️ Como Compilar e Executar o Jogo

O **Re:7** é desenvolvido em linguagem C com a biblioteca [raylib](https://www.raylib.com/). Ele é compilado e executado pelo terminal e, ao iniciar, abre uma janela com o jogo.

### 🧰 Requisitos

- Windows
- Compilador **GCC** (MinGW-w64, por exemplo o w64devkit)
- Biblioteca **raylib** instalada para esse compilador

### 📁 Estrutura de pastas

```text
repositorio/
├── src/        código-fonte (.c e .h)
├── assets/     imagens (backgrounds, characters, ui)
└── README.md
```

### 🔨 Como compilar

Abra o terminal **na pasta raiz do projeto** (a que contém `src` e `assets`) e execute:

```bash
gcc src/*.c -o re7.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

O comando deve terminar sem erros nem avisos.

### ▶️ Como executar

Ainda na pasta raiz do projeto:

```bash
.\re7.exe
```

O jogo precisa ser aberto a partir da pasta raiz, porque ele lê as imagens da pasta `assets/`.

### 🎮 Como jogar

- **Menu:** clique nos botões com o mouse (Novo Jogo, Continuar, Créditos e Sair).
- **História:** `ESPAÇO` avança as falas.
- **Qualquer momento:** `ESC` volta ao menu e salva o progresso.
- **Minigame (corrida):** `ESPAÇO`, `W` ou `↑` para pular.
- **Minigame (puzzle):** `WASD` ou setas movem, `ESPAÇO` atira e `R` reinicia a fase.
- **Tela final:** `ENTER` joga de novo, `M` volta ao menu e `ESC` sai do jogo.

### ✅ O que o jogo contém

- Menu principal com Novo Jogo, Continuar (usa save), Créditos e Sair.
- Missão jogável do início ao fim: introdução em 2007, minigame de obstáculos com puzzle de 3 fases e epílogo.
- Entradas inválidas tratadas com laço `while` na tela final.
- Game loop que, ao terminar, pergunta se o jogador quer jogar de novo, voltar ao menu ou sair.
