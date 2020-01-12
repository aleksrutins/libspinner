/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Brian J. Downs
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _SPINNER_H
#define _SPINNER_H

#include <pthread.h>
#include <stdint.h>
#include <sys/types.h>

/*
 * maximun number of characters in an array
 * of indicators.
 */
#ifndef MAX_CHARS
#define MAX_CHARS 1024
#endif

/*
 * char_sets is the collection of spinners.
 */
extern char *char_sets[][MAX_CHARS];

/*
 * spinner_t maintains the state of the spinner
 * and allows for control.
 */
typedef struct
{
    uint8_t char_set_id;
    uint64_t delay;
    pthread_mutex_t mu;
    FILE* output_dst;
    char* prefix;
    char* suffix;
    char* final_msg;
    char* last_output;
    int active;
    int reversed;
} spinner_t;

/*
 * spinner_new creates a new pointer to a spinner_t
 * struct and sets sane defaults for immediate use.
 */
spinner_t*
spinner_new(const int id);

/*
 * spinner_free frees the used memory of the
 * spinner_t pointer.
 */
void
spinner_free(spinner_t *s);

/*
 * spinner_start starts the spinner.
 */
void
spinner_start(spinner_t *s);

/*
 * spinner_stop stops the spinner.
 */
void
spinner_stop(spinner_t *s);

/*
 * spinner_restart will restart the spinner.
 */
void
spinner_restart(spinner_t *s);

/*
 * spinner_char_set_update updates the character
 * set with the new given one.
 */
void
spinner_char_set_update(spinner_t *s, const int id);

/*
 * spinner_update_speed updates the speed at which
 * the spinner is spinning.
 */
void
spinner_update_speed(spinner_t *s, const uint64_t delay);

/*
 * spinner_set_output_dest sets the file descriptor to
 * write spinner output to.
 */
void
spinner_set_output_dest(spinner_t *s, FILE *fd);

/*
 * spinner_reverse reverses the direction of the spinner.
 */
void
spinner_reverse(spinner_t *s);

#endif
