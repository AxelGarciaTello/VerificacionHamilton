#include <stdlib.h>
#include <stdio.h>

typedef struct arista{
  int nodo1,
      nodo2;
} ARISTA;

typedef struct grafo{
  int nodos[10];
  ARISTA aristas[55];
} GRAFO;

typedef struct certificado{
  int nodo[25];
} CERTIFICADO;

void leerGrafo(GRAFO *grafo){
  int i=0;
  char caracter=0;
  FILE *fp;
  for(i=0; i<10; i++){
    grafo->nodos[i]=0;
  }
  for(i=0; i<55; i++){
    grafo->aristas[i].nodo1=0;
    grafo->aristas[i].nodo2=0;
  }
  fp = fopen("Grafo.txt","r");
  if(fp==NULL){
    fprintf(stderr, "File error");
    exit(-1);
  }
  i=0;
  while((caracter=fgetc(fp))!='\n'){
    if(caracter!=' '){
      grafo->nodos[i]=caracter-'0';
      i++;
    }
  }
  i=0;
  while((caracter=fgetc(fp))!=EOF){
    grafo->aristas[i].nodo1=caracter-'0';
    caracter=fgetc(fp);
    caracter=fgetc(fp);
    grafo->aristas[i].nodo2=caracter-'0';
    caracter=fgetc(fp);
    i++;
  }
  fclose(fp);
}

void imprimirGrafo(GRAFO grafo){
  int i=0;
  for(i=0; i<10; i++){
    printf("%d\t", grafo.nodos[i]);
  }
  printf("\n");
  for(i=0; i<55; i++){
    printf("(%d,%d)\n", grafo.aristas[i].nodo1, grafo.aristas[i].nodo2);
  }
}

int verificacionHamilton(GRAFO grafo, CERTIFICADO certificado){
  int tamanioGrafo=0,
      tamanioCertificado=0,
      i=0,
      j=0;
  int registro[10];
  int bandera=0;
  for(i=0; i<10; i++){
    registro[i]=0;
  }
  for(i=0; grafo.nodos[i]!=0; i++);
  tamanioGrafo=i;
  for(i=0; certificado.nodo[i]!=0; i++);
  tamanioCertificado=i;
  if(tamanioCertificado!=(tamanioGrafo+1)){
    return 0;
  }
  if(certificado.nodo[0]!=certificado.nodo[tamanioGrafo]){
    return 0;
  }
  for(j=0; j<tamanioCertificado-1; j++){
    for(i=0; i<55; i++){
      if(
        grafo.aristas[i].nodo1==certificado.nodo[j] &&
        grafo.aristas[i].nodo2==certificado.nodo[j+1]
      ){
        bandera=1;
        break;
      }
      if(
        grafo.aristas[i].nodo2==certificado.nodo[j] &&
        grafo.aristas[i].nodo1==certificado.nodo[j+1]
      ){
        bandera=1;
        break;
      }
    }
    if(!bandera){
      return 0;
    }
    if(registro[certificado.nodo[j]-1]==0){
      registro[certificado.nodo[j]-1]=1;
    }
    else{
      return 0;
    }
  }
  for(i=0; i<tamanioGrafo; i++){
    if(registro[i]==0){
      return 0;
    }
  }
  return 1;
}

void imprimirCertificado(CERTIFICADO certificado){
  int i=0;
  for(i=0; (certificado.nodo[i])!=0; i++){
    printf("%d\t", certificado.nodo[i]);
  }
  printf("\n");
}

int main(void){
  int i=0,
      j=0;
  char caracter=0;
  int resultado;
  CERTIFICADO certificado[10];
  GRAFO grafo;
  FILE *fp;
  leerGrafo(&grafo);
  for(i=0; i<10; i++){
    for(j=0; j<25; j++){
      certificado[i].nodo[j]=0;
    }
  }
  fp = fopen("Certificados.txt","r");
  if(fp==NULL){
    fprintf(stderr, "File error");
    exit(-1);
  }
  i=j=0;
  while((caracter=fgetc(fp))!=EOF){
    if(caracter=='\n'){
      i++;
      j=0;
    }
    else if(caracter!=' '){
      certificado[i].nodo[j]=caracter-'0';
      j++;
    }
  }
  fclose(fp);
  for(i=0; certificado[i].nodo[1]!=0; i++){
    printf("Verificando certificado %d\n", i+1);
    resultado=verificacionHamilton(grafo, certificado[i]);
    imprimirCertificado(certificado[i]);
    if(resultado){
      printf("Es un ciclo simple hamiltoniano\n\n\n");
    }
    else{
      printf("NO Es un ciclo simple hamiltoniano\n\n\n");
    }
  }
}
