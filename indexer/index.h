#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
/**
A function which takes a source file, loads up its index, goes to the desired line
and fetches the line from the source file.
@param source_file  The input file
@param index_file   The generated index_file
@param desired_line The desired line
*/

char * read_from_index(FILE *source_file, FILE *index_file, long desired_line) {
  long line_number = 0;
  long begin;
  long end;
  struct stat st;
  /*
    For each line in the source file, a tuple of three 32 bit longs are stored
      -> [line_number, begin, end].
   */

  fstat(fileno(index_file), &st);
  long size = st.st_size;
  long to_seek = desired_line*3*sizeof(line_number);
  //printf("%ld %ld\n", to_seek, size );
  if (to_seek > size){
    //printf("Greater\n");
    return NULL;
  }

  fseek(index_file, to_seek, SEEK_SET);

  fread(&line_number,sizeof(line_number),1,index_file);
  fread(&begin,sizeof(begin),1,index_file);
  fread(&end,sizeof(end),1,index_file);


  // Seek to the begin in the source file.
  fseek(source_file, begin, SEEK_SET);

  char * buf = malloc(sizeof(char) * (end -begin));
  buf[0] = '\0';
  fread(buf, end - begin, 1, source_file);
  buf[strlen(buf)] = '\0';
  //printf("%s", buf);
  return buf;

}



/**
A function which builds an index file for a given source file
@param source_file The input file
@param target_file The file to which index is saved
*/
int make_index_from_file(char const *source_file, char const *target_file, int visual) {
  FILE * fp, * op;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  long line_number = 0;
  long total_size_read = 0;

  fp = fopen(source_file, "r");
  remove(target_file);
  op = fopen(target_file, "a");

  if (fp == NULL)
  return -200; /* A Custom error for informing that, your file does not exist*/

  while ((read = getline(&line, &len, fp)) != -1) {
    //printf("%d %zu %zu\n", line_number, total_size_read, total_size_read + read);
    fwrite(&line_number, sizeof(line_number), 1, op);
    fwrite(&total_size_read, sizeof(total_size_read), 1, op);
    total_size_read += read;
    fwrite(&total_size_read, sizeof(total_size_read), 1, op);

    // if (visual && ((line_number % 1000) == 0)){
    //   printf("\r%d", line_number);
    // }
    line_number++;

  }
  fclose(fp);

  if (line)
  free(line);

  return 0;
}
