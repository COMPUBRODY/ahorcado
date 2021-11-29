#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define BGI_PATH "C:\\TURBOC3\\BGI"

enum el_man{
	HEAD = 1,
	EYE_IZQ,
	EYE_DER,
	BOCA,
	BODY,
	HAND_IZQ,
	HAND_DER,
	FOOT_IZQ,
	FOOT_DER,
	CUERPO
};

enum states{
	ok,
	lose,
	win,
	fail
};
void Draw_Grid()
{
   int midx = getmaxx()/2;
   int midy = getmaxy()/2;
   // line for x1, y1, x2, y2
   line(midx, 0, midx, getmaxy());  
   // line for x1, y1, x2, y2
   line(0, midy, getmaxx(), midy); 
}

/*
FUNCION DE DIBUJO DEL MONO AHORCADO
RETORNA TRUE SI DIBUJO 
RETORNA FALSE SI NO DIBUJO
*/
int draw_man(int part){
	
	int state = ok;
	
	switch(part){
		
		case HEAD:
			circle(100,50,15);					//cabeza
			state = ok;
			break;
		case EYE_IZQ:
			ellipse(93, 45, 0, 360, 1, 3); 		//ojo izq
			state = ok;
			break;
		case EYE_DER:
			ellipse(107, 45, 0, 360, 1, 3); 	//ojo der
			state = ok;
			break;
		case BOCA:
			ellipse(100,50,250,300,20,9); 		//boca
			state = ok;
			break;
		case BODY:
			ellipse(100, 100, 0, 360, 15, 35); 	//cuerpo
			state = ok;
			break;
		case HAND_IZQ:
			line(115, 80, 150, 115);			// mano izq
			state = ok;
			break;
		case HAND_DER:
			line(85, 80, 50, 115);				// mano der
			state = ok;
			break;
		case FOOT_IZQ:
			line(115, 125, 125, 180);			// pie izq
			state = ok;
			break;
		case FOOT_DER:
			line(85, 125, 75, 180);				// pie der
			state = ok;
			break;
		default:
			outtextxy(150, 150, "YOU LOSE!");
			state = lose;
			break;
	}
	return  state;
	
}

void draw_horca(){
	line(250, 20, 250, 215);		// poste 
	line(100, 20, 250, 20);			// viga
	line(200, 215, 300, 215);		// soporte
	line(100, 20, 100, 40);			// soga
	line(235, 20, 250, 75);			// trave
}

void draw_underlines(int size){
	int i = 0;
	int a=32, b=40;
	for(i=0; i<size; i++){
		line(a, 220, b, 220);		// letra
		a+=10;
		b+=10;
	}
	
}

int draw_char(char *word,int times,int size_word){
	int pos_x = 32;
	char ch=NULL;
	char arr[2]= {};
	char *ret=NULL;
	char *token = NULL;
	int index =0;
	printf("Ingresa Letra:\n");
	ch = getch();
	ret=strchr(word, ch);
	if(ret){
		index = (int)(ret-word);
		printf("acertada %d, indice %d\n", times,index);
	}
		//si no encuentra la misma letra acaba la funcion retornando false
		//para que imprima una parte del ahorcado.
	else{
		printf("Incorrecto \n");
		return fail;
	}

	
	memcpy(arr, ret, 1);
	//token = strtok(word,arr);
	
	if(times==size_word){;
		outtextxy(150, 150, "WIN!");
		return win;
	}
	else if(index <= size_word){
		if(index==0)	pos_x=32;
		if(index==1)	pos_x+=10;
		if(index==2)	pos_x+=20;
		if(index==3)	pos_x+=30;
		if(index==4)	pos_x+=40;
		if(index==5)	pos_x+=50;
		if(index==6)	pos_x+=60;
		if(index==7)	pos_x+=70;
		if(index==8)	pos_x+=80;
		if(index==9)	pos_x+=90;
		if(index==10)	pos_x+=100;
		
		outtextxy(pos_x, 215, arr);
	}

	
	
	return ok;
}

int main(void){
	
	int gd    = DETECT,gm; 
	initgraph(&gd,&gm,BGI_PATH);
	int size_word=0, part=0;
	char *word;
	int ahorcado = ok;
	int corrects=0;
	int state = ok;
	word = (char*)malloc( 20*sizeof(char));
	
	Draw_Grid();
	draw_horca();
	
	printf("Ingresa Palabra\n");
	gets(word);
	size_word = strlen(word);
	draw_underlines(size_word);
	
	while(!ahorcado){
		state = draw_char(word, corrects, size_word);
		if(state == fail){
			part++;
			ahorcado = draw_man(part);
		}
		else if(state == ok ){
			corrects++;
		}
		else if (state == win){
			ahorcado = lose;
		}
	
	}

	getch();
	closegraph();
   	
   	return 0;
	
}

