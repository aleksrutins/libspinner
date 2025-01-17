/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2021 Brian J. Downs
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * maximun number of characters in an array
 * of indicators.
 */
#define MAX_CHARS 1024

/*
 * toggle the cursor on and off.
 */
#define CURSOR_STATE(x)        \
    switch (x) {               \
        case 0:                \
            printf("\e[?25l"); \
            break;             \
        case 1:                \
            printf("\e[?25h"); \
            break;             \
    }                          \
    fflush(stdout);

/*
 * char_sets is the collection of spinners.
 */
static char* char_sets[][MAX_CHARS] = {
    { "←", "↖", "↑", "↗", "→", "↘", "↓", "↙" },
    { "▁", "▃", "▄", "▅", "▆", "▇", "█", "▇", "▆", "▅", "▄", "▃", "▁" },
    { "▖", "▘", "▝", "▗" },
    { "┤", "┘", "┴", "└", "├", "┌", "┬", "┐" },
    { "◢", "◣", "◤", "◥" },
    { "◰", "◳", "◲", "◱" },
    { "◴", "◷", "◶", "◵" },
    { "◐", "◓", "◑", "◒" },
    { ".", "o", "O", "@", "*" },
    { "|", "/", "-", "\\" },
    { "◡◡", "⊙⊙", "◠◠" },
    { "⣾", "⣽", "⣻", "⢿", "⡿", "⣟", "⣯", "⣷" },
    { ">))'>", " >))'>", "  >))'>", "   >))'>", "    >))'>", "   <'((<", "  <'((<", " <'((<" },
    { "⠁", "⠂", "⠄", "⡀", "⢀", "⠠", "⠐", "⠈" },
    { "⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏" },
    { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
      "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" },
    { "▉", "▊", "▋", "▌", "▍", "▎", "▏", "▎", "▍", "▌", "▋", "▊", "▉" },
    { "■", "□", "▪", "▫" },
    { "←", "↑", "→", "↓" },
    { "╫", "╪" },
    { "⇐", "⇖", "⇑", "⇗", "⇒", "⇘", "⇓", "⇙" },
    { "⠁", "⠁", "⠉", "⠙", "⠚", "⠒", "⠂", "⠂", "⠒", "⠲", "⠴", "⠤", "⠄", "⠄", "⠤",
      "⠠", "⠠", "⠤", "⠦", "⠖", "⠒", "⠐", "⠐", "⠒", "⠓", "⠋", "⠉", "⠈", "⠈" },
    { "⠈", "⠉", "⠋", "⠓", "⠒", "⠐", "⠐", "⠒", "⠖", "⠦", "⠤", "⠠",
      "⠠", "⠤", "⠦", "⠖", "⠒", "⠐", "⠐", "⠒", "⠓", "⠋", "⠉", "⠈" },
    { "⠁", "⠉", "⠙", "⠚", "⠒", "⠂", "⠂", "⠒", "⠲", "⠴", "⠤", "⠄",
      "⠄", "⠤", "⠴", "⠲", "⠒", "⠂", "⠂", "⠒", "⠚", "⠙", "⠉", "⠁" },
    { "⠋", "⠙", "⠚", "⠒", "⠂", "⠂", "⠒", "⠲", "⠴", "⠦", "⠖", "⠒", "⠐", "⠐", "⠒", "⠓", "⠋" },
    { "ｦ", "ｧ", "ｨ", "ｩ", "ｪ", "ｫ", "ｬ", "ｭ", "ｮ", "ｯ", "ｱ", "ｲ", "ｳ", "ｴ", "ｵ", "ｶ", "ｷ", "ｸ", "ｹ",
      "ｺ", "ｻ", "ｼ", "ｽ", "ｾ", "ｿ", "ﾀ", "ﾁ", "ﾂ", "ﾃ", "ﾄ", "ﾅ", "ﾆ", "ﾇ", "ﾈ", "ﾉ", "ﾊ", "ﾋ", "ﾌ",
      "ﾍ", "ﾎ", "ﾏ", "ﾐ", "ﾑ", "ﾒ", "ﾓ", "ﾔ", "ﾕ", "ﾖ", "ﾗ", "ﾘ", "ﾙ", "ﾚ", "ﾛ", "ﾜ", "ﾝ" },
    { ".", "..", "..." },
    { "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█", "▉", "▊", "▋", "▌", "▍", "▎", "▏",
      "▏", "▎", "▍", "▌", "▋", "▊", "▉", "█", "▇", "▆", "▅", "▄", "▃", "▂", "▁" },
    { ".", "o", "O", "°", "O", "o", "." },
    { "+", "x" },
    { "v", "<", "^", ">" },
    { ">>--->",
      " >>--->",
      "  >>--->",
      "   >>--->",
      "    >>--->",
      "    <---<<",
      "   <---<<",
      "  <---<<",
      " <---<<",
      "<---<<" },
    { "|",
      "||",
      "|||",
      "||||",
      "|||||",
      "|||||||",
      "||||||||",
      "|||||||",
      "||||||",
      "|||||",
      "||||",
      "|||",
      "||",
      "|" },
    { "[          ]",
      "[=         ]",
      "[==        ]",
      "[===       ]",
      "[====      ]",
      "[=====     ]",
      "[======    ]",
      "[=======   ]",
      "[========  ]",
      "[========= ]",
      "[==========]" },
    { "(*---------)",
      "(-*--------)",
      "(--*-------)",
      "(---*------)",
      "(----*-----)",
      "(-----*----)",
      "(------*---)",
      "(-------*--)",
      "(--------*-)",
      "(---------*)" },
    { "█▒▒▒▒▒▒▒▒▒", "███▒▒▒▒▒▒▒", "█████▒▒▒▒▒", "███████▒▒▒", "██████████" },
    { "[                    ]",
      "[=>                  ]",
      "[===>                ]",
      "[=====>              ]",
      "[======>             ]",
      "[========>           ]",
      "[==========>         ]",
      "[============>       ]",
      "[==============>     ]",
      "[================>   ]",
      "[==================> ]",
      "[===================>]" },
    { "🌍", "🌎", "🌏" },
    { "◜", "◝", "◞", "◟" },
    { "⬒", "⬔", "⬓", "⬕" },
    { "⬖", "⬘", "⬗", "⬙" },
    { "[>>>          >]",
      "[]>>>>        []",
      "[]  >>>>      []",
      "[]    >>>>    []",
      "[]      >>>>  []",
      "[]        >>>>[]",
      "[>>          >>]" },
    { "♠", "♣", "♥", "♦" },
    { "➞", "➟", "➠", "➡", "➠", "➟" },
    { "  |  ", " \\   ", "_    ", " \\   ", "  |  ", "   / ", "    _", "   / " },
    { "  . . . .", ".   . . .", ". .   . .", ". . .   .", ". . . .  ", ". . . . ." },
    { " |     ", "  /    ", "   _   ", "    \\  ", "     | ", "    \\  ", "   _   ", "  /    " },
    { "⎺", "⎻", "⎼", "⎽", "⎼", "⎻" },
    { "▹▹▹▹▹", "▸▹▹▹▹", "▹▸▹▹▹", "▹▹▸▹▹", "▹▹▹▸▹", "▹▹▹▹▸" },
    { "[    ]", "[   =]", "[  ==]", "[ ===]", "[====]", "[=== ]", "[==  ]", "[=   ]" },
    { "( ●    )", "(  ●   )", "(   ●  )", "(    ● )", "(     ●)", "(    ● )", "(   ●  )", "(  ●   )", "( ●    )" },
    { "✶", "✸", "✹", "✺", "✹", "✷" },
    { "▐|\\____________▌", "▐_|\\___________▌", "▐__|\\__________▌", "▐___|\\_________▌", "▐____|\\________▌",
      "▐_____|\\_______▌", "▐______|\\______▌", "▐_______|\\_____▌", "▐________|\\____▌", "▐_________|\\___▌",
      "▐__________|\\__▌", "▐___________|\\_▌", "▐____________|\\▌", "▐____________/|▌",  "▐___________/|_▌",
      "▐__________/|__▌",  "▐_________/|___▌",  "▐________/|____▌",  "▐_______/|_____▌",  "▐______/|______▌",
      "▐_____/|_______▌",  "▐____/|________▌",  "▐___/|_________▌",  "▐__/|__________▌",  "▐_/|___________▌",
      "▐/|____________▌" },
    { "▐⠂       ▌", "▐⠈       ▌", "▐ ⠂      ▌", "▐ ⠠      ▌", "▐  ⡀     ▌", "▐  ⠠     ▌", "▐   ⠂    ▌", "▐   ⠈    ▌",
      "▐    ⠂   ▌", "▐    ⠠   ▌", "▐     ⡀  ▌", "▐     ⠠  ▌", "▐      ⠂ ▌", "▐      ⠈ ▌", "▐       ⠂▌", "▐       ⠠▌",
      "▐       ⡀▌", "▐      ⠠ ▌", "▐      ⠂ ▌", "▐     ⠈  ▌", "▐     ⠂  ▌", "▐    ⠠   ▌", "▐    ⡀   ▌", "▐   ⠠    ▌",
      "▐   ⠂    ▌", "▐  ⠈     ▌", "▐  ⠂     ▌", "▐ ⠠      ▌", "▐ ⡀      ▌", "▐⠠       ▌" },
    { "?", "¿" },
    { "⢹", "⢺", "⢼", "⣸", "⣇", "⡧", "⡗", "⡏" },
    { "⢄", "⢂", "⢁", "⡁", "⡈", "⡐", "⡠" },
    { ".  ", ".. ", "...", " ..", "  .", "   " },
    { ".", "o", "O", "°", "O", "o", "." },
    { "▓", "▒", "░" },
    { "▌", "▀", "▐", "▄" },
    { "⊶", "⊷" },
    { "▪", "▫" },
    { "□", "■" },
    { "▮", "▯" },
    { "-", "=", "≡" },
    { "d", "q", "p", "b" },
    { "∙∙∙", "●∙∙", "∙●∙", "∙∙●", "∙∙∙" },
    { "🌑 ", "🌒 ", "🌓 ", "🌔 ", "🌕 ", "🌖 ", "🌗 ", "🌘 " },
    { "☗", "☖" },
    { "⧇", "⧆" },
    { "◉", "◎" },
    { "㊂", "㊀", "㊁" },
    { "⦾", "⦿" },
    { "ဝ", "၀" },
    { "▌", "▀", "▐▄" }
};

/*
 * spinner_t maintains the state of the spinner
 * and allows for control. The library methods 
 * should be used to update values on this data
 * to avoid potential races. This memory needs
 * to be freed by the caller.
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
    uint8_t active;
    uint8_t reversed;
} LibspinnerSpinner;

/*
 * spinner_new creates a new pointer to a spinner_t
 * struct and sets sane defaults for immediate use.
 */
LibspinnerSpinner*
libspinner_spinner_new(const int id)
{
    LibspinnerSpinner *s = malloc(sizeof(LibspinnerSpinner));
    s->char_set_id = id;
    s->output_dst = stdout;
    s->prefix = "";
    s->suffix = "";
    s->final_msg = "";
    s->active = 0;
    return s;
}

/*
 * spinner_free frees the used memory of the
 * spinner_t pointer.
 */
void
libspinner_spinner_free(LibspinnerSpinner *s)
{
    if (s) {
        free(s);
    }
    return;
}

/*
 * spinner_state safely checks the state of the
 * spinner by aquiring a lock and returning the
 * current state.
 */
static uint8_t
libspinner_spinner_state(LibspinnerSpinner *s)
{
    uint8_t state;
    pthread_mutex_lock(&s->mu);
    state = s->active;
    pthread_mutex_unlock(&s->mu);
    return state;
}

/*
 * spin is run in a pthread and is responsible for
 * iterating across the selected character set and
 * printing the character to screen.
 */
static void*
libspinner_spin(void *arg)
{
    LibspinnerSpinner *s = (LibspinnerSpinner*)arg;
    int i = 0;
    while(true) {
        // check if we're reached an index with no string. If
        // we have, reset the counter and start again.
        if (!char_sets[s->char_set_id][i]) {
            i = -1;
            continue;
        }
        char output[MAX_CHARS * 4];
        sprintf(output, "\r%s%s%s", s->prefix, char_sets[s->char_set_id][i], s->suffix);
        s->last_output = output;
        fprintf(s->output_dst, "%s", output);
        fflush(stdout);
        printf("%c[2K", 27);
        usleep(s->delay);
        i++;
    }
    return NULL;
}

/*
 * spinner_start starts the spinner.
 */
void
libspinner_spinner_start(LibspinnerSpinner *s)
{
    if (s->active > 0) {
        return;
    }
    pthread_mutex_lock(&s->mu);
    CURSOR_STATE(0);
    pthread_t spin_thread;
    pthread_mutex_unlock(&s->mu);
    if (pthread_create(&spin_thread, NULL, libspinner_spin, s)) {
        fprintf(stderr, "error creating thread\n");
        return;
    }
    s->active = 1;
}

/*
 * spinner_stop stops the spinner.
 */
void
libspinner_spinner_stop(LibspinnerSpinner *s)
{
    pthread_mutex_lock(&s->mu);
    s->active = 0;
    pthread_mutex_unlock(&s->mu);
    if (strlen(s->final_msg) > 0) {
        printf("%s", s->final_msg);
    }
    CURSOR_STATE(1);
}

/*
 * spinner_restart will restart the spinner.
 */
void
libspinner_spinner_restart(LibspinnerSpinner *s)
{
    libspinner_spinner_stop(s);
    libspinner_spinner_start(s);
}

/*
 * spinner_char_set_update updates the character
 * set with the new given one.
 */
void
libspinner_spinner_char_set_update(LibspinnerSpinner *s, const int id)
{
    pthread_mutex_lock(&s->mu);
    s->char_set_id = id;
    pthread_mutex_unlock(&s->mu);
}

/*
 * spinner_update_speed updates the speed at which
 * the spinner is spinning.
 */
void
libspinner_spinner_update_speed(LibspinnerSpinner *s, const uint64_t delay)
{
    pthread_mutex_lock(&s->mu);
    s->delay = delay;
    pthread_mutex_unlock(&s->mu);
}

/*
 * spinner_set_output_dest sets the file descriptor to
 * write spinner output to.
 */
void
libspinner_spinner_set_output_dest(LibspinnerSpinner *s, FILE *fd)
{
    pthread_mutex_lock(&s->mu);
    s->output_dst = fd;
    pthread_mutex_unlock(&s->mu);
}

/*
 * spinner_reverse reverses the direction of the spinner.
 */
void
libspinner_spinner_reverse(LibspinnerSpinner *s)
{
    pthread_mutex_lock(&s->mu);
    if (s->reversed == 0) {
        s->reversed = 1;
    }
    size_t n = sizeof(char_sets[s->char_set_id]) / sizeof(char_sets[s->char_set_id][0]) - 1;
    int j = 0;
    while (n > j) {
        if (char_sets[s->char_set_id][n] == NULL) {
            n--;
            j++;
            continue;
        }
        char* temp = char_sets[s->char_set_id][n];
        char_sets[s->char_set_id][n] = char_sets[s->char_set_id][j];
        char_sets[s->char_set_id][j] = temp;
        n--;
        j++;
    }
    pthread_mutex_unlock(&s->mu);
    libspinner_spinner_restart(s);
}

#endif
