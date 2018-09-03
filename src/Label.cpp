#include <cstring>
#include <cstdlib>
#include "../include/Label.hpp"

Label::Label() : count(0){} 


int Label::find(const char *label) const
{
    for (int i = 0; i < count; i++)
        if (strcmp(addresses[i].get_info(), label) == 0)
            return addresses[i].get_address();

    cerr << label << " not found!\n";
    exit(1); // SO DANGEROUS TO CONTINUE PAST HERE!
}

istream &operator>>(istream &is, Label &lbls)
{
    char line[256], *ptr;
    int address = 100;
    lbls.count = 0;

    // Seeking through the file
    while (is.getline(line, 256))
    {
        // Seeks for horizontal tabs and replaces them with space characters
        for (ptr = strchr(line, '\t'); ptr; ptr = strchr(line, '\t'))
        {
            *ptr = ' ';
        }

        // Skipping occasional spaces
        for (ptr = line; *ptr == ' '; ptr++)
            ;

        // Did it hit a label/directive?
        if (*ptr == '.' || *ptr == '_' || strchr(ptr, ':'))
        {
            if (line[strlen(line) - 1] == ':' || strstr(line, "main:"))
            {
                lbls.addresses[lbls.count].set_address(address);

                // Getting rid of the colon
                *(strchr(ptr, ':')) = '\0';

                // Stores it
                lbls.addresses[lbls.count++].set_info(ptr);
            }
        }
        else
            address += 4; // No main, label or directive
    }

    return is;
}