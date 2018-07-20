/*****************************************************************************
 * @file compdir.c
 *
 * @date 05/30/18
 * @author Joseph Fallon
 *
 * Unix Spring 2018 OIT Assignment 3
 *
 * @detail Assignment 3: Implement compdir script in C
 *
 * @flow (1) Process Command Line
 *       (2) Verify Directories Given Are Accessible
 *       (3) Recurse Through Dirs
 *	 (4) Print NEW, MODIFIED/REVERTED with `diff`, or DELETED. 
 *           Repeat step 3&4 until all files are processed
 *           
 *        
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h> //http://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
#include <sys/types.h>
#include <ctype.h>

#include "prettyprint.h"

/*Magic Numbers*/
#define SRVR_PATH_SIZE 1024
#define STDIN_BUF_SIZE 256

/*Error Codes: Assume 0 is success, 
 * non-zero exits are various errorcodes */
#define E_INVALID_OPTION -1
#define E_TOO_MANY_ARGS -2
#define E_TOO_FEW_ARGS -3
#define E_INVALID_ARG -4
#define E_OPENDIR_FAIL -5
#define X_ABORT -6

void usage()
{
  printf("Usage: compdir [-R] [-D] <base_dir> <modified_dir>\n");
  printf("\t-R\t\tRecurse into sub-directories\n");
  printf("\t-D\t\tPrint differences between modified files\n");
  printf("\t-?\t\tSee More Information about 'Compare Directory'\n");
  printf("\t-V\t\tVerbose mode: print program traces\n");
  printf("\t<base_dir>\tOriginal Dir\n");
  printf("\t<modified_dir>\tNew Dir with modded files inside\n\n");
}

/*Forward Declarations*/

//Print extra help if given option `-?`
void extraUsage();

//Prints message to console and stderr and returns errCode
int errMsg(char* msg, int errCode);

//returns current working directory
char* getMYcwd (char*);

//Set flags and save directory names
int processCmdLine(int, char**, short *, int *, int *, char**, char**);

//Checks if directory arg is accessible
void validate_directory(char* name);

//Get last modified time from filename 'name' using stat
time_t get_time_stamp(char* name);

//Compare filenames and timestamps of two directories to print NEW, DEL, etc.
void compare_directories(char* base_dir, char* modified_dir, short r,
short v, short d, char*, char*, char*);


/*********** MAIN ********************************************************/
int main(int argc, char ** argv)
{
  short recursive_flag = 0;
  int difference_flag = 0;
  int verbose_flag = 0;
  char * base_dir = NULL;
  char * modified_dir = NULL;

  /**1** 
    Process Command Line
   **1**/
  int errorInCmdLineProcess;

  errorInCmdLineProcess = 
    processCmdLine(argc, argv, &recursive_flag, &difference_flag, 
	&verbose_flag, &base_dir, &modified_dir );

  if (errorInCmdLineProcess != 0){
    exit(errorInCmdLineProcess);
  }
  if (verbose_flag == 1){
    printf("Base Dir: %s\n", base_dir);
    printf("Mod Dir: %s\n", modified_dir);
    printf(" RecurseFlag: %d\n", recursive_flag);
    printf(" DiffFlag: %d\n", difference_flag);
  }
  /**2**
    Verify Directories Given Are Accessible
   **2**/
  validate_directory(base_dir);
  validate_directory(modified_dir);

  /**3**
    Recurse Through Directories With opendir() and DIR struct
    print NEW, DELETED, and MODIFIED depending on stat structs
   **3**/
  compare_directories(base_dir, modified_dir, recursive_flag,
  verbose_flag, difference_flag, "", "DELETED", "MODIFIED");

  //Reverse order; missing files will be reported as 'NEW'
  compare_directories(modified_dir, base_dir, recursive_flag, 
  verbose_flag, difference_flag, "", "NEW","REVERTED");
  /*4* takes place inside compare_directories function
  */

if(verbose_flag == 1)
{
  printf(AC_GRN"\n^(;,;)^"AC_RESET); 
  printf("  COMPDIR COMPLETE  ");
  printf(AC_GRN"^(;,;)^\n"AC_RESET); 
}
  return 0;
}
/******* END OF MAIN **************************************************/


/*$$$ FUNCTION DEFINITIONS $$$*/

//Have to add extra level of indirection to change address of pointer
int processCmdLine(int argCount, char** argVector, short *recurse, 
    int *diffa, int *verbose, char** baseDir, char** modDir)
{
  int i;
  for (i = 1; i < argCount; i++)
  {
    //if first character in argv str is '-', options start with dash '-'
    if (argVector[i][0] == '-')
    {
      //2nd char of argument is 'r' or 'R'
      if (toupper(argVector[i][1]) == 'R')
      {
	*recurse = 1;
      }
      else if (toupper(argVector[i][1]) == 'V')
      {
	*verbose = 1;
      }
      else if (strcmp(argVector[i], "-D") == 0 || strcmp(argVector[i], "-d") == 0)
      {
	*diffa = 1;
      }else if (strcmp(argVector[i], "-?") == 0)
      {
	usage();
	extraUsage();
	return X_ABORT;
      }
      else
      {
	fprintf(stderr, "Error: Invalid Option %s\t\t(╯°_°)︵[_]\n\n", argVector[i]);
	usage();
	return E_INVALID_OPTION;
      }
    }else
    {
      //Arg is dir argument not an option
      if (*baseDir == NULL)
      {
	*baseDir = argVector[i];
      }
      else if (*modDir == NULL)
      {
	*modDir = argVector[i];
      }
      else 
      {
	fprintf(stderr, "Error: Too Many Arguments %s\t\t(╯°_°)︵[_]\n\n", argVector[i]);
	usage();
	return E_TOO_MANY_ARGS;

      }

    }
  }
  if (*baseDir == NULL || *modDir == NULL){
    fprintf(stderr, "Error: Not enough arguments\t\t(╯°_°)︵[_]\n\n");
    usage();
    return E_TOO_FEW_ARGS;
  }
  return 0;
}
//validate that name exists and is a directory
void validate_directory(char* name)
{
  struct stat s;
  //stat() returns 0 if file is found and was 'statted'
  if (stat(name, &s) == 0)
  { 
    if (S_ISDIR(s.st_mode) == 0)
    {
      //file is not directory
      printf("--File \"%s\" is NOT a directory\n",name);
      exit(errMsg("validate_directory()@->S_ISDIR fail",E_INVALID_ARG));
    }
  }else //file not found
  {
    char cwd[SRVR_PATH_SIZE];
    printf("--File \"%s\"\n--not found in current working dir: %s\n", name,getMYcwd(cwd));
    exit(errMsg("validate_directory()@->stat() fail",E_INVALID_ARG));
  }
}

/*return time stamp for file
  if file @name does not exist encode maximum time (-1) as retval
 */
time_t get_time_stamp(char* name)
{
  struct stat s;
  if(stat(name, &s) == 0)
  {
    /*file exists; extract time from stat struct*/
    time_t time_stamp = s.st_mtime;
    return time_stamp;
  }
  /*Could not stat() file*/
  return (time_t)-1;
}


//Use dirent*, directory entry pointer to compare normal files and 
//sub-directory normal files by time last modified and name.
/*
 * compare_directories
 */
void compare_directories(
char* base_dir, char* modified_dir, //command-line arguments that are directory name
short recurseFlag, //0 do not recurse into sub-dirs; 1 yes recurse into sub-dirs
short verboseFlag, //0 do not print program trace; 1 yes print messages along the way
short difFlag, //0 do not run diff on modified files; 1 run system(diff) on 2 files
char* pathname,
//print missing_label when a file is in the base_dir but not the modified_dir
char* missing_label,
/*print modified_label when a file in modified_dir has been touched more recently
  than a file of the same name in base_dir
*/
char* modified_label
)
{
  DIR * baseDIR = opendir(base_dir);
  if(baseDIR != NULL)
  {
    struct dirent * durr;
    while ((durr = readdir(baseDIR)) != NULL)
    {  
      if(verboseFlag == 1)
      {
          printf("found entry in base_dir: %s\n",durr->d_name);
      }
      //filter . and .. 
      if (strcmp(durr->d_name, ".") != 0 && strcmp(durr->d_name, "..") != 0)
      {
	//get type of file, 8 is file 'DT_REG'  4 is dir 'DT_DIR'
	if(durr->d_type == DT_REG)
	{
	  //check if this file is in the mod_dir
	  //Construct path to modified file:
	  char modified_file[STDIN_BUF_SIZE];
	  sprintf(modified_file, "%s/%s", modified_dir, durr->d_name);

	  time_t mod_stamp = get_time_stamp(modified_file);
	  if(verboseFlag == 1) {
	  printf("mod_stamp=%d, %s\n", mod_stamp, ctime(&mod_stamp));
	  }
	  if (mod_stamp != -1)
	  {  
	    /*file exists*/

	    char base_file[STDIN_BUF_SIZE];
	    sprintf(base_file, "%s/%s", base_dir, durr->d_name);
	    time_t base_stamp = get_time_stamp(base_file);
	    if (verboseFlag == 1)
	    {
	    printf("base_stamp=%d, %s\n", base_stamp, ctime(&mod_stamp));
	    }
	    if (base_stamp != -1)
	    {
	      /**4**
	        Print how files have been changed
	      **4**/
	      if (mod_stamp > base_stamp)
	      {
		//FILE HAS BEEN MODIFIED
		printf("%s%s %s\n", pathname, durr->d_name, modified_label);
		if (difFlag == 1)
		{
		  //print out diff using prettyprint.h
		  char diff_command[STDIN_BUF_SIZE];
		  sprintf(diff_command, "diff -us %s %s | %s",
		  base_file, modified_file, DIFF_SEDb);
		 system(diff_command);
		 fflush(stdout);
		  }
	      }
	    }else //time stamp BaseDir file fail
	    {
	      printf("TIME STAMP FAIL\n");
	    }
	  }else //file not in ModDir (or is unaccessible)
	  {

	    //file is in one dir but not the other
	    printf("%s%s %s\n", pathname, durr->d_name, missing_label);
	      

	  }
	}else if(durr->d_type == DT_DIR)
	{
	  //SUB_DIR LOCATED. Curse Again. Re-curse
	  if (recurseFlag == 1)
	  {
	    char b_sub_dir[SRVR_PATH_SIZE];
	    char m_sub_dir[SRVR_PATH_SIZE];
	    char sub_pathname[SRVR_PATH_SIZE];
	    //append sub-dir name onto filename path
	    sprintf(b_sub_dir, "%s/%s", base_dir, durr->d_name);
	    sprintf(m_sub_dir, "%s/%s", modified_dir, durr->d_name);
	    sprintf(sub_pathname, "%s%s/", pathname, durr->d_name);
	    //call this function again with sub_dirs as path
	    compare_directories(b_sub_dir, m_sub_dir, 
	    recurseFlag, verboseFlag, difFlag,
	    sub_pathname, missing_label, modified_label);
	  }

	}

      }
    }//end while
    closedir(baseDIR);
  }else
  {
    errMsg("failed to open base dir",E_OPENDIR_FAIL);
  }

}


//Print more advanced error messages, for users that fail in execution
//      instead of during cmdline processing
int errMsg(char* msg, int errCode){
  fprintf(stderr, "Error: %s\t\t(╯°o°)╯︵[x]\n\n",msg);
  //usage();
  return errCode;
}

//getcwd helper function
char* getMYcwd (char* buf){
  if (getcwd(buf, SRVR_PATH_SIZE) == NULL)
  {
    perror("getMYcwd@->getcwd() fail\n");
  }		        
  return buf;
}

//If user asks for help with -? option, give them extra information.
void extraUsage()
{
  printf(AC_CYN"\tCompare Directory\n"AC_RESET);
  printf("( ˘ ³˘)");
  printf(AC_RED"♥\t\t"AC_RESET);
  printf("(^_^ ");
  printf(AC_PRP"✿"AC_RESET);
  printf("}\n\n");
  printf("Run this:     ./compdir -R -D dir1 dir2\n\tFrom where both the dirs are in the current working directory\n\n~(˘--˘)\n");
  printf("MODIFIED FILES: New Dir has newer file with same name as file in Base Dir\n\n(@_-)~\n");
printf("REVERTED FILES: Base Dir has newer file with same name as file in New Dir\n\n(╥﹏╥)\n");
  printf("DELETED FILES:  New Dir missing file that Base Dir has\n\n(/.__.)/\n");
  printf("NEW FILES:      New Dir has files that Base Dir doesn't\n");
fflush(stdout);
}

//Ideas for further development of compdir:
/*
1) Document compare_directories better
2) Break up printing logic from time stamps into own function
3) Try a linked-list of DIR directory structs for fun
4) Further file options/handling
5) Print better output
*/
