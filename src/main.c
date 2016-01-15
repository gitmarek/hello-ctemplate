/*
The MIT License (MIT)
Copyright (c) 2016 <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "main.h"
#include "xmalloc.h"


void
print_help_page (void)
{
  printf("%s %s\n", PROGNAME, VERSION_STRING);
  printf("Usage: %s [OPTIONS] ARG1 [ARG2, ARG3, ...]\n", PROGNAME);
  printf("\n");
  printf("Options:\n");
  printf("  -h, --help          Print this help page and exit\n");
  printf("  -V, --version       Print version number and exit\n");
  printf("  -v, --verbose       Be more verbose\n");
  printf("\n");
  printf("Written by ?? and others, see ??.\n");
  printf("Report bugs to ??.\n");
  printf("\n");
  printf("License: MIT (see https://opensource.org/licenses/MIT).\n");
  printf("The software is provided \"as is\", without warranty of any kind.\n");
}

/* Flag set by ‘--verbose’. */
static int verbose_flag = 0;

int
main (int argc, char **argv)
{

#ifdef VERSION_MAJOR
    snprintf (VERSION_STRING, 22, "v%d.%d.%d-%s",
              VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH,
              VERSION_HASH);
#else // not VERSION_MAJOR
    snprintf (VERSION_STRING, 9, "(no git)");
#endif // not VERSION_MAJOR

  // Parse the command options
  int c;
  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"verbose", no_argument,       &verbose_flag, 1},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"add",     no_argument,       0, 'a'},
          {"append",  no_argument,       0, 'b'},
          {"delete",  required_argument, 0, 'd'},
          {"create",  required_argument, 0, 'c'},
          {"file",    required_argument, 0, 'f'},
          {"help",    no_argument,       0, 'h'},
          {"version", no_argument,       0, 'V'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "abc:d:f:hV",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'a':
          puts ("option -a\n");
          break;

        case 'b':
          puts ("option -b\n");
          break;

        case 'c':
          printf ("option -c with value `%s'\n", optarg);
          break;

        case 'd':
          printf ("option -d with value `%s'\n", optarg);
          break;

        case 'f':
          printf ("option -f with value `%s'\n", optarg);
          break;

        case 'h':
          print_help_page();
          return EXIT_SUCCESS;

        case 'V':
          printf ("%s-%s\n", PROGNAME, VERSION_STRING);
          return EXIT_SUCCESS;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Instead of reporting ‘--verbose’
     we report the final status resulting from them. */
  if (verbose_flag)
    puts ("verbose flag is set");

    // Print any remaining command line arguments (not options).
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  return EXIT_SUCCESS;
}
