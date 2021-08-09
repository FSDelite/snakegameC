#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//DEFININDO AS TECLAS
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//DECLARANDO AS FUNCOES
void update();
void draw();
void setup();
void input();

//DECLARANDO VARIAVEIS GLBOAIS
int larg = 23, alt = 23, score = 0, timer = 75, tailX[50] = { 0 }, tailY[50] = { 0 };
int x = 0, y = 0, gameOver = 0, pointX = 0, pointY = 0, flag = 0, bFoodX = 0, bFoodY = 0;
int* pTimer = &timer;

int main(void)
{
    setup();
    draw();
    while (gameOver != 1)
    {
        input();
        system("CLS");
        draw();
        update();
    }
    system("CLS");
    printf("\t*GAME OVER*\a\a\a");

    return 0;
}
/*******************************************************************/
void setup()
{
    x = larg / 2;
    y = alt / 2;
    do // DEFININDO LUGAR DA COMIDA
    {
        pointX = rand() % (larg - 1);
        pointY = rand() % (alt - 1);
    } while (pointX == 0 || pointY == 0);
    do // DEFININDO LUGAR DA COMIDA RUIM (BAD FOOD)
    {
        bFoodX = rand() % (larg - 1);
        bFoodY = rand() % (alt - 1);
    } while (bFoodX == 0 || bFoodY == 0);
}
/*******************************************************************/
void draw()
{
    for (int i = 0; i < alt; i++)
    {
        for (int j = 0; j < larg; j++)
        {
            if (i == x && j == y) // IMPRESSAO DA CABE�A DA COBRA
            {
                printf("%c", 254);
                j++;
            }
            if (pointX == i && pointY == j) // IMPRESSAO DA COMIDA BOA
            {
                printf("%c", 248); 
                j++;
            }
            if (bFoodX == i && bFoodY == j) // IMPRESSAO DA COMIDA RUIM
            {
                printf("!"); 
                j++;
            }

            if ((j == 0 || j == larg - 1) || (i == 0 || i == alt - 1)) // IMPRESSAO DAS PAREDES DO TABULEIRO
            {
                printf("%c", 178);
            }
            else
            {
                for (int k = 0; k < score; k++)// IMPRESSAO DA CAUDA DA COBRA
                {
                    if (i == tailX[k] && j == tailY[k])
                    {
                        printf("%c", 254);
                        j++;
                    }
                }
                printf(" ");
            }
            if ((x == 0 || x == larg - 1) || (y == alt - 1 || y == 0))//VERIFICA SE A COBRA ESTA BATENDO NA PAREDE
            {
                gameOver = 1;
                break;
            }
        }
        printf("\n");
    }
    printf("       SCORE: %d", score);
    printf("\n");
    for (int a = 0; a < 10; a++) //LACOS QUE IMPRIMEM OS VETORES tailX e tailY, A IMPRESSAO AJUDOU NA VISUALIZACAO DA IMPLEMENTACAO DA FILA
    {
        printf("%d ", tailX[a]);
    }
    printf("\n");
    for (int a = 0; a < 10; a++)
    {
        printf("%d ", tailY[a]);
    }
}
/*******************************************************************/
void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
        {
            if (flag != DOWN)
            {
                flag = UP;
            }
            break;
        }
        case 'a':
        {
            if (flag != RIGHT)
            {
                flag = LEFT;
            }
            break;
        }
        case 's':
        {
            if (flag != UP)
            {
                flag = DOWN;
            }
            break;
        }
        case 'd':
        {
            if (flag != LEFT)
            {
                flag = RIGHT;
            }
            break;
        }
        case 'x':
        {
            gameOver = 1;
            break;
        }
        }
    }
}
/*******************************************************************/
void update()
{
    int vetPrevX = tailX[0], vetPrevY = tailY[0];
    int vet2PrevX, vet2PrevY;

    tailX[0] = x;
    tailY[0] = y;

    Sleep(*pTimer); //FUNCAO PARA PAUSA NO PROGRAMA, EH USADA UMA VARIAVEL PARA QUE POSTERIORMENTE EU POSSA DIMUI-LA, AUMENTANDO A VELOCIDADE DO JOGO

    switch (flag) //MOVIMENTO
    {
    case UP:
    {
        x--;
        break;
    }
    case DOWN:
    {
        x++;
        break;
    }
    case LEFT:
    {
        y--;
        break;
    }
    case RIGHT:
    {
        y++;
        break;
    }
    }


    if (x == pointX && y == pointY) //A VERIFICACAO QUE PERGUNTA SE A COBRA ESTA NO MESMO LUGAR QUE A COMIDA
    {
        score++;
        system("color a");
        printf("\a");
        system("color f");
        do //TROCA DE LUGAR DA COMIDA
        {
            pointX = rand() % (larg - 1);
            pointY = rand() % (alt - 1);
        } while (pointX == 0 || pointY == 0);
        if (score % 5 == 0 && timer >= 0) //PEQUENO IF PARA AUMENTAR A VELOCIADADE GRADATIVAMENTE (A CADA 5 PONTOS)
        {
            timer = timer - 5;
        }
    }
    for (int k = 1; k <= score; k++)
    {
        vet2PrevX = tailX[k];
        vet2PrevY = tailY[k];
        tailX[k] = vetPrevX;
        tailY[k] = vetPrevY;
        vetPrevX = vet2PrevX;
        vetPrevY = vet2PrevY;
    }
    if (x == bFoodX && y == bFoodY) // VERIFICA SE A COBRA ESTA EM CIMA DA COMIDA RUIM
    {
        if (score > 0)
        {
            score--;
            system("color c");
            printf("\a");
            system("color f");
            do // REDEFININDO LUGAR DA COMIDA RUIM (BAD FOOD)
            {
                bFoodX = rand() % (larg - 1);
                bFoodY = rand() % (alt - 1);
            } while (bFoodX == 0 || bFoodY == 0);
            for (int i = 0; i <= score; i++)
            {
                tailX[i] = 0;
                tailY[i] = 0;
                tailX[i] = tailX[i + 1];
                tailY[i] = tailY[i + 1];
                tailX[i + 1] = 0;
                tailY[i + 1] = 0;
            }
        }
        else
        {
            gameOver = 1;
        }
    }
}