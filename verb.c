#include <stdio.h>
#include <stdlib.h>

#include "anicca.h"
#include "memory.h"
#include "verb.h"
#include "util.h"

MONAD(fact) {
    MONAD_PROLOG;
    I n = yv[0], r = 1;
    z = gen_array(INT, 0, 1, NULL);
    v = (I *)AV(z);
    DO(n, r *= n--);
    *v = r;
    return z;
}

DYAD(outof) {
    DYAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    return z;
}

MONAD(conjugate) {
    MONAD_PROLOG;
    return z;
}

DYAD(plus) {
    DYAD_PROLOG;
    z = gen_array(INT, AR(y), yn, AS(y));
    v = (I *)AV(z);
    DO(yn, v[i] = xv[i] + yv[i]);
    return z;
}

MONAD(negate) {
    MONAD_PROLOG;
    z = gen_array(INT, AR(y), yn, AS(y));
    v = (I *)AV(z);
    DO(yn, v[i] = - yv[i]);
    return z;
}

DYAD(minus) {
    DYAD_PROLOG;
    z = gen_array(INT, AR(y), yn, AS(y));
    v = (I *)AV(z);
    DO(yn, v[i] = xv[i] - yv[i]);
    return z;
}

MONAD(iota) {
    MONAD_PROLOG;
    I n = yv[0];
    z = gen_array(INT, AR(y), n, AS(y));
    v = (I *)AV(z);
    DO(n, v[i] = i);
    return z;
}

MONAD(tail) {
    MONAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    *(I *)AV(z) = yv[AN(y)-1];
    return z;
}
