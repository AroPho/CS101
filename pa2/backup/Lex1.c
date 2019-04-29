#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160





void sort(List L, char A[MAX_LEN][MAX_LEN], int in){
  moveFront(L);
  while(index(L) != -1){
    int comp = strcmp(A[in], A[get(L)]);
    if(comp == 0){
      insertAfter(L, in);
    }else if(comp < 0){
      insertBefore(L,in);
    }else{
      moveNext(L);
    }
    append(L, in);
  }
}



int main(int argc, char * argv[]){

   /*int linecount=0;
   FILE *in, *out;
   //char list[MAX_LEN];
   char line[MAX_LEN];
   //char* token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }*/

   // open files for reading and writing 
   /*in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }*/

   printf("%c", 'a');

   /*while(fgets(line, MAX_LEN,in)!= NULL){
     linecount++;
     printf("%d", linecount);
   }

   rewind(in);*/


   //char words[linecount][MAX_LEN];

   /* read each line of input file, then count and print tokens */
   /*for(int i = 0; i< linecount;i++){
     fgets(line, MAX_LEN,in );
     strcpy(words[i], line);
     printf("%s", line);
   }

   List sorted = newList();

   for(int x = 0; x < linecount; x++){
     if(length(sorted) == 0){
       append(sorted, x);
     }else{
       sort(sorted, words, x);
     }
   }
   moveFront(sorted);
   for(int x = 0; x < linecount; x++){
     fprintf(out, "%s\n", words[get(sorted)]);
     moveNext(sorted);
   }*/


   /* close files */
   //fclose(in);
   //fclose(out);

   return(0);
}
