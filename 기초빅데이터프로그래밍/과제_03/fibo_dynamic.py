# 간단한 방법 (재귀함수를 통해서 간단하게 구현할 수 있다.)
def fibo_1(num):
    if num == 0:
        return 0
    elif num == 1:
        return 1
    else:
        return fibo_1(num-1) + fibo_1(num-2)


# 약간은 복잡한 방법 (이미 구한 값을 저장해서 다음 호출에서 사용한다.)
def fibo_2_recursive(num, data):
    if data[num] == -1:
        data[num] = fibo_2_recursive(num-1, data) + fibo_2_recursive(num-2, data)
    
    return data[num]

def fibo_2(num):
    global fibo_data = [-1 for i in range(0, num + 1)]
    fibo_data[0] = 0
    fibo_data[1] = 1
    
    return fibo_2_recursive(num, fibo_data)

