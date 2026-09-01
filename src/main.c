#include <stdio.h>

#include "artikel.h"
#include "kunde.h"


int main(void)
{
    artikelbestand_initialisieren();
    kundenbestand_initialisieren();


    Kunde *kunde =
        kunde_finden("1001");


    if (kunde != NULL)
    {
        printf(
            "%s %s\n",
            kunde->nummer,
            kunde->name
        );
    }


    return 0;
}
