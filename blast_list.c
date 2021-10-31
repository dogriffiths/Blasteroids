#include <stdlib.h>
#include "blast_list.h"

//region BlastList
Node* fireBlast(Ship *s, Node* startOfBlastList) {
    Blast *blast = malloc(sizeof(*blast));

    blast->x = (*s).x;
    blast->y = (*s).y;
    blast->heading = (*s).heading;
    blast->speed = 20.0f;

    return insertBefore(blast, startOfBlastList);
}
//endregion

