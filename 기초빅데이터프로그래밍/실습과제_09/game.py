# 실습 2-4
import random

arr = ['가위', '바위', '보']

choice = input("가위, 바위, 보 중 하나를 선택하시오: ")
print("플레이어:", choice)

computer_choice = arr[random.randint(0,2)]
print("컴퓨터:", computer_choice)

if choice == computer_choice:
    print("비겼습니다.")

elif choice == '가위' and computer_choice == '보':
    print("당신이 이겼습니다.")
    
elif chioce == '가위' and computer_choice == '바위':
    print("컴퓨터가 이겼습니다.")
    
elif choice == '바위' and computer_choice == '가위':
    print("당신이 이겼습니다.")
    
elif chioce == '바위' and computer_choice == '보':
    print("컴퓨터가 이겼습니다.")
    
elif choice == '보' and computer_choice == '바위':
    print("당신이 이겼습니다.")
    
elif chioce == '보' and computer_choice == '가위':
    print("컴퓨터가 이겼습니다.")
