import sys
f = open(sys.argv[1], "r")
test_number = sys.argv[2]
for line in sys.stdin:
    myout = line.strip('\n').split(" ")
    myout = int(myout[0])
    line2 = f.readline()
    hisout = line2.strip('\n').split(" ")
    hisout = int(hisout[0])
    if (myout != hisout):
        print("Wrond answer in testace " + str(test_number))
