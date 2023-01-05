# 실습 1

import sys
import datetime

date = ['월요일', '화요일', '수요일', '목요일', '금요일', '토요일', '일요일']
dt = datetime.date(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))

print(date[dt.weekday()])
