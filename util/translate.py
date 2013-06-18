﻿#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Imports
import argparse
import os
import os.path

translations = {'cz': [('\\200', 'á'),
                       ('\\201', 'č'),
                       ('\\201', 'Č'),
                       ('\\202', 'é'),
                       ('\\203', 'ě'),
                       ('\\204', 'í'),
                       ('\\205', 'ó'),
                       ('\\206', 'ř'),
                       ('\\207', 'š'),
                       ('\\207', 'Š'),
                       ('\\210', 'ú'),
                       ('\\211', 'ů'),
                       ('\\212', 'ý'),
                       ('\\213', 'Á'),
                       ('\\214', 'Í'),
                       ('\\215', 'Ř'),
                       ('\\216', 'Ý'),
                       ('\\217', 'ž'),
                       ('\\217', 'Ž'),
                       ('\\220', 'É')],

                'de': [('\\200', 'Ä'),
                       ('\\201', 'ä'),
                       ('\\202', 'Ö'),
                       ('\\203', 'ö'),
                       ('\\204', 'Ü'),
                       ('\\205', 'ü'),
                       ('\\206', 'ß')],

                'es': [('\\200', 'Ñ'),
                       ('\\201', 'ñ')],

                'fr': [('\\200', 'é'),
                       ('\\201', 'è'),
                       ('\\202', 'à'),
                       ('\\203', 'î'),
                       ('\\204', 'ç')],

                'it': [('\\200', 'à'),
                       ('\\201', 'ù')],

                'pt': [('\\200', 'Á'),
                       ('\\201', 'á'),
                       ('\\202', 'Â'),
                       ('\\203', 'â'),
                       ('\\204', 'Ã'),
                       ('\\205', 'ã'),
                       ('\\206', 'À'),
                       ('\\207', 'à'),
                       ('\\210', 'Ç'),
                       ('\\211', 'ç'),
                       ('\\212', 'É'),
                       ('\\213', 'é'),
                       ('\\214', 'Ê'),
                       ('\\215', 'ê'),
                       ('\\216', 'Í'),
                       ('\\217', 'í'),
                       ('\\218', 'Ó'),
                       ('\\219', 'ó'),
                       ('\\220', 'Ô'),
                       ('\\221', 'ô'),
                       ('\\222', 'Õ'),
                       ('\\223', 'õ'),
                       ('\\224', 'Ú'),
                       ('\\225', 'ú'),],

                'se': [('\\200', 'å'),
                       ('\\201', 'ä'),
                       ('\\202', 'ö'),
                       ('\\203', 'Å'),
                       ('\\204', 'Ä'),
                       ('\\205', 'Ö')],
               }

# Take care of command line options
parser = argparse.ArgumentParser(description='Encoder for open9x translations')
parser.add_argument('input', action="store")
parser.add_argument('output', action="store")
parser.add_argument('language', action="store")
args =  parser.parse_args()

if args.language not in translations:
    parser.error(args.language  + ' is not a supported language. Try one of the supported ones: ' + str(translations.keys()))
    system.exit()
    
# Read the input file into a buffer
in_file = open( args.input, 'r')
text = in_file.read()
in_file.close()

# Do the replacements
for before, after in translations[args.language]:
    text = text.replace(after, before)
      
# Write the result to a temporary file
out_file = open( args.output, 'w')
out_file.write( text )
out_file.close()


