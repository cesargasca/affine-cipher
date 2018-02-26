/**********************************************************
****programa que cifra y descifra mediante affine method****
**********************************************************/
//GASCA SANCHEZ CESAR EDUARDO cgascas2597@gmail.com
//HIDALGO CONTRERAS ALAN 	  alansdfs@gmail.com
//CRYPTOGRAPHY 3CV7


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale.h>
//#include <wchar.h>
int inverso(int a,int m){								 //--------------encuentra el inverso multiplicativo
	int b,x;
	for(b = 0 ; b < m ;b++){							 //--------------verifica uno a uno los elementos de Z
		x = (a * b) % m;
		if(x == 1)
			break;
	}
	if(x != 1)								
		return -1;									     //--------------regresa -1 si no tiene inverso
	else
		return b;							 		     //--------------regresa el inverso
}

void imprimir(char *l, int longitud){    				 //---------------imprime los valores de un alfabeto
	int i;
	for(i = 0; i < longitud ; i++){
		printf("%c",l[i]);
	}
	printf("\n");
}

int numberOfBytesInChar(unsigned char val) {
    if (val < 128) {
        return 1;
    } else if (val < 224) {
        return 2;
    } else if (val < 240) {
        return 3;
    } else {
        return 4;
    }
}

int buscar(char *alfabeto,char letra,int longitud){		 //---------------Busca un caracter en un alfabeto
	int i;
	//ingles
	if(letra==32)
		return -2;
	else if(letra==10)
		return -3;
	if(longitud==26){	//para alfabeto ingles
		for(i = 0 ; i < longitud ; i++){
			if(alfabeto[i] == letra || alfabeto[i]-32 == letra){
				return i;
			}
		}
	}
	if(longitud==33){ //para alfabeto español
		if(numberOfBytesInChar(letra) > 1){ //regresa caracteres especiales
			if(letra==-95) //á
				return 26;
			else if(letra==-87) //é
				return 27;
			else if(letra==-83) //í
				return 28;
			else if(letra==-77) //ó
				return 29;
			else if(letra==-70) //ú
				return 30;
			else if(letra==-79) //ñ
				return 31;
			else if(letra==-68) //ü
				return 32;
		}
		else{
		for(i = 0 ; i < 26 ; i++){
			if(alfabeto[i] == letra || alfabeto[i]-32 == letra){ //regresa caracteres normales
				return i;
			}
		}	
		}
	}
	if(longitud==42){//frances
		if(numberOfBytesInChar(letra) > 1){ //regresa caracteres especiales del frances
			if(letra==-96)
				return 26;
			else if(letra==-94)
				return 27;
			else if(letra==-90)
				return 28;
			else if(letra==-89)
				return 29;
			else if(letra==-87)
				return 30;
			else if(letra==-88)
				return 31;
			else if(letra==-86)
				return 32;
			else if(letra==-85)
				return 33;
			else if(letra==-82)
				return 34;
			else if(letra==-81)
				return 35;
			else if(letra==-76)
				return 36;
			else if(letra==-109)
				return 37;
			else if(letra==-71)
				return 38;
			else if(letra==-69)
				return 39;
			else if(letra==-68)
				return 40;
			else if(letra==-65)
				return 41;
		}
		else{
		for(i = 0 ; i < 26 ; i++){
			if(alfabeto[i] == letra || alfabeto[i]-32 == letra){ //regresa caracteres normales
				return i;
			}
		}	
		}
	}
	if(longitud==30){ //ALEMAN
		if(numberOfBytesInChar(letra) > 1){ //regresa caracteres especiales en aleman
			if(letra==-92)
				return 26;
			else if(letra==-74)
				return 27;
			else if(letra==-68)
				return 28;
			else if(letra==-97)
				return 29;
		}
		else{
		for(i = 0 ; i < 26 ; i++){
			if(alfabeto[i] == letra || alfabeto[i]-32 == letra){ //regresa caracteres normales
				return i;
			}
		}	
		}
	}
	
	return -1;
}



char  cifrar(int a, int b, char *alfabeto,int longitud,FILE *fin,FILE *fout){ //--------------lee y cifra un mensaje de un archivo
	int i,n=0;
	int nuevo;
	char character,ch2;
	 while( (character = fgetc(fin)) != EOF) {
	 	//printf("-------->%d\n",numberOfBytesInChar((unsigned char)character));
        for (int i = 0; i < numberOfBytesInChar((unsigned char)character) - 1; i++) {
            //putchar(character);
           // fprintf(fout, "%c", character);
            character = fgetc(fin);
            //printf("------>%d\n",character);
        }

        putchar(character);
        printf("------>%d ",character); //numero ascii caracter sera < 0 si es caracter especuial
        printf("------>%d",buscar(alfabeto,character,longitud)); //posicion en alfabeto
        printf("------>%d\n",((buscar(alfabeto,character,longitud)*a + b) % longitud)); //posicion en alfabeto sustituido
        int bu = buscar(alfabeto,character,longitud);
        if(bu>=0){ //para posiciones ya existentes en el alfabeto incluyendo caracteres especiales
        	 int l = (bu*a + b) % longitud;// formula affine cipher
        	if(l > 25 && longitud==42){ //sustituir en Frances
	        	printf("SI ENTRA\n");
	        	// a partir de aqui escribe caracteres en archivo cifrado
	        	if(l==26){ // los siguientes if son para caracteres especiales cada uno tiene un respectivo codigo en unicode
	        		fprintf(fout,"\u00e4");// ä	  
	        	}
	        	else if(l==27){
	        		fprintf(fout, "\u00e2");//â
	        	}
	        	else if(l==28){
	        		fprintf(fout, "\u00e6"); //æ	
	        	}
	        	else if(l==29){
	        		fprintf(fout, "\u00e7"); //ç	
	        	}
	        	else if(l==30){
	        		fprintf(fout, "\u00e9"); //é	
	        	}
	        	else if(l==31){
	        		fprintf(fout, "\u00e8"); //è	
	        	}
	        	else if(l==32){
	        		fprintf(fout, "\u00ea");	//ê
	        	}
	        	else if(l==33){
	        		fprintf(fout, "\u00eb");	//ë
	        	}
	        	else if(l==34){
	        		fprintf(fout, "\u00ee");	//î
	        	}
	        	else if(l==35){
	        		fprintf(fout, "\u00ef"); //ï	
	        	}
	        	else if(l==36){
	        		fprintf(fout, "\u00f4"); //ô	
	        	}
	        	else if(l==37){
	        		fprintf(fout, "\u0153"); //œ
	        	}
	        	else if(l==38){
	        		fprintf(fout, "\u00f9");	//ù
	        	}
	        	else if(l==39){
	        		fprintf(fout, "\u00fb"); //û	
	        	}
	        	else if(l==40){
	        		fprintf(fout, "\u00fc");	//ü
	        	}
	        	else if(l==41){
	        		fprintf(fout, "\u00ff");	//ÿ	
	        	}
        	}
	        else if(l > 25 && longitud==30){ //sustituir en aleman
	        	printf("SI ENTRA\n");
	        	if(l==26){
	        		fprintf(fout, "\u00e4");	//ä
	        	}
	        	else if(l==27){
	        		fprintf(fout, "\u00f6"); //ö
	        	}
	        	else if(l==28){ //ü
	        		fprintf(fout, "\u00fc"); 
	        	}
	        	else if(l==29){
	        		fprintf(fout, "\u00df"); //ß
	        	}
	        }
	        else if(l > 25 && longitud==33){ //sustituir en español
	        	printf("SI ENTRA\n");
	        	if(l==26){
	        		fprintf(fout, "\u00e2");	//á
	        	}
	        	else if(l==27){
	        		fprintf(fout, "\u00e9"); //é
	        	}
	        	else if(l==28){ 
	        		fprintf(fout, "\u00ed"); //í
	        	}
	        	else if(l==29){
	        		fprintf(fout, "\u00f3"); //ó
	        	}
	        	else if(l==30){
	        		fprintf(fout, "\u00fa"); //ú
	        	}
	        	else if(l==31){
	        		fprintf(fout, "\u00f1"); //ñ
	        	}
	        	else if(l==32){
	        		fprintf(fout, "\u00fc"); //ü
	        	}
	        }
	       	else{
		        //printf(" ");
		        fprintf(fout, "%c", alfabeto[l]); //caracteres normales
		    }
       }
       	else if(bu == -2){
       	fprintf(fout, "%c",' '); //manejo de espacios
       	}
       else if(bu == -3){
       	fprintf(fout, "%c",10); //manejo de saltos de linea
       	}
       		
	}
	    return ch2;
    }
	
char  descifrar(int a, int b, char *alfabeto,int longitud,FILE *fin,FILE *fout){ //--------------lee y cifra un mensaje de un archivo
	int i,n=0;
	int nuevo;
	char character,ch2;
	 while( (character = fgetc(fin)) != EOF) {
	 	//printf("-------->%d\n",numberOfBytesInChar((unsigned char)character));
        for (int i = 0; i < numberOfBytesInChar((unsigned char)character) - 1; i++) {
            //putchar(character);
           // fprintf(fout, "%c", character);
            character = fgetc(fin);
            //printf("------>%d\n",character);
        }

        putchar(character);
        printf("------>%d ",character);
        printf("------>%d",buscar(alfabeto,character,longitud));
        printf("------>%d\n",((buscar(alfabeto,character,longitud) - b)*(inverso(a,longitud)) % longitud));
        int bu = buscar(alfabeto,character,longitud);
        if(bu>=0){
        	 int l = (bu - b)*(inverso(a,longitud)) % longitud;//formula para decifrar con affine cipher
        	 // a partir de aqui escribe caracteres en archivo cifrado

			if(l<0){											   		 //--------------si la posicion es negativa
				l = longitud - (-l%longitud);			   		 //--------------a mod n = n - (a mod n)
			}
        	if(l > 25 && longitud==42){ //sustituir en Frances
	        	printf("SI ENTRA\n");
	        	if(l==26){ // los siguientes if son para caracteres especiales cada uno tiene un respectivo codigo en unicode
	        		fprintf(fout,"\u00e4");// ä	  
	        		fprintf(fout,"\u00e4");// ä	
	        	}
	        	else if(l==27){
	        		fprintf(fout, "\u00e2");//â
	        	}
	        	else if(l==28){
	        		fprintf(fout, "\u00e6"); //æ	
	        	}
	        	else if(l==29){
	        		fprintf(fout, "\u00e7"); //ç	
	        	}
	        	else if(l==30){
	        		fprintf(fout, "\u00e9"); //é	
	        	}
	        	else if(l==31){
	        		fprintf(fout, "\u00e8"); //è	
	        	}
	        	else if(l==32){
	        		fprintf(fout, "\u00ea");	//ê
	        	}
	        	else if(l==33){
	        		fprintf(fout, "\u00eb");	//ë
	        	}
	        	else if(l==34){
	        		fprintf(fout, "\u00ee");	//î
	        	}
	        	else if(l==35){
	        		fprintf(fout, "\u00ef"); //ï	
	        	}
	        	else if(l==36){
	        		fprintf(fout, "\u00f4"); //ô	
	        	}
	        	else if(l==37){
	        		fprintf(fout, "\u0153"); //œ
	        	}
	        	else if(l==38){
	        		fprintf(fout, "\u00f9");	//ù
	        	}
	        	else if(l==39){
	        		fprintf(fout, "\u00fb"); //û	
	        	}
	        	else if(l==40){
	        		fprintf(fout, "\u00fc");	//ü
	        	}
	        	else if(l==41){
	        		fprintf(fout, "\u00ff");	//ÿ	
	        	}
        	}
	        else if(l > 25 && longitud==30){ //sustituir en aleman
	        	printf("SI ENTRA\n");
	        	if(l==26){
	        		fprintf(fout, "\u00e4");	//ä
	        	}
	        	else if(l==27){
	        		fprintf(fout, "\u00f6"); //ö
	        	}
	        	else if(l==28){ //ü
	        		fprintf(fout, "\u00fc"); 
	        	}
	        	else if(l==29){
	        		fprintf(fout, "\u00df"); //ß
	        	}
	        }
	        else if(l > 25 && longitud==33){ //sustituir en español
	        	printf("SI ENTRA\n");
	        	if(l==26){
	        		fprintf(fout, "\u00e2");	//á
	        	}
	        	else if(l==27){
	        		fprintf(fout, "\u00e9"); //é
	        	}
	        	else if(l==28){ 
	        		fprintf(fout, "\u00ed"); //í
	        	}
	        	else if(l==29){
	        		fprintf(fout, "\u00f3"); //ó
	        	}
	        	else if(l==30){
	        		fprintf(fout, "\u00fa"); //ú
	        	}
	        	else if(l==31){
	        		fprintf(fout, "\u00f1"); //ñ
	        	}
	        	else if(l==32){
	        		fprintf(fout, "\u00fc"); //ü
	        	}
	        }
	       	else{
		        //printf(" ");
		        fprintf(fout, "%c", alfabeto[l]); //caracteres normales
		    }
       }
       	else if(bu == -2){
       	fprintf(fout, "%c",' '); //manejo espacios
       	}
       else if(bu == -3){
       	fprintf(fout, "%c",10); //manejo de saltos de linea
       	}
       		
	}
	    return ch2;
    }
	




char  *concatena(char *text,char *text2){ //concatena text con text2
	int i;
	char *nvo = (char *)malloc(strlen(text) + strlen(text2));
	for(i = 0 ; i < strlen(text) ; i++){
		nvo[i] = text[i];
	}
	for(i = 0 ; i < strlen(text2) ; i++){
		nvo[strlen(text) + i] = text2[i];
	}
	nvo[strlen(text) + strlen(text2)] = '\0';
	return nvo;
}

int main(){
	//setlocale(LC_CTYPE, "");
	FILE *fp1,*fp2,*fp3; 
	char *nombreArchivo = (char *)malloc(20);
	printf("dame el nombre del archivo a encriptar(sin extension): ");
	scanf("%s",nombreArchivo);
	char *nombre2 = malloc(50);
	nombre2 = concatena(nombreArchivo,"_encriptado"); //nombrearchivo_encriptado
	fp1 = fopen(concatena(nombreArchivo,".txt"),"r"); //nombrearchivo.txt	//-------------abre texto.txt para leer
	fp2 = fopen(concatena(nombre2,".txt"),"w");	 //nombrearchivo_encriptato.txt
	if (fp1 == NULL||fp2 ==NULL)                           					//-------------verifica que se abrieron correctamente
	{
		printf("Failed to open file'\n");
		exit(0);
	}

	int longitud, i,a,b;
	char aux;
	printf("ingresa el numero de elementos que tiene el alfabeto:\n");
	scanf("%d", &longitud);												    //-------------guarda la longitud de el alfabeto
	char *alfabeto = (char *)malloc(longitud+1);								//-------------reserva memoria para el alfabeto
	if(longitud==26){														//-------------alfabeto ingles
		alfabeto="abcdefghijklmnopqrstuvwxyz";
	}
	if(longitud==33){
		alfabeto="abcdefghijklmnopqrstuvwxyz";
	}
	else if(longitud==30){													//-------------alfabeto espanol
		alfabeto="abcdefghijklmnopqrstuvwxyz";
	}
	else if(longitud==42){													//-------------alfabeto espanol
		alfabeto="abcdefghijklmnopqrstuvwxyz";
	}
	else{																	//-------------alfabeto creado
		
		for(i = 0; i < longitud ; i++){										//-------------pide y guarda los caracteres del alfabeto
			scanf("%c",&aux);
			printf("letra #%d:", i);
			scanf("%c", &alfabeto[i]);
			//printf("%c\n", alfabeto[i]);
		}
	}
	
	imprimir(alfabeto,longitud);											//-------------imprime el alfabeto
	printf("DAME EL VALOR DE a:");
	scanf("%d", &a);														//-------------guarda a
	while(inverso(a,longitud) == -1){										//-------------verifica que sea una a valida
		printf("***NO TIENE INVERSO**\n");
		printf("DAME EL VALOR DE a:");
		scanf("%d", &a);
	}
	//printf("inverso de a: %d\n", inverso(a,26) );
	printf("DAME EL VALOR DE b:");											//-------------guarda b
	scanf("%d", &b);
	printf("\n***TEXTO CIFRADO***\n"); //cifra mensaje
	cifrar(a,b,alfabeto,longitud,fp1,fp2);	 								//-------------cifra el mensaje
	fclose(fp1); //cierra archivo
	fclose(fp2); //cierra archivo
	fp2= fopen(concatena(nombre2,".txt"),"r");//nombrearchivo_encriptado.txt
	fp3 = fopen(concatena(nombre2,"_descifrado.txt"),"w");//crea nombrearchivo_encriptado_descifrado.txt
	printf("\n****TEXTO DESCIFRADO\n");//descifra mensaje
	descifrar(a,b,alfabeto,longitud,fp2,fp3);
	fclose(fp2);//cierra archivo
	fclose(fp3);//cierra archivo
}
