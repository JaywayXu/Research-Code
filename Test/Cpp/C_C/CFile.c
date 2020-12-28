#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    
    // write to file
    fp = fopen("file.txt", "w"); // fopen() open file to FILE pointer

    if(NULL == fp) {
        printf("fail to open file\n");
    } else {
        printf("put char (end with '#'): ");
        char ch;
        while((ch=getchar()) != '#') { // getchar() get char from command line
            fputc(ch, fp); // fputc() put char to file
        }
        fputs("it is fputs str\n", fp);
        fputs("it is fputs str\n", fp);
        fclose(fp); // fclose() close file with FILE pointer
    }

    // read file
    fp = fopen("file.txt", "r");

    if(NULL == fp) {
        printf("fail to open file!\n");
    } else {
        char s[20];
        fgets(s, 20, fp); // fgets() get file string, end with '\n' or 'EOF'
        puts(s); // puts() put string to command line

        char ch;
        while(!feof(fp)) { // feof() return the file pointer is or not 'EOF'
            ch = fgetc(fp); // fgetc() get char from file
            putchar(ch); //putchar() put char to command line
        }
        fclose(fp);
    }

    return 0;
}