
#include "main.h"

// $Id: display.c 311 2011-06-15 22:39:59Z jessekornblum $

static void display_banner(state *s)
{
  int argc;
  size_t bytes_written, current_bytes;
  hashname_t i;
  
  print_status("%s", HASHDEEP_HEADER_10);

  fprintf (stdout,"%ssize,",HASHDEEP_PREFIX);  
  for (i = 0 ; i < NUM_ALGORITHMS ; ++i)
  {
    if (s->hashes[i]->inuse)
      printf ("%s,", s->hashes[i]->name);
  }  
  print_status("filename");

  fprintf(stdout,"## Invoked from: ");
  display_filename(stdout,s->cwd);
  fprintf(stdout,"%s",NEWLINE);
  
  // Display the command prompt as the user saw it
  fprintf(stdout,"## ");
#ifdef _WIN32
  fprintf(stdout,"%c:\\>", s->cwd[0]);
#else
  if (0 == geteuid())
    fprintf(stdout,"#");
  else
    fprintf(stdout,"$");
#endif

  // Accounts for '## ', command prompt, and space before first argument
  bytes_written = 8;

  for (argc = 0 ; argc < s->argc ; ++argc)
  {
    fprintf(stdout," ");
    bytes_written++;

    current_bytes = _tcslen(s->argv[argc]);

    // The extra 32 bytes is a fudge factor
    if (current_bytes + bytes_written + 32 > MAX_STRING_LENGTH)
    {
      fprintf(stdout,"%s## ", NEWLINE);
      bytes_written = 3;
    }

    display_filename(stdout,s->argv[argc]);
    bytes_written += current_bytes;
  }

  fprintf(stdout,"%s## %s",NEWLINE, NEWLINE);

  s->banner_displayed = TRUE;
}


int display_hash_simple(state *s)
{
  hashname_t i;

  if ( ! (s->banner_displayed))
    display_banner(s);

  // In piecewise mode the size of each 'file' is the size
  // of the block it came from. This is important when doing an
  // audit in piecewise mode. In all other cases we use the 
  // total number of bytes from the file we *actually* read
  if (s->mode & mode_piecewise)
    printf ("%"PRIu64",", s->bytes_read);
  else
    printf ("%"PRIu64",", s->actual_bytes);

  for (i = 0 ; i < NUM_ALGORITHMS ; ++i)
  {
    if (s->hashes[i]->inuse)
      printf("%s,", s->current_file->hash[i]);
  }
  
  display_filename(stdout,s->current_file->file_name);
  fprintf(stdout,"%s",NEWLINE);

  return FALSE;
}


// This function is called by hash.c when the hashing operation is complete.
int display_hash(state *s)
{
  if (NULL == s)
    return TRUE;

  switch (s->primary_function)
    {
    case primary_compute: 
      return display_hash_simple(s);

    case primary_match: 
    case primary_match_neg: 
      return display_match_result(s);

    case primary_audit: 
      return audit_update(s);
    }

  return FALSE;
}
