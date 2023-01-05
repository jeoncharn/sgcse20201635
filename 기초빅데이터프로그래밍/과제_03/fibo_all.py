# 간단한 방법 (재귀함수를 통해서 간단하게 구현할 수 있다.)
def fibo_1(num):
    if num<=1:
        return num
    else:
        return fibo_1(num-1) + fibo_1(num-2)
    
    
# loop를 이용한 방법 (피보나치 수를 구하는 데에 걸리는 시간을 줄여준다.)
def fibo_2(num):
    fibo_n = 1
    fibo_n_1 = 1
    if num<=1:
        return num
    else:
        for i in range(num-2):
            fibo_n, fibo_n_1 = fibo_n + fibo_n_1, fibo_n
        
        return fibo_n

# Dynamic programming을 이용한 방법 (이미 구한 값을 저장해서 다음 호출에서 사용한다.)
def fibonacci_recursive(num):
    #아직 fibonacci(num)을 구하지 않은 경우, 구한 이후 fibo_data[num]에 저장한다.
    if fibo_data[num] == -1:
        fibo_data[num] = fibonacci_recursive(num-1) + fibonacci_recursive(num-2)
    
    return fibo_data[num]

def fibo_3(num):
    if num<=1:
        return num
    
    global fibo_data
    fibo_data = [-1 for i in range(0, num + 1)]
    fibo_data[0] = 0
    fibo_data[1] = 1
    
    return fibonacci_recursive(num)
