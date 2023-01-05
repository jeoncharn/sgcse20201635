# 두 번째 실습

import sys

num = list(range(0, 11))

try:
    while True:
        index = int(input("Input index: "))
        if index >= len(num) or index < 0:
            raise ValueError
        print(num[index], "의 값을 갖고 있습니다.")

except IndexError:
    print("-1")

except ValueError:
    print("프로그램을 종료합니다.")
    sys.exit()
