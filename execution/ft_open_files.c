

#include "execution.h"

int open_outfiles(char *outfile, int append)
{
    int outf_fd;
    
    if (append == 1)
        outf_fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else
        outf_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outf_fd < 0)
    {
        perror("Error opening output file");
        exit(1);
    }
    return (outf_fd);
}

int open_infile(char *infile)
{
    int inf_fd;

    inf_fd = open(infile, O_RDONLY);
    if (inf_fd < 0)
    {
        perror("Error opening input file");
        inf_fd = open("/dev/null", O_RDONLY);
        if (inf_fd < 0)
            exit(1);
    }
    return (inf_fd);
}
