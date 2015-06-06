def main(argv):
    output = argv + '.bkp'
    inlet = open(argv, 'r')
    outlet = open(output, 'w')

    for line in inlet:
        outlet.write(line)

    inlet.close()
    outlet.close()

while True:
    try:
        main(raw_input())
    except:
        break
