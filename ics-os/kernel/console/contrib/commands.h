typedef struct command_tag{ // structure of a command
   
   char * word; // the command
   struct command_tag * next; // the previous command entered

}COMMAND;

typedef struct commands_tag{ // a structure that holds commands

   COMMAND * head; // the most recent command put
   int size;
   int current_command_index; // the command that's currently showed by the program

}COMMANDS;

COMMAND * init_Command(char * buffer){ // creates a COMMAND entity with the current buffer content
   COMMAND * toReturn = (COMMAND *) malloc(sizeof(COMMAND));

   char * command = (char *) malloc(255 * sizeof(char));
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

void reset_current_command_index(COMMANDS ** cl){
   (*cl)->current_command_index = -1;
}

void addCommand(COMMANDS ** cl, COMMAND ** toADD){ // insert at head
   (*toADD)->next = (*cl)->head; // toADD => cl(head)
   (*cl)->head = (*toADD); // cl(head) => toADD
}

void printCommands(COMMANDS * cl){
   COMMAND * traverser = cl->head;

   printf("******************Commands Print********************\n");

   while(traverser != NULL){
      printf("traverser kun\n");
      traverser = traverser->next;
   }

   printf("******************Commands Print********************\n");

}