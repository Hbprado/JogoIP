// Os arquivos de cabeçalho
#include "ACore.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Atributos da tela
#define LARGURA_TELA 800
#define ALTURA_TELA 600
#define BUFFER_SIZE 100
#define ASTRBR 1
#define ASTRURSS 2
#define ASTRMESSI 3
#define ASTRDEFAULT 4
#define LOGIN_MAX_SIZE 13



 
int main(void){
    
     
    char ServerIP[30] = {"127.0.0.1"};
    //Salva o login
    char loginMsg[BUFFER_SIZE]={0};
    
    // Flag que condicionará nosso looping
    int sair = 0,historia = 0,tutorial=0,jogar=0,telaIp=0,telaLogin=0,telaCharacter=0;
    if (!coreInit()){
        return -1;
	}
    //Agora vamos criar a nossa janela. Largura e Altura em pixels, o título é uma string.
    if (!windowInit(LARGURA_TELA, ALTURA_TELA, "OxygenIsUnderrated")){
	    return -1;
	}
    //Agora inicializamos nosso teclado e mouse, para que a janela responda às entradas deles
    if (!inputInit()){
		printf("Erro no teclado");
        return -1;
	}
    //Agora inicializamos nossas fontes
    if(!fontInit()){
      return -1;
	}
    if(!loadMusic()){
        return -1;
	}
    //E por fim todas as imagens que vamos utilizar no programa.
    if(!loadGraphics()){
        return -1;
	}
    
    
    
    
    
    
 
    //addon que da suporte as extensoes de audio
    
    
    
 
    // Flag indicando se o mouse está sobre o retângulo central
    int botaoSair = 0,botaoJogar = 0,botaoTutorial = 0,botaoHistoria = 0;
    while (!sair){        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
 
            // Se o evento foi de movimentação do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_AXES){
                // Verificamos se ele está sobre a região do retângulo central
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 50 &&
                evento.mouse.x <= LARGURA_TELA - 50 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10){
                    botaoSair = 1;
                }
                else{
                    botaoSair = 0;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_jogar) - 550 &&
                evento.mouse.x <= LARGURA_TELA - 550 && evento.mouse.y <= ALTURA_TELA - 150 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_jogar) - 150){
                    botaoJogar = 1;
                }
                else{
                    botaoJogar = 0;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_historia) - 550 &&
                evento.mouse.x <= LARGURA_TELA - 550 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_historia) - 10){
                    botaoHistoria = 1;
                }
                else{
                    botaoHistoria = 0;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_tutorial) - 300 &&
                evento.mouse.x <= LARGURA_TELA - 300 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_tutorial) - 10){
                    botaoTutorial = 1;
                }
                else{
                    botaoTutorial = 0;
                }
            }
            // Ou se o evento foi um clique do mouse
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 50 &&
                evento.mouse.x <= LARGURA_TELA - 50 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10){
                    sair = 1;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_historia) - 550 &&
                evento.mouse.x <= LARGURA_TELA - 550 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_historia) - 10){
                    historia = 1;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_tutorial) - 300 &&
                evento.mouse.x <= LARGURA_TELA - 300 && evento.mouse.y <= ALTURA_TELA - 10 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_tutorial) - 10){
                    tutorial = 1;
                }
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_jogar) - 550 &&
                evento.mouse.x <= LARGURA_TELA - 550 && evento.mouse.y <= ALTURA_TELA - 150 &&
                evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_jogar) - 150){
                    jogar = 1;
                }
            }
        }
        while(jogar==1){
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
             readInput(evento,ServerIP,20);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        telaLogin=1;
                        jogar=0;
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
	                sair=1;
	            }
        }
             al_draw_bitmap(backgroundIP, LARGURA_TELA - al_get_bitmap_width(backgroundIP),
        ALTURA_TELA  - al_get_bitmap_height(backgroundIP), 0);

        if (strlen(ServerIP) > 0)
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, ServerIP);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "0.0.0.0");
    }
         al_flip_display();    
    }
         while(telaLogin==1){
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            readInput(evento,loginMsg,LOGIN_MAX_SIZE);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        telaCharacter=1;
                        telaLogin=0;
                }
            }
            if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
	                sair=1;
	            }
        }
             al_draw_bitmap(backgroundLogin, LARGURA_TELA - al_get_bitmap_width(backgroundLogin),
        ALTURA_TELA  - al_get_bitmap_height(backgroundLogin), 0);

        if (strlen(loginMsg) > 0)
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, loginMsg);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(font)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "<login>");
    }
        
         al_flip_display();    
    }         
        while(historia==1){
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        historia=0;
                }
            }
        }
             al_draw_bitmap(backgroundHistoria, LARGURA_TELA - al_get_bitmap_width(backgroundHistoria),
        ALTURA_TELA  - al_get_bitmap_height(backgroundHistoria), 0);
        
         al_flip_display();    
    }
    int personagem_exibido = ASTRBR;
     while(telaCharacter==1){
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_RIGHT:
                         personagem_exibido+=1;
							personagem_exibido%=5;
							if(personagem_exibido == 0){
								personagem_exibido++;
							}
                        break;
                    case ALLEGRO_KEY_LEFT:
                        personagem_exibido-=1;
							if(personagem_exibido == 0){
								personagem_exibido+=4;
							}
                        break;
                    
                        
                }
            }
        }
         al_draw_bitmap(backgroundCharacter, LARGURA_TELA - al_get_bitmap_width(backgroundCharacter),
        ALTURA_TELA  - al_get_bitmap_height(backgroundCharacter), 0);
        if(personagem_exibido==1){
            al_draw_bitmap(astrBR, LARGURA_TELA - al_get_bitmap_width(astrBR)-340,
            ALTURA_TELA  - al_get_bitmap_height(astrBR)-220, 0);
            al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-150,
                     ALLEGRO_ALIGN_CENTRE, "BRASIL");
        }
        if(personagem_exibido==2){
           al_draw_bitmap(astrURSS, LARGURA_TELA - al_get_bitmap_width(astrURSS)-340,
        ALTURA_TELA  - al_get_bitmap_height(astrURSS)-220, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-150,
                     ALLEGRO_ALIGN_CENTRE, "URSS");
        }
        if(personagem_exibido==3){
           al_draw_bitmap(astrMessi, LARGURA_TELA - al_get_bitmap_width(astrMessi)-340,
        ALTURA_TELA  - al_get_bitmap_height(astrMessi)-220, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-150,
                     ALLEGRO_ALIGN_CENTRE, "ARGENTINA");
        }
        if(personagem_exibido==4){
            al_draw_bitmap(astrDefault, LARGURA_TELA - al_get_bitmap_width(astrDefault)-340,
        ALTURA_TELA  - al_get_bitmap_height(astrDefault)-220, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), LARGURA_TELA- al_get_font_ascent(font)-340,
                     ALTURA_TELA - al_get_font_ascent(font)-150,
                     ALLEGRO_ALIGN_CENTRE, "DEFAULT");
        }
         al_flip_display();    
    }
     while(tutorial==1){
            while (!al_is_event_queue_empty(fila_eventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_ENTER:
                        tutorial=0;
                }
            }
        }
             al_draw_bitmap(backgroundTutorial, LARGURA_TELA - al_get_bitmap_width(backgroundTutorial),
        ALTURA_TELA  - al_get_bitmap_height(backgroundTutorial), 0);
        
         al_flip_display();    
    }
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(background, LARGURA_TELA - al_get_bitmap_width(background),
        ALTURA_TELA  - al_get_bitmap_height(background), 0);
        if(botaoSair==1){
            al_draw_bitmap(botao_sair, LARGURA_TELA - al_get_bitmap_width(botao_sair) - 50,
            ALTURA_TELA - al_get_bitmap_height(botao_sair) - 20, 0);}
        else{
            al_draw_bitmap(botao_sair, LARGURA_TELA - al_get_bitmap_width(botao_sair) - 50,
            ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10, 0);
        }
        if(botaoHistoria==1){
        al_draw_bitmap(botao_historia, LARGURA_TELA - al_get_bitmap_width(botao_historia)-550,
        ALTURA_TELA  - al_get_bitmap_height(botao_historia)-20, 0);
        }
        else{
            al_draw_bitmap(botao_historia, LARGURA_TELA - al_get_bitmap_width(botao_historia)-550,
        ALTURA_TELA  - al_get_bitmap_height(botao_historia)-10, 0);
        }
        if(botaoJogar==1){
        al_draw_bitmap(botao_jogar, LARGURA_TELA - al_get_bitmap_width(botao_jogar)-550,
        ALTURA_TELA  - al_get_bitmap_height(botao_jogar)-160, 0);
        }
        else{
            al_draw_bitmap(botao_jogar, LARGURA_TELA - al_get_bitmap_width(botao_jogar)-550,
        ALTURA_TELA  - al_get_bitmap_height(botao_jogar)-150, 0);
        }
        if(botaoTutorial==1){
        al_draw_bitmap(botao_tutorial, LARGURA_TELA - al_get_bitmap_width(botao_tutorial)-300,
        ALTURA_TELA  - al_get_bitmap_height(botao_tutorial)-20, 0);
        }
        else{
            al_draw_bitmap(botao_tutorial, LARGURA_TELA - al_get_bitmap_width(botao_tutorial)-300,
        ALTURA_TELA  - al_get_bitmap_height(botao_tutorial)-10, 0);
        }
        
        
        // Atualiza a tela
        al_flip_display();
    }
 
    // Desaloca os recursos utilizados na aplicação
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(botao_historia);
    al_destroy_bitmap(botao_jogar);
    al_destroy_bitmap(botao_tutorial);
    al_destroy_bitmap(background);
    al_destroy_display(janela);
    al_destroy_font(font);
    al_destroy_event_queue(fila_eventos);
     al_destroy_audio_stream(musica);
    return 0;
}
