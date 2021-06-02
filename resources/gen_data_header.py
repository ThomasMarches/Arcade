#!/usr/bin/env python3

from sys import argv
import re

if __name__ == '__main__':
    if len(argv) != 2:
        print("Wrong usage, try ./gen_data_header.py file")
        exit(84)
    with open(argv[1], 'rb') as f:
        out = open(argv[1] + '.h', 'w')

        encoded = []
        data = f.read()
        for c in data:
            c_hex = hex(c)[2:]
            if len(c_hex) == 1:
                c_hex = '0' + c_hex
            encoded.append(('\\x' + c_hex))

        out.write('''/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ''' + argv[1] + ''' header
*/

#ifndef ''' + re.sub(r'[^a-zA-Z]+', '', argv[1]).upper() + '''_H_
#define ''' + re.sub(r'[^a-zA-Z]+', '', argv[1]).upper() + '''_H_

static char const ''' + re.sub(r'[^a-zA-Z]+', '', argv[1]).upper() + '''[] = {\'''' + '\',\''.join(encoded) + '''\'};
static const int ''' + re.sub(r'[^a-zA-Z]+', '', argv[1]).upper() + '''_LENGTH = ''' + str(len(encoded)) + ''';

#endif /* !''' + re.sub(r'[^a-zA-Z]+', '', argv[1]).upper() + '''_H_ */''')