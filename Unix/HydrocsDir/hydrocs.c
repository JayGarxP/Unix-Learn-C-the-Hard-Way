/*****************************************************************************
 * @file hydrocs.c
 * @PRGM ***HYDROCS***
 *
 * @date 06/13/18
 * @author Joseph Fallon
 *
 * Unix Spring 2018 OIT
 * Assignment 4
 *
 * @detail Hydrocs generates an html documentation page from your c code like a horrible version of Doxygen! </br> enjoy!
 * 
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINE_BUF 240
#define PRGM_TAG "PRGM"
#define TEMPLT_FNAME "/UNIX_A4/windex.html"

int main(int argc, char** argv)
{

  printf("Source code file:  %s\n", argv[1]);
  printf("Hydrocs.html  %s\n", argv[2]);

  char* src_fname = argv[1];
  char* hydroc_fname = argv[2];
 const char* templt_fname = "UNIX_A4/windex.html";
  char* PRGM_line = NULL;

  //TODO: decouple all strings, tags, flags, @comments  into config files and templates
  const char dro_flg[9] = "$@PRGM$@"; //all documentation tags are 4 chars long with "$@" on each side "$@xxxx$@"


  char buffer[LINE_BUF + 2]; //newline + \0 null
  char *buff_ptr, *find_ptr = NULL;
  FILE *fp_src, *fp_hydroc, *fp_templt = NULL;

  size_t find_len = strlen(dro_flg);
  fp_src = fopen(src_fname,"r");
  fp_templt = fopen(templt_fname, "r");
  fp_hydroc = fopen(hydroc_fname,"w");


  //printf("find_len = %zu \n", find_len);
 // if ( fp_templt != NULL ) printf("fp_templt is not null\n");
 // if ( fp_hydroc != NULL ) printf("fp_hydroc is not null\n");


  /* 1 Pull the good comment lines out the source code */
  int charin = fgetc(fp_src);
  while( charin != EOF)
  {
    //chekc charin
    if (charin == '@')
    {
      //Load up the whole line, we found us an @ symbol!
      fgets(buffer, LINE_BUF + 2, fp_src);
      buff_ptr = buffer;
      if(strstr(buffer, PRGM_TAG) != NULL)
      {
	if ((PRGM_line = malloc(sizeof(char) * strlen(buffer))) != NULL) {
	  strcpy(PRGM_line, buffer); //copy whole line for now
	}   
      }
    }

    charin =  fgetc(fp_src);
  }

  if (feof(fp_src)) printf("\n End of src code reached\n"); 
  else {
    printf("fp_src fgetc() fail\n");
  }

  //Close source code file
  fclose(fp_src);
//printf("LINE 82\n");

  /* 2 Fill hydroc up from template using tasty comments from source code file */
  while(fgets(buffer,LINE_BUF + 2,fp_templt))
  {
    buff_ptr = buffer;
    while ((find_ptr = strstr(buff_ptr, dro_flg)))
    {
      while(buff_ptr < find_ptr)
	fputc((int)*buff_ptr++, fp_hydroc); //assume char is 1byte
      fputs(PRGM_line,fp_hydroc);
      buff_ptr += find_len;
    }
    fputs(buff_ptr,fp_hydroc);
  }


fclose(fp_templt);
  fclose(fp_hydroc);


  if (PRGM_line != NULL)
  {
    free(PRGM_line);
  }



  return 0;
}
