
#x를 거꾸로 출력하는 함수이다.
def inverse(x):
    return x[::-1]

#input 함수는 기본적으로 string 형태로 입력을 받으며, int() 등의 형변환이 가능하다.
input_string = input("Input :")

#range(0, k)는 0~k-1을 원소로 가지는 배열을 reuturn해준다.
for i in range(0, len(input_string)):
    #list[i:j]는 list의 i~j-1까지의 원소를 return해준다.
    print(inverse(input_string[0:i+1]))
