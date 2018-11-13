import sys

f = open(sys.argv[1], "r")
test_number = sys.argv[2];
cnt = 1
for line in sys.stdin:
    myout = line.strip('\n').split(" ")
    p1 = int(myout[0])
    p2 = int(myout[1])
    line2 = f.readline()
    hisout = line2.strip('\n').split(" ")
    p3 = int(hisout[0])
    p4 = int(hisout[1])
    if (p1 != p3) or (p2 != p4):
        print("Wrong answer in crash " + str(cnt) + " in testcase " + str(test_number))
    cnt += 1
