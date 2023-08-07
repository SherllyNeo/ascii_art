# A simple ascii art app

useage

--help for help

--random for some random art

--select for selection menu



json_format 
'''{json}
{"ASCII_ART_OBJECTS": [
    {
        "art": "@-->--->---",
        "desc": "Rose",
        "category": "ascii-one-line",
        "width": 11,
        "height": 1
    },
    {
        "art": ">>------>",
        "desc": "Arrow",
        "category": "ascii-one-line",
        "width": 9,
        "height": 1
    }]}
'''

bash that turns input file $1, to a header to be compiled by C
'''{bash}
cat $1 > art; xxd -i art | tac | sed "3s/$/, 0x00/" | tac > src_files/art.h; rm art;
'''


credit to 
mini_json library https://minijson.readthedocs.io/en/latest/index.html

and 
https://github.com/asweigart/asciiartjsondb for the ascii art
