// PA2
// CMPS 101 Tantalo Spring 2019
// Aaron Nguyen
// anguy200
// 1585632





#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 180


int main(int argc, char* argv[]){
   int linecount = 0;
   FILE *in, *out;
   char line[MAX_LEN];
	// check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   //printf("Hello");

   while(fgets(line, MAX_LEN, in) != NULL){
     linecount++;
     //printf("%d", linecount);
   }

   rewind(in);

   char words[linecount][MAX_LEN];

   for(int i = 0; i < linecount; i++){
     fgets(line, MAX_LEN, in);
     strcpy(words[i], line);
     //printf("%s", line);
   }

   List sorted = newList();

   for(int x = 0; x < linecount; x++){
     if(length(sorted) == 0){
       append(sorted, x);
     }else{
       int inserted = 0;
       moveFront(sorted);
       while(index(sorted) != -1){
         int comp = strcmp(words[x], words[get(sorted)]);
         if(comp == 0){
           insertAfter(sorted, x);
           inserted++;
           break;
         }else if(comp < 0){
           insertBefore(sorted, x);
           inserted++;
           break;
         }else{
           moveNext(sorted);
         }
     }
       if(inserted == 0){
         append(sorted,x);
       }
   }
}

   //printList(stdout, sorted);
   moveFront(sorted);
   for(int x = 0; x < linecount; x++){
     fprintf(out, "%s", words[get(sorted)]);
     moveNext(sorted);
   }

   freeList(&sorted);

   fclose(in);
   fclose(out);

   return(0);

}
