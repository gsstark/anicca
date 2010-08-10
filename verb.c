#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "anicca.h"
#include "char.h"
#include "error.h"
#include "memory.h"
#include "verb.h"
#include "verb-atomic.h"
#include "util.h"

MONAD(fact) { MONAD_PROLOG;
    I temp, r;
    ASSERT(AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, r = 1; temp = yv[i];
       DO(temp, r *= temp--);
       v[i] = r;
    );
    return z;
}

DYAD(outof) { DYAD_PROLOG;
    z = divide(fact(y), times(fact(x), fact(minus(y, x))));
    return z;
}

MONAD(tally) { MONAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    v = IAV(z); *v = AN(y);
    return z;
}

DYAD(copy) { DYAD_PROLOG;
    I n = 0, itm, cnt;
    ASSERT(xn==yn, ERLEN );
    DO(xn, n += xv[i]);
    z = gen_array(INT, AR(y), n, AS(y));
    v = IAV(z);
    DO(xn, cnt = xv[i]; itm = yv[i];
       if (cnt>0) { DO(cnt, *v++ = itm); }
    );
    return z;
}

MONAD(reciprocal) {
    I yn = AN(y), *yv = IAV(y); D *v; A z;
    ASSERT(AT(y)&INT, ERDOM)
    z = gen_array(FLT, AR(y), yn, AS(y));
    v = DAV(z);
    DO(yn, v[i] = 1/(D)yv[i]);
    return z;
}

DYAD(divide) { A z;
    ASSERT(AT(x)&NUMERIC&&AT(y)&NUMERIC, ERDOM);
    z = va2(CFWSL, x, y);
    return z;
}

MONAD(signum) { MONAD_PROLOG;
    I r;
    ASSERT(AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn,
       r = yv[i];
       v[i] = r > 0 ? 1 : r < 0 ? -1 : 0);
    return z;
}

DYAD(times) { A z;
    ASSERT(AT(x)&NUMERIC&&AT(y)&NUMERIC, ERDOM);
    z = va2(CSTAR, x, y);
    return z;
}

MONAD(square) { MONAD_PROLOG;
    ASSERT(AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, v[i] = yv[i] * yv[i]);
    return z;
}

MONAD(conjugate) { MONAD_PROLOG;
    return z;
}

DYAD(plus) { A z;
    ASSERT(AT(x)&NUMERIC&&AT(y)&NUMERIC, ERDOM);
    z = va2(CPLUS, x, y);
    return z;
}

MONAD(duble) { MONAD_PROLOG;
    ASSERT(AT(y)&INT, ERDOM);
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, v[i] = yv[i] + yv[i]);
    return z;
}

DYAD(append) {
    I xt = AT(x), yt = AT(y), xn = AN(x), yn = AN(y), zn = yn + xn, k;
    C *xv = CAV(x), *yv = CAV(y), *v;
    A z;
    if (xt==yt) {
        z = gen_array(yt, AR(y), zn, AS(y));
        v = CAV(z); k = type_size(yt);
        memcpy(v, xv, k*xn);
        v += k*xn;
        memcpy(v, yv, k*yn);
    } else { a_signal(ERDOM); }
    return z;
}

MONAD(negate) { MONAD_PROLOG;
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    DO(yn, v[i] = - yv[i]);
    return z;
}

DYAD(minus) { A z;
    ASSERT(AT(x)&NUMERIC&&AT(y)&NUMERIC, ERDOM);
    z = va2(CPLUS, x, y);
    return z;
}

DYAD(link) {
    A z; return z;
}

MONAD(box) {
    A z; return z;
}

DYAD(lthan) { A z;
    ASSERT(AT(x)&NUMERIC&&AT(y)&NUMERIC, ERDOM);
    z = va2(CPLUS, x, y);
    return z;
}

DYAD(equal) { A z;
    ASSERT(AT(x)&NUMERIC&&AT(y)&NUMERIC, ERDOM);
    z = va2(CPLUS, x, y);
    return z;
}

MONAD(unbox) {
    A z; return z;
}

DYAD(gthan) { A z;
    ASSERT(AT(x)&NUMERIC&&AT(y)&NUMERIC, ERDOM);
    z = va2(CPLUS, x, y);
    return z;
}

MONAD(roll) {
    A z; return z;
}

DYAD(deal) {
    A z; return z;
}

MONAD(indices) { MONAD_PROLOG;
    z = gen_array(INT, AR(y), yn, AS(y));
    v = IAV(z);
    return z;
}

MONAD(expntl) {
    I yn = AN(y), *yv = IAV(y);
    A z = gen_array(FLT, AR(y), yn, AS(y)); D *v = DAV(z);
    DO(yn, v[i] = exp((D)yv[i]));
    return z;
}

MONAD(iota) { MONAD_PROLOG;
    I n = yv[0];
    z = gen_array(INT, AR(y), n, AS(y));
    v = IAV(z);
    DO(n, v[i] = i);
    return z;
}

MONAD(same) {
    A z = y;
    return z;
}

DYAD(left) {
    A z = x;
    return z;
}

DYAD(right) {
    A z = y;
    return z;
}

DYAD(residue) {
    A z; return z;
}

MONAD(tail) { MONAD_PROLOG;
    z = gen_array(INT, 0, 1, NULL);
    *IAV(z) = yv[AN(y)-1];
    return z;
}
