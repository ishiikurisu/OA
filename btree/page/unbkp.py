import os

def main(argv):
    dot = '.'
    data = argv.split(dot)
    output = data[0] + dot + data[1]
    command = 'copy %s %s' % (argv, output)
    os.system(command)

while True:
    try:
        main(raw_input())
    except:
        break
