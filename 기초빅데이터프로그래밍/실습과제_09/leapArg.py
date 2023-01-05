# 실습 2-2

import sys
import datetime

#윤년인지 아닌지를 파악하는 함수이다.
def is_leap(year):
    #400으로 나누어지는 해는 윤년이다.
    if year%400 == 0:
        return True
    
    #100으로 나누어지는 해는 윤년이 아니다.
    elif year%100 == 0:
        return False
    
    #4로 나누어지는 해는 윤년이다.
    elif year%4 == 0:
        return True
    
    else:
        return False
        

#년, 월, 일에 따라 요일, 혹은 False를 return하는 함수이다.
def get_day_name(year, month, day):
    #2월 29일이며 윤년이 아닌 경우, return False를 수행한다.
    #이외의 경우, return "_요일" 을 수행한다.
    
    #총 일수를 세는 변수이다.
    day_count = 0
    day_per_month = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    date = ["월", "화", "수", "목", "금", "토", "일"]
    
    if is_leap(year) == False:
        if month==2 and day == 29:
            return False
    
    #요일을 계산한다.
    #year에 의한 일수를 계산한다.
    for i in range(1, year):
        if is_leap(i) == True:
            day_count += 366
        else:
            day_count += 365
    
    #month에 의한 일수를 계산한다.
    for i in range(1, month):
        day_count += day_per_month[i]
        if i == 2 and is_leap(year) == True:
            day_count += 1
    
    #day에 의한 일수를 계산한다.
    day_count += (day - 1) #1일부터 시작하므로, 1을 빼준다.
    
    #총 day_count를 7로 나누어서 date를 통해 무슨 요일인지 파악한다.
    return date[day_count%7] + "요일"


if __name__ == "__main__":
    
    year, month, day = int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3])
    day_name = get_day_name(year, month, day)
    if day_name == False:
        print("입력하신 날짜는 존재하지 않습니다.")
    else:
        print(day_name)
        if is_leap(year) == True:
            print("입력하신 %s은 윤년입니다" % year)
