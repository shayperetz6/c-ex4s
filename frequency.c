#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUM_LETTERS ((int)26)
typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct node {
    char letter;
    long unsigned int count;
    boolean endWord ;
    struct node* children[NUM_LETTERS];
} node;
struct node* getnode()
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    if (node == NULL){
    	printf("No space for dynamic allocation");
    	exit(1);
    }
    // init all the child to NULL
    for (int i = 0; i < NUM_LETTERS; i++) {
        node->children[i] = NULL;
    }
    node ->endWord = FALSE;
    return node;
}

//*********insertWord **********


void insertWord (node **root, char *word ) {
if (word[0]==' '||word[0]=='\n'||word[0]=='\t')  return;    
int len = strlen(word);
    node* current = *root;
    for (int i = 0; i < len; i++) {
        char c = word[i];
        int index = c - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = getnode();
            current = current->children[index];
        }
	 else { //exsict this char
            current = current->children[index]; //go to the next Node
        } 
        current->letter = c;
    }
    current->endWord = TRUE;
	current->count++;
}
//*********printWordDefult **********


void printWordDefult ( node *root, char *str, int level) {
    if (root->endWord==TRUE) {
        str[level] = '\0';
        printf("%s %ld\n", str, root->count);

    }
    for (int i = 0; i < NUM_LETTERS; i++) {
        if (root->children[i] !=NULL) {
            str[level] = i + 'a';
            printWordDefult(root->children[i], str, level + 1);
        }
    }
}

//*********printWordReverse **********

void printWordReverse( node *root, char *str, int level) {

    for (int i = NUM_LETTERS-1; i > -1; i--) {
        if (root->children[i]) {
            str[level] = i + 'a';
            printWordReverse(root->children[i], str, level + 1);
        }
    }
   if (root->endWord==TRUE) {
        str[level] = '\0';
        printf("%s %ld \n", str, root->count);

    }
}

// ** destroy the tree from the memory ***

void delete (node *toDelete){


    for (int i=0; i<NUM_LETTERS; i++){
        if (toDelete->children[i])
            delete(toDelete->children[i]);
    }
    free(toDelete);
}

int main(int argc,char *argv[] )
{
   struct node* head=getnode();
    char ch;
    //printf("enter your string:\n");
    ch=getchar();
    size_t size=0;
    char* word=(char *)malloc(sizeof(char));
    if (word == NULL){
    	printf("No space for dynamic allocation");
    	exit(1);
    }
    word[size++]='\0';
    while(ch!=EOF)
    {
        while ((ch!=' ') && (ch!='\t')&& (ch!= '\n')&& (ch!=EOF))
        {
            if ((ch>='a')&& (ch<='z'))
            {
                char* preWord= word;
                word=realloc(word, (size+1)*sizeof(char));
                if (word == NULL){
    	             printf("No space for dynamic allocation");
    	               free(preWord);
                	exit(1);
                     }
                word[size-1]=ch;
                word[size++]='\0';
            }
            else if ((ch>='A') && (ch<='Z'))
            {
                ch+=32;
                char* preWord= word;
                word=realloc(word, (size+1)*sizeof(char));
                if (word == NULL){
    	             printf("No space for dynamic allocation");
    	               free(preWord);
                	exit(1);
                }
                word[size-1]=ch;
                word[size++]='\0';
            }
            ch=getchar();
        }
        insertWord(&head,word);
        free(word);
        if (ch==EOF) break;
        ch=getchar();
        if(ch==EOF) break;
        size=0;
        word=(char *)malloc(sizeof(char));
        if (word == NULL){
    	    printf("No space for dynamic allocation");
           exit(1);
        }
        word[size++]='\0';   
    } 
    char* str =(char *)malloc(sizeof(char));
    if (str == NULL){
    	 printf("No space for dynamic allocation");
         exit(1);
        }
    if (argc==1){
    //printf("Defult \n");
        printWordDefult(head, str, 0);
    }
    else if(argv[1][0]=='r'){
        //printf("Reverse \n");
 	printWordReverse(head, str, 0);

}
free (str);
delete(head);
    
}
