#include "auto_complete.h"
typedef struct command_tag{ // structure of a command
   
   char * word; // the command
   struct command_tag * next; // the previous command entered

}COMMAND;

typedef struct commands_tag{ // a structure that holds commands

   COMMAND * head; // the most recent command put
   int size;
   int current_command_index; // the command that's currently shown by the program

}COMMANDS;

COMMAND * init_Command(char * buffer){ // creates a COMMAND entity with the current buffer content
   COMMAND * toReturn = (COMMAND *) malloc(sizeof(COMMAND));

   char * command = (char *) malloc(255 * sizeof(char));
   char * ptr = strtok(buffer," ");


   strcpy(command, buffer);


   toReturn->word = command;
   toReturn->next = NULL;

   return toReturn;
}


COMMANDS * init_CommandLine(){ // initializes a COMMANDS structure
   COMMANDS * cl = (COMMANDS *) malloc(sizeof(COMMANDS));
   cl->head = NULL;
   cl->size = 0;
   cl->current_command_index = -1;

   return cl;
}

void reset_current_command_index(COMMANDS ** cl){ // resets the current command index
   (*cl)->current_command_index = -1;
}

int deleteCommand(COMMANDS ** cl, COMMAND * check){ // deletes a command that's already inside the list
   COMMAND * traverser = (*cl)->head;
   COMMAND * prev = NULL;
   if(strcmp(traverser->word, check->word) == 0){ //head
      (*cl)->head = (*cl)->head->next;
      free(traverser);

      return 1;
   }else{
      while(traverser != NULL){ 
         
         if(strcmp(traverser->word, check->word) == 0){ //mid
            prev->next = traverser->next;
            free(traverser);
            return 1;
         }

         prev = traverser;
         traverser = traverser->next;

      }
   }

   return 0;
}

int justWhiteSpace(char * buf){ // checks if  there is only whitespace in buffer

   if(strlen(buf) == 0)return 0;

   int x;
   for(x = 0; x < strlen(buf); x++){
      if(!isspace(buf[x]))return 0;
   }return 1;

}

void addCommand(COMMANDS ** cl, char * buf){ // adds a command
   COMMAND * toADD = init_Command(buf);

   if(justWhiteSpace(buf) || strlen(buf) == 0)return;

   int x = deleteCommand(cl, toADD);

   reset_current_command_index(cl);

   if((*cl)->size == 0){ // direct insert
      (*cl)->head = toADD;
   }else{ //insert at head
      toADD->next = (*cl)->head; // toADD => cl(head)
      (*cl)->head = toADD; // cl(head) => toADD
   }

   (*cl)->size += x ? 0 : 1;
   
   // printCommands(*cl);

}


COMMAND * getCommand(COMMANDS * cl){ // gets a command
   COMMAND * traverser = cl->head;
   int traverser_index = 0;

   while(traverser_index < cl->size && traverser != NULL){

      if(traverser_index == cl->current_command_index){
         return traverser;
      }

      traverser = traverser->next;
      traverser_index++;
   }

   return NULL;
}

void printCommands(COMMANDS * cl){
   COMMAND * traverser = cl->head;

   printf("\n******************Commands Print********************\n");

   while(traverser != NULL){
      printf("%s\n", traverser->word);
      traverser = traverser->next;
   }

   printf("******************Commands Print********************\n");

}

void removeLetter( char ** buf,  DEX32_DDL_INFO * dev, int * i ){ // removes a letter from the buffer
   if((*i)>0){
      (*i)--;
      (*buf)[(*i)] = '\0';
      if (Dex32GetX(dev)==0){
         Dex32SetX(dev,79);
         if (Dex32GetY(dev)>0) 
            Dex32SetY(dev,Dex32GetY(dev)-1);
      }else{
         Dex32SetX(dev,Dex32GetX(dev)-1);
      }     
      Dex32PutChar(dev,Dex32GetX(dev),Dex32GetY(dev),' ',Dex32GetAttb(dev));
   };
}

void clearStdOut(char ** buf,  DEX32_DDL_INFO * dev, int * i){ // clears the current stdout and buffer
   int buff_length = strlen(buf), x;
   for(x = 0; x < buff_length; x++)removeLetter(buf, dev, i);
}

void prevCommand(COMMANDS ** commands, char ** buf,  DEX32_DDL_INFO * dev, int * i){  // shows the previous command entered   

   (*commands)->current_command_index++;

   if((*commands)->current_command_index >= (*commands)->size){
      (*commands)->current_command_index = (*commands)->size - 1;
      return;
   }


   clearStdOut(buf, dev, i);

   char * prev = getCommand(*commands)->word;
      
   writeToStdOut(prev, buf, dev, i);
}

void nextCommand(COMMANDS ** commands, char ** buf,  DEX32_DDL_INFO * dev, int * i){ // shows the "next" command

   (*commands)->current_command_index--;

   if((*commands)->current_command_index < -1){
      (*commands)->current_command_index = -1;
      return;
   }

   clearStdOut(buf, dev, i);

   char * next = getCommand(*commands)->word;
      
   writeToStdOut(next, buf, dev, i);
}

void freeCommandList(COMMANDS ** cl){ // frees all the commands in a command list

   COMMAND * traverser = (*cl)->head, * toFree = NULL;

   while( traverser != NULL ){
      toFree = traverser;
      traverser = traverser->next;
      free(toFree);
   }

   (*cl)->head = NULL;
   (*cl)->size = 0;

   printf("\nCommands Freed\n");

}
