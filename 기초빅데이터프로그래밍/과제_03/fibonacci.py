#loop를 통해 피보나치 수를 구하는 함수이다.
def fibo(num):
    #n = 2일 때,  fibo(n) = 1, fibo(n-1) = 1을 저장한다.
    fibo_n = 1
    fibo_n_1 = 1
    
    #input이 1, 0인 경우 num을 return 해준다.
    if num<=1:
        return num
    
    #input이 2 이상인 경우, loop를 통해 fibo_n의 값을 구해준다.
    #이때 a, b = b, a 형식의 할당문을 사용한다.
    else:
        for i in range(num-2):
            fibo_n, fibo_n_1 = fibo_n + fibo_n_1, fibo_n
        
        return fibo_n

# %run 을 통해 실행한 경우, 바로 함수가 실행되도록, import하는 경우 실행되지 않도록 설정한다. 
if __name__ == "__main__":
    num = int(input("input: "))
    print(fibo(num))
