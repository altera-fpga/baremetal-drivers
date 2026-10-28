/*
 * SPDX-FileCopyrightText: Copyright (C) 2025 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 *
 * Assembly routines for cache maintenance
 */


/* ---------------------------------------------
 * void cache_force_write_back(void *addr, size_t sz)
 * Function to force data writeback to cache
 * Out : void.
 * Clobber list : x0-x9
 * ---------------------------------------------
 */
.globl cache_force_write_back

/* ---------------------------------------------
 * void cache_force_invalidate(void *addr, size_t sz)
 * Function to force cache invalidation
 * Out : void.
 * Clobber list : x0-x9
 * ---------------------------------------------
 */
.globl cache_force_invalidate

/* ---------------------------------------------
 * void cache_flush(void *addr, size_t sz)
 * Function to flush the cache
 * Out : void.
 * Clobber list : x0-x9
 * ---------------------------------------------
 */
.global cache_flush

cache_force_write_back:
    ADD x1, x1, x0
    MRS x2, CTR_EL0
    UBFX x3, x2, #16, #4
    LDR x2, =4
    LSL x3, x2, x3
    CMP x3, #0
    B.EQ writebackCache_end
    SUBS x4, x3, #1
    MVN x4,x4
    AND x0, x0, x4

writebackCache_mem:
    CMP x0, x1
    B.GT writebackCache_end
    DC CVAC, x0
    ADD x0, x0, x3
    B writebackCache_mem

writebackCache_end:
    RET

cache_force_invalidate:
    ADD x1, x1, x0
    MRS x2, CTR_EL0
    UBFX x3, x2, #16, #4
    LDR x2, =4
    LSL x3, x2, x3
    CMP x3, #0
    B.EQ invalidateCache_end
    SUBS x4, x3, #1
    MVN x4,x4
    AND x0, x0, x4

invalidateCache_mem:
    CMP x0, x1
    B.GT invalidateCache_end
    DC IVAC, x0
    ADD x0, x0, x3
    B invalidateCache_mem

invalidateCache_end:
    RET

cache_flush:
    ADD x1, x1, x0
    MRS x2, CTR_EL0
    UBFX x3, x2, #16, #4
    LDR x2, =4
    LSL x3, x2, x3
    CMP x3, #0
    B.EQ flushCache_end
    SUBS x4, x3, #1
    MVN x4,x4
    AND x0, x0, x4

flushCache_mem:
    CMP x0, x1
    B.GT flushCache_end
    DC CIVAC, x0
    ADD x0, x0, x3
    B flushCache_mem

flushCache_end:
    RET

.end

/*Data cache maintainance instruction DC
 *
 * DC <dc_op>, Xt
 *  Xt      -> address argument
 *  <dc_op> -> opeartion
 *      <dc_op>    = <function><type>{<point>}
 *      <function> = “I” (invalidate) | “C” (clean) | “CI” (clean & invalidate) | “Z” (zero)
 *      <type>     = “VA” (by virtual address) | “SW” (by set/way)
 *      <point>    = “C” (to point of coherency) | “U” (to point of unification)
 */

